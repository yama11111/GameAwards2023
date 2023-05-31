#include "GoalDrawer.h"
#include "CalcTransform.h"
#include "DrawerConfig.h"
#include "CoreColor.h"
#include "DrawerHelper.h"
#include <cassert>

#pragma region 名前空間

using std::array;
using std::unique_ptr;

using YGame::Transform;
using YGame::Model;
using YGame::Audio;
using YGame::CBColor;

using YGame::SlimeActor;

using YMath::Vector3;
using YMath::Vector4;

using namespace DrawerConfig::Goal;

#pragma endregion

#pragma region Static

array<Model*, GoalDrawerCommon::sPartsNum_> GoalDrawerCommon::spModels_ =
{
	nullptr, nullptr, nullptr, nullptr, nullptr,
};
Audio* GoalDrawerCommon::spGoalSE_ = nullptr;

#pragma endregion

#pragma region インデックス

static const size_t CoreIdx = static_cast<size_t>(GoalDrawerCommon::Parts::Core); // 核
static const size_t InsideIdx = static_cast<size_t>(GoalDrawerCommon::Parts::InsideCore); // 内枠核
static const size_t InsideCoreIdx = static_cast<size_t>(GoalDrawerCommon::Parts::Inside); // 内枠
static const size_t OutsideIdx = static_cast<size_t>(GoalDrawerCommon::Parts::OutsideCore); // 外枠核
static const size_t OutsideCoreIdx = static_cast<size_t>(GoalDrawerCommon::Parts::Outside); // 外枠

#pragma endregion

#pragma region Common

void GoalDrawerCommon::StaticInitialize()
{
	// ----- モデル読み込み ----- //

	spModels_[CoreIdx] = Model::LoadObj("goal/core", true); // 核
	spModels_[InsideIdx] = Model::LoadObj("goal/inside", true); // 内枠核
	spModels_[InsideCoreIdx] = Model::LoadObj("goal/insideCore", true); // 内枠
	spModels_[OutsideIdx] = Model::LoadObj("goal/outside", true); // 外枠核
	spModels_[OutsideCoreIdx] = Model::LoadObj("goal/outsideCore", true); // 外枠

	spGoalSE_ = Audio::Load("SE/SE_clear.wav");
}

#pragma endregion

#pragma region Drawer

void GoalDrawer::Initialize(YGame::Transform* pParent, const bool isRock)
{
	// 基底クラス初期化
	IDrawer::Initialze(pParent);

	// オブジェクト生成 + 親行列挿入 (パーツの数)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i].reset(Model::Object::Create(Transform::Status::Default(), spVP_, nullptr, spMate_));
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// 縛る回転タイマー
	bindRotaTim_.Initialize(BindRota::Frame);

	// 縛る回転 (内)
	inBindRotaEas_.Initialize(BindRota::Inside::Start, BindRota::Inside::End, BindRota::Exponent);
	
	// 縛る回転 (外)
	outBindRotaEas_.Initialize(BindRota::Outside::Start, BindRota::Outside::End, BindRota::Exponent);


	// ログインタイマー
	loginTim_.Initialize(Login::Frame);


	// ハッキング回転タイマー
	hackRotaTim_.Initialize(HackRota::Frame);


	// クリア回転タイマー
	clearRotaTim_.Initialize(ClearRota::Frame);

	// クリア回転 (内) イージング
	inClearRotaEas_.Initialize({}, {}, 0.0f);

	// クリア回転 (外) イージング
	outClearRotaEas_.Initialize({}, {}, 0.0f);


	// リセット
	Reset(isRock);
}

void GoalDrawer::Reset(const bool isRock)
{
	// リセット
	IDrawer::Reset();

	// ----- オブジェクト初期化 ----- //

	// 親トランスフォーム初期化
	core_->Initialize({ {0.0f,0.0f,0.0f}, {0.0f,+PI / 6.0f,0.0f}, {1.0f,1.0f,1.0f} });

	// モデルごとに初期化
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->Initialize(Transform::Status::Default());
	}

	// 核の色とマテリアル設定
	CoreColor::ColorType color = CoreColor::ColorType::eBlue;
	if (isRock_)
	{
		color = CoreColor::ColorType::eGray;
	}

	CoreColor::PartsType coreParts = CoreColor::PartsType::eCore;
	CoreColor::PartsType shellParts = CoreColor::PartsType::eShell;

	modelObjs_[CoreIdx]->SetColor(CoreColor::ColorPtr(color, coreParts));
	modelObjs_[CoreIdx]->SetMaterial(CoreColor::MaterialPtr(color, coreParts));
	
	modelObjs_[InsideIdx]->SetColor(CoreColor::ColorPtr(color, shellParts));
	modelObjs_[InsideIdx]->SetMaterial(CoreColor::MaterialPtr(color, shellParts));
	
	modelObjs_[InsideCoreIdx]->SetColor(CoreColor::ColorPtr(color, coreParts));
	modelObjs_[InsideCoreIdx]->SetMaterial(CoreColor::MaterialPtr(color, coreParts));
	
	modelObjs_[OutsideIdx]->SetColor(CoreColor::ColorPtr(color, shellParts));
	modelObjs_[OutsideIdx]->SetMaterial(CoreColor::MaterialPtr(color, shellParts));
	
	modelObjs_[OutsideCoreIdx]->SetColor(CoreColor::ColorPtr(color, coreParts));
	modelObjs_[OutsideCoreIdx]->SetMaterial(CoreColor::MaterialPtr(color, coreParts));


	// ----- アニメーション初期化 ----- //
	
	// クリアフラグ
	isClear_ = false;

	// ロックフラグ
	isRock_ = isRock;


	// 縛る回転タイマー
	bindRotaTim_.Reset(true);
	

	// ログインフラグ
	isActLogin_ = false;

	// ログインタイマー
	loginTim_.Reset(false);


	// ハッキング回転フラグ
	isActHackRota_ = false;

	// ハッキング回転タイマー
	hackRotaTim_.Reset(false);

	// ハッキング回転スピード
	inHackRotaSpeed_ = outHackRotaSpeed_ = {};


	// クリア回転フラグ
	isActClearRota_ = false;

	// クリア回転タイマー
	clearRotaTim_.Reset(false);
}

void GoalDrawer::ActivateClearAnimation(const Vector3& playerPos)
{
	// クリア
	isClear_ = true;

	// ログイン開始
	StartLogin(playerPos);
}

void GoalDrawer::StartLogin(const Vector3& emitStartPos)
{
	// ログイン開始
	isActLogin_ = true;

	// タイマーリセット + 開始
	loginTim_.Reset(true);

	// リレー虫発生
	spParticleMan_->EmitRelayBug(
		Login::RelayBug::Num,
		Login::RelayBug::StartToRelayFrame, Login::RelayBug::RelayToEndFrame,
		emitStartPos, pParent_->pos_,
		Login::RelayBug::RelayRange, 
		Login::RelayBug::MinRota, Login::RelayBug::MaxRota, 
		Login::RelayBug::MinScale, Login::RelayBug::MaxScale, 
		Login::RelayBug::Color, 
		Login::RelayBug::Place,
		YGame::DrawLocation::Center);
}

void GoalDrawer::StartHackRota()
{
	// 回転開始
	isActHackRota_ = true;

	// ハッキング回転スピード初期化
	inHackRotaSpeed_ = outHackRotaSpeed_ = {};

	// タイマーリセット + 開始
	hackRotaTim_.Reset(true);
}

void GoalDrawer::StartClearRota()
{
	// 回転開始
	isActClearRota_ = true;

	// クリア回転 (内) イージング
	inClearRotaEas_.Initialize(modelObjs_[InsideCoreIdx]->rota_, {}, ClearRota::Exponent);

	// クリア回転 (外) イージング
	outClearRotaEas_.Initialize(modelObjs_[OutsideCoreIdx]->rota_, {}, ClearRota::Exponent);

	// タイマーリセット + 開始
	clearRotaTim_.Reset(true);
}

void GoalDrawer::BindRotaAnimation()
{
	// クリアしたなら弾く
	if (isClear_) { return; }

	// 縛る回転タイマー更新
	bindRotaTim_.Update();
	if (isRock_)
	{
		if (bindRotaTim_.Ratio() >= 0.4f)
		{
			// タイマーリセット
			bindRotaTim_.Reset(true);
		}
	}
	
	// タイマー終了したら
	if (bindRotaTim_.IsEnd())
	{
		// タイマーリセット
		bindRotaTim_.Reset(true);
	}

	// 縛る回転 (内)
	modelObjs_[InsideCoreIdx]->rota_ = inBindRotaEas_.In(bindRotaTim_.Ratio());
	modelObjs_[InsideIdx]->rota_ = inBindRotaEas_.In(bindRotaTim_.Ratio());
	// 縛る回転 (外)
	modelObjs_[OutsideCoreIdx]->rota_ = outBindRotaEas_.In(bindRotaTim_.Ratio());
	modelObjs_[OutsideIdx]->rota_ = outBindRotaEas_.In(bindRotaTim_.Ratio());
}

void GoalDrawer::ClearAnimation()
{
	// クリアしていないなら弾く
	if (isClear_ == false) { return; }
	
	// ログイン中なら
	if (isActLogin_)
	{
		// タイマー更新
		loginTim_.Update();
		// タイマー終了したら
		if (loginTim_.IsEnd())
		{
			// ハッキング回転開始
			StartHackRota();

			// フラグをfalseに
			isActLogin_ = false;
		}
	}

	// ハッキング回転中なら
	else if (isActHackRota_)
	{
		// ハッキング回転タイマー更新
		hackRotaTim_.Update();
		// タイマー終了したら
		if (hackRotaTim_.IsEnd())
		{
			// クリア回転開始
			StartClearRota();

			// フラグをfalseに
			isActHackRota_ = false;
		}

		// スピード加速
		inHackRotaSpeed_ += HackRota::InAcceleration;
		outHackRotaSpeed_ += HackRota::OutAcceleration;

		// ハッキング回転 (内)
		modelObjs_[InsideCoreIdx]->rota_ += inHackRotaSpeed_;
		modelObjs_[InsideIdx]->rota_ += inHackRotaSpeed_;
		// ハッキング回転 (外)
		modelObjs_[OutsideCoreIdx]->rota_ += outHackRotaSpeed_;
		modelObjs_[OutsideIdx]->rota_ += outHackRotaSpeed_;
	}

	// クリア回転中なら
	else if (isActClearRota_)
	{
		// クリア回転タイマー更新
		clearRotaTim_.Update();
		// タイマー終了したら
		if (clearRotaTim_.IsEnd())
		{
			// 描画クラスクリア演出
			DrawerHelper::StaticClear();

			spGoalSE_->Stop();
			spGoalSE_->Play(false);

			// フラグをfalseに
			isActClearRota_ = false;
		}

		// クリア回転 (内)
		modelObjs_[InsideCoreIdx]->rota_ = inClearRotaEas_.Out(clearRotaTim_.Ratio());
		modelObjs_[InsideIdx]->rota_ = inClearRotaEas_.Out(clearRotaTim_.Ratio());
		// クリア回転 (外)
		modelObjs_[OutsideCoreIdx]->rota_ = outClearRotaEas_.Out(clearRotaTim_.Ratio());
		modelObjs_[OutsideIdx]->rota_ = outClearRotaEas_.Out(clearRotaTim_.Ratio());
	}
}

void GoalDrawer::Update()
{
	// 基底クラス更新 
	IDrawer::Update({});

	// 縛る回転アニメーション
	BindRotaAnimation();

	// クリアアニメーション
	ClearAnimation();

	// 行列更新 (子)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix();
	}
}

void GoalDrawer::Draw()
{
	// 描画
	for (size_t i = 0; i < spModels_.size(); i++)
	{
		spModels_[i]->SetDrawCommand(modelObjs_[i].get(), YGame::DrawLocation::Center);
	}
}

void GoalDrawer::Unlock()
{
	if (isRock_ == false) { return; }

	isRock_ = false;
	
	// 核の色とマテリアル設定
	CoreColor::ColorType color = CoreColor::ColorType::eBlue;
	CoreColor::PartsType coreParts = CoreColor::PartsType::eCore;
	CoreColor::PartsType shellParts = CoreColor::PartsType::eShell;

	modelObjs_[CoreIdx]->SetColor(CoreColor::ColorPtr(color, coreParts));
	modelObjs_[CoreIdx]->SetMaterial(CoreColor::MaterialPtr(color, coreParts));

	modelObjs_[InsideIdx]->SetColor(CoreColor::ColorPtr(color, shellParts));
	modelObjs_[InsideIdx]->SetMaterial(CoreColor::MaterialPtr(color, shellParts));

	modelObjs_[InsideCoreIdx]->SetColor(CoreColor::ColorPtr(color, coreParts));
	modelObjs_[InsideCoreIdx]->SetMaterial(CoreColor::MaterialPtr(color, coreParts));

	modelObjs_[OutsideIdx]->SetColor(CoreColor::ColorPtr(color, shellParts));
	modelObjs_[OutsideIdx]->SetMaterial(CoreColor::MaterialPtr(color, shellParts));

	modelObjs_[OutsideCoreIdx]->SetColor(CoreColor::ColorPtr(color, coreParts));
	modelObjs_[OutsideCoreIdx]->SetMaterial(CoreColor::MaterialPtr(color, coreParts));

	spParticleMan_->EmitSmoke(
		20, 8, 
		pParent_->pos_, Vector3(), 0.2f, 0.4f, 
		Vector3(-0.1f,-0.1f,-0.1f), Vector3(+0.1f, +0.1f, +0.1f), 
		Vector3(-0.1f,-0.1f,-0.1f), Vector3(+0.1f, +0.1f, +0.1f), 
		{	
			CoreColor::ColorPtr(color, coreParts)->GetRGBA().r_, 
			CoreColor::ColorPtr(color, coreParts)->GetRGBA().g_, 
			CoreColor::ColorPtr(color, coreParts)->GetRGBA().b_ 
		}, 
		100.0f, YGame::DrawLocation::Center
	);
}

#pragma endregion

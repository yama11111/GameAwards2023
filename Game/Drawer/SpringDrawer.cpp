#include "SpringDrawer.h"
#include "CalcTransform.h"
#include "DrawerConfig.h"
#include "CoreColor.h"
#include <cassert>

#pragma region 名前空間

using std::array;
using std::unique_ptr;

using YGame::Transform;
using YGame::Model;
using YGame::CBColor;
using YGame::CBMaterial;

using YGame::SlimeActor;
using YGame::Audio;

using YMath::Ease;
using YMath::Power;
using YMath::Vector3;
using YMath::Vector4;

using namespace DrawerConfig::Spring;

#pragma endregion

#pragma region Static

array<Model*, SpringDrawerCommon::sPartsNum_> SpringDrawerCommon::spModels_ =
{
	nullptr, nullptr,
};

array<Ease<float>, SpringDrawerCommon::sRingNum_> SpringDrawerCommon::sIdleHeightEases_;
Ease<float> SpringDrawerCommon::sIdleRotaSpeedEase_;
Ease<float>SpringDrawerCommon::sJumpAnticipationHeightEase_;
array<Ease<float>, SpringDrawerCommon::sRingNum_> SpringDrawerCommon::sJumpHeightEases_;
Ease<Vector3>SpringDrawerCommon::sJumpAnticipationScaleEase_;
array<Ease<Vector3>, SpringDrawerCommon::sRingNum_> SpringDrawerCommon::sJumpScaleEases_;
Audio* SpringDrawerCommon::spJumpSE_ = nullptr;

#pragma endregion

#pragma region インデックス

static const size_t BaseIdx = static_cast<size_t>(SpringDrawerCommon::Parts::eBase); // 台座
static const size_t CoreIdx = static_cast<size_t>(SpringDrawerCommon::Parts::eCore); // 核
static const size_t TopCoreIdx = static_cast<size_t>(SpringDrawerCommon::Parts::eTopCore); // 上核
static const size_t TopShellIdx = static_cast<size_t>(SpringDrawerCommon::Parts::eTopShell); // 上殻
static const size_t BottomCoreIdx = static_cast<size_t>(SpringDrawerCommon::Parts::eBottomCore); // 下核
static const size_t BottomShellIdx = static_cast<size_t>(SpringDrawerCommon::Parts::eBottomShell); // 下殻

static const size_t TopRingIdx = 0; // 上輪っか
static const size_t BottomRingIdx = 1; // 下輪っか

#pragma endregion

#pragma region Common

void SpringDrawerCommon::StaticInitialize()
{
	// ----- モデル読み込み ----- //

	// ばね
	spModels_[BaseIdx] = Model::LoadObj("spring/base", true); // 台座
	spModels_[CoreIdx] = Model::LoadObj("spring/core", true); // 核
	spModels_[TopCoreIdx] = Model::LoadObj("spring/top/core", true); // 上核
	spModels_[TopShellIdx] = Model::LoadObj("spring/top/shell", true); // 上殻
	spModels_[BottomCoreIdx] = Model::LoadObj("spring/bottom/core", true); // 下核
	spModels_[BottomShellIdx] = Model::LoadObj("spring/bottom/shell", true); // 下殻

	// ----- アニメーション ----- //
	
	// 立ち高さイージング
	sIdleHeightEases_[TopRingIdx].Initialize(Idle::Height::Top::Start, Idle::Height::Top::End, Idle::Height::Top::Exponent);
	sIdleHeightEases_[BottomRingIdx].Initialize(Idle::Height::Bottom::Start, Idle::Height::Bottom::End, Idle::Height::Bottom::Exponent);
	
	// 立ち回転スピードイージング
	sIdleRotaSpeedEase_.Initialize(Idle::RotaSpeed::Start, Idle::RotaSpeed::End, Idle::RotaSpeed::Exponent);
	

	// ジャンプ予備動作高さイージング
	sJumpAnticipationHeightEase_.Initialize(
		Jump::Height::Anticipation::Start, Jump::Height::Anticipation::End, Jump::Height::Anticipation::Exponent);
	
	// ジャンプ高さイージング
	sJumpHeightEases_[TopRingIdx].Initialize(
		Jump::Height::Performance::Top::Start, Jump::Height::Performance::Top::End, Jump::Height::Performance::Top::Exponent);
	sJumpHeightEases_[BottomRingIdx].Initialize(
		Jump::Height::Performance::Bottom::Start, Jump::Height::Performance::Bottom::End, Jump::Height::Performance::Bottom::Exponent);

	// ジャンプ予備動作大きさイージング
	sJumpAnticipationScaleEase_.Initialize(
		Jump::Scale::Anticipation::Start, Jump::Scale::Anticipation::End, Jump::Scale::Anticipation::Exponent);

	// ジャンプ大きさイージング
	sJumpScaleEases_[TopRingIdx].Initialize(
		Jump::Scale::Performance::Top::Start, Jump::Scale::Performance::Top::End, Jump::Scale::Performance::Top::Exponent);
	sJumpScaleEases_[BottomRingIdx].Initialize(
		Jump::Scale::Performance::Bottom::Start, Jump::Scale::Performance::Bottom::End, Jump::Scale::Performance::Bottom::Exponent);


	spJumpSE_ = Audio::Load("SE/SE_spring.wav");
}

#pragma endregion

#pragma region Drawer

void SpringDrawer::Initialize(Transform* pParent)
{
	// 基底クラス初期化
	IDrawer::Initialze(pParent);

	// オブジェクト生成 + 親行列挿入 (パーツの数)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		// 生成
		modelObjs_[i].reset(Model::Object::Create(Transform::Status::Default(), spVP_));

		// 親行列挿入
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// リセット
	Reset();
}

void SpringDrawer::Reset()
{
	// リセット
	IDrawer::Reset();

	// 核の色とマテリアル設定
	CoreColor::ColorType color = CoreColor::ColorType::eBlue;
	CoreColor::PartsType coreParts = CoreColor::PartsType::eCore;
	CoreColor::PartsType shellParts = CoreColor::PartsType::eShell;

	modelObjs_[BaseIdx]->SetColor(CoreColor::ColorPtr(color, shellParts));
	modelObjs_[BaseIdx]->SetMaterial(CoreColor::MaterialPtr(color, shellParts));

	modelObjs_[CoreIdx]->SetColor(CoreColor::ColorPtr(color, coreParts));
	modelObjs_[CoreIdx]->SetMaterial(CoreColor::MaterialPtr(color, coreParts));

	modelObjs_[TopCoreIdx]->SetColor(CoreColor::ColorPtr(color, coreParts));
	modelObjs_[TopCoreIdx]->SetMaterial(CoreColor::MaterialPtr(color, coreParts));
	
	modelObjs_[TopShellIdx]->SetColor(CoreColor::ColorPtr(color, shellParts));
	modelObjs_[TopShellIdx]->SetMaterial(CoreColor::MaterialPtr(color, shellParts));

	modelObjs_[BottomCoreIdx]->SetColor(CoreColor::ColorPtr(color, coreParts));
	modelObjs_[BottomCoreIdx]->SetMaterial(CoreColor::MaterialPtr(color, coreParts));

	modelObjs_[BottomShellIdx]->SetColor(CoreColor::ColorPtr(color, shellParts));
	modelObjs_[BottomShellIdx]->SetMaterial(CoreColor::MaterialPtr(color, shellParts));


	// ----- アニメーション ----- //

	// 動く
	isAct_ = true;

	// アニメ用初期化
	for (size_t i = 0; i < sRingNum_; i++)
	{
		animePoss_[i] = animeRotas_[i] = animeScales_[i] = {};
	}


	// 立ちモーションする
	isIdle_ = true;

	// 立ち高さモーションする
	isIdleHeight_ = true;

	// 立ちモーションタイマー初期化 + 開始
	idleTimer_.Initialize(Idle::RotaSpeed::Frame);
	idleTimer_.SetActive(true);

	// 立ちモーションパワー初期化
	idlePowers_[TopRingIdx].Initialize(Idle::Height::Frame);
	idlePowers_[BottomRingIdx].Initialize(Idle::Height::Frame);
	
	// 立ちモーションスイッチ初期化
	isIdlePowerSwitches_[TopRingIdx] = false;
	isIdlePowerSwitches_[BottomRingIdx] = false;


	// ジャンプしていない
	isJumped_ = false;

	// ジャンプ予備動作パワー初期化
	jumpAnticipationPower_.Initialize(Jump::Frame::Anticipation);

	// ジャンプ予備動作パワースイッチ初期化
	isJumpedAnticipationSwitch_ = false;

	// ジャンプアニメーションパワー初期化
	jumpPowers_[TopRingIdx].Initialize(Jump::Frame::Performance);
	jumpPowers_[BottomRingIdx].Initialize(Jump::Frame::Performance);

	// ジャンプアニメーションパワースイッチ初期化
	isJumpedSwitch_ = false;
}

void SpringDrawer::Update()
{
	// 基底クラス更新 
	IDrawer::Update({});


	// アニメ用初期化
	for (size_t i = 0; i < sRingNum_; i++)
	{
		animePoss_[i] = animeRotas_[i] = animeScales_[i] = {};
	}


	// 立ちモーション更新
	UpdateIdle();

	// ジャンプアニメーション更新
	UpdateJump();


	// 行列更新 (子)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		// アニメ用
		Vector3 pos = {};
		Vector3 rota = {};
		Vector3 scale = {};

		// 上リング
		if (i == TopCoreIdx || i == TopShellIdx)
		{
			pos = animePoss_[TopRingIdx];
			rota = animeRotas_[TopRingIdx];
			scale = animeScales_[TopRingIdx];
		}
		// 下リング
		else if (i == BottomCoreIdx || i == BottomShellIdx)
		{
			pos = animePoss_[BottomRingIdx];
			rota = animeRotas_[BottomRingIdx];
			scale = animeScales_[BottomRingIdx];
		}

		// 回転量調整
		if (rota.y_ >= +PI * 4) { rota.y_ -= PI * 4; }
		if (rota.y_ <= -PI * 4) { rota.y_ += PI * 4; }

		modelObjs_[i]->UpdateMatrix({ pos, rota, scale });
	}
}

void SpringDrawer::Draw()
{
	// モデルの数描画
	for (size_t i = 0; i < spModels_.size(); i++)
	{
		spModels_[i]->SetDrawCommand(modelObjs_[i].get(), YGame::DrawLocation::Center);
	}
}

void SpringDrawer::AnimateJump()
{
	// 立ち高さモーション終了
	isIdleHeight_ = false;

	// ジャンプ予備動作スイッチオン
	isJumpedAnticipationSwitch_ = true;

	// ジャンプした
	isJumped_ = true;

	spJumpSE_->Stop();
	spJumpSE_->Play(false);
}

void SpringDrawer::UpdateIdle()
{
	// 動いていないなら弾く
	if (isAct_ == false) { return; }

	// 立ちモーションじゃないなら弾く
	if (isIdle_ == false) { return; }


	// タイマー更新
	idleTimer_.Update();

	// 回転
	float rota = sIdleRotaSpeedEase_.In(idleTimer_.Ratio());
	
	// 回転
	animeRotas_[TopRingIdx].y_ += rota;
	animeRotas_[BottomRingIdx].y_ += rota + BottomRingDefaultRotaValue;

	// タイマー終わったら
	if (idleTimer_.IsEnd())
	{
		// タイマーリセット
		idleTimer_.Reset(true);
	}


	// 立ち高さモーションしないなら弾く
	if (isIdleHeight_ == false) { return; }


	// 上リングのパワーの比率が規定値以上の
	if(idlePowers_[TopRingIdx].Ratio() >= 0.2f)
	{
		// 下リングのモーション開始
		isIdleHeightBottomStart_ = true;
	}

	// リングの数
	for (size_t i = 0; i < sRingNum_; i++)
	{
		// 下リングの時 && モーション開始しないなら
		if (i == BottomRingIdx && isIdleHeightBottomStart_ == false)
		{
			// 周回を飛ばす
			continue;
		}

		// パワー更新
		idlePowers_[i].Update(isIdlePowerSwitches_[i]);

		// スイッチ
		if (idlePowers_[i].IsZero())
		{
			isIdlePowerSwitches_[i] = true; 
		}
		else if (idlePowers_[i].IsMax()) 
		{
			isIdlePowerSwitches_[i] = false; 
		}

		// 位置
		if (isIdlePowerSwitches_[i]) 
		{
			animePoss_[i].y_ += sIdleHeightEases_[i].Out(idlePowers_[i].Ratio()); 
		}
		else 
		{
			animePoss_[i].y_ += sIdleHeightEases_[i].In(idlePowers_[i].Ratio()); 
		}
	}
}

void SpringDrawer::UpdateJump()
{
	// 動いていないなら弾く
	if (isAct_ == false) { return; }

	// ジャンプしていないなら弾く
	if (isJumped_ == false) { return; }


	// 予備動作パワー更新
	jumpAnticipationPower_.Update(isJumpedAnticipationSwitch_);

	// 高さ
	if (isJumpedAnticipationSwitch_)
	{
		animePoss_[TopRingIdx].y_ += sJumpAnticipationHeightEase_.Out(jumpAnticipationPower_.Ratio());
		animePoss_[BottomRingIdx].y_ += sJumpAnticipationHeightEase_.Out(jumpAnticipationPower_.Ratio());
		
		animeScales_[TopRingIdx] += sJumpAnticipationScaleEase_.Out(jumpAnticipationPower_.Ratio());
		animeScales_[BottomRingIdx] += sJumpAnticipationScaleEase_.Out(jumpAnticipationPower_.Ratio());
	}
	else
	{
		animePoss_[TopRingIdx].y_ += sJumpAnticipationHeightEase_.In(jumpAnticipationPower_.Ratio());
		animePoss_[BottomRingIdx].y_ += sJumpAnticipationHeightEase_.In(jumpAnticipationPower_.Ratio());
		
		animeScales_[TopRingIdx] += sJumpAnticipationScaleEase_.In(jumpAnticipationPower_.Ratio());
		animeScales_[BottomRingIdx] += sJumpAnticipationScaleEase_.In(jumpAnticipationPower_.Ratio());
	}

	// 予備動作パワー最大なら
	if (jumpAnticipationPower_.IsMax())
	{
		// スイッチオフ
		isJumpedAnticipationSwitch_ = false;

		// ジャンプスイッチオン
		isJumpedSwitch_ = true;
	}


	for (size_t i = 0; i < sRingNum_; i++)
	{
		// パワー更新
		jumpPowers_[i].Update(isJumpedSwitch_);

		// 高さ
		if (isJumpedSwitch_) 
		{
			animePoss_[i].y_ += sJumpHeightEases_[i].Out(jumpPowers_[i].Ratio()); 
			animeScales_[i] += sJumpScaleEases_[i].Out(jumpPowers_[i].Ratio());
		}
		else
		{ 
			animePoss_[i].y_ += sJumpHeightEases_[i].In(jumpPowers_[i].Ratio()); 
			animeScales_[i] += sJumpScaleEases_[i].In(jumpPowers_[i].Ratio());
		}
	}
	
	// パワー最大なら
	if (jumpPowers_[BottomRingIdx].IsMax()) 
	{
		// スイッチオフ
		isJumpedSwitch_ = false; 
	}
	// 予備含めパワーゼロなら
	else if (jumpPowers_[BottomRingIdx].IsZero() && jumpAnticipationPower_.IsZero())
	{
		// ジャンプ終了
		isJumped_ = false;

		// 立ち高さモーション開始
		isIdleHeight_ = true;
	}
}

#pragma endregion
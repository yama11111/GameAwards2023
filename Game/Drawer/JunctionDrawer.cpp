#include "JunctionDrawer.h"
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

using YMath::Ease;
using YMath::Power;
using YMath::Vector3;
using YMath::Vector4;

using namespace DrawerConfig::Junction;

#pragma endregion

#pragma region Static

array<array<Model*, JunctionDrawerCommon::sPartsNum_>, JunctionDrawerCommon::sTypeNum_> JunctionDrawerCommon::spModels_ =
{
	nullptr, nullptr,
	//nullptr, nullptr,
};

Ease<float> JunctionDrawerCommon::sIdleRotaSpeedEase_{};
Ease<float> JunctionDrawerCommon::sConnectPosFactorEase_{};
Ease<float> JunctionDrawerCommon::sConnectRotaFactorEase_{};
Ease<float> JunctionDrawerCommon::sConnectRotaSpeedEase_{};
Ease<Vector3> JunctionDrawerCommon::sConnectScaleEase_{};

#pragma endregion

#pragma region インデックス

static const size_t CoreIdx = static_cast<size_t>(JunctionDrawerCommon::Parts::eCore); // 核
static const size_t ShellIdx = static_cast<size_t>(JunctionDrawerCommon::Parts::eShell); // 殻

static const size_t GreenIdx = static_cast<size_t>(JunctionDrawerCommon::Type::eGreen); // 緑
static const size_t RedIdx = static_cast<size_t>(JunctionDrawerCommon::Type::eRed); // 赤

#pragma endregion

#pragma region Common

void JunctionDrawerCommon::StaticInitialize()
{
	// ----- モデル読み込み ----- //

	// ブロック (黒)
	spModels_[GreenIdx][CoreIdx] = Model::LoadObj("junction/core", true); // 核
	spModels_[GreenIdx][ShellIdx] = Model::LoadObj("junction/shell", true); // 殻

	spModels_[RedIdx][ShellIdx] = Model::LoadObj("junction/core", true); // 殻
	spModels_[RedIdx][ShellIdx] = Model::LoadObj("junction/shell", true); // 殻

	// ----- アニメーション ----- //

	// 立ち回転スピードイージング
	sIdleRotaSpeedEase_.Initialize(Idle::RotaSpeed::Start, Idle::RotaSpeed::End, Idle::RotaSpeed::Exponent);

	// 接続位置係数イージング
	sConnectPosFactorEase_.Initialize(Connect::PosFactor::Start, Connect::PosFactor::End, Connect::PosFactor::Exponent);

	// 接続位置係数イージング
	sConnectRotaFactorEase_.Initialize(Connect::RotaFactor::Start, Connect::RotaFactor::End, Connect::RotaFactor::Exponent);
	
	// 接続回転スピードイージング
	sConnectRotaSpeedEase_.Initialize(Connect::RotaSpeed::Start, Connect::RotaSpeed::End, Connect::RotaSpeed::Exponent);

	// 接続大きさイージング
	sConnectScaleEase_.Initialize(Connect::Scale::Start, Connect::Scale::End, Connect::Scale::Exponent);
}

#pragma endregion

#pragma region Drawer

void JunctionDrawer::Initialize(Transform* pParent, const Vector3& direction, const Type& type)
{
	// 基底クラス初期化
	IDrawer::Initialze(pParent);

	// オブジェクト生成 + 親行列挿入 (パーツの数)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		// 子供生成
		for (size_t j = 0; j < modelObjs_[i].size(); j++)
		{
			// 大きさ
			Vector3 scale = Vector3(1.0f, 1.0f, 1.0f);
			scale -= ScaleDifference * static_cast<float>(i);

			// 生成
			modelObjs_[i][j].reset(Model::Object::Create({ {}, {}, scale }, spVP_));

			// 親行列挿入
			modelObjs_[i][j]->parent_ = &core_->m_;
		}
	}

	// リセット
	Reset(direction, type);
}

void JunctionDrawer::Reset(const Vector3& direction, const Type& type)
{
	// リセット
	IDrawer::Reset();

	// 向き代入
	direction_ = direction.Normalized();

	// 代入
	type_ = type;

	// インデックスを計算
	typeIndex_ = static_cast<size_t>(type);

	// 核の色とマテリアル設定
	CBColor* pColor = nullptr;
	CBMaterial* pMaterial = nullptr;

	if (type == Type::eGreen)
	{
		pColor = CoreColor::ColorPtr(CoreColor::ColorType::eGreen);
		pMaterial = CoreColor::MaterialPtr();
	}
	else if (type == Type::eRed)
	{
		pColor = CoreColor::ColorPtr(CoreColor::ColorType::eRed);
		pMaterial = CoreColor::MaterialPtr();
	}

	// カラーとマテリアル設定
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i][CoreIdx]->SetColor(pColor);
		modelObjs_[i][CoreIdx]->SetMaterial(pMaterial);
	}

	// パートナー解除
	pPartner_ = nullptr;


	// ----- アニメーション ----- //

	// 動く
	isAct_ = true;

	// アニメ用初期化
	for (size_t i = 0; i < sFrameNum_; i++)
	{
		animePoss_[i] = animeRotas_[i] = animeScales_[i] = {};
	}

	// 立ちモーションする
	isIdle_ = true;

	// 立ちタイマー初期化
	for (size_t i = 0; i < idleTimers_.size(); i++)
	{
		idleTimers_[i].Initialize(Idle::Frame);
		idleTimers_[i].SetActive(true);
	}

	// 接続しない
	isConnected_ = false;

	// 接続タイマー初期化
	connectTimer_.Initialize(Connect::Frame);

	// 向き合わせタイマー初期化
	alignDirectionTimer_.Initialize(Connect::AlignDirection::Frame);
}

void JunctionDrawer::Update()
{
	// アニメーション用
	Vector3 pos{}, rota{}, scale{};

	// 向き合わせ
	rota = YMath::AdjustAngle(direction_);


	// 基底クラス更新 
	IDrawer::Update({ pos, rota, scale });


	// アニメ用初期化
	for (size_t i = 0; i < sFrameNum_; i++)
	{
		animePoss_[i] = animeRotas_[i] = animeScales_[i] = {};
	}

	// 立ちモーション更新
	UpdateIdleAnimation();

	// 接続モーション更新
	UpdateConnectAnimation();


	// 行列更新 (子)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		// 子供生成
		for (size_t j = 0; j < modelObjs_[i].size(); j++)
		{
			// 回転量調整
			if (animeRotas_[i].z_ >= +PI * 4) { animeRotas_[i].z_ -= PI * 4; }
			else if (animeRotas_[i].z_ <= -PI * 4) { animeRotas_[i].z_ += PI * 4; }
			
			modelObjs_[i][j]->UpdateMatrix({animePoss_[i], animeRotas_[i], animeScales_[i]});
		}
	}
}

void JunctionDrawer::Draw()
{
	// モデルの数描画
	for (size_t i = 0; i < spModels_[typeIndex_].size(); i++)
	{
		for (size_t j = 0; j < modelObjs_.size(); j++)
		{
			spModels_[typeIndex_][i]->SetDrawCommand(modelObjs_[j][i].get(), YGame::DrawLocation::Center);
		}
	}
}

void JunctionDrawer::SetPartner(JunctionDrawer* pPartner)
{
	// nullチェック
	assert(pPartner);
	// 代入
	pPartner_ = pPartner;
}

Vector3 JunctionDrawer::GetDirection()
{
	// 向き返す
	return direction_;
}

void JunctionDrawer::AnimateConnection(JunctionDrawer* pPartner)
{
	// パートナー設定
	SetPartner(pPartner);

	// 向きイージング初期化
	Vector3 d = Vector3(core_->pos_ - pParent_->pos_);
	alignDirectionEase_.Initialize(direction_, d.Normalized(), Connect::AlignDirection::Exponent);

	// 向きタイマーリセット
	alignDirectionTimer_.Reset(true);

	// 接続した
	isConnected_ = true;

	// 立ちモーションしない
	isIdle_ = false;

	// タイマー初期化
	connectTimer_.Reset(true);
}

void JunctionDrawer::UpdateIdleAnimation()
{
	// 動いていないなら弾く
	if (isAct_ == false) { return; }

	// 立ちモーションじゃないなら弾く
	if (isIdle_ == false) { return; }


	for (size_t i = 0; i < sFrameNum_; i++)
	{
		// タイマー更新
		idleTimers_[i].Update();
		
		// 回転
		animeRotas_[i].z_ += sIdleRotaSpeedEase_.In(idleTimers_[i].Ratio());

		// タイマー終わったら
		if (idleTimers_[i].IsEnd())
		{
			// タイマーリセット
			idleTimers_[i].Reset(true);
		}

		// 最後なら通らない
		if (i + 1 == sFrameNum_) { break; }

		// 接続後
		if (isConnected_)
		{
			// 条件
			bool b = (idleTimers_[i].Ratio() >= 0.25f);
			
			// 動かすか決める
			idleTimers_[i + 1].SetActive(b);
		}
	}
}

void JunctionDrawer::UpdateConnectAnimation()
{
	// 動いていないなら弾く
	if (isAct_ == false) { return; }

	// 動いていないなら弾く
	if (isConnected_ == false) { return; }


	// 接続タイマー更新
	connectTimer_.Update();

	// ベクトルの大きさ取得
	float len = Vector3(core_->pos_ - pParent_->pos_).Length() / 25.0f;

	// アニメ
	for (size_t i = 0; i < sFrameNum_; i++)
	{
		// 位置係数
		animePoss_[i].z_ += sConnectPosFactorEase_.Out(connectTimer_.Ratio()) * (len * i);

		// 位置係数
		animeRotas_[i].z_ += sConnectRotaFactorEase_.Out(connectTimer_.Ratio()) * i;


		// 回転
		animeRotas_[i].z_ += sConnectRotaSpeedEase_.Out(connectTimer_.Ratio());

		// 大きさ
		animeScales_[i] += sConnectScaleEase_.Out(connectTimer_.Ratio());
	}


	// タイマー終わったら
	if (connectTimer_.IsEnd())
	{
		// リセットしてないなら
		if (isIdle_ == false)
		{
			// 立ちタイマーリセット
			idleTimers_[0].Reset(true);
			float frame1 = static_cast<float>(Idle::Frame) * 0.75f;
			float frame2 = static_cast<float>(Idle::Frame) * 0.75f * 0.75f;

			idleTimers_[1].Initialize(static_cast<unsigned int>(frame1));
			idleTimers_[2].Initialize(static_cast<unsigned int>(frame2));
		}

		// 立ちモーション開始
		isIdle_ = true;
	}


	// 向き合わせタイマー更新
	alignDirectionTimer_.Update();

	// 向き合わせ
	direction_ = alignDirectionEase_.In(alignDirectionTimer_.Ratio());
}

#pragma endregion
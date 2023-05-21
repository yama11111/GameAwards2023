#include "LaserDrawer.h"
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

using namespace DrawerConfig::Laser;

#pragma endregion

#pragma region Static

array<Model*, LaserDrawerCommon::sPartsNum_> LaserDrawerCommon::spModels_ =
{
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
};

Ease<float> LaserDrawerCommon::sIdleBeamRotaEase_;
Ease<float> LaserDrawerCommon::sIdleFannelRotaEase_;
Ease<float> LaserDrawerCommon::sShootFannelHeightEase_;
Ease<float> LaserDrawerCommon::sShootFannelPosFactorEase_;
Ease<float> LaserDrawerCommon::sShootFannelRotaEase_;

#pragma endregion

#pragma region インデックス

static const size_t BaseIdx		 = static_cast<size_t>(LaserDrawerCommon::Parts::eBase); // 台座
static const size_t CoreIdx		 = static_cast<size_t>(LaserDrawerCommon::Parts::eCore); // 核
static const size_t Funnel1Idx	 = static_cast<size_t>(LaserDrawerCommon::Parts::eFunnel1); // ファンネル1
static const size_t Funnel2Idx	 = static_cast<size_t>(LaserDrawerCommon::Parts::eFunnel2); // ファンネル2
static const size_t Funnel3Idx	 = static_cast<size_t>(LaserDrawerCommon::Parts::eFunnel3); // ファンネル3
static const size_t Funnel4Idx	 = static_cast<size_t>(LaserDrawerCommon::Parts::eFunnel4); // ファンネル4
static const size_t BeamIdx		 = static_cast<size_t>(LaserDrawerCommon::Parts::eBeam); // ビーム

#pragma endregion

#pragma region Common

void LaserDrawerCommon::StaticInitialize()
{
	// ----- モデル読み込み ----- //

	// 射出機
	spModels_[BaseIdx] = Model::LoadObj("laser/base", true); // 台座
	spModels_[CoreIdx] = Model::LoadObj("laser/core", true); // 核
	spModels_[Funnel1Idx] = Model::LoadObj("laser/funnel/01", true); // ファンネル1
	spModels_[Funnel2Idx] = Model::LoadObj("laser/funnel/02", true); // ファンネル2
	spModels_[Funnel3Idx] = Model::LoadObj("laser/funnel/03", true); // ファンネル3
	spModels_[Funnel4Idx] = Model::LoadObj("laser/funnel/04", true); // ファンネル4
	spModels_[BeamIdx] = Model::CreateCube(); // レーザー


	// ----- 演出 ----- //
	
	// ビーム立ち回転イージング初期化
	sIdleBeamRotaEase_.Initialize(Idle::BeamRota::Start, Idle::BeamRota::End, Idle::BeamRota::Exponent);

	// ファンネル立ち回転イージング
	sIdleFannelRotaEase_.Initialize(Idle::FannelRota::Start, Idle::FannelRota::End, Idle::FannelRota::Exponent);


	// ファンネル発射高度イージング
	sShootFannelHeightEase_.Initialize(Shoot::Height::Start, Shoot::Height::End, Shoot::Height::Exponent);

	// ファンネル発射位置係数イージング
	sShootFannelPosFactorEase_.Initialize(Shoot::PosFactor::Start, Shoot::PosFactor::End, Shoot::PosFactor::Exponent);
	
	// ファンネル発射回転イージング
	sShootFannelRotaEase_.Initialize(Shoot::Rota::Start, Shoot::Rota::End, Shoot::Rota::Exponent);
}

#pragma endregion

#pragma region Drawer

void LaserDrawer::Initialize(Transform* pParent, float* pLength)
{
	// nullチェック
	assert(pLength);
	// 代入
	pLength_ = pLength;

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

void LaserDrawer::Reset()
{
	// リセット
	IDrawer::Reset();

	// 核の色とマテリアル設定
	CBColor* pColor = nullptr;
	CBMaterial* pMaterial = nullptr;

	pColor = CoreColor::ColorPtr(CoreColor::ColorType::eBlue);
	pMaterial = CoreColor::MaterialPtr();

	modelObjs_[CoreIdx]->SetColor(pColor);
	modelObjs_[CoreIdx]->SetMaterial(pMaterial);
	
	modelObjs_[BeamIdx]->SetColor(pColor);
	modelObjs_[BeamIdx]->SetMaterial(pMaterial);


	// ----- 演出 ----- //

	// 動かす
	isAct_ = true;

	// アニメ用初期化
	animeFunnelPoss_[0] = animeFunnelPoss_[1] = animeFunnelPoss_[2] = animeFunnelPoss_[3] = {};
	animeFunnelRota_ = {};
	animeBeamPos_ = animeBeamRota_ = animeBeamSca_ = {};


	// 撃っていない
	isShooted_ = false;

	// 撃つモーションタイマー初期化
	shootTimer_.Initialize(Shoot::Frame);

	// ビーム発射大きさイージング初期化
	shootBeamScaEase_.Initialize({}, {}, 0.0f);


	// 立ちモーションする
	isIdle_ = true;

	// 立ちモーションタイマー初期化
	idleTimer_.Initialize(Idle::Frame);
	idleTimer_.SetActive(true);


	// 発射
	AnimateShoot();
}

void LaserDrawer::Update()
{
	// 基底クラス更新 
	IDrawer::Update({});
	

	// アニメ用初期化
	animeFunnelPoss_[0] = animeFunnelPoss_[1] = animeFunnelPoss_[2] = animeFunnelPoss_[3] = {};
	animeFunnelRota_ = {};
	animeBeamPos_ = animeBeamRota_ = animeBeamSca_ = {};


	// ビーム位置
	animeBeamPos_.y_ = *pLength_ + BeamHeight;

	// 立ちモーション更新
	UpdateIdleAnimation();

	// 発射モーション更新
	UpdateShootAnimation();


	// 行列更新 (子)
	modelObjs_[BaseIdx]->UpdateMatrix();
	modelObjs_[CoreIdx]->UpdateMatrix();
	modelObjs_[Funnel1Idx]->UpdateMatrix({ animeFunnelPoss_[0], animeFunnelRota_, {} });
	modelObjs_[Funnel2Idx]->UpdateMatrix({ animeFunnelPoss_[1], animeFunnelRota_, {} });
	modelObjs_[Funnel3Idx]->UpdateMatrix({ animeFunnelPoss_[2], animeFunnelRota_, {} });
	modelObjs_[Funnel4Idx]->UpdateMatrix({ animeFunnelPoss_[3], animeFunnelRota_, {} });
	modelObjs_[BeamIdx]->UpdateMatrix({ animeBeamPos_, animeBeamRota_, animeBeamSca_ });
}

void LaserDrawer::Draw()
{
	// モデルの数描画
	for (size_t i = 0; i < spModels_.size(); i++)
	{
		spModels_[i]->SetDrawCommand(modelObjs_[i].get(), YGame::DrawLocation::Center);
	}
}

void LaserDrawer::AnimateShoot()
{
	// 大きさイージング初期化
	shootBeamScaEase_.Initialize(
		{ Shoot::Scale::Start,*pLength_,Shoot::Scale::Start }, 
		{ Shoot::Scale::End,*pLength_,Shoot::Scale::End },
		Shoot::Scale::Exponent);

	// 発射した
	isShooted_ = true;

	// タイマーリセット + 開始
	shootTimer_.Reset(true);
}

void LaserDrawer::UpdateIdleAnimation()
{
	// 動いていないなら弾く
	if (isAct_ == false) { return; }

	// 立ちモーションじゃないなら弾く
	if (isIdle_ == false) { return; }


	// タイマー更新
	idleTimer_.Update();
	
	// ビーム回転
	animeBeamRota_.y_ += sIdleBeamRotaEase_.In(idleTimer_.Ratio());
	
	// ファンネル回転
	animeFunnelRota_.y_ += sIdleFannelRotaEase_.In(idleTimer_.Ratio());

	
	// タイマー終わったら
	if (idleTimer_.IsEnd())
	{
		// タイマーリセット
		idleTimer_.Reset(true);
	}

}

void LaserDrawer::UpdateShootAnimation()
{
	// 動いていないなら弾く
	if (isAct_ == false) { return; }

	// 発射アニメーションじゃないなら弾く
	if (isShooted_ == false) { return; }


	// タイマー更新
	shootTimer_.Update();

	// 大きさイージング初期化
	shootBeamScaEase_.Initialize(
		{ Shoot::Scale::Start,*pLength_,Shoot::Scale::Start },
		{ Shoot::Scale::End,*pLength_,Shoot::Scale::End },
		Shoot::Scale::Exponent);

	// 大きさ
	animeBeamSca_ = shootBeamScaEase_.Out(shootTimer_.Ratio());

	// 位置係数
	float posFactor = sShootFannelPosFactorEase_.Out(shootTimer_.Ratio());

	// 回転量
	float rotaVal = animeFunnelRota_.y_;
	float rotaRange = PI / 2.0f;

	// ファンネルの向き
	Vector3 vec0 = Vector3(sinf(rotaVal + (rotaRange * 0.0f)), 0.0f, cosf(rotaVal + (rotaRange * 0.0f))).Normalized();
	Vector3 vec1 = Vector3(sinf(rotaVal + (rotaRange * 1.0f)), 0.0f, cosf(rotaVal + (rotaRange * 1.0f))).Normalized();
	Vector3 vec2 = Vector3(sinf(rotaVal + (rotaRange * 2.0f)), 0.0f, cosf(rotaVal + (rotaRange * 2.0f))).Normalized();
	Vector3 vec3 = Vector3(sinf(rotaVal + (rotaRange * 3.0f)), 0.0f, cosf(rotaVal + (rotaRange * 3.0f))).Normalized();
	
	// 高さ
	float height = sShootFannelHeightEase_.Out(shootTimer_.Ratio());

	// ファンネルの位置
	animeFunnelPoss_[0] = (vec2 * posFactor) + Vector3(0.0f, height, 0.0f);
	animeFunnelPoss_[1] = (vec0 * posFactor) + Vector3(0.0f, height, 0.0f);
	animeFunnelPoss_[2] = (vec1 * posFactor) + Vector3(0.0f, height, 0.0f);
	animeFunnelPoss_[3] = (vec3 * posFactor) + Vector3(0.0f, height, 0.0f);


	// タイマーが終わったら
	if (shootTimer_.IsEnd())
	{

	}
}

#pragma endregion
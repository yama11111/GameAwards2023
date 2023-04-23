#include "PlayerDrawer.h"
#include "CalcTransform.h"
#include "DrawerConfig.h"
#include <cassert>

#pragma region 名前空間

using std::array;
using std::unique_ptr;

using YGame::Transform;
using YGame::ModelObject;
using YGame::Model;
using YGame::Color;

using YGame::SlimeActor;

using YMath::Vector3;
using YMath::Vector4;

using namespace DrawerConfig::Player;

#pragma endregion

#pragma region Static

array<Model*, PlayerDrawerCommon::PartsNum_> PlayerDrawerCommon::spModels_ =
{
	nullptr, nullptr
};

#pragma endregion

// インデックス
static const size_t BodyIdx = static_cast<size_t>(PlayerDrawerCommon::Parts::Body); // 体

void PlayerDrawerCommon::StaticInitialize()
{
	// ----- モデル読み込み ----- //

	spModels_[BodyIdx] = Model::Load("player", true); // 体
	spModels_[1] = Model::CreateCube();
}


void PlayerDrawer::Initialize(Transform* pParent, Vector3* pDirection)
{
	// nullチェック
	assert(pDirection);

	// 基底クラス初期化
	IDrawer::Initialze(pParent, Mode::Normal, Idle::IntervalTime);

	// 色生成
	color_.reset(Color::Create());

	// オブジェクト生成 + 親行列挿入 (パーツの数)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		// 生成
		modelObjs_[i].reset(ModelObject::Create({}, spVP_, color_.get(), nullptr, spMate_));

		// 親行列代入
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// 向きポインタ挿入
	pDirection_ = pDirection;

	// リセット
	Reset();
}

void PlayerDrawer::Reset()
{
	// リセット
	IDrawer::Reset(Mode::Normal);

	// モデル用オブジェクト初期化
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		// 初期化
		modelObjs_[i]->Initialize({ {}, {}, DefScale });
	}

	// 色初期化
	color_->SetRGB(DefColor);

	// ----- アニメーション ----- //
	
	// リスポーンフラグ
	isRespawn_ = false;
	// リスポーン用タイマー
	respawnTim_.Initialize(Respawn::Frame);
	// リスポーン用スケールイージング
	respScaleEas_.Initialize(-1.0f,0.0f,Respawn::Exponent);
	// リスポーン用アルファ値イージング
	respAlphaEas_.Initialize(0.0f,1.0f,Respawn::Exponent);
}

void PlayerDrawer::ResetAnimation()
{
	// ブヨブヨアニメーション初期化
	SlimeActor::Initialize();

	// 立ちモーションタイマーリセット
	idleTim_.Reset(true);

	// リスポーン用タイマーリセット
	respawnTim_.Reset(false);
}

void PlayerDrawer::Update()
{
	// アニメーション用
	Vector3 pos{}, rota{}, scale{};

	// 向き合わせ
	rota = YMath::AdjustAngle(*pDirection_);

	// リスポーン中なら
	if (isRespawn_)
	{
		// リスポーン用タイマー更新
		respawnTim_.Update();
		// リスポーン用のスケール計算
		float respSca = respScaleEas_.In(respawnTim_.Ratio());
		
		// 代入
		scale = Vector3(respSca, respSca, respSca);

		// リスポーン用のアルファ値計算
		float respAlpha = respAlphaEas_.In(respawnTim_.Ratio());

		// 代入
		color_->SetAlpha(respAlpha);
	}

	// 基底クラス更新 
	IDrawer::Update({ pos, rota, scale });

	// 行列更新 (子)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix();
	}
}

void PlayerDrawer::Draw()
{
	//// モデルの数描画
	//for (size_t i = 0; i < spModels_.size(); i++)
	//{
	//	spModels_[i]->Draw(modelObjs_[i].get());
	//}
	spModels_[BodyIdx]->Draw(modelObjs_[BodyIdx].get());
}

void PlayerDrawer::JumpAnimation()
{
	// 伸縮量
	Vector3 val = core_->scale_ * DrawerConfig::Player::Jump::SlimeAction::Value;
	val.y_ *= -1.0f;

	// つぶれる量
	Vector3 squash = +val;
	// のびる量
	Vector3 streach = -val;

	// 時間 (フレーム)
	unsigned int frame = DrawerConfig::Player::Jump::SlimeAction::Frame;
	// 指数 (緩急)
	float pow = DrawerConfig::Player::Jump::SlimeAction::Exponent;

	// ぷよぷよアニメーション
	SlimeActor::Activate(
		{
			{{}, frame, pow},
			{squash, frame, pow},
			{streach, frame, pow},
			{{}, frame, pow },
		}
	);
}
void PlayerDrawer::LandingAnimation()
{
	// つぶれる量
	Vector3 squash = core_->scale_ * DrawerConfig::Player::Landing::SlimeAction::Value;
	squash.y_ *= -1.0f;

	// 時間 (フレーム)
	unsigned int frame = DrawerConfig::Player::Landing::SlimeAction::Frame;
	// 指数 (緩急)
	float exponent = DrawerConfig::Player::Landing::SlimeAction::Exponent;

	// ぷよぷよアニメーション
	SlimeActor::Activate(
		{
			{{}, frame, exponent},
			{squash, frame, exponent},
			{{}, frame, exponent}
		}
	);
}

void PlayerDrawer::RespawnAnimation()
{
	// アニメーションリセット
	ResetAnimation();

	// リスポーンタイマー開始
	respawnTim_.SetActive(true);

	// つぶれる量
	Vector3 squash = core_->scale_ * DrawerConfig::Player::Respawn::SlimeAction::Value;

	// 時間 (フレーム)
	unsigned int frame = DrawerConfig::Player::Respawn::SlimeAction::Frame;
	// 指数 (緩急)
	float exponent = DrawerConfig::Player::Respawn::SlimeAction::Exponent;

	// ぷよぷよアニメーション
	SlimeActor::Activate(
		{
			{{}, frame, exponent},
			{squash, frame, exponent},
			{{}, frame, exponent}
		}
	);

	// リスポーンアニメーション開始
	isRespawn_ = true;
}

void PlayerDrawer::IdleAnimation()
{
}

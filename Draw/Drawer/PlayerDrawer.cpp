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
using namespace DrawerConfig::Player;

#pragma endregion

#pragma region Static

// インデックス
static const size_t NormalIdx = static_cast<size_t>(IDrawer::Mode::Normal); // 通常
static const size_t RedIdx = static_cast<size_t>(IDrawer::Mode::Red); // 赤
static const size_t InvisibleIdx = static_cast<size_t>(IDrawer::Mode::Invisivle); // 透明

static const size_t BodyIdx = static_cast<size_t>(PlayerDrawerCommon::Parts::Body); // 体


// 静的 モデル配列 初期化
array<Model*, PlayerDrawerCommon::PartsNum_> PlayerDrawerCommon::spModels_ =
{
	nullptr, nullptr
};

// 静的ビュープロジェクション
YGame::ViewProjection* PlayerDrawerCommon::spVP_ = nullptr;

void PlayerDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP)
{
	// nullチェック
	assert(pVP);
	// 代入
	spVP_ = pVP;

	// ----- モデル読み込み ----- //

	spModels_[BodyIdx] = Model::Load("player", true); // 体
	spModels_[1] = Model::CreateCube();
}

#pragma endregion

void PlayerDrawer::Initialize(YGame::Transform* pParent, Vector3* pDirection, const Mode& mode)
{
	// nullチェック
	assert(pDirection);

	// 基底クラス初期化
	IDrawer::Initialze(pParent, mode, Idle::IntervalTime);

	// 色生成
	colors_[NormalIdx]	 .reset(Color::Create());
	colors_[RedIdx]		 .reset(Color::Create());
	colors_[InvisibleIdx].reset(Color::Create());

	// オブジェクト生成 + 親行列挿入 (パーツの数)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		for (size_t j = 0; j < modelObjs_[i].size(); j++)
		{
			// 生成
			modelObjs_[i][j].reset(ModelObject::Create({}, spVP_, colors_[i].get(), nullptr));
			
			// 親行列代入
			modelObjs_[i][j]->parent_ = &core_->m_;
		}
	}

	// 向きポインタ挿入
	pDirection_ = pDirection;

	// リセット
	Reset(mode);
}

void PlayerDrawer::Reset(const Mode& mode)
{
	// リセット
	IDrawer::Reset(mode);

	// モデル用オブジェクト初期化
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		for (size_t j = 0; j < modelObjs_[i].size(); j++)
		{
			// 大きさ
			Vector3 scale = DefScale;

			// 透明なら
			if (i == InvisibleIdx)
			{
				// 大きさ調整
				scale *= DrawerConfig::InvisibleScale;
			}

			// 初期化
			modelObjs_[i][j]->Initialize({ {}, {}, scale });
		}
	}

	// 色初期化
	colors_[NormalIdx]->Initialize(DefColor::Normal, DefColor::Normal);
	colors_[RedIdx]->Initialize(DefColor::Red, DefColor::Red);
	colors_[InvisibleIdx]->Initialize(DefColor::Invisible);

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
		colors_[NormalIdx]->SetAlpha(respAlpha);
		colors_[RedIdx]->SetAlpha(respAlpha);
		colors_[InvisibleIdx]->SetAlpha(respAlpha);
	}

	// 基底クラス更新 
	IDrawer::Update({ pos, rota, scale });

	// 行列更新 (子)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		for (size_t j = 0; j < modelObjs_[i].size(); j++)
		{
			modelObjs_[i][j]->UpdateMatrix();
		}
	}
}

void PlayerDrawer::PreDraw()
{
	// 透明描画
	spModels_[BodyIdx]->Draw(modelObjs_[InvisibleIdx][BodyIdx].get());

	// 通常なら
	if (current_ == Mode::Normal)
	{
		// 描画
		spModels_[BodyIdx]->Draw(modelObjs_[NormalIdx][BodyIdx].get());
	}
}

void PlayerDrawer::PostDraw()
{
	// 赤なら
	if (current_ == Mode::Red)
	{
		// 描画
		spModels_[BodyIdx]->Draw(modelObjs_[RedIdx][BodyIdx].get());
	}
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

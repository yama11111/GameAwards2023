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
static const size_t NormalIdx = 0; // 通常
static const size_t RedIdx = 1; // 赤
static const size_t InvisibleIdx = 2; // 透明
static const size_t BodyIdx = static_cast<size_t>(PlayerDrawerCommon::Parts::Body); // 体


// 静的 モデル配列 初期化
array<array<unique_ptr<Model>, PlayerDrawerCommon::PartsNum_>, PlayerDrawerCommon::ModeNum_> PlayerDrawerCommon::sModels_ =
{
	nullptr, nullptr, 
	nullptr, nullptr,
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

	// 通常
	sModels_[NormalIdx][BodyIdx].reset(Model::LoadObj("player/playerNormal", true)); // 体
	sModels_[NormalIdx][1].reset(Model::Create());

	// 赤
	sModels_[RedIdx][BodyIdx].reset(Model::LoadObj("player/playerRed", true)); // 体
	sModels_[RedIdx][1].reset(Model::Create());

	// 透明
	sModels_[InvisibleIdx][BodyIdx].reset(Model::LoadObj("player/playerInvisible", true)); // 体
	sModels_[InvisibleIdx][1].reset(Model::Create());
}

#pragma endregion

void PlayerDrawer::Initialize(YGame::Transform* pParent, Vector3* pDirection, const Mode& mode)
{
	// nullチェック
	assert(pDirection);

	// 基底クラス初期化
	IDrawer::Initialze(pParent, mode, Idle::IntervalTime);

	// 透明色生成
	invisibleColor_.reset(Color::Create({ 1.0f,1.0f,1.0f,0.25f }));

	// オブジェクト生成 + 親行列挿入 (パーツの数)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		for (size_t j = 0; j < modelObjs_[i].size(); j++)
		{
			// 色ポインタ
			Color* pColor = color_.get();

			// 透明なら
			if (i == InvisibleIdx)
			{
				// 透明色ポインタを入れる
				pColor = invisibleColor_.get();
			}

			// 生成
			modelObjs_[i][j].reset(ModelObject::Create({}, spVP_, pColor, nullptr));
			
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

	// フィルターと衝突しているか初期化
	isCollFilter_ = false;
}

void PlayerDrawer::Update()
{
	// 向き合わせ
	Vector3 dire = YMath::AdjustAngle(*pDirection_);

	// 基底クラス更新 
	IDrawer::Update(
		{
			{}, 
			dire,
			{}
		}
	);

	// 行列更新 (子)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		for (size_t j = 0; j < modelObjs_[i].size(); j++)
		{
			modelObjs_[i][j]->UpdateMatrix();
		}
	}


	// フィルター操作 && フィルターと衝突していたら
	if (*spIsPlayer_ == false && isCollFilter_)
	{
		// 色を変える
		invisibleColor_->SetRGB(BadColor);
	}
	// 違うなら
	else
	{
		// デフォルトの色に
		invisibleColor_->SetRGB({ 1.0f,1.0f,1.0f });
	}
}

void PlayerDrawer::PreDraw()
{
	// 透明描画
	sModels_[InvisibleIdx][BodyIdx]->Draw(modelObjs_[InvisibleIdx][BodyIdx].get());

	// 通常なら
	if (current_ == Mode::Normal)
	{
		// 描画
		sModels_[NormalIdx][BodyIdx]->Draw(modelObjs_[NormalIdx][BodyIdx].get());
	}
}

void PlayerDrawer::PostDraw()
{
	// 赤なら
	if (current_ == Mode::Red)
	{
		// 描画
		sModels_[RedIdx][BodyIdx]->Draw(modelObjs_[RedIdx][BodyIdx].get());
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
	float pow = DrawerConfig::Player::Jump::SlimeAction::Power;

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
	float exponent = DrawerConfig::Player::Landing::SlimeAction::Power;

	// ぷよぷよアニメーション
	SlimeActor::Activate(
		{
			{{}, frame, exponent},
			{squash, frame, exponent},
			{{}, frame, exponent}
		}
	);
}

void PlayerDrawer::ChangeColorAnimation(const Mode& mode)
{
	// 代入
	current_ = mode;
	
	// 色
	YMath::Vector4 color = {};

	// 通常
	if (mode == Mode::Normal)
	{
		color = { 0.1f,1.0f,0.8f,1.0f };
	}
	// 赤
	else if (mode == Mode::Red)
	{
		color = { 1.0f,0.0f,0.3f,1.0f };
	}

	// 発生
	spParticleMan_->EmitFireWorks(20, 10, pParent_->pos_, pParent_->scale_.x_, color);
}

void PlayerDrawer::IdleAnimation()
{
}

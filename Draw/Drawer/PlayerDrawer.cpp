#include "PlayerDrawer.h"
#include "CalcTransform.h"
#include "DrawerConfig.h"
#include <cassert>

#pragma region 名前空間

using YGame::Transform;
using YGame::ModelObject;
using YGame::Model;
using YGame::Color;
using YGame::SlimeActor;
using YMath::Vector3;
using namespace DrawerConfig::Player;

#pragma endregion

#pragma region Static

// 静的 モデル配列 初期化
std::array<std::unique_ptr<Model>, PlayerDrawerCommon::PartsNum_> PlayerDrawerCommon::sModels_ =
{ nullptr, nullptr, };
YGame::ViewProjection* PlayerDrawerCommon::spVP_ = nullptr;

void PlayerDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP)
{
	// nullチェック
	assert(pVP);
	// 代入
	spVP_ = pVP;

	// ----- モデル読み込み ----- //

	// 体
	sModels_[static_cast<size_t>(Parts::Normal)].reset(Model::LoadObj("player/playerNormal", true));
	sModels_[static_cast<size_t>(Parts::Red)]	.reset(Model::LoadObj("player/playerRed", true));
}

#pragma endregion

void PlayerDrawer::Initialize(YMath::Matrix4* pParent, Vector3* pDirection, const Mode& mode)
{
	// nullチェック
	assert(pDirection);

	// 基底クラス初期化
	IDrawer::Initialze(pParent, mode, Idle::IntervalTime);

	// オブジェクト生成 + 親行列挿入 (パーツの数)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i].reset(ModelObject::Create({}, spVP_, color_.get(), nullptr));
		modelObjs_[i]->parent_ = &core_->m_;
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
		modelObjs_[i]->Initialize({});
	}

	ChangeColorAnimation(mode);
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
		modelObjs_[i]->UpdateMatrix();
	}
}

void PlayerDrawer::Draw()
{
	// 描画
	//for (size_t i = 0; i < sModels_.size(); i++)
	//{
	//	sModels_[i]->Draw(modelObjs_[i].get());
	//}
	
	sModels_[static_cast<size_t>(current_)]->Draw(modelObjs_[static_cast<size_t>(current_)].get());
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
	current_ = mode;
}

void PlayerDrawer::IdleAnimation()
{
}

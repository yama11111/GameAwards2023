#include "GoalDrawer.h"
#include "CalcTransform.h"
#include "DrawerConfig.h"
#include "Def.h"
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
using namespace DrawerConfig::Goal;

#pragma endregion

#pragma region Static

// インデックス
static const size_t CoreIdx = static_cast<size_t>(GoalDrawerCommon::Parts::Core); // 核
static const size_t InsideIdx = static_cast<size_t>(GoalDrawerCommon::Parts::Inside); // 内枠
static const size_t OutsideIdx = static_cast<size_t>(GoalDrawerCommon::Parts::Outside); // 外枠
static const size_t BaseIdx = static_cast<size_t>(GoalDrawerCommon::Parts::Base); // 台座

// 静的 モデル配列 初期化
array<unique_ptr<Model>, GoalDrawerCommon::PartsNum_> GoalDrawerCommon::sModels_ =
{
	nullptr, nullptr, nullptr, nullptr,
};

// 静的ビュープロジェクション
YGame::ViewProjection* GoalDrawerCommon::spVP_ = nullptr;

void GoalDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP)
{
	// nullチェック
	assert(pVP);
	// 代入
	spVP_ = pVP;

	// ----- モデル読み込み ----- //

	sModels_[CoreIdx].reset(Model::LoadObj("goal/core", true)); // 核
	sModels_[InsideIdx].reset(Model::LoadObj("goal/inside", true)); // 内枠
	sModels_[OutsideIdx].reset(Model::LoadObj("goal/outside", true)); // 外枠
	sModels_[BaseIdx].reset(Model::LoadObj("goal/base", true)); // 台座
}

#pragma endregion

void GoalDrawer::Initialize(YGame::Transform* pParent)
{
	// 基底クラス初期化
	IDrawer::Initialze(pParent, Mode::Normal, Idle::IntervalTime);

	// オブジェクト生成 + 親行列挿入 (パーツの数)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i].reset(ModelObject::Create({}, spVP_, color_.get(), nullptr));
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// リセット
	Reset();
}

void GoalDrawer::Reset()
{
	// リセット
	IDrawer::Reset(Mode::Red);

	// ----- モデル用オブジェクト初期化 ----- //

	core_->Initialize({ {0.0f,+3.0f,0.0f}, {0.0f,-PI / 4.0f,0.0f}, {0.5f,0.5f,0.5f} });

	modelObjs_[CoreIdx]->	Initialize({}); // 核
	modelObjs_[InsideIdx]->	Initialize({}); // 内枠
	modelObjs_[OutsideIdx]->Initialize({}); // 外枠
	modelObjs_[BaseIdx]->	Initialize({}); // 台座
}

void GoalDrawer::Update()
{
	// 基底クラス更新 
	IDrawer::Update({});

	// 行列更新 (子)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix();
	}
}

void GoalDrawer::Draw()
{
	// 描画
	for (size_t i = 0; i < sModels_.size(); i++)
	{
		sModels_[i]->Draw(modelObjs_[i].get());
	}
}

void GoalDrawer::IdleAnimation()
{
}

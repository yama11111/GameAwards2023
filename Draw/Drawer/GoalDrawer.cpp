#include "GoalDrawer.h"
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
using namespace DrawerConfig::Goal;

#pragma endregion

#pragma region Static

// インデックス
static const size_t CoreIdx = static_cast<size_t>(GoalDrawerCommon::Parts::Core); // 核


// 静的 モデル配列 初期化
array<unique_ptr<Model>, GoalDrawerCommon::PartsNum_> GoalDrawerCommon::sModels_ =
{
	nullptr, nullptr,
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

	// 体
	sModels_[CoreIdx].reset(Model::Create("goal.png"));
	sModels_[1].reset(Model::Create());
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

	// 核
	modelObjs_[CoreIdx]->Initialize({});
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
	sModels_[CoreIdx]->Draw(modelObjs_[CoreIdx].get());
}

void GoalDrawer::IdleAnimation()
{
}

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
array<Model*, GoalDrawerCommon::PartsNum_> GoalDrawerCommon::spModels_ =
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

	spModels_[CoreIdx] = Model::Load("goal/core", true); // 核
	spModels_[InsideIdx] = Model::Load("goal/inside", true); // 内枠
	spModels_[OutsideIdx] = Model::Load("goal/outside", true); // 外枠
	spModels_[BaseIdx] = Model::Load("goal/base", true); // 台座
}

#pragma endregion

void GoalDrawer::Initialize(YGame::Transform* pParent)
{
	// 基底クラス初期化
	IDrawer::Initialze(pParent, Mode::Normal, Idle::IntervalTime);

	// オブジェクト生成 + 親行列挿入 (パーツの数)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i].reset(ModelObject::Create({}, spVP_, nullptr, nullptr));
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// 回転 (内)
	inRotaEas.Initialize(Rota::Inside::Start, Rota::Inside::End, Rota::Exponent);
	// 回転 (外)
	outRotaEas.Initialize(Rota::Outside::Start, Rota::Outside::End, Rota::Exponent);

	// 回転タイマー
	rotaTim_.Initialize(Rota::Frame);

	// リセット
	Reset();
}

void GoalDrawer::Reset()
{
	// リセット
	IDrawer::Reset(Mode::Red);

	// ----- モデル用オブジェクト初期化 ----- //

	core_->Initialize({ {0.0f,0.0f,0.0f}, {0.0f,+PI / 6.0f,0.0f}, {1.0f,1.0f,1.0f} });

	modelObjs_[CoreIdx]->Initialize({ {0.0f,+2.0f,0.0f } }); // 核
	modelObjs_[InsideIdx]->Initialize({ {0.0f,+2.0f,0.0f } }); // 内枠
	modelObjs_[OutsideIdx]->Initialize({ {0.0f,+2.0f,0.0f } }); // 外枠
	modelObjs_[BaseIdx]->Initialize({}); // 台座

	// ----- タイマー初期化 ----- //
	
	// 回転タイマー
	rotaTim_.Reset(true);
}

void GoalDrawer::IdleAnimation()
{
}

void GoalDrawer::RotaAnimation()
{
	// 回転タイマー更新
	rotaTim_.Update();
	// タイマー終了したら
	if (rotaTim_.IsEnd())
	{
		// タイマーリセット
		rotaTim_.Reset(true);
	}

	// 回転 (内)
	modelObjs_[InsideIdx]->rota_ = inRotaEas.In(rotaTim_.Ratio());
	// 回転 (外)
	modelObjs_[OutsideIdx]->rota_ = outRotaEas.In(rotaTim_.Ratio());
}

void GoalDrawer::Update()
{
	// 基底クラス更新 
	IDrawer::Update({});

	// 回転アニメーション
	RotaAnimation();

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
		spModels_[i]->Draw(modelObjs_[i].get());
	}
}

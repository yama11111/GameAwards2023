#include "GoalDrawer.h"
#include "CalcTransform.h"
#include "DrawerConfig.h"
#include "CoreColor.h"
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

using namespace DrawerConfig::Goal;

#pragma endregion

#pragma region Static

array<Model*, GoalDrawerCommon::PartsNum_> GoalDrawerCommon::spModels_ =
{
	nullptr, nullptr, nullptr, nullptr, nullptr,
};

#pragma endregion

#pragma region インデックス

static const size_t CoreIdx = static_cast<size_t>(GoalDrawerCommon::Parts::Core); // 核
static const size_t InsideIdx = static_cast<size_t>(GoalDrawerCommon::Parts::InsideCore); // 内枠核
static const size_t InsideCoreIdx = static_cast<size_t>(GoalDrawerCommon::Parts::Inside); // 内枠
static const size_t OutsideIdx = static_cast<size_t>(GoalDrawerCommon::Parts::OutsideCore); // 外枠核
static const size_t OutsideCoreIdx = static_cast<size_t>(GoalDrawerCommon::Parts::Outside); // 外枠

#pragma endregion

#pragma region Common

void GoalDrawerCommon::StaticInitialize()
{
	// ----- モデル読み込み ----- //

	spModels_[CoreIdx] = Model::Load("goal/core", true); // 核
	spModels_[InsideIdx] = Model::Load("goal/inside", true); // 内枠核
	spModels_[InsideCoreIdx] = Model::Load("goal/insideCore", true); // 内枠
	spModels_[OutsideIdx] = Model::Load("goal/outside", true); // 外枠核
	spModels_[OutsideCoreIdx] = Model::Load("goal/outsideCore", true); // 外枠
}

#pragma endregion

#pragma region Drawer

void GoalDrawer::Initialize(YGame::Transform* pParent)
{
	// 基底クラス初期化
	IDrawer::Initialze(pParent, Idle::IntervalTime);

	// オブジェクト生成 + 親行列挿入 (パーツの数)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i].reset(ModelObject::Create({}, spVP_, nullptr, nullptr, spMate_));
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
	IDrawer::Reset();

	// ----- モデル用オブジェクト初期化 ----- //

	// 親トランスフォーム初期化
	core_->Initialize({ {0.0f,0.0f,0.0f}, {0.0f,+PI / 6.0f,0.0f}, {1.0f,1.0f,1.0f} });

	// モデルごとに初期化
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->Initialize({});
	}

	// 核の色設定
	modelObjs_[CoreIdx]->SetColor(CoreColor::ColorPtr(CoreColor::ColorType::Blue));
	modelObjs_[InsideCoreIdx] ->SetColor(CoreColor::ColorPtr(CoreColor::ColorType::Blue));
	modelObjs_[OutsideCoreIdx]->SetColor(CoreColor::ColorPtr(CoreColor::ColorType::Blue));

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
	modelObjs_[InsideCoreIdx]->rota_ = inRotaEas.In(rotaTim_.Ratio());
	modelObjs_[InsideIdx]->rota_ = inRotaEas.In(rotaTim_.Ratio());
	// 回転 (外)
	modelObjs_[OutsideCoreIdx]->rota_ = outRotaEas.In(rotaTim_.Ratio());
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

#pragma endregion

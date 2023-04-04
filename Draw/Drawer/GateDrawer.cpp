#include "GateDrawer.h"
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
using namespace DrawerConfig::Gate;

#pragma endregion

#pragma region Static

// インデックス
static const size_t NormalIdx = 0; // 通常
static const size_t RedIdx = 1; // 赤
static const size_t InvisibleIdx = 2; // 透明

static const size_t InsideIdx	 = static_cast<size_t>(GateDrawerCommon::Parts::Inside); // 内枠
static const size_t InLightIdx	 = static_cast<size_t>(GateDrawerCommon::Parts::InsideLight); // 内枠 (光)
static const size_t OutsideIdx	 = static_cast<size_t>(GateDrawerCommon::Parts::Outside); // 外枠
static const size_t OutLightIdx	 = static_cast<size_t>(GateDrawerCommon::Parts::OutsideLight); // 外枠 (光)

// 静的 モデル配列 初期化
array<array<unique_ptr<Model>, GateDrawerCommon::PartsNum_>, GateDrawerCommon::ModeNum_> GateDrawerCommon::sModels_ =
{
	nullptr, nullptr,
	nullptr, nullptr,
	nullptr, nullptr,
	nullptr, nullptr,
	nullptr, nullptr
};

// 静的ビュープロジェクション
YGame::ViewProjection* GateDrawerCommon::spVP_ = nullptr;

void GateDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP)
{
	// nullチェック
	assert(pVP);
	// 代入
	spVP_ = pVP;

	// ----- モデル読み込み ----- //
	
	// 通常
	sModels_[NormalIdx][InsideIdx].reset(Model::LoadObj("gate/inside", true)); // 内枠
	sModels_[NormalIdx][InLightIdx].reset(Model::LoadObj("gate/insideLight", true)); // 内枠 (光)
	sModels_[NormalIdx][OutsideIdx].reset(Model::LoadObj("gate/outside", true)); // 外枠
	sModels_[NormalIdx][OutLightIdx].reset(Model::LoadObj("gate/outsideLight", true)); // 外枠 (光)

	// 赤
	sModels_[RedIdx][InsideIdx].reset(Model::LoadObj("gate/inside", true)); // 内枠
	sModels_[RedIdx][InLightIdx].reset(Model::LoadObj("gate/insideLight", true)); // 内枠 (光)
	sModels_[RedIdx][OutsideIdx].reset(Model::LoadObj("gate/outside", true)); // 外枠
	sModels_[RedIdx][OutLightIdx].reset(Model::LoadObj("gate/outsideLight", true)); // 外枠 (光)

	// 透明
	sModels_[InvisibleIdx][InsideIdx].reset(Model::LoadObj("gate/inside", true)); // 内枠
	sModels_[InvisibleIdx][InLightIdx].reset(Model::LoadObj("gate/insideLight", true)); // 内枠 (光)
	sModels_[InvisibleIdx][OutsideIdx].reset(Model::LoadObj("gate/outside", true)); // 外枠
	sModels_[InvisibleIdx][OutLightIdx].reset(Model::LoadObj("gate/outsideLight", true)); // 外枠 (光)
}

#pragma endregion

void GateDrawer::Initialize(YGame::Transform* pParent, const Mode& mode)
{
	// 基底クラス初期化
	IDrawer::Initialze(pParent, mode, Idle::IntervalTime);

	// 透明色生成
	invisibleColor_.reset(Color::Create({ 1.0f,1.0f,1.0f,0.25f }));

	// オブジェクト生成 + 親行列挿入 (パーツの数)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		for (size_t j = 0; j < modelObjs_[i].size(); j++)
		{
			// 透明ver
			if (i == InvisibleIdx)
			{
				modelObjs_[i][j].reset(ModelObject::Create({}, spVP_, invisibleColor_.get(), nullptr));
			}
			// 通常、赤ver
			else
			{
				modelObjs_[i][j].reset(ModelObject::Create({}, spVP_, color_.get(), nullptr));
			}

			// 親行列挿入
			modelObjs_[i][j]->parent_ = &core_->m_;
		}
	}

	// リセット
	Reset(mode);
}

void GateDrawer::Reset(const Mode& mode)
{
	// リセット
	IDrawer::Reset(mode);

	// ----- モデル用オブジェクト初期化 ----- //

	core_->Initialize({ {0.0f,0.0f,0.0f}, {0.0f,+PI / 6.0f,0.0f}, {1.0f,1.0f,1.0f} }); // 核

	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		// 大きさ
		Vector3 scale = Vector3(1.0f, 1.0f, 1.0f);
		
		// 透明なら
		if (i == InvisibleIdx)
		{
			scale *= DrawerConfig::InvisibleScale;
		}

		modelObjs_[i][InsideIdx]->Initialize({ {}, {}, scale }); // 内枠
		modelObjs_[i][InLightIdx]->Initialize({ {}, {}, scale }); // 内枠 (光)
		modelObjs_[i][OutsideIdx]->Initialize({ {}, {}, scale }); // 外枠
		modelObjs_[i][OutLightIdx]->Initialize({ {}, {}, scale }); // 外枠 (光)
	}

	current_ = mode;
}

void GateDrawer::Update()
{
	// 基底クラス更新 
	IDrawer::Update({});

	// 行列更新 (子)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		for (size_t j = 0; j < modelObjs_[i].size(); j++)
		{
			modelObjs_[i][j]->UpdateMatrix();
		}
	}
}

void GateDrawer::PreDraw()
{
	// 透明描画
	for (size_t i = 0; i < sModels_[InvisibleIdx].size(); i++)
	{
		sModels_[InvisibleIdx][i]->Draw(modelObjs_[InvisibleIdx][i].get());
	}

	// 通常なら
	if (current_ == Mode::Normal)
	{
		// 描画
		for (size_t i = 0; i < sModels_[NormalIdx].size(); i++)
		{
			sModels_[NormalIdx][i]->Draw(modelObjs_[NormalIdx][i].get());
		}
	}
}

void GateDrawer::PostDraw()
{
	// 赤なら
	if (current_ == Mode::Red)
	{
		// 描画
		for (size_t i = 0; i < sModels_[NormalIdx].size(); i++)
		{
			sModels_[RedIdx][i]->Draw(modelObjs_[RedIdx][i].get());
		}
	}
}

void GateDrawer::IdleAnimation()
{
}

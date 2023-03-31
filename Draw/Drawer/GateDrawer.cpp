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
static const size_t FrameIdx = static_cast<size_t>(GateDrawerCommon::Parts::Frame); // 枠


// 静的 モデル配列 初期化
array<array<unique_ptr<Model>, GateDrawerCommon::PartsNum_>, GateDrawerCommon::ModeNum_> GateDrawerCommon::sModels_ =
{
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
	sModels_[NormalIdx][FrameIdx].reset(Model::Create("GateNormal.png")); // 枠
	sModels_[NormalIdx][1].reset(Model::Create());

	// 赤
	sModels_[RedIdx][FrameIdx].reset(Model::Create("GateRed.png")); // 枠
	sModels_[RedIdx][1].reset(Model::Create());

	// 透明
	sModels_[InvisibleIdx][FrameIdx].reset(Model::Create("GateInvisible.png")); // 枠
	sModels_[InvisibleIdx][1].reset(Model::Create());
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

	// 大きさ
	Vector3 scale = { 0.25f,2.0f,1.0f };

	// モデル用オブジェクト初期化
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		for (size_t j = 0; j < modelObjs_[i].size(); j++)
		{
			// 透明ver
			if (i == InvisibleIdx)
			{
				Vector3 scaleVal = { 
					scale.x_ - 0.01f,
					scale.y_ - 0.01f,
					DrawerConfig::InvisibleScale 
				};

				modelObjs_[i][j]->Initialize({ {}, {}, scaleVal });
			}
			// 通常、赤ver
			else
			{
				modelObjs_[i][j]->Initialize({ {}, {}, scale });
			}
		}
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
	sModels_[InvisibleIdx][FrameIdx]->Draw(modelObjs_[InvisibleIdx][FrameIdx].get());

	// 通常なら
	if (current_ == Mode::Normal)
	{
		// 描画
		sModels_[NormalIdx][FrameIdx]->Draw(modelObjs_[NormalIdx][FrameIdx].get());
	}
}

void GateDrawer::PostDraw()
{
	// 赤なら
	if (current_ == Mode::Red)
	{
		// 描画
		sModels_[RedIdx][FrameIdx]->Draw(modelObjs_[RedIdx][FrameIdx].get());
	}
}

void GateDrawer::IdleAnimation()
{
}

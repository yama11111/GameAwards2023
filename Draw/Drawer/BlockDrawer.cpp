#include "BlockDrawer.h"
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
using namespace DrawerConfig::Block;

#pragma endregion

#pragma region Static

// インデックス
static const size_t NormalIdx = 0; // 通常
static const size_t RedIdx = 1; // 赤
static const size_t InvisibleIdx = 2; // 透明
static const size_t CubeIdx = static_cast<size_t>(BlockDrawerCommon::Parts::Cube); // 体


// 静的 モデル配列 初期化
array<array<unique_ptr<Model>, BlockDrawerCommon::PartsNum_>, BlockDrawerCommon::ModeNum_> BlockDrawerCommon::sModels_ =
{
	nullptr, nullptr,
	nullptr, nullptr,
	nullptr, nullptr
};

// 静的ビュープロジェクション
YGame::ViewProjection* BlockDrawerCommon::spVP_ = nullptr;

void BlockDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP)
{
	// nullチェック
	assert(pVP);
	// 代入
	spVP_ = pVP;

	// ----- モデル読み込み ----- //

	// 通常
	sModels_[NormalIdx][CubeIdx].reset(Model::Create("blockNormal.png")); // 立方体
	sModels_[NormalIdx][1].reset(Model::Create());

	// 赤
	sModels_[RedIdx][CubeIdx].reset(Model::Create("blockRed.png")); // 立方体
	sModels_[RedIdx][1].reset(Model::Create());

	// 透明
	sModels_[InvisibleIdx][CubeIdx].reset(Model::Create("blockInvisible.png")); // 立方体
	sModels_[InvisibleIdx][1].reset(Model::Create());
}

#pragma endregion

void BlockDrawer::Initialize(YMath::Matrix4* pParent, const Mode& mode)
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

void BlockDrawer::Reset(const Mode& mode)
{
	// リセット
	IDrawer::Reset(mode);

	// モデル用オブジェクト初期化
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		for (size_t j = 0; j < modelObjs_[i].size(); j++)
		{
			// 透明ver
			if (i == InvisibleIdx)
			{
				Vector3 scaleVal = {
					DrawerConfig::InvisibleScale,
					DrawerConfig::InvisibleScale,
					DrawerConfig::InvisibleScale
				};

				modelObjs_[i][j]->Initialize({ {},{},scaleVal });
			}
			// 通常、赤ver
			else
			{
				modelObjs_[i][j]->Initialize({});
			}
		}
	}
}

void BlockDrawer::Update()
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

void BlockDrawer::PreDraw()
{
	// 透明描画
	sModels_[InvisibleIdx][CubeIdx]->Draw(modelObjs_[InvisibleIdx][CubeIdx].get());

	// 通常なら
	if (current_ == Mode::Normal)
	{
		// 描画
		sModels_[NormalIdx][CubeIdx]->Draw(modelObjs_[NormalIdx][CubeIdx].get());
	}
}

void BlockDrawer::PostDraw()
{
	// 赤なら
	if (current_ == Mode::Red)
	{
		// 描画
		sModels_[RedIdx][CubeIdx]->Draw(modelObjs_[RedIdx][CubeIdx].get());
	}
}

void BlockDrawer::IdleAnimation()
{
}

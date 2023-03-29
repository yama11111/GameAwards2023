#include "BlockDrawer.h"
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
using namespace DrawerConfig::Block;

#pragma endregion

#pragma region Static

// 静的 モデル配列 初期化
std::array<std::unique_ptr<Model>, BlockDrawerCommon::PartsNum_> BlockDrawerCommon::sModels_ =
{ nullptr, nullptr, };
YGame::ViewProjection* BlockDrawerCommon::spVP_ = nullptr;

void BlockDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP)
{
	// nullチェック
	assert(pVP);
	// 代入
	spVP_ = pVP;

	// ----- モデル読み込み ----- //

	// 体
	sModels_[static_cast<size_t>(Parts::Normal)].reset(Model::Create("blockNormal.png"));
	sModels_[static_cast<size_t>(Parts::Red)]	.reset(Model::Create("blockRed.png"));
}

#pragma endregion

void BlockDrawer::Initialize(YMath::Matrix4* pParent, const Mode& mode)
{
	// 基底クラス初期化
	IDrawer::Initialze(pParent, mode, Idle::IntervalTime);

	// オブジェクト生成 + 親行列挿入 (パーツの数)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i].reset(ModelObject::Create({}, spVP_, color_.get(), nullptr));
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// リセット
	Reset(mode);
}

void BlockDrawer::Reset(const Mode& mode)
{
	// リセット
	IDrawer::Reset(mode);

	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->Initialize({});
	}

	current_ = mode;
}

void BlockDrawer::Update()
{
	// 基底クラス更新 
	IDrawer::Update({});

	// 行列更新 (子)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix();
	}
}

void BlockDrawer::Draw()
{
	// 描画
	//for (size_t i = 0; i < sModels_.size(); i++)
	//{
	//	sModels_[i]->Draw(modelObjs_[i].get());
	//}

	sModels_[static_cast<size_t>(current_)]->Draw(modelObjs_[static_cast<size_t>(current_)].get());
}

void BlockDrawer::IdleAnimation()
{
}

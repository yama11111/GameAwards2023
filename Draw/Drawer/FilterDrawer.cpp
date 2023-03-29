#include "FilterDrawer.h"
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
using namespace DrawerConfig::Filter;

#pragma endregion

#pragma region Static

// 静的 モデル配列 初期化
std::array<std::unique_ptr<Model>, FilterDrawerCommon::PartsNum_> FilterDrawerCommon::sModels_ =
{ nullptr, nullptr, };
YGame::ViewProjection* FilterDrawerCommon::spVP_ = nullptr;

void FilterDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP)
{
	// nullチェック
	assert(pVP);
	// 代入
	spVP_ = pVP;

	// ----- モデル読み込み ----- //

	// 体
	sModels_[static_cast<size_t>(Parts::Monitor)].reset(Model::Create());
	sModels_[static_cast<size_t>(1)].reset(Model::Create());
}

#pragma endregion

void FilterDrawer::Initialize(YMath::Matrix4* pParent)
{
	// 基底クラス初期化
	IDrawer::Initialze(pParent, Mode::Red, Idle::IntervalTime);

	// オブジェクト生成 + 親行列挿入 (パーツの数)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i].reset(ModelObject::Create({}, spVP_, color_.get(), nullptr));
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// リセット
	Reset();
}

void FilterDrawer::Reset()
{
	// リセット
	IDrawer::Reset(Mode::Red);

	// ----- モデル用オブジェクト初期化 ----- //
	
	// モニター
	modelObjs_[static_cast<size_t>(Parts::Monitor)]->Initialize(
		{
			{0,0,-5.0f},
			{},
			{1.0f,1.0f,0.0001f},
		}
	);

	color_->SetRGBA({ 1.0f,0.0f,0.0f,0.25f });
}

void FilterDrawer::Update()
{
	// 基底クラス更新 
	IDrawer::Update({});

	// 行列更新 (子)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix();
	}
}

void FilterDrawer::Draw()
{
	// 描画
	//for (size_t i = 0; i < sModels_.size(); i++)
	//{
	//	sModels_[i]->Draw(modelObjs_[i].get());
	//}
	
	sModels_[static_cast<size_t>(Parts::Monitor)]->Draw(modelObjs_[static_cast<size_t>(Parts::Monitor)].get());
}

void FilterDrawer::IdleAnimation()
{
}

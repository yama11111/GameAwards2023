#include "BuildingDrawer.h"
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

#pragma endregion

#pragma region Static

// 静的 モデル配列 初期化
std::array<Model*, BuildingDrawerCommon::PartsNum_> BuildingDrawerCommon::spModels_ = 
{ nullptr, nullptr, };
YGame::ViewProjection* BuildingDrawerCommon::spVP_ = nullptr;

void BuildingDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP)
{
	// nullチェック
	assert(pVP);
	// 代入
	spVP_ = pVP;

	// ----- モデル読み込み ----- //

	// 体
	spModels_[static_cast<size_t>(Parts::Building)] = Model::Load("building", true);
	spModels_[static_cast<size_t>(1)] = Model::Load("building", true);
}

#pragma endregion

void BuildingDrawer::Initialize(YMath::Matrix4* pParent)
{
	// nullチェック
	assert(pParent);

	// オブジェクト生成 + 親行列挿入
	core_.reset(new Transform());
	core_->Initialize({});
	core_->parent_ = pParent;

	// 色生成
	color_.reset(Color::Create());

	// オブジェクト生成 + 親行列挿入 (パーツの数)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i].reset(ModelObject::Create({}, spVP_, color_.get(), nullptr));
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// リセット
	Reset();
}

void BuildingDrawer::Reset()
{
	// 初期化
	SlimeActor::Initialize();

	core_->Initialize({});

	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->Initialize({});
	}

	idleTim_.Initialize(DrawerConfig::Block::Idle::IntervalTime);
	idleTim_.SetActive(true);
}

void BuildingDrawer::Update()
{
	// 立ちモーションタイマー更新
	idleTim_.Update();

	// タイマーが終わったら
	if (idleTim_.IsEnd())
	{
		// 立ちモーション再生
		IdleAnimation();
		// タイマーリセット
		idleTim_.Reset(true);
	}

	// 行列更新 (親)
	core_->UpdateMatrix(
		{
			-SlimeActor::JiggleValue(),
			{},
			SlimeActor::JiggleValue()
		}
	);

	// 行列更新 (子)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix();
	}
}

void BuildingDrawer::Draw()
{
	// 描画
	for (size_t i = 0; i < spModels_.size(); i++)
	{
		spModels_[i]->Draw(modelObjs_[i].get());
	}
}

void BuildingDrawer::IdleAnimation()
{
}

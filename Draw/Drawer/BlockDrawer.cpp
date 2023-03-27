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

#pragma endregion

#pragma region Static

// 静的 モデル配列 初期化
std::array<std::unique_ptr<Model>, BlockDrawerCommon::PartsNum_> BlockDrawerCommon::sModels_ =
{ nullptr, nullptr, };

void BlockDrawerCommon::StaticInitialize()
{
	// ----- モデル読み込み ----- //

	// 体
	sModels_[static_cast<size_t>(Parts::Cube)].reset(Model::LoadObj("player/player_body", true));
	sModels_[static_cast<size_t>(1)].reset(Model::LoadObj("player/player_body", true));
}

#pragma endregion

void BlockDrawer::Initialize(YMath::Matrix4* pParent)
{
	// nullチェック
	assert(pParent);

	// オブジェクト生成 + 親行列挿入
	core_.reset(new Transform());
	core_->Initialize({});
	core_->parent_ = pParent;

	// オブジェクト生成 + 親行列挿入 (パーツの数)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i].reset(ModelObject::Create({}));
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// リセット
	Reset();
}

void BlockDrawer::Reset()
{
	// 初期化
	SlimeActor::Initialize();

	core_->Initialize({});

	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->Initialize({});
	}

	idelTim_.Initialize(DrawerConfig::Block::Idle::IntervalTime);
	idelTim_.SetActive(true);
}

void BlockDrawer::Update()
{
	// 立ちモーションタイマー更新
	idelTim_.Update();

	// タイマーが終わったら
	if (idelTim_.IsEnd())
	{
		// 立ちモーション再生
		IdleAnimation();
		// タイマーリセット
		idelTim_.Reset(true);
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

void BlockDrawer::Draw()
{
	// 描画
	for (size_t i = 0; i < sModels_.size(); i++)
	{
		sModels_[i]->Draw(modelObjs_[i].get());
	}
}

void BlockDrawer::IdleAnimation()
{
}

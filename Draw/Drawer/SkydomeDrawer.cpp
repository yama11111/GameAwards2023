#include "SkydomeDrawer.h"

using YGame::ModelObject;
using YGame::Model;
using YGame::Color;

std::unique_ptr<Model> SkydomeDrawerCommon::sModel_ = nullptr;

void SkydomeDrawerCommon::StaticInitialize()
{
	// モデル読み込み
	sModel_.reset(Model::LoadObj("skydome", true));
}

void SkydomeDrawer::Initalize(YMath::Matrix4* pParent)
{
	// 色生成
	color_.reset(Color::Create());

	// オブジェクト生成
	obj_.reset(ModelObject::Create({}, nullptr, color_.get(), nullptr));
	
	// 親行列代入
	obj_->parent_ = pParent;

	// リセット
	Reset();
}

void SkydomeDrawer::Reset()
{
	// オブジェクト初期化
	obj_->Initialize(
		{
			{},
			{},
			{ 100.0f, 100.0f, 100.0f }
		}
	);
}

void SkydomeDrawer::Update()
{
	// オブジェクト更新
	obj_->UpdateMatrix();
}

void SkydomeDrawer::Draw()
{
	// 描画
	sModel_->Draw(obj_.get());
}

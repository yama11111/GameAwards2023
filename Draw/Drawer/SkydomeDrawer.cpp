#include "SkydomeDrawer.h"

using YGame::ModelObject;
using YGame::Model;
using YGame::Color;

Model* SkydomeDrawerCommon::spModel_ = nullptr;
Color* SkydomeDrawerCommon::spColor_ = nullptr;

void SkydomeDrawerCommon::StaticInitialize(YGame::Color* pColor)
{
	// モデル読み込み
	spModel_ = Model::Load("skydome", true);

	// 色ポインタ
	spColor_ = pColor;
}

void SkydomeDrawer::Initialize(YMath::Matrix4* pParent, const float scaleSize)
{
	// オブジェクト生成
	obj_.reset(ModelObject::Create({}, nullptr, spColor_, nullptr, nullptr));
	
	// 親行列代入
	obj_->parent_ = pParent;

	// リセット
	Reset(scaleSize);
}

void SkydomeDrawer::Reset(const float scaleSize)
{
	// オブジェクト初期化
	obj_->Initialize(
		{
			{},
			{},
			{ scaleSize, scaleSize, scaleSize }
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
	spModel_->Draw(obj_.get());
}

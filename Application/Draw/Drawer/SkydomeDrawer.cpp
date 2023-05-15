#include "SkydomeDrawer.h"

using YGame::Model;
using YGame::CBColor;

Model* SkydomeDrawerCommon::spModel_ = nullptr;
CBColor* SkydomeDrawerCommon::spColor_ = nullptr;

void SkydomeDrawerCommon::StaticInitialize(YGame::CBColor* pColor)
{
	// モデル読み込み
	spModel_ = Model::LoadObj("skydome", true);

	// 色ポインタ
	spColor_ = pColor;
}

void SkydomeDrawer::Initialize(YMath::Matrix4* pParent, const float scaleSize)
{
	// オブジェクト生成
	obj_.reset(Model::Object::Create({}, nullptr, spColor_, nullptr, nullptr, nullptr));
	
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
	spModel_->SetDrawCommand(obj_.get(), YGame::DrawLocation::Back);
}

#include "UIButtonDrawer.h"

using YGame::UIButtonDrawer;

void UIButtonDrawer::Initialize(Texture* pButtonTex, Texture* pPressedTex)
{
	// ----- スプライト生成 ----- //

	// ボタン
	pButtonSpr_[0] = Sprite2D::Create({}, { pButtonTex });

	// 押されたボタン
	pButtonSpr_[1] = Sprite2D::Create({}, { pPressedTex });

	// ----- その他 ----- //

	// 押されたか
	isPush_ = false;
}

void UIButtonDrawer::Update(const bool isPush)
{
	// フラグ更新
	isPush_ = isPush;
}

void UIButtonDrawer::Draw(Sprite2D::Object* pObject)
{
	// ボタン描画
	pButtonSpr_[isPush_]->SetDrawCommand(pObject, DrawLocation::Front);
}

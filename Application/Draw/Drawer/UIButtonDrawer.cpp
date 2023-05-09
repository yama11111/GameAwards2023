#include "UIButtonDrawer.h"

using YGame::UIButtonDrawer;

void UIButtonDrawer::Initialize(Texture* pButtonTex, Texture* pPressedTex)
{
	// ----- �X�v���C�g���� ----- //

	// �{�^��
	pButtonSpr_[0] = Sprite2D::Create({}, { pButtonTex });

	// �����ꂽ�{�^��
	pButtonSpr_[1] = Sprite2D::Create({}, { pPressedTex });

	// ----- ���̑� ----- //

	// �����ꂽ��
	isPush_ = false;
}

void UIButtonDrawer::Update(const bool isPush)
{
	// �t���O�X�V
	isPush_ = isPush;
}

void UIButtonDrawer::Draw(Sprite2D::Object* pObject)
{
	// �{�^���`��
	pButtonSpr_[isPush_]->SetDrawCommand(pObject, DrawLocation::Front);
}

#pragma once
#include "Sprite2D.h"

class TitleDrawerCommon
{
protected:
	// �ÓI���S�X�v���C�g
	static YGame::Sprite2D* spLogoSpr_;
public:
	// �ÓI������
	static void StaticInitialize();
};

class TitleDrawer : 
	private TitleDrawerCommon
{
private:
	// ----- �I�u�W�F�N�g ----- //

	// �j
	std::unique_ptr<YGame::Transform> core_;

	// ----- �A�j���[�V���� ----- //

	// �I��ԍ��|�C���^
	int* pStageIdx_ = nullptr;

	// ���쒆��
	bool isAct_ = false;
public:
	// ������
	void Initalize(int* pStageIdx);
	// ���Z�b�g
	void Reset();
	// �X�V
	void Update();
	// �`��
	void Draw();
};


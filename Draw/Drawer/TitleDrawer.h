#pragma once
#include "Sprite2D.h"
#include "Model.h"

class TitleDrawerCommon
{
protected:

	// ----- Sprite2D ----- //

	// �ÓI���S�X�v���C�g
	static YGame::Sprite2D* spLogoSpr_;

	// �ÓI�e�X�v���C�g
	static YGame::Sprite2D* spShadowSpr_;

	// �ÓI�w�i�X�v���C�g
	static YGame::Sprite2D* spBackSpr_;


	// �ÓI�X�^�[�g�X�v���C�g
	static YGame::Sprite2D* spStartSpr_;

	// �ÓI�I���X�v���C�g
	static YGame::Sprite2D* spExitSpr_;

	// ----- Model ----- //

	// �ÓI�r�����f��
	static YGame::Model* spBuildingMod_;

public:

	// �ÓI������
	static void StaticInitialize();

};

class TitleDrawer :
	private TitleDrawerCommon
{
public:

	// �I��
	enum class Selection
	{
		Start, // �J�n
		Exit,  // �I��
	};

private:
	// ----- �I�u�W�F�N�g ----- //

	// �j
	std::unique_ptr<YGame::Transform> core_;

	// ���S
	std::unique_ptr<YGame::Sprite2DObject> logoObj_;


	// �e
	std::unique_ptr<YGame::Sprite2DObject> shadowObj_;

	// �w�i
	std::unique_ptr<YGame::Sprite2DObject> backObj_;


	// �X�^�[�g
	std::unique_ptr<YGame::Sprite2DObject> startObj_;
	// �X�^�[�g�F
	std::unique_ptr<YGame::Color> startColor_;

	// �I��
	std::unique_ptr<YGame::Sprite2DObject> exitObj_;
	// �I���F
	std::unique_ptr<YGame::Color> exitColor_;

	// ----- �A�j���[�V���� ----- //

	// ���쒆��
	bool isAct_ = false;

	// �I��
	Selection current_ = Selection::Start;

public:

	// ������
	void Initalize();

	// ���Z�b�g
	void Reset();

	// �I��
	void Select(const bool isUp, const bool isUnder);

	// �X�V
	void Update();

	// �X�v���C�g2D�`��
	void DrawSprite2D();

	// ���f���`��
	void DrawModel();

public:

	// ���݂̑I���擾
	Selection GetSelection() { return current_; }

	// ���݂̑I��ݒ�
	void SetSelection(const Selection& selection) { current_ = selection; }

};


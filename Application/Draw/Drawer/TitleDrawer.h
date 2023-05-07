#pragma once
#include "Sprite2D.h"
#include "Model.h"
#include "Lerp.h"
#include "Power.h"

// ���d��`���p
namespace YInput { class Keys; }

class TitleDrawerCommon
{

public:

	// �I��
	enum class Selection
	{
		Start, // �J�n
		Exit,  // �I��
	};

protected:

	// �L�[
	static YInput::Keys* sKeys_;


	// �ÓI���S�X�v���C�g
	static YGame::Sprite2D* spLogoSpr_;

	// �ÓI�e�X�v���C�g
	static YGame::Sprite2D* spShadowSpr_;


	// �ÓI�X�^�[�g�X�v���C�g
	static YGame::Sprite2D* spStartSpr_;

	// �ÓI�I���X�v���C�g
	static YGame::Sprite2D* spExitSpr_;

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


	YMath::Power selectStartPow_;
	YMath::Ease<float> selectMoveXEas_;

	YMath::Power selectExitPow_;
	YMath::Ease<float> selectScaleEas_;

public:

	// ������
	void Initialize();

	// ���Z�b�g
	void Reset();

	// �I��
	void Select(const bool isUp, const bool isUnder);

	// �X�V
	void Update();

	// �`��
	void Draw();

public:

	// ���݂̑I���擾
	Selection GetSelection() { return current_; }

	// ���݂̑I��ݒ�
	void SetSelection(const Selection& selection) { current_ = selection; }

};


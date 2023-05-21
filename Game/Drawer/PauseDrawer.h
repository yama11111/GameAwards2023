#pragma once
#include "Sprite2D.h"
#include "Lerp.h"
#include "Power.h"
#include <array>

// ���d��`���p
namespace YInput { class Keys; }

class PauseDrawerCommon
{

public:
	
	// �I��
	enum class Selection
	{
		Resume, // �߂�
		Change, // �J��
	};

protected:
	
	// �L�[
	static YInput::Keys* sKeys_;

	// pause
	static YGame::Sprite2D* spPauseSpr_;
	// resume
	static YGame::Sprite2D* spResumeSpr_;
	// title
	static YGame::Sprite2D* spTitleSpr_;
	// stage
	static YGame::Sprite2D* spStageSpr_;
	
	// curten
	static YGame::Sprite2D* spCurtenSpr_;

public:
	
	/// <summary> 
	/// �ÓI������
	/// </summary>
	static void StaticInitialize();

public:
	
	virtual ~PauseDrawerCommon() = default;

};

class PauseDrawer : private PauseDrawerCommon
{

private:
	
	// ----- Object ----- //

	// pause
	std::unique_ptr<YGame::Sprite2D::Object> pauseObj_;
	// resume
	std::unique_ptr<YGame::Sprite2D::Object> resumeObj_;
	// change
	std::unique_ptr<YGame::Sprite2D::Object> changeObj_;

	// curten
	std::unique_ptr<YGame::Sprite2D::Object> curtenObj_;
	
	// ----- Color ----- //

	// resumeColor
	std::unique_ptr<YGame::CBColor> resumeColor_;
	// changeColor
	std::unique_ptr<YGame::CBColor> changeColor_;

	// curtenColor
	std::unique_ptr<YGame::CBColor> curtenColor_;


	// �|�[�Y����
	bool isPause_ = false;

	// �|�[�Y����������
	bool isElderPause_ = false;

	// ���݂̑I��
	Selection current_ = Selection::Resume;

	// �I��Resume�p���[
	YMath::Power selectResumePow_;
	
	// �I��Change�p���[
	YMath::Power selectChangePow_;

	// �I���X�P�[���C�[�W���O
	YMath::Ease<float> selectScaleEas_;

public:
	// ������
	void Initialize();
	// ���Z�b�g
	void Reset();
	// �X�V
	void Update();
	// �`��
	void Draw();
private:
	void ResumeReset();
public:
	// �|�[�Y����
	bool IsPause() const { return isPause_; }
	// �|�[�Y����������
	bool IsElderPause() const { return isElderPause_; }
};


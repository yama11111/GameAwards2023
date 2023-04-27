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
	enum class Select
	{
		Resume, // �߂�
		Title, // �^�C�g��
		Stage, // �X�e�[�W�Z���N�g
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
	// �ÓI������
	static void StaticInitialize();
public:
	virtual ~PauseDrawerCommon() = default;
};

class PauseDrawer : private PauseDrawerCommon
{
public:
	// �������p�V�[��
	enum class SceneType
	{
		Select, // �X�e�[�W�Z���N�g
		Play, // �Q�[��
	};

private:
	// ----- Object ----- //

	// pause
	std::unique_ptr<YGame::Sprite2DObject> pauseObj_;
	// resume
	std::unique_ptr<YGame::Sprite2DObject> resumeObj_;
	// change
	std::unique_ptr<YGame::Sprite2DObject> changeObj_;

	// curten
	std::unique_ptr<YGame::Sprite2DObject> curtenObj_;
	
	// ----- Color ----- //

	// resumeColor
	std::unique_ptr<YGame::Color> resumeColor_;
	// changeColor
	std::unique_ptr<YGame::Color> changeColor_;

	// curtenColor
	std::unique_ptr<YGame::Color> curtenColor_;


	// �|�[�Y����
	bool isPause_ = false;

	// �|�[�Y����������
	bool isElderPause_ = false;

	// ���݂̑I��
	Select current_ = Select::Resume;

	// ���݂̃V�[��
	SceneType sceneType_ = SceneType::Select;

	// �I��Resume�p���[
	YMath::Power selectResumePow_;
	// �I��Change�p���[
	YMath::Power selectChangePow_;

	// �I���X�P�[���C�[�W���O
	YMath::Ease<float> selectScaleEas_;

public:
	// ������
	void Initialize(const SceneType& sceneType);
	// ���Z�b�g
	void Reset(const SceneType& sceneType);
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


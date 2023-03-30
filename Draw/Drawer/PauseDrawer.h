#pragma once
#include "Sprite2D.h"
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
	};
protected:
	// �L�[
	static YInput::Keys* sKeys_;

	// pause
	static std::unique_ptr<YGame::Sprite2D> pauseSpr_;
	// resume
	static std::unique_ptr<YGame::Sprite2D> resumeSpr_;
	// title
	static std::unique_ptr<YGame::Sprite2D> titleSpr_;
	
	// curten
	static std::unique_ptr<YGame::Sprite2D> curtenSpr_;
public:
	// �ÓI������
	static void StaticInitialize();
};

class PauseDrawer : private PauseDrawerCommon
{
private:
	// ----- Object ----- //

	// pause
	std::unique_ptr<YGame::Sprite2DObject> pauseObj_;
	// resume
	std::unique_ptr<YGame::Sprite2DObject> resumeObj_;
	// title
	std::unique_ptr<YGame::Sprite2DObject> titleObj_;

	// curten
	std::unique_ptr<YGame::Sprite2DObject> curtenObj_;
	
	// ----- Color ----- //

	// resumeColor
	std::unique_ptr<YGame::Color> resumeColor_;
	// titleColor
	std::unique_ptr<YGame::Color> titleColor_;

	// curtenColor
	std::unique_ptr<YGame::Color> curtenColor_;


	// �|�[�Y����
	bool isPause_ = false;

	// ���݂̑I��
	Select current_ = Select::Resume;

public:
	// ������
	void Initalize();
	// ���Z�b�g
	void Reset();
	// �X�V
	void Update();
	// �`��
	void Draw();
public:
	// �|�[�Y����
	bool IsPause() const { return isPause_; }
};


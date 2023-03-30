#pragma once
#include "InputDrawer.h"
#include "PauseDrawer.h"

class HUDDrawerCommon
{
public:
	// ���c�m
	enum class Pilot
	{
		Player, // �v���C���[
		Filter, // �t�B���^�[
	};
protected:	
	// player
	static std::unique_ptr<YGame::Sprite2D> playerSpr_;
	// filter
	static std::unique_ptr<YGame::Sprite2D> filterSpr_;
public:
	// �ÓI������
	static void StaticInitialize();
};

class HUDDrawer : private HUDDrawerCommon
{
private:
	// ���c�m
	Pilot pilot_ = Pilot::Player;

	// player
	std::unique_ptr<YGame::Sprite2DObject> playerObj_;
	// filter
	std::unique_ptr<YGame::Sprite2DObject> filterObj_;

	// playerColor
	std::unique_ptr<YGame::Color> playerColor_;
	// filterColor
	std::unique_ptr<YGame::Color> filterColor_;


	// input
	InputDrawer inputDra_;

	// pause
	PauseDrawer pauseDra_;
public:
	// ������
	void Initalize(const Pilot& pilot = Pilot::Player);
	// ���Z�b�g
	void Reset(const Pilot& pilot = Pilot::Player);
	// �X�V
	void Update();
	// �`��
	void Draw();
public:
	// ���c�m�ݒ�
	void SetPilot(const Pilot& pilot);
	// �|�[�Y����
	bool IsPause() const { return pauseDra_.IsPause(); }
};


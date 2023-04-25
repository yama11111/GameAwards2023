#pragma once
#include "InputDrawer.h"
#include "PauseDrawer.h"

class HUDDrawerCommon
{

public:

	// �ÓI������
	static void StaticInitialize();

public:

	virtual ~HUDDrawerCommon() = default;
};

class HUDDrawer : private HUDDrawerCommon
{

private:

	// input
	InputDrawer inputDra_;

	// pause
	PauseDrawer pauseDra_;

public:
	
	// ������
	void Initialize();
	
	// ���Z�b�g
	void Reset();
	
	// �X�V
	void Update();
	
	// �`��
	void Draw();

public:
	
	// �|�[�Y����
	bool IsPause() const { return pauseDra_.IsPause(); }

};


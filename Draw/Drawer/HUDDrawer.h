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
	
	/// <summary> 
	/// ������
	/// </summary>
	void Initialize();
	
	/// <summary> 
	/// ���Z�b�g
	/// </summary>
	void Reset();
	
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	
	/// <summary> 
	/// �`��
	/// </summary>
	void Draw();

public:
	
	// �|�[�Y����
	bool IsPause() const { return pauseDra_.IsPause(); }

	// �|�[�Y����������
	bool IsElderPause() const { return pauseDra_.IsElderPause(); }

};


#pragma once
#include "Model.h"
#include "Lerp.h"
#include "Power.h"

class GridDrawerCommon
{

protected:

	// ���f���|�C���^
	static YGame::Model* spGridMod_;

	// �r���[�v���W�F�N�V�����|�C���^
	static YGame::ViewProjection* spVP_;

public:

	/// <summary>
	/// �ÓI������
	/// </summary>
	static void StaticInitialize(YGame::ViewProjection* pVP);

public:

	virtual ~GridDrawerCommon() = default;

};

class GridDrawer : private GridDrawerCommon
{

private:

	// ----- �I�u�W�F�N�g ----- //
	
	// �O���b�h
	std::list<std::unique_ptr<YGame::ModelObject>> grids_;

	// �F
	std::unique_ptr<YGame::Color> color_;

	// ----- �A�j���[�V���� ----- //
	
	// �A���t�@�l�ϓ����邩
	bool isActAlpha_ = false;

	// �A���t�@�l�X�C�b�`���[
	bool isSwitchAlpha_ = false;

	// �A���t�@�l�p���[
	YMath::Power alphaPow_;
		
	// �A���t�@�l�C�[�W���O
	YMath::Ease<float> alphaEas_;

public:

	// ������
	void Initialize(const YMath::Vector3& leftTop, const YMath::Vector3& num, const float scaleSize);

	// ���Z�b�g
	void Reset();

	// �X�V
	void Update();

	// �`��
	void Draw();

public:

	// �A���t�@�l�A�j���[�V�����J�n
	void ActAlphaAnimation();

private:

	// �A���t�@�l�A�j���[�V�����X�V
	void UpdateAlphaAnimation();

};


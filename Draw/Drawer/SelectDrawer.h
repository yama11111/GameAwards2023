#pragma once
#include "StageDrawer.h"
#include "Sprite2D.h"
#include "Power.h"

class SelectDrawerCommon
{
protected:
	// �ÓI�����X�v���C�g
	static std::array<std::unique_ptr<YGame::Sprite2D>, 10> sNumberSpr_;
	// �ÓI�X�v���C�g
	// static std::unique_ptr<YGame::Sprite2D> sStageSpr_;
	// �ÓI�n�����f��
	static std::unique_ptr<YGame::Model> sEarthModel_;
	// �r���[�v���W�F�N�V�����|�C���^
	static YGame::ViewProjection* spVP_;
public:
	// �ÓI������
	static void StaticInitialize(YGame::ViewProjection* pVP);
};

class SelectDrawer : private SelectDrawerCommon
{
private:
	// �j
	std::unique_ptr<YGame::Transform> core_;
	
	
	// �n�����f���I�u�W�F�N�g
	std::unique_ptr<YGame::ModelObject> earthObj_;
	// �F
	std::unique_ptr<YGame::Color> color_;

	
	// �X�e�[�W�g�����X�t�H�[�� (�g���p)
	std::array<std::unique_ptr<YGame::Transform>, 24> aliveStages_;
	// �X�e�[�W�g�����X�t�H�[�� (�g��Ȃ��p)
	std::unique_ptr<YGame::Transform> deadStage_;
	// �X�e�[�W�`��N���X
	std::vector<std::unique_ptr<StageDrawer>> stageDras_;

	
	// �X�e�[�W�ԍ��|�C���^
	int* pStageIdx_ = nullptr;

	// ���쒆��
	bool isAct_ = false;
	
	// �J�n����]�p�C�[�W���O
	YMath::Ease<float> startRotaEas_;
	// �J�n����]�p�^�C�}�[
	YMath::Timer startRotaTim_;
	
	// �X�e�[�W��]�p�C�[�W���O
	YMath::Ease<float> stageRotaEas_;
	// �X�e�[�W��]�p�p���[
	std::vector<YMath::Power> stageRotaPows_;
public:
	// ������
	void Initalize(int* pStageIdx);
	// ���Z�b�g
	void Reset();
	// �X�V
	void Update();
	// �`�� (���f��)
	void DrawModel();
	// �`�� (�X�v���C�g2D)
	void DrawSprite3D();
	// �`�� (�X�v���C�g3D)
	void DrawSprite2D();
public:
	// ����ݒ�
	void SetActive(const bool isAct) { isAct_ = isAct; }
private:
	// �A�j���[�V�����̉�]�X�V
	void UpdateRotaAnimation();
};


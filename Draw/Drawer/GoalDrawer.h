#pragma once
#include "Model.h"
#include "SlimeActor.h"
#include <array>
#include <memory>

// �S�[���`��p�R�����N���X
class GoalDrawerCommon
{
protected:
	// �p�[�c�̖��O
	enum class Parts
	{
		Cube, // �����`
	};
protected:
	// �p�[�c�̑���
	static const size_t PartsNum_ = 2;
protected:
	// ���f�� (�p�[�c�̐�����)
	static std::array<std::unique_ptr<YGame::Model>, PartsNum_> sModels_;
	// �r���[�v���W�F�N�V�����|�C���^
	static YGame::ViewProjection* spVP_;
public:
	// �ÓI������
	static void StaticInitialize(YGame::ViewProjection* pVP);
};

// �S�[���`��p�N���X
class GoalDrawer :
	private GoalDrawerCommon,
	private YGame::SlimeActor
{
private:
	// �g�����X�t�H�[�� 
	std::unique_ptr<YGame::Transform> core_;
	// ���f���p�I�u�W�F�N�g (�q)
	std::array<std::unique_ptr<YGame::ModelObject>, PartsNum_> modelObjs_;
	// �F
	std::unique_ptr<YGame::Color> color_;
	
	// �������[�V�����p�^�C�}�[
	YMath::Timer idleTim_;
public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="pParent"> : �e�s��|�C���^ (���̍s��ɒǏ]����)</param>
	void Initialize(YMath::Matrix4* pParent);
	// ���Z�b�g (���g����������)
	void Reset();
	// �X�V
	void Update();
	// �`��
	void Draw();
public:
	// �������[�V����
	void IdleAnimation();
	// �F�ւ��A�j���[�V����
	//void ChangeColor(const );
};


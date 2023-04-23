#pragma once
#include "IDrawer.h"
#include <array>

// �S�[���`��p�R�����N���X
class GoalDrawerCommon
{

public:
	
	// �p�[�c�̖��O
	enum class Parts
	{
		Core, // �j
		Inside, // ���g
		Outside, // �O�g
	};

protected:
	
	// �p�[�c�̑���
	static const size_t PartsNum_ = 3;

protected:
	
	// ���f�� (�p�[�c�̐�����)
	static std::array<YGame::Model*, PartsNum_> spModels_;

public:

	/// <summary>
	/// �ÓI������
	/// </summary>
	static void StaticInitialize();

public:
	
	virtual ~GoalDrawerCommon() = default;
};

// �S�[���`��p�N���X
class GoalDrawer :
	private IDrawer,
	private GoalDrawerCommon
{

private:
	
	// ���f���p�I�u�W�F�N�g (�q)
	std::array<std::unique_ptr<YGame::ModelObject>, PartsNum_> modelObjs_;

	// ��] (��)
	YMath::Ease<YMath::Vector3> inRotaEas;
	
	// ��] (�O)
	YMath::Ease<YMath::Vector3> outRotaEas;
	
	// ��]�^�C�}�[
	YMath::Timer rotaTim_;

public:
	
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="pParent"> : �e�|�C���^ (���̍s��ɒǏ]����)</param>
	void Initialize(YGame::Transform* pParent);
	
	// ���Z�b�g (���g����������)
	void Reset();
	
	// �X�V
	void Update();
	
	// �`��
	void Draw();

private:
	
	// �������[�V����
	void IdleAnimation() override;
	
	// ��]�A�j���[�V����
	void RotaAnimation();

};


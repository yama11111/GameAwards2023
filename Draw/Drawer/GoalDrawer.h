#pragma once
#include "IDrawer.h"
#include "IMode.h"
#include <array>

// �S�[���`��p�R�����N���X
class GoalDrawerCommon
{

public:
	
	// �p�[�c�̖��O
	enum class Parts
	{
		Core, // �j
		InsideCore, // ���g�j
		Inside, // ���g
		OutsideCore, // �O�g�j
		Outside, // �O�g
	};

protected:
	
	// �p�[�c�̑���
	static const size_t PartsNum_ = 5;

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
	
	/// <summary>
	/// ���Z�b�g (���g����������)
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

private:
	
	// �������[�V����
	void IdleAnimation() override;
	
	// ��]�A�j���[�V����
	void RotaAnimation();

};


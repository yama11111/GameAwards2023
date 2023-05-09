#pragma once
#include "IDrawer.h"
#include <array>

// �v���C���[�`��p�R�����N���X
class PlayerDrawerCommon
{

public:
	
	// �p�[�c�̖��O
	enum class Parts
	{
		Body, // ��
	};

protected:
	
	// �p�[�c�̑���
	static const size_t PartsNum_ = 2;

protected:
	
	// ���f�� (�p�[�c�̐�����)
	static std::array<YGame::Model*, PartsNum_> spModels_;
public:
	
	/// <summary>
	/// �ÓI������
	/// </summary>
	static void StaticInitialize();

public:
	
	virtual ~PlayerDrawerCommon() = default;
};

// �v���C���[�`��p�N���X
class PlayerDrawer :
	private IDrawer,
	private PlayerDrawerCommon
{

private:
	
	// ----- �I�u�W�F�N�g ----- //
	
	// ���f���p�I�u�W�F�N�g (�q)
	std::array<std::unique_ptr<YGame::Model::Object>, PartsNum_> modelObjs_;
	
	// �F
	std::unique_ptr<YGame::Color> color_;

	// �����|�C���^
	YMath::Vector3* pDirection_ = nullptr;

	
	// ----- �A�j���[�V���� ----- //

	// �ړ�����
	bool isMove_ = false;
	
	// �ړ����Ă�����
	bool isElderMove_ = false;

	// �ړ��p��]�p���[
	YMath::Power moveRotaPow_;

	// �ړ��p��]�C�[�W���O
	YMath::Ease<float> moveRotaEas_;

	// �ړ��p�G�~�b�g�^�C�}�[
	YMath::Timer moveEmitTimer_;


	// ���X�|�[������
	bool isRespawn_ = false;
	
	// ���X�|�[���p�^�C�}�[
	YMath::Timer respawnTim_;
	
	// ���X�|�[���p�X�P�[���C�[�W���O
	YMath::Ease<float> respScaleEas_;
	
	// ���X�|�[���p�A���t�@�l�C�[�W���O
	YMath::Ease<float> respAlphaEas_;


	// �S�[��������
	bool isGoal_ = false;

	// �S�[���p�^�C�}�[
	YMath::Timer goalTim_;

	// �S�[���p�X�P�[���C�[�W���O
	YMath::Ease<float> goalScaleEas_;

	// �S�[���p�A���t�@�l�C�[�W���O
	YMath::Ease<float> goalAlphaEas_;

public:
	
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="pParent"> : �e�|�C���^ (���̍s��ɒǏ]����)</param>
	/// <param name="pDirection"> : �����|�C���^ (���̌����Ɍ���)</param>
	void Initialize(YGame::Transform* pParent, YMath::Vector3* pDirection);
	
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

public:
	
	// �ړ����[�V����
	void SetActMoveAnimation(const bool isMove) { isMove_ = isMove; }
	
	// �W�����v���[�V����
	void JumpAnimation();
	
	// ���n���[�V����
	void LandingAnimation();

	
	// ���X�|�[���A�j���[�V����
	void RespawnAnimation();

	// �S�[���A�j���[�V����
	void GoalAnimation();

private:
	
	// �A�j���[�V�������Z�b�g
	void ResetAnimation();

	// �������X�V
	void UpdateSmokeEmitter();
	
	// �������[�V����
	void IdleAnimation() override;

public:
	
	~PlayerDrawer() = default;
};


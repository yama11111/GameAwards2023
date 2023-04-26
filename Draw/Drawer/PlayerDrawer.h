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
	std::array<std::unique_ptr<YGame::ModelObject>, PartsNum_> modelObjs_;
	
	// �F
	std::unique_ptr<YGame::Color> color_;

	// �����|�C���^
	YMath::Vector3* pDirection_ = nullptr;

	
	// ----- �A�j���[�V���� ----- //

	// ���X�|�[������
	bool isRespawn_ = false;
	
	// ���X�|�[���p�^�C�}�[
	YMath::Timer respawnTim_;
	
	// ���X�|�[���p�X�P�[���C�[�W���O
	YMath::Ease<float> respScaleEas_;
	
	// ���X�|�[���p�A���t�@�l�C�[�W���O
	YMath::Ease<float> respAlphaEas_;

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
	
	// �W�����v���[�V����
	void JumpAnimation();
	
	// ���n���[�V����
	void LandingAnimation();
	
	// ���X�|�[���A�j���[�V����
	void RespawnAnimation();

private:
	
	// �A�j���[�V�������Z�b�g
	void ResetAnimation();
	
	// �������[�V����
	void IdleAnimation() override;

public:
	
	~PlayerDrawer() = default;
};


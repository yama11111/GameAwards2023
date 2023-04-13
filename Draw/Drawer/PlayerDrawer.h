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
	// �r���[�v���W�F�N�V�����|�C���^
	static YGame::ViewProjection* spVP_;
public:
	// �ÓI������
	static void StaticInitialize(YGame::ViewProjection* pVP);
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
	std::array<std::array<std::unique_ptr<YGame::ModelObject>, PartsNum_>, ModeNum_> modelObjs_;

	// �F (����, ��, ����)
	std::array<std::unique_ptr<YGame::Color>, ModeNum_> colors_;

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
	/// <param name="mode"> : ���</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="Mode::Noraml"> : �ʏ���</param>
	/// <param name="Mode::Red"> : �ԐF���</param>
	/// <param name="Mode::None"> : ���� (�g��Ȃ�)</param>
	void Initialize(YGame::Transform* pParent, YMath::Vector3* pDirection, const Mode& mode);
	/// <summary>
	/// ���Z�b�g (���g����������)
	/// </summary>
	/// <param name="mode"> : ���</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="Mode::Noraml"> : �ʏ���</param>
	/// <param name="Mode::Red"> : �ԐF���</param>
	/// <param name="Mode::None"> : ���� (�g��Ȃ�)</param>
	void Reset(const Mode& mode);
	// �X�V
	void Update();
	// �O���`�� (�t�B���^�[��� �� �ɌĂ�)
	void PreDraw();
	// ����`�� (�t�B���^�[��� �� �ɌĂ�)
	void PostDraw();
public:
	// �W�����v���[�V����
	void JumpAnimation();
	// ���n���[�V����
	void LandingAnimation();
	// �F�ւ��A�j���[�V����
	void ChangeColorAnimation(const Mode& mode);
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


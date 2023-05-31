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
		eBody, // ��
		eEnd, // ���T�C�Y�p
	};

protected:
	
	// �p�[�c�̑���
	static const size_t sPartsNum_ = static_cast<size_t>(Parts::eEnd);

protected:
	
	// ���f�� (�p�[�c�̐�����)
	static std::array<YGame::Model*, sPartsNum_> spModels_;

	static YGame::Audio* spJumpSE_;
	
	static YGame::Audio* spDeadSE_;


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
	std::array<std::unique_ptr<YGame::Model::Object>, sPartsNum_> modelObjs_;
	
	// �F
	std::unique_ptr<YGame::CBColor> color_;

	// �����|�C���^
	YMath::Vector3* pDirection_ = nullptr;

	
	// ���f���p�I�u�W�F�N�g (�e���|�[�g)
	std::array<std::unique_ptr<YGame::Model::Object>, sPartsNum_> teleportModelObjs_;

	// �F
	std::unique_ptr<YGame::CBColor> teleportColor_;
	

	// ----- �A�j���[�V���� ----- //

	// �A�j���[�V�����p
	YMath::Vector3 animePos{}, animeRota{}, animeScale{};
	
	YMath::Vector3 teleportAnimePos{}, teleportAnimeRota{}, teleportAnimeScale{};

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


	// �e���|�[�g����
	bool isTeleport_ = false;

	// �e���|�[�g�^�C�}�[
	YMath::Timer teleportTim_;

	// �e���|�[�g�p�A���t�@�l�C�[�W���O
	YMath::Ease<float> teleportAlphaEas_;

	// �e���|�[�g�p�X�P�[���C�[�W���O
	YMath::Ease<float> teleportScaleEas_;


	// ���S����
	bool isDead_ = false;

	// ���S�^�C�}�[
	YMath::Timer deadTim_;


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

	bool IsEndDeadAnime() const { return deadTim_.IsEnd(); }

public:
	
	// �ړ����[�V����
	void SetActMoveAnimation(const bool isMove) { isMove_ = isMove; }
	
	// �W�����v���[�V����
	void AnimateJump();
	
	// ���n���[�V����
	void AnimateLanding();


	// �e���|�[�g���[�V����
	void AnimateTeleport();


	// ���S�A�j���[�V����
	void AnimateDead();
	
	// ���X�|�[���A�j���[�V����
	void AnimateRespawn();

	// �S�[���A�j���[�V����
	void AnimateGoal();

private:
	
	// �A�j���[�V�������Z�b�g
	void ResetAnimation();

	// �ړ��A�j���[�V����
	void UpdateMoveAnimation();
	
	// �e���|�[�g�A�j���[�V����
	void UpdateTeleportAnimation();
	
	// ���S�A�j���[�V����
	void UpdateDeadAnimation();

	// ���X�|�[���A�j���[�V����
	void UpdateRespawnAnimation();

	// �S�[���A�j���[�V����
	void UpdateGoalAnimation();

	// �������X�V
	void UpdateSmokeEmitter();

public:
	
	~PlayerDrawer() = default;
};


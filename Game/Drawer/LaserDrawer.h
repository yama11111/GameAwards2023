#pragma once
#include "IDrawer.h"
#include <array>

// ���[�U�[�`��p�R�����N���X
class LaserDrawerCommon
{

public:

	// �p�[�c�̖��O
	enum class Parts
	{
		eBase, // ���
		eCore, // �j
		eFunnel1, // �t�@���l��1
		eFunnel2, // �t�@���l��2
		eFunnel3, // �t�@���l��3
		eFunnel4, // �t�@���l��4
		eBeam, // �r�[��
		eEnd, // ���T�C�Y�p
	};

protected:

	// �p�[�c�̑���
	static const size_t sPartsNum_ = static_cast<size_t>(Parts::eEnd);

protected:

	// ----- ���[�U�[ ----- //

	// �ˏo���f�� (�p�[�c�̐�����)
	static std::array<YGame::Model*, sPartsNum_> spModels_;

	
	// ----- ���o ----- //

	// �r�[��������]�C�[�W���O
	static YMath::Ease<float> sIdleBeamRotaEase_;

	// �t�@���l��������]�C�[�W���O
	static YMath::Ease<float> sIdleFannelRotaEase_;


	// �t�@���l�����ˍ��x�C�[�W���O
	static YMath::Ease<float> sShootFannelHeightEase_;

	// �t�@���l�����ˈʒu�W���C�[�W���O
	static YMath::Ease<float> sShootFannelPosFactorEase_;

	// �t�@���l�����ˉ�]�C�[�W���O
	static YMath::Ease<float> sShootFannelRotaEase_;

public:

	/// <summary>
	/// �ÓI������
	/// </summary>
	static void StaticInitialize();

public:

	virtual ~LaserDrawerCommon() = default;
};

// ���[�U�[�`��p�N���X
class LaserDrawer :
	private IDrawer,
	private LaserDrawerCommon
{

private:

	// ------ �I�u�W�F�N�g ------ // 

	// ���f���p�I�u�W�F�N�g (�q)
	std::array<std::unique_ptr<YGame::Model::Object>, sPartsNum_> modelObjs_;

	// �����|�C���^
	float* pLength_ = nullptr;


	// ----- ���o ----- //

	// �����Ă��邩
	bool isAct_ = false;

	// �t�@���l���ʒu (�A�j���p)
	std::array<YMath::Vector3, 4> animeFunnelPoss_;

	// �r�[����] (�A�j���p)
	YMath::Vector3 animeFunnelRota_;

	// �r�[���ʒu (�A�j���p)
	YMath::Vector3 animeBeamPos_;

	// �r�[����] (�A�j���p)
	YMath::Vector3 animeBeamRota_;

	// �r�[���傫�� (�A�j���p)
	YMath::Vector3 animeBeamSca_;


	// �������[�V��������
	bool isIdle_ = false;

	// �������[�V�����p�^�C�}�[
	YMath::Timer idleTimer_;


	// ���˂�����
	bool isShooted_ = false;

	// ���˃C�[�W���O�p�^�C�}�[
	YMath::Timer shootTimer_;

	// �r�[�����ˑ傫���C�[�W���O
	YMath::Ease<YMath::Vector3> shootBeamScaEase_;

public:

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="pParent"> : �e�|�C���^ (���̍s��ɒǏ]����)</param>
	/// <param name="pLength"> : �����|�C���^</param>
	void Initialize(YGame::Transform* pParent, float* pLength);

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
	
	/// <summary>
	/// ���˃A�j���[�V����
	/// </summary>
	void AnimateShoot();

private:

	/// <summary>
	/// �������[�V�����X�V
	/// </summary>
	void UpdateIdleAnimation();

	/// <summary>
	/// ���˃A�j���[�V�����X�V
	/// </summary>
	void UpdateShootAnimation();

public:

	~LaserDrawer() = default;
};


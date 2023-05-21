#pragma once
#include "IDrawer.h"
#include <array>

// �΂˕`��p�R�����N���X
class SpringDrawerCommon
{

public:

	// �p�[�c�̖��O
	enum class Parts
	{
		eBase, // ���
		eCore, // �j
		eTopCore, // ��j
		eTopShell, // ��k
		eBottomCore, // ���j
		eBottomShell, // ���k
		eEnd, // ���T�C�Y�p
	};

protected:

	// �p�[�c�̑���
	static const size_t sPartsNum_ = static_cast<size_t>(Parts::eEnd);
	
	// �ւ����̐�
	static const size_t sRingNum_ = 2;

protected:

	// ----- �u���b�N ----- //

	// ���f�� (�p�[�c�̐�����)
	static std::array<YGame::Model*, sPartsNum_> spModels_;

	// ----- �A�j���[�V���� ----- //

	// ���������C�[�W���O
	static std::array<YMath::Ease<float>, sRingNum_> sIdleHeightEases_;
	
	// ������]�X�s�[�h�C�[�W���O
	static YMath::Ease<float> sIdleRotaSpeedEase_;


	// �W�����v�\�����썂���C�[�W���O
	static YMath::Ease<float> sJumpAnticipationHeightEase_;
	
	// �W�����v�����C�[�W���O
	static std::array<YMath::Ease<float>, sRingNum_> sJumpHeightEases_;

	// �W�����v�\������傫���C�[�W���O
	static YMath::Ease<YMath::Vector3> sJumpAnticipationScaleEase_;

	// �W�����v�傫���C�[�W���O
	static std::array<YMath::Ease<YMath::Vector3>, sRingNum_> sJumpScaleEases_;

public:

	/// <summary>
	/// �ÓI������
	/// </summary>
	static void StaticInitialize();

public:

	virtual ~SpringDrawerCommon() = default;
};

// �΂˕`��p�N���X
class SpringDrawer :
	private IDrawer,
	private SpringDrawerCommon
{

private:

	// ------ �I�u�W�F�N�g ------ // 

	// ���f���p�I�u�W�F�N�g (�q)
	std::array<std::unique_ptr<YGame::Model::Object>, sPartsNum_> modelObjs_;

	// ----- ���o ----- //

	// �����Ă��邩
	bool isAct_ = false;


	// �ʒu (�A�j���p)
	std::array<YMath::Vector3, sRingNum_> animePoss_;

	// ��] (�A�j���p)
	std::array<YMath::Vector3, sRingNum_> animeRotas_;

	// �傫�� (�A�j���p)
	std::array<YMath::Vector3, sRingNum_> animeScales_;


	// �������[�V������
	bool isIdle_ = false;

	// �����^�C�}�[
	YMath::Timer idleTimer_;


	// �����������[�V������
	bool isIdleHeight_ = false;
	
	// ���������������O�����[�V�����J�n���邩
	bool isIdleHeightBottomStart_ = false;
	
	// �����p���[
	std::array<YMath::Power, sRingNum_> idlePowers_;

	// �����p���[�X�C�b�`
	std::array<bool, sRingNum_> isIdlePowerSwitches_;


	// �W�����v������
	bool isJumped_ = false;
	
	// �W�����v�\������p���[
	YMath::Power jumpAnticipationPower_;

	// �W�����v�\������p���[�X�C�b�`
	bool isJumpedAnticipationSwitch_ = false;
	
	// �W�����v�p���[
	std::array<YMath::Power, sRingNum_> jumpPowers_;
	
	// �W�����v�p���[�X�C�b�`
	bool isJumpedSwitch_ = false;

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

public:

	/// <summary>
	/// �W�����v
	/// </summary>
	void AnimateJump();

private:

	/// <summary>
	/// �������[�V�����X�V
	/// </summary>
	void UpdateIdle();

	/// <summary>
	/// �W�����v�A�j���[�V�����X�V
	/// </summary>
	void UpdateJump();

public:

	~SpringDrawer() = default;
};


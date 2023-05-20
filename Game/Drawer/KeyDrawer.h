#pragma once
#include "IDrawer.h"
#include <array>

// ���`��p�R�����N���X
class KeyDrawerCommon
{

public:

	// �p�[�c�̖��O
	enum class Parts
	{
		eBlade, // �n
		eRingCore, // �����O�j
		eRingShell, // �����O�k
		eEnd, // ���T�C�Y�p
	};

protected:

	// �p�[�c�̑���
	static const size_t sPartsNum_ = static_cast<size_t>(Parts::eEnd);

	// �p�[�c�Z�b�g�̐�
	static const size_t sSetNum_ = 2;

protected:

	// ----- �� ----- //

	// ���f�� (�p�[�c�̐�����)
	static std::array<YGame::Model*, sPartsNum_> spModels_;

	// ----- �A�j���[�V���� ----- //
	
	// ���������C�[�W���O
	static YMath::Ease<float> sIdleHeightEase_;


public:

	/// <summary>
	/// �ÓI������
	/// </summary>
	static void StaticInitialize();

public:

	virtual ~KeyDrawerCommon() = default;
};

// ���`��p�N���X
class KeyDrawer :
	private IDrawer,
	private KeyDrawerCommon
{

private:

	// ------ �I�u�W�F�N�g ------ // 

	// ���f���p�I�u�W�F�N�g (�q)
	std::array<std::unique_ptr<YGame::Model::Object>, sPartsNum_> modelObjs_;


	// ----- ���o ----- //

	// �����Ă��邩
	bool isAct_ = false;


	// �n�ʒu (�A�j���p)
	YMath::Vector3 animeBladePos_;
	

	// �����O�ʒu (�A�j���p)
	YMath::Vector3 animeRingPos_;

	// �����O��] (�A�j���p)
	YMath::Vector3 animeRingRota_;
	

	// �������[�V������
	bool isIdle_ = false;

	// ���������p���[
	std::array<YMath::Power, sSetNum_> idlePowers_;

	// ���������p���[�X�C�b�`
	std::array<bool, sSetNum_> isIdlePowerSwitches_;


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



private:

	/// <summary>
	/// �������[�V�����X�V
	/// </summary>
	void UpdateIdleAnimation();

public:

	~KeyDrawer() = default;
};

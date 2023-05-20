#pragma once
#include "IDrawer.h"
#include <array>

// �X�C�b�`�`��p�R�����N���X
class SwitchDrawerCommon
{

public:

	// �p�[�c�̖��O
	enum class Parts
	{
		eBaseOnCore, // ����I���j
		eBaseOnShell, // ����I���k
		eBaseOffCore, // ����I�t�j
		eBaseOffShell, // ����I�t�k
		eLeverCore, // ���o�[�j
		eLeverShell, // ���o�[�k
		eEnd, // ���T�C�Y�p
	};

	// ���
	enum class Type
	{
		eGreen, // ��
		eRed, // ��
		eEnd, // ���T�C�Y�p
	};

protected:

	// �p�[�c�̑���
	static const size_t sPartsNum_ = static_cast<size_t>(Parts::eEnd);

protected:

	// ----- �X�C�b�` ----- //

	// ���f�� (�p�[�c�̐�����)
	static std::array<YGame::Model*, sPartsNum_> spModels_;

	
	// ----- �A�j���[�V���� ----- //

	// �X�C�b�`�I����]�X�s�[�h�C�[�W���O
	static YMath::Ease<float> sSwitchOnRotaSpeedEase_;

public:

	/// <summary>
	/// �ÓI������
	/// </summary>
	static void StaticInitialize();

public:

	virtual ~SwitchDrawerCommon() = default;
};

// �X�C�b�`�`��p�N���X
class SwitchDrawer :
	private IDrawer,
	private SwitchDrawerCommon
{

private:

	// ------ �I�u�W�F�N�g ------ // 

	// ���f���p�I�u�W�F�N�g (�q)
	std::array<std::unique_ptr<YGame::Model::Object>, sPartsNum_> modelObjs_;

	// ���
	Type type_ = Type::eGreen;

	// ��ރC���f�b�N�X
	size_t typeIndex_ = 0;
	
	
	// ----- ���o ----- //

	// �����Ă��邩
	bool isAct_ = false;

	// ����ʒu (�A�j���p)
	YMath::Vector3 animeBasePos_;
	

	// ���o�[�ʒu (�A�j���p)
	YMath::Vector3 animeLeverPos_;

	// ���o�[��] (�A�j���p)
	YMath::Vector3 animeLeverRota_;


	// �X�C�b�`�I����
	bool isSwitchOn_ = false;

	// �X�C�b�`�I���p���[
	YMath::Power switchOnPower_;

public:

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="pParent"> : �e�|�C���^ (���̍s��ɒǏ]����)</param>
	/// <param name="Type"> : ���</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="BlockDrawerCommon::Type::eGreen"> : ��</param>
	/// <param name="BlockDrawerCommon::Type::eRed"> : ��</param>
	void Initialize(YGame::Transform* pParent, const Type& type);

	/// <summary>
	/// ���Z�b�g (���g����������)
	/// </summary>
	/// <param name="Type"> : ���</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="BlockDrawerCommon::Type::eGreen"> : ��</param>
	/// <param name="BlockDrawerCommon::Type::eRed"> : ��</param>
	void Reset(const Type& type);

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
	/// �X�C�b�`
	/// </summary>
	/// <param name="isSwitchOn"> : ��������</param>
	void AnimateSwitch(const bool isSwitchOn);

private:

	/// <summary>
	/// �X�C�b�`�A�j���[�V����
	/// </summary>
	void UpdateSwitchAnimation();

public:

	~SwitchDrawer() = default;
};

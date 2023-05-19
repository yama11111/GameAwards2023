#pragma once
#include "IDrawer.h"
#include <array>

// �ڍ����`��p�R�����N���X
class JunctionDrawerCommon
{

public:

	// �p�[�c�̖��O
	enum class Parts
	{
		eCore, // �j
		eShell, // �k
		eEnd, // ���T�C�Y�p
	};

	// ���
	enum class Type
	{
		eGreen, // ��
		eEnd, // ���T�C�Y�p
	};

protected:

	// �p�[�c�̑���
	static const size_t sPartsNum_ = static_cast<size_t>(Parts::eEnd);

	// ��ނ̑���
	static const size_t sTypeNum_ = static_cast<size_t>(Type::eEnd);

	// �g�̑���
	static const size_t sFrameNum_ = 3;

protected:

	// ----- �ڍ��� ----- //

	// ���f�� (�p�[�c�̐�����)
	static std::array<std::array<YGame::Model*, sPartsNum_>, sTypeNum_> spModels_;

	// ----- �A�j���[�V���� ----- //

	// ������]�X�s�[�h�C�[�W���O
	static YMath::Ease<float> sIdleRotaSpeedEase_;


	// �ڑ��ʒu�W���C�[�W���O
	static YMath::Ease<float> sConnectPosFactorEase_;

	// �ڑ��ʒu�W���C�[�W���O
	static YMath::Ease<float> sConnectRotaFactorEase_;

	// �ڑ���]�X�s�[�h�C�[�W���O
	static YMath::Ease<float> sConnectRotaSpeedEase_;

	// �ڑ��傫���C�[�W���O
	static YMath::Ease<YMath::Vector3> sConnectScaleEase_;

public:

	/// <summary>
	/// �ÓI������
	/// </summary>
	static void StaticInitialize();

public:

	virtual ~JunctionDrawerCommon() = default;
};

// �ڍ����`��p�N���X
class JunctionDrawer :
	private IDrawer,
	private JunctionDrawerCommon
{

private:

	// ------ �I�u�W�F�N�g ------ // 

	// ���f���p�I�u�W�F�N�g (�q)
	std::array<std::array<std::unique_ptr<YGame::Model::Object>, sPartsNum_>, sFrameNum_> modelObjs_;

	// ����
	YMath::Vector3 direction_;

	// ���
	Type type_ = Type::eGreen;

	// ��ރC���f�b�N�X
	size_t typeIndex_ = 0;

	// �ڑ���
	JunctionDrawer* pPartner_ = nullptr;

	// ----- ���o ----- //

	// �����Ă��邩
	bool isAct_ = false;

	
	// �ʒu (�A�j���p)
	std::array<YMath::Vector3, sFrameNum_> animePoss_;
	
	// ��] (�A�j���p)
	std::array<YMath::Vector3, sFrameNum_> animeRotas_;
	
	// �傫�� (�A�j���p)
	std::array<YMath::Vector3, sFrameNum_> animeScales_;


	// �������[�V������
	bool isIdle_ = false;

	// �����^�C�}�[
	std::array<YMath::Timer, sFrameNum_> idleTimers_;


	// �ڑ�������
	bool isConnected_ = false;

	// �ڑ��^�C�}�[
	YMath::Timer connectTimer_;


	// �������킹�^�C�}�[
	YMath::Timer alignDirectionTimer_;

	// �������킹�C�[�W���O
	YMath::Ease<YMath::Vector3> alignDirectionEase_;

public:

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="pParent"> : �e�|�C���^ (���̍s��ɒǏ]����)</param>
	/// <param name="direction"> : ����</param>
	/// <param name="Type"> : ���</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="BlockDrawerCommon::Type::eBlack"> : ��</param>
	/// <param name="BlockDrawerCommon::Type::eWhite"> : ��</param>
	void Initialize(YGame::Transform* pParent, const YMath::Vector3& direction, const Type& type);

	/// <summary>
	/// ���Z�b�g (���g����������)
	/// </summary>
	/// <param name="direction"> : ����</param>
	/// <param name="Type"> : ���</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="BlockDrawerCommon::Type::eBlack"> : ��</param>
	/// <param name="BlockDrawerCommon::Type::eWhite"> : ��</param>
	void Reset(const YMath::Vector3& direction, const Type& type);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private:

	/// <summary>
	/// �ڑ���ݒ�
	/// </summary>
	/// <param name="pPartner"> : �ڑ���̃|�C���^</param>
	void SetPartner(JunctionDrawer* pPartner);

	/// <summary>
	/// �����擾
	/// </summary>
	/// <returns> : ����</returns>
	YMath::Vector3 GetDirection();

public:
	
	/// <summary>
	/// �ڑ�
	/// </summary>
	/// <param name="pPartner"> : �ڑ���̃|�C���^</param>
	void AnimateConnection(JunctionDrawer* pPartner);

private:

	/// <summary>
	/// �������[�V�����X�V
	/// </summary>
	void UpdateIdleAnimation();

	/// <summary>
	/// �ڑ����[�V�����X�V
	/// </summary>
	void UpdateConnectAnimation();

public:

	~JunctionDrawer() = default;
};


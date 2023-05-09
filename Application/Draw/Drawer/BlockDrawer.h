#pragma once
#include "IDrawer.h"
#include "IMode.h"
#include <array>

// �u���b�N�`��p�R�����N���X
class BlockDrawerCommon
{

public:

	// �p�[�c�̖��O
	enum class Parts
	{
		Core, // �j
		Shell, // �k
	};

protected:

	// �p�[�c�̑���
	static const size_t PartsNum_ = 2;

protected:

	// ----- �u���b�N ----- //

	// ���f�� (�p�[�c�̐�����)
	static std::array<std::array<YGame::Model*, PartsNum_>, IMode::sTypeNum_> spModels_;

	// �k���s�F
	static std::unique_ptr<YGame::Color> sFailShellColor_;


	// ----- �O���b�h ----- //

	// �O���b�h���f��
	static YGame::Model* spGridModel_;

	// �O���b�h�F
	static std::unique_ptr<YGame::Color> sGridColor_;
	
	// �O���b�h���s�F
	static std::unique_ptr<YGame::Color> sFailGridColor_;

	// �O���b�h�}�e���A��
	static std::unique_ptr<YGame::Material> sGridMate_;


	// �擾���傫���C�[�W���O
	static YMath::Ease<float> sCatchGridScaleValueEas_;

	// �擾���s���傫���C�[�W���O
	static YMath::Ease<float> sFailToCatchGridScaleValueEas_;

	// �ݒu���傫���C�[�W���O
	static YMath::Ease<float> sPlaceGridScaleValueEas_;

	// �ݒu���s���傫���C�[�W���O
	static YMath::Ease<float> sFailToPlaceGridScaleValueEas_;

public:

	/// <summary>
	/// �ÓI������
	/// </summary>
	/// <param name="pCoreColors"> : �j�F�|�C���^�z��</param>
	/// <param name="pCoreMate"> : �j�}�e���A���|�C���^</param>
	static void StaticInitialize();

public:

	virtual ~BlockDrawerCommon() = default;
};

// �u���b�N�`��p�N���X
class BlockDrawer :
	private IDrawer,
	private IMode,
	private BlockDrawerCommon
{

private:

	// ------ �I�u�W�F�N�g ------ // 

	// ���f���p�I�u�W�F�N�g (�q)
	std::array<std::unique_ptr<YGame::Model::Object>, PartsNum_> modelObjs_;

	// �O���b�h���f���p�I�u�W�F�N�g
	std::unique_ptr<YGame::Model::Object> gridObj_;

	// ----- �A�j���[�V���� ----- //

	// ���s�p�V�F�C�N
	YMath::Shake failureShake_;


	// �O���b�h����t���O
	bool isActGrid_ = false;


	// �擾�\��Ԃ�
	bool isCanCatch_ = false;

	// �O�͎擾�\��Ԃ�������
	bool isElderCanCatch_ = false;


	// �擾�A�j���[�V���������邩
	bool isActCatchAnimition_ = false;

	// �擾���C�[�W���O�p�^�C�}�[
	YMath::Timer catchGridTim_;

	// �擾���s�A�j���[�V���������邩
	bool isActFailToCatchAnimition_ = false;

	// �擾���s���C�[�W���O�p�^�C�}�[
	YMath::Timer failToCatchGridTim_;


	// �u�����Ԃ�
	bool isCanPlace_ = false;

	// �O�͒u�����Ԃ�������
	bool isElderCanPlace_ = false;


	// �ݒu�A�j���[�V���������邩
	bool isActPlaceAnimition_ = false;

	// �ݒu���C�[�W���O�p�^�C�}�[
	YMath::Timer placeGridTim_;

	// �ݒu���s�A�j���[�V���������邩
	bool isActFailToPlaceAnimition_ = false;

	// �ݒu���s���C�[�W���O�p�^�C�}�[
	YMath::Timer failToPlaceGridTim_;

public:

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="pParent"> : �e�|�C���^ (���̍s��ɒǏ]����)</param>
	/// <param name="modeType"> : ���</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="IMode::Type::Noraml"> : �ʏ���</param>
	/// <param name="IMode::Type::Movable"> : �����</param>
	void Initialize(YGame::Transform* pParent, const IMode::Type& modeType);

	/// <summary>
	/// ���Z�b�g (���g����������)
	/// </summary>
	/// <param name="modeType"> : ���</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="IMode::Type::Noraml"> : �ʏ���</param>
	/// <param name="IMode::Type::Movable"> : �����</param>
	void Reset(const IMode::Type& modeType);

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
	/// �t�B���^�[�Ŏ擾�\���ݒ�
	/// </summary>
	/// <param name="isCanCatch"> : �擾�\��Ԃ�</param>
	void SetIsCanCatch(const bool isCanCatch) { isCanCatch_ = isCanCatch; }

	/// <summary>
	/// �擾�A�j���[�V����
	/// </summary>
	void CatchAnimation();

	/// <summary>
	/// �擾�ł��Ȃ��A�j���[�V����
	/// </summary>
	void FailToCatchAnimation();


	/// <summary>
	/// �u���邩�ݒ�
	/// </summary>
	/// <param name="isCanPlace"> : �u���邩</param>
	void SetIsCanPlace(const bool isCanPlace) { isCanPlace_ = isCanPlace; }

	/// <summary>
	/// �ݒu�A�j���[�V����
	/// </summary>
	void PlaceAnimation();

	/// <summary>
	/// �ݒu�ł��Ȃ��A�j���[�V����
	/// </summary>
	void FailToPlaceAnimation();

private:

	/// <summary>
	/// �擾�\�A�j���[�V����
	/// </summary>
	void CanCatchAnimation();

	/// <summary>
	/// �u���Ȃ���ԃA�j���[�V����
	/// </summary>
	void NotPlaceAnimation();

	/// <summary>
	/// �������[�V����
	/// </summary>
	void IdleAnimation() override;

public:

	~BlockDrawer() = default;
};


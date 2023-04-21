#pragma once
#include "IDrawer.h"
#include <array>

// �u���b�N�`��p�R�����N���X
class BlockDrawerCommon
{

public:
	
	// �p�[�c�̖��O
	enum class Parts
	{
		Cube, // ������
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
	
	/// <summary>
	/// �ÓI������
	/// </summary>
	/// <param name="pVP"> : �r���[�v���W�F�N�V�����|�C���^</param>
	static void StaticInitialize(YGame::ViewProjection* pVP);

public:
	
	virtual ~BlockDrawerCommon() = default;
};

// �u���b�N�`��p�N���X
class BlockDrawer :
	private IDrawer, 
	private BlockDrawerCommon
{

private:

	// ----- �I�u�W�F�N�g ----- // 

	// ���f���p�I�u�W�F�N�g (�q)
	std::array<std::unique_ptr<YGame::ModelObject>, PartsNum_> modelObjs_;

	// �F
	std::unique_ptr<YGame::Color> color_;

	// ----- �A�j���[�V����	 ----- //

	// �擾�\��Ԃ�
	bool isRetrievable_ = false;

	// �O�͎擾�\��Ԃ�������
	bool isElderRetrievable_ = false;

	// �擾�\�A�j���[�V�����p�^�C�}�[
	YMath::Timer RetrievableTim_;


	// �u�����Ԃ�
	bool isCanPlace_ = false;

	// �O�͒u�����Ԃ�������
	bool isElderCanPlace_ = false;


	// �u���Ȃ��������p�V�F�C�N
	YMath::Shake notPlaceShake_;

public:
	
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="pParent"> : �e�|�C���^ (���̍s��ɒǏ]����)</param>
	/// <param name="mode"> : ���</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="Mode::Noraml"> : �ʏ���</param>
	/// <param name="Mode::Red"> : �ԐF���</param>
	/// <param name="Mode::Invisible"> : �������</param>
	/// <param name="Mode::None"> : ���� (�g��Ȃ�)</param>
	void Initialize(YGame::Transform* pParent, const Mode& mode);
	
	/// <summary>
	/// ���Z�b�g (���g����������)
	/// </summary>
	/// <param name="mode"> : ���</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="Mode::Noraml"> : �ʏ���</param>
	/// <param name="Mode::Red"> : �ԐF���</param>
	/// <param name="Mode::Invisible"> : �������</param>
	/// <param name="Mode::None"> : ���� (�g��Ȃ�)</param>
	void Reset(const Mode& mode);

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
	/// �擾�\��Ԃ��ݒ�
	/// </summary>
	/// <param name="isRetrievable"> : �擾�\��Ԃ�</param>
	void SetIsRetrievable(const bool isRetrievable) { isRetrievable_ = isRetrievable; }

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
	void CanNotPlaceAnimation();

private:

	/// <summary>
	/// �擾�\�A�j���[�V����
	/// </summary>
	void RetrievableAnimation();

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


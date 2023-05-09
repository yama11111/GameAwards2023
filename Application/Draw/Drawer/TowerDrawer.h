#pragma once
#include "IMode.h"
#include "Model.h"

// �^���[�`��p�R�����N���X
class TowerDrawerCommon
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
	
	// ���f�� (�p�[�c�̐�����)
	static std::array<std::array<YGame::Model*, PartsNum_>, IMode::sTypeNum_> spModels_;
	
	// �r���[�v���W�F�N�V�����|�C���^
	static YGame::ViewProjection* spVP_;

	// �}�e���A���|�C���^
	static YGame::Material* spMate_;

public:

	/// <summary>
	/// �ÓI������
	/// </summary>
	/// <param name="pVP"> : �r���[�v���W�F�N�V�����|�C���^</param>
	/// <param name="pMate"> : �}�e���A���|�C���^</param>
	/// <param name="pCoreColors"> : �j�F�|�C���^�z��</param>
	/// <param name="pCoreMate"> : �j�}�e���A���|�C���^</param>
	static void StaticInitialize(YGame::ViewProjection* pVP, YGame::Material* pMate);

public:
	
	virtual ~TowerDrawerCommon() = default;

};

// �^���[�`��p�N���X
class TowerDrawer :
	private IMode,
	private TowerDrawerCommon
{

private:
	
	// �j
	std::unique_ptr<YGame::Transform> core_;
	
	// ���f���p�I�u�W�F�N�g (�q)
	std::array<std::unique_ptr<YGame::Model::Object>, PartsNum_> modelObjs_;

public:
	
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="pParent"> : �e�|�C���^ (���̍s��ɒǏ]����)</param>
	/// <param name="modeType"> : ���</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="IMode::Type::Noraml"> : �ʏ���</param>
	/// <param name="IMode::Type::Movable"> : �����</param>
	void Initialize(YMath::Matrix4* pParent, const IMode::Type& modeType);

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
	/// <param name="location"> : �`��ꏊ</param>
	void Draw(const YGame::DrawLocation& location);

private:

};


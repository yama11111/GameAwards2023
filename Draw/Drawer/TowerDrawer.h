#pragma once
#include "Model.h"
#include "Lerp.h"
#include "Timer.h"
#include "Power.h"
#include <array>
#include <memory>

// �^���[�`��p�R�����N���X
class TowerDrawerCommon
{

public:
	
	// ���
	enum class Mode
	{
		Normal, // �ʏ�
		Red, // ��
	};
	
	// �p�[�c�̖��O
	enum class Parts
	{
		Core, // �j
		Shell, // �k
	};

protected:

	// ���[�h�̐�
	static const size_t ModeNum_ = 2;
	
	// �p�[�c�̑���
	static const size_t PartsNum_ = 2;

protected:
	
	// ���f�� (�p�[�c�̐�����)
	static std::array<std::array<YGame::Model*, PartsNum_>, ModeNum_> spModels_;
	
	// �r���[�v���W�F�N�V�����|�C���^
	static YGame::ViewProjection* spVP_;

	// �}�e���A���|�C���^
	static YGame::Material* spMate_;


	// �j�F
	static std::array<std::unique_ptr<YGame::Color>, ModeNum_> sCoreColor_;

	// �j�}�e���A��
	static std::unique_ptr<YGame::Material> sCoreMate_;


	// �j�F�p�p���[
	static YMath::Power coreColorPow_;

	// �j�F�p���[�X�C�b�`
	static bool isSwitchCoreColorPower_;

	// �j�F�C�[�W���O
	static std::array<YMath::Ease<YMath::Vector4>, ModeNum_> coreColorEas_;

public:

	/// <summary>
	/// �ÓI������
	/// </summary>
	/// <param name="pVP"> : �r���[�v���W�F�N�V�����|�C���^</param>
	/// <param name="pMate"> : �}�e���A���|�C���^</param>
	static void StaticInitialize(YGame::ViewProjection* pVP, YGame::Material* pMate);

	/// <summary>
	/// �ÓI���Z�b�g
	/// </summary>
	static void StaticReset();

	/// <summary>
	/// �ÓI�X�V
	/// </summary>
	static void StaticUpdate();

public:
	
	virtual ~TowerDrawerCommon() = default;

};

// �^���[�`��p�N���X
class TowerDrawer :
	private TowerDrawerCommon
{
private:
	
	// �j
	std::unique_ptr<YGame::Transform> core_;
	
	// ���f���p�I�u�W�F�N�g (�q)
	std::array<std::unique_ptr<YGame::ModelObject>, PartsNum_> modelObjs_;
	

	// ���
	Mode mode_ = Mode::Normal;

	// ��Ԕԍ�
	size_t modeIdx_ = 0;

public:
	
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="pParent"> : �e�s��|�C���^ (���̍s��ɒǏ]����)</param>
	/// <param name="mode"> : ���</param>
	void Initialize(YMath::Matrix4* pParent, const Mode& mode);
	
	/// <summary>
	/// ���Z�b�g
	/// </summary>
	/// <param name="mode"> : ���</param>
	void Reset(const Mode& mode);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private:

};


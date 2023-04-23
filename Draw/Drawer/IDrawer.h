#pragma once
#include "ParticleManager.h"
#include "SlimeActor.h"
#include "Camera.h"
#include <memory>

// �`����N���X
class IDrawer : protected YGame::SlimeActor
{
public:
	
	// ���
	enum class Mode
	{
		Normal	  = 0, // �ʏ�
		Red		  = 1, // ��
	};
	
protected:

	// �g�����X�t�H�[�� 
	std::unique_ptr<YGame::Transform> core_;
	
	// �e�|�C���^
	YGame::Transform* pParent_ = nullptr;
	
	// �������[�V�����p�^�C�}�[
	YMath::Timer idleTim_;

private:
	
	// ���݂̏��
	Mode current_ = Mode::Normal;

	// ���݂̏�Ԕԍ�
	size_t currentIdx_ = 0;

protected:

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="pParent"> : �e�g�����X�t�H�[��</param>
	/// <param name="mode"> : ���݂̏��</param>
	/// <param name="intervalTime"> : �������[�V�����̊Ԋu</param>
	void Initialze(YGame::Transform* pParent, const Mode& mode, const UINT intervalTime);

	/// <summary>
	/// ���Z�b�g
	/// </summary>
	/// <param name="mode"> : ���݂̏��</param>
	void Reset(const Mode& mode);

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="status"></param>
	void Update(const YGame::Transform::Status& status);

protected:

	/// <summary>
	/// �������[�V����
	/// </summary>
	virtual void IdleAnimation() = 0;

protected:
	
	/// <summary>
	/// ���݂̏�Ԕԍ��擾
	/// </summary>
	/// <returns>���݂̏�Ԕԍ�</returns>
	size_t CurrentModeIndex() { return currentIdx_; }
	
	/// <summary>
	/// ���݂̏�Ԏ擾
	/// </summary>
	/// <returns>���݂̏��</returns>
	Mode CurrentMode() { return current_; }

	/// <summary>
	/// ��ԕύX
	/// </summary>
	/// <param name="mode"> : ���</param>
	void ChangeMode(const Mode& mode);

protected:
	
	// �r���[�v���W�F�N�V�����|�C���^
	static YGame::ViewProjection* spVP_;

	// �}�e���A���|�C���^
	static YGame::Material* spMate_;

	// �ÓI�J�����|�C���^
	static YGame::Camera* spCamera_;

	// �ÓI�p�[�e�B�N���}�l�[�W���[�|�C���^
	static YGame::ParticleManager* spParticleMan_;

public:

	/// <summary>
	/// �ÓI������
	/// </summary>
	/// <param name="pVP"> : �r���[�v���W�F�N�V�����|�C���^</param>
	/// <param name="pMate"> : �}�e���A���|�C���^</param>
	/// <param name="pCamera"> : �J�����|�C���^</param>
	/// <param name="pParticleMan"> : �p�[�e�B�N���}�l�[�W���[�|�C���^</param>
	static void StaticInitialize(
		YGame::ViewProjection* pVP, 
		YGame::Material* pMate, 
		YGame::Camera* pCamera, 
		YGame::ParticleManager* pParticleMan);

public:
	
	virtual ~IDrawer() = default;
};


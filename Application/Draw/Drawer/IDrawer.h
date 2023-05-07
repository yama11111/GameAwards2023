#pragma once
#include "ParticleManager.h"
#include "SlimeActor.h"
#include "Camera.h"
#include <memory>

// �`����N���X
class IDrawer : protected YGame::SlimeActor
{

protected:

	// �g�����X�t�H�[�� 
	std::unique_ptr<YGame::Transform> core_;
	
	// �e�|�C���^
	YGame::Transform* pParent_ = nullptr;
	
	// �������[�V�����p�^�C�}�[
	YMath::Timer idleTim_;

protected:

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="pParent"> : �e�g�����X�t�H�[��</param>
	/// <param name="intervalTime"> : �������[�V�����̊Ԋu</param>
	void Initialze(YGame::Transform* pParent, const UINT intervalTime);

	/// <summary>
	/// ���Z�b�g
	/// </summary>
	void Reset();

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


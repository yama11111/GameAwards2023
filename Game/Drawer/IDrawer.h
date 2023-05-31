#pragma once
#include "ParticleManager.h"
#include "SlimeActor.h"
#include "Camera.h"
#include "Audio.h"
#include <memory>

// �`����N���X
class IDrawer : protected YGame::SlimeActor
{

protected:

	// �g�����X�t�H�[�� 
	std::unique_ptr<YGame::Transform> core_;
	
	// �e�|�C���^
	YGame::Transform* pParent_ = nullptr;

protected:

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="pParent"> : �e�g�����X�t�H�[��</param>
	void Initialze(YGame::Transform* pParent);

	/// <summary>
	/// ���Z�b�g
	/// </summary>
	void Reset();

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="status"></param>
	void Update(const YGame::Transform::Status& status);

	/// <summary>
	/// �y�A�����g����Ă��邩�擾
	/// </summary>
	/// <returns>�y�A�����g����Ă��邩</returns>
	bool GetIsParented() { return pParent_ != nullptr; }

protected:
	
	// �r���[�v���W�F�N�V�����|�C���^
	static YGame::ViewProjection* spVP_;

	// �}�e���A���|�C���^
	static YGame::CBMaterial* spMate_;

	// �����|�C���^
	static YGame::CBLightGroup* spLightGroup_;

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
	/// <param name="pLightGroup"> : �����|�C���^</param>
	/// <param name="pCamera"> : �J�����|�C���^</param>
	/// <param name="pParticleMan"> : �p�[�e�B�N���}�l�[�W���[�|�C���^</param>
	static void StaticInitialize(
		YGame::ViewProjection* pVP, 
		YGame::CBMaterial* pMate, 
		YGame::CBLightGroup* pLightGroup, 
		YGame::Camera* pCamera, 
		YGame::ParticleManager* pParticleMan);

public:
	
	virtual ~IDrawer() = default;
};


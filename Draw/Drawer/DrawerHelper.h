#pragma once
#include "ParticleManager.h"
#include "Camera.h"

class DrawerHelper
{

private:

	// �f�t�H���g�}�e���A��
	static std::unique_ptr<YGame::Material> sDefMate_;

	// �w�i�}�e���A��
	static std::unique_ptr<YGame::Material> sBackMate_;


	// �S�[���t���O
	static bool sIsGoal_;

public:
	
	/// <summary>
	/// �ÓI������
	/// </summary>
	/// <param name="pVP"> : �r���[�v���W�F�N�V�����|�C���^</param>
	/// <param name="pCamera"> : �J�����|�C���^</param>
	/// <param name="pParticleMan"> : �p�[�e�B�N���}�l�[�W���[�|�C���^</param>
	static void StaticInitialize(YGame::ViewProjection* pVP, YGame::Camera* pCamera, YGame::ParticleManager* pParticleMan);

	/// <summary>
	/// �ÓI���Z�b�g
	/// </summary>
	static void StaticReset();

	/// <summary>
	/// �ÓI�X�V
	/// </summary>
	static void StaticUpdate();

public:

	/// <summary>
	/// �S�[��
	/// </summary>
	static void StaticGoal() { sIsGoal_ = true; }

};


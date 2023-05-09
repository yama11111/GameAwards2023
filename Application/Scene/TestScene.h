#pragma once
#include "BaseScene.h"

#include "PlayerDrawer.h"
#include "BlockDrawer.h"
#include "GateDrawer.h"
#include "GoalDrawer.h"

#include "BackgroundDrawer.h"
#include "HUDDrawer.h"

#include "EffectManager.h"
#include "ScrollCamera.h"


namespace YScene
{
	// �e�X�g�V�[��
	class TestScene : public BaseScene
	{

	private:

#pragma region ���\�[�X

#pragma endregion


#pragma region �Q�[���I�u�W�F�N�g		

		// �j
		YGame::Transform core_;

		// �v���C���[��
		bool isPlayer_ = false;

		// �v���C���[�`��N���X
		PlayerDrawer playerDra_;
		// ���� (�v���C���[�p)
		YMath::Vector3 direction_;
		// �v���C���[�`�悷�邩
		bool isDrawPlayer_ = false;

		// �u���b�N�`��N���X
		BlockDrawer blockDra_;
		// �u���b�N�`�悷�邩
		bool isDrawBlock_ = false;
		// �A�j���[�V�����p�t���O
		bool isCanCatch_ = false;
		bool isCanPlace_ = false;

		// �Q�[�g�`��N���X
		GateDrawer gateDra_;
		// �Q�[�g�`�悷�邩
		bool isDrawGate_ = false;

		// �S�[���`��N���X
		GoalDrawer goalDra_;
		// �S�[���`�悷�邩
		bool isDrawGoal_ = false;


		// �w�i
		BackgroundDrawer background_;
		// �w�i�`�悷�邩
		bool isDrawBackground_ = false;

		// HUD
		HUDDrawer hud_;
		// HUD�`�悷�邩
		bool isDrawHUD_ = false;


		// �p�[�e�B�N���}�l�[�W���[
		YGame::ParticleManager particleMan_;
		// �p�[�e�B�N���`�悷�邩
		bool isDrawParticle_ = false;

		// �G�t�F�N�g�}�l�[�W���[
		YGame::EffectManager effectMan_;
		// �G�t�F�N�g�`�悷�邩
		bool isDrawEffect_ = false;


		// �J�����ݒ�
		enum class CameraConfig
		{
			None,
			Camera1,
			ScrollCamera,
		};

		// �J�����ݒ�
		CameraConfig cameraConfig_ = CameraConfig::None;

		// �J���������p
		YGame::ViewProjection noneVP_;
		
		// �J����
		YGame::Camera camera_;
		
		// �X�N���[���J����
		YGame::ScrollCamera scrollCamera_;

		// �]���p�r���[�v���W�F�N�V����
		YGame::ViewProjection transferVP_;

#pragma endregion

	public:

		/// <summary>
		/// �ǂݍ���
		/// </summary>
		void Load() override;

		/// <summary>
		/// ������
		/// </summary>
		void Initialize() override;

		/// <summary>
		/// �I������
		/// </summary>
		void Finalize() override;

		/// <summary>
		/// �X�V
		/// </summary>
		void Update() override;

		/// <summary>
		/// �`��
		/// </summary>
		void Draw() override;

	public:

		// �R���X�g���N�^
		TestScene() = default;
		
		// �f�X�g���N�^
		~TestScene() = default;

	};
}

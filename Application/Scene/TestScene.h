#pragma once
#include "BaseScene.h"

#include "PlayerDrawer.h"
#include "BlockDrawer.h"
#include "SpringDrawer.h"
#include "JunctionDrawer.h"
#include "PlatformDrawer.h"
#include "LaserDrawer.h"
#include "KeyDrawer.h"
#include "SwitchDrawer.h"
#include "GateDrawer.h"
#include "GoalDrawer.h"

#include "BackgroundDrawer.h"
#include "HUDDrawer.h"

#include "ScrollCamera.h"

#include "Player.h"
#include "Block.h"


namespace YScene
{
	// �e�X�g�V�[��
	class TestScene : public BaseScene
	{

	private:

#pragma region ���\�[�X

#pragma endregion


#pragma region �Q�[���I�u�W�F�N�g		

		// �v���C���[
		Player player_;

		// �u���b�N
		Block block_;


		// �j
		YGame::Transform core_;


#pragma region Player

		// �v���C���[�`��N���X
		PlayerDrawer playerDra_;
		
		// ���� (�v���C���[�p)
		YMath::Vector3 direction_;
		
		// �v���C���[�`�悷�邩
		bool isDrawPlayer_ = false;

#pragma endregion


#pragma region Block

		// �u���b�N�`��N���X
		BlockDrawer blockDra_;
		
		// �u���b�N�`�悷�邩
		bool isDrawBlock_ = false;

#pragma endregion


#pragma region Sping

		// �΂˕`��N���X
		SpringDrawer springDra_;

		// �΂˕`�悷�邩
		bool isDrawSpring_ = false;

#pragma endregion


#pragma region Platform

		// �j
		YGame::Transform platform_;

		// ����`��N���X
		PlatformDrawer platformDra_;

		// ����`�悷�邩
		bool isDrawPlatform_ = false;

#pragma endregion


#pragma region Junction

		// �j
		std::array<YGame::Transform, 2> junctions_;

		// �ڍ����`��N���X
		std::array<JunctionDrawer, 2> junctionDras_;
		
		// �ڑ����`�悷�邩
		bool isDrawJunction_ = false;

#pragma endregion


#pragma region Laser

		// �j
		YGame::Transform laser_;
		
		// ����
		float length_ = 0.0f;

		// ���[�U�[�`��N���X
		LaserDrawer laserDra_;

		// ���[�U�[�`�悷�邩
		bool isDrawLaser_ = false;

#pragma endregion


#pragma region Key

		// ���`��N���X
		KeyDrawer keyDra_;

		// ���`�悷�邩
		bool isDrawKey_ = false;

#pragma endregion


#pragma region Switch

		// �X�C�b�`�`��N���X
		SwitchDrawer switchDra_;

		// �X�C�b�`�`�悷�邩
		bool isDrawSwitch_ = false;

#pragma endregion


#pragma region Gate

		// �Q�[�g�`��N���X
		GateDrawer gateDra_;
		
		// �Q�[�g�`�悷�邩
		bool isDrawGate_ = false;

#pragma endregion


#pragma region Goal

		// �S�[���`��N���X
		GoalDrawer goalDra_;
		
		// �S�[���`�悷�邩
		bool isDrawGoal_ = false;

#pragma endregion


#pragma region BackGround

		// �w�i
		BackgroundDrawer background_;
		
		// �w�i�`�悷�邩
		bool isDrawBackground_ = false;

#pragma endregion


		// HUD
		HUDDrawer hud_;
		
		// HUD�`�悷�邩
		bool isDrawHUD_ = false;


		// �p�[�e�B�N���}�l�[�W���[
		YGame::ParticleManager particleMan_;
		
		// �p�[�e�B�N���`�悷�邩
		bool isDrawParticle_ = false;


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

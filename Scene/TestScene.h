#pragma once
#include "BaseScene.h"

#include "PlayerDrawer.h"
#include "FilterDrawer.h"
#include "BlockDrawer.h"
#include "GateDrawer.h"
#include "GoalDrawer.h"

#include "Skydome.h"
#include "HUDDrawer.h"

#include "EffectManager.h"
#include "ScrollCamera.h"

namespace YScene
{
	// �e�X�g�V�[��
	class TestScene : public BaseScene
	{
	public:
#pragma region ���\�[�X

		// ----- �e�N�X�`�� ----- //

		// ----- �I�[�f�B�I ----- //

		// ----- �X�v���C�g (2D) ----- //

		// ----- �X�v���C�g (3D) ----- //

		// ----- ���f�� ----- //

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

		// �t�B���^�[�`��N���X
		FilterDrawer filterDra_;
		// �t�B���^�[�`�悷�邩
		bool isDrawFilter_ = false;

		// �u���b�N�`��N���X
		BlockDrawer blockDra_;
		// �u���b�N�`�悷�邩
		bool isDrawBlock_ = false;

		// �Q�[�g�`��N���X
		GateDrawer gateDra_;
		// �Q�[�g�`�悷�邩
		bool isDrawGate_ = false;

		// �S�[���`��N���X
		GoalDrawer goalDra_;
		// �S�[���`�悷�邩
		bool isDrawGoal_ = false;

		// �V��
		Skydome skydome_;
		// �V���`�悷�邩
		bool isDrawSkydome_ = false;

		// HUD
		HUDDrawer hud_;
		// HUD�`�悷�邩
		bool isDrawHUD_ = false;

		// �p�[�e�B�N���}�l�[�W���[
		YGame::ParticleManager particleMan_;

		// �G�t�F�N�g�}�l�[�W���[
		YGame::EffectManager effectMan_;

		// �X�N���[���J����
		YGame::ScrollCamera scrollCamera_;

		// �]���p�r���[�v���W�F�N�V����
		YGame::ViewProjection transferVP_;

#pragma endregion
	public:
		// �ǂݍ���
		void Load() override;
		// ������
		void Initialize() override;
		// �I������
		void Finalize() override;
		// �X�V
		void Update() override;
		// �`��
		void Draw() override;
	private:
		// �w�i�X�v���C�g2D�`��
		void DrawBackSprite2Ds();
		// ���f���`��
		void DrawModels();
		// �X�v���C�g3D�`��
		void DrawSprite3Ds();
		// �O�i�X�v���C�g2D�`��
		void DrawFrontSprite2Ds();
	public:
		// �R���X�g���N�^
		TestScene() = default;
		// �f�X�g���N�^
		~TestScene() = default;
	};
}

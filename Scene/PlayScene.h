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

namespace YScene
{
	// �Q�[���V�[��
	class PlayScene : public BaseScene
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

		// �v���C���[
		YGame::Transform player_;
		// ���� (�v���C���[�p)
		YMath::Vector3 direction_;
		// �v���C���[�`��N���X
		PlayerDrawer playerDra_;
		

		// �t�B���^�[
		YGame::Transform filter_;
		// �t�B���^�[�`��N���X
		FilterDrawer filterDra_;


		// �u���b�N
		YGame::Transform block_;
		// �u���b�N�`��N���X
		BlockDrawer blockDra_;


		// �Q�[�g
		YGame::Transform gate_;
		// �Q�[�g�`��N���X
		GateDrawer gateDra_;


		// �S�[��
		YGame::Transform goal_;
		// �S�[���`��N���X
		GoalDrawer goalDra_;


		// �V��
		Skydome skydome_;
		
		// HUD
		HUDDrawer hud_;

		// �p�[�e�B�N���}�l�[�W���[
		YGame::ParticleManager particleMan_;

		// �G�t�F�N�g�}�l�[�W���[
		YGame::EffectManager effectMan_;

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
		// �X�v���C�g3D�`��
		void DrawBackSprite3Ds();
		// ���f���`��
		void DrawModels();
		// �X�v���C�g3D�`��
		void DrawFrontSprite3Ds();
		// �O�i�X�v���C�g2D�`��
		void DrawFrontSprite2Ds();
	public:
		// �R���X�g���N�^
		PlayScene() = default;
		// �f�X�g���N�^
		~PlayScene() = default;
	};
}

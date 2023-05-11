#pragma once
#include "BaseScene.h"

#include "GateDrawer.h"
#include "GoalDrawer.h"

#include "BackgroundDrawer.h"
#include "HUDDrawer.h"

#include "EffectManager.h"
#include "ScrollCamera.h"
#include "StageConfig.h"

#include "Piece.h"
#include "Stage.h"
#include "BasicBlock.h"
#include "Player.h"

namespace YScene
{
	// �Q�[���V�[��
	class PlayScene : public BaseScene
	{
	
	public:

#pragma region ���\�[�X

		// �v���CBGM
		YGame::Audio* pPlayBGM_ = nullptr;

#pragma endregion

#pragma region �Q�[���I�u�W�F�N�g

		// ------------ �� �v���C�V�[���̕ϐ� �� ------------//
        Stage stage_{};
        Piece* piecePtr_{};
        Piece* piece2Ptr_{};
        Piece* piece3Ptr_{};
        Player player_{ &stage_ };
		
		// ------------ �� �v���C�V�[���̕ϐ� �� ------------//


		// �X�e�[�W�ݒ�
		StageConfig* stageConfig_ = nullptr;


		// �w�i
		BackgroundDrawer background_;

		// HUD
		HUDDrawer hud_;


		// �p�[�e�B�N���}�l�[�W���[
		YGame::ParticleManager particleMan_;

		// �J����
		YGame::Camera camera_;

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
		PlayScene() = default;

		// �f�X�g���N�^
		~PlayScene() = default;

	};
}

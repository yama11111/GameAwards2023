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

		// �v���C���[���삩
		bool isPlayer_ = true;
		

		// �v���C���[
		YGame::Transform player_;
		// ���� (�v���C���[�p)
		YMath::Vector3 direction_;
		// �v���C���[�`��N���X
		PlayerDrawer playerDra_;
		// �X�s�[�h
		YMath::Vector3 playerSpeed_{};


		// �t�B���^�[
		YGame::Transform filter_;
		// �t�B���^�[�`��N���X
		FilterDrawer filterDra_;


		// �u���b�N��
		static const size_t idx = 20;
		// �u���b�N
		std::array<YGame::Transform, idx> block_;
		// �u���b�N�`��N���X
		std::array<BlockDrawer, idx> blockDra_;


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

	private:

		/// <summary>
		/// �w�i�X�v���C�g2D�`��
		/// </summary>
		void DrawBackSprite2Ds();

		/// <summary>
		/// ���f���`��
		/// </summary>
		void DrawModels();

		/// <summary>
		/// �X�v���C�g3D�`��
		/// </summary>
		void DrawSprite3Ds();

		/// <summary>
		/// �O�i�X�v���C�g2D�`��
		/// </summary>
		void DrawFrontSprite2Ds();

	public:
		
		// �R���X�g���N�^
		PlayScene() = default;
		
		// �f�X�g���N�^
		~PlayScene() = default;

	};
}

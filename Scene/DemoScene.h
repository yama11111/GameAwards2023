#pragma once
#include "BaseScene.h"

#include "DemoPlayer.h"
#include "DemoGoal.h"
#include "MapChipManager.h"

#include "BackGroundDrawer.h"
#include "HUDDrawer.h"

namespace YScene
{
	class DemoScene : public BaseScene
	{

	private:

		// �v���C���[
		DemoPlayer player_;

		// �S�[��
		DemoGoal goal_;

		// �}�b�v�`�b�v�}�l�[�W���[
		YGame::MapChipManager mapChipMan_;


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
		DemoScene() = default;

		// �f�X�g���N�^
		~DemoScene() = default;

	};
}


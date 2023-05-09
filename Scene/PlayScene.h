#pragma once
#include "BaseScene.h"

#include "Player.h"
//#include "Pises.h"
#include "PuzzleMat.h"
#include "Block.h"
#include "GateDrawer.h"
#include "GoalDrawer.h"

#include "BackgroundDrawer.h"
#include "HUDDrawer.h"

#include "EffectManager.h"
#include "ScrollCamera.h"
#include "StageConfig.h"

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
		std::unique_ptr<Player> player;

		//// �t�B���^�[
		//std::unique_ptr<Filter> filter;
		std::unique_ptr<Pises> pises;
		//std::vector<std::unique_ptr<Pises>> piseses;

		// �v���C���[
		std::unique_ptr<PuzzleMat> puzzleMat;

		//// �X�e�[�W�ݒ�
		//StageConfig* stageConfig_;

		//int map[9][9] =
		//{
		//	{0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0},
		//};

		////��Ŏ���
		//int map1[9][9] =
		//{
		//	{1,1,1,1,1,1,1,1,1},
		//	{1,0,0,0,0,1,0,0,1},
		//	{1,1,0,0,0,0,0,0,1},
		//	{1,0,0,0,0,0,0,0,1},
		//	{1,0,0,1,0,0,0,0,1},
		//	{1,0,0,0,0,0,1,1,1},
		//	{1,0,0,0,0,0,0,0,1},
		//	{1,1,1,1,1,1,1,1,1},
		//	{1,1,1,1,1,1,1,1,1},
		//};

		//const int blockCountY = 9;
		//const int blockCountX = 9;

		//�u���b�N�i�[�p�ϐ�
		std::vector<std::unique_ptr<Block>> block;

		//���S����̏c���T�C�Y
		YMath::Vector2 RL = { 0.0f,0.0f };
		YMath::Vector2 WS = { 0.0f,0.0f };

		//���͊m�F�p
		YMath::Vector2 DS = { 0.0f,0.0f };
		YMath::Vector2 AW = { 0.0f,0.0f };

		// �S�[��
		YGame::Transform goal_;
		// �S�[���`��N���X
		GoalDrawer goalDra_;

		//��ŏ���
		bool nowMode = false;

		// �w�i
		BackgroundDrawer background_;

		// HUD
		HUDDrawer hud_;

		// �p�[�e�B�N���}�l�[�W���[
		YGame::ParticleManager particleMan_;

		// �G�t�F�N�g�}�l�[�W���[
		YGame::EffectManager effectMan_;

		// �J����
		YGame::Camera camera_;

		// �J�����̒Ǐ]�_
		YMath::Vector3 followPoint_;

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

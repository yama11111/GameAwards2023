#pragma once
#include "BaseScene.h"

//#include "PlayerDrawer.h"
#include "Player.h"
//#include "FilterDrawer.h"
#include "Filter.h"
#include "Block.h"
//#include "BlockDrawer.h"
#include "Skydome.h"
#include "EffectManager.h"

namespace YScene
{
	// �Q�[���V�[��
	class PlayScene : public BaseScene
	{
	public:
#pragma region ���\�[�X

		// ----- �e�N�X�`�� ----- //

		// ���n�摜
		UINT plainTex_ = 0;

		// ----- �I�[�f�B�I ----- //

		// ----- �X�v���C�g (2D) ----- //

		// ��ʑS��
		std::unique_ptr<YGame::Sprite2D> windowSpr_ = nullptr;

		// ----- �X�v���C�g (3D) ----- //

		// ----- ���f�� ----- //

		// �����̃��f��
		std::unique_ptr<YGame::Model> cubeMod_ = nullptr;

#pragma endregion
#pragma region �Q�[���I�u�W�F�N�g

		//�v���C���[true�A�t�B���^�[false;
		bool nowMode;

		// �v���C���[
		Player player;

		// �t�B���^�[
		Filter filter;

		// �u���b�N
		Block block[20];

		const int blockCount = 5;

		// �V��
		Skydome skydome_;

		// �p�[�e�B�N���}�l�[�W���[
		YGame::ParticleManager particleMan_;

		// �G�t�F�N�g�}�l�[�W���[
		YGame::EffectManager effectMan_;

		// �]���p�r���[�v���W�F�N�V����
		YGame::ViewProjection transferVP_;

		YMath::Vector2 RL = { 0.0f,0.0f };
		YMath::Vector2 WS = { 0.0f,0.0f };

		YMath::Vector2 DS = { 0.0f,0.0f };
		YMath::Vector2 AW = { 0.0f,0.0f };

		YMath::Vector2 filterSize = { 0.0f,0.0f };

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

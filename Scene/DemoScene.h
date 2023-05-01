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

#pragma region ���\�[�X

		// �v���CBGM
		YGame::Audio* pPlayBGM_ = nullptr;

#pragma endregion

#pragma region �Q�[���I�u�W�F�N�g

		// �v���C���[
		DemoPlayer player_;

		// �S�[��
		DemoGoal goal_;

		// �}�b�v�`�b�v�}�l�[�W���[
		YGame::MapChipManager mapChipMan_;

		
		// �S�[���t���O
		bool isGoal_ = false;

		bool isAfterglow_ = false;

		YMath::Timer goalTim_;

		YMath::Timer fontScaleTim_;

		YMath::Timer afterglowTim_;
		
		YMath::Ease<YMath::Vector3> fontScaleEas_;

		YMath::Ease<float> fontAlphaEas_;

		std::unique_ptr<YGame::Sprite2DObject> fontObj_;
		std::unique_ptr<YGame::Color> fontColor_;

		YGame::Sprite2D* fontSpr_ = nullptr;


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


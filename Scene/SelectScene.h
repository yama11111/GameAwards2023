#pragma once
#include "BaseScene.h"
#include "SelectDrawer.h"
#include "InputDrawer.h"
#include "PauseDrawer.h"
#include "Camera.h"
#include "Skydome.h"

namespace YScene
{
	// �Z���N�g�V�[��
	class SelectScene : public BaseScene
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

		// input
		InputDrawer inputDra_;
		// pause
		PauseDrawer pauseDra_;

		// �X�e�[�W�ԍ�
		int stageIdx_ = 0;

		// �X�e�[�W�Z���N�g�`��N���X
		SelectDrawer dra_;

		// �V��
		Skydome skydome_;

		// �J����
		YGame::Camera camera_;

		// �r���[�v���W�F�N�V����
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
		SelectScene() = default;
		// �f�X�g���N�^
		~SelectScene() = default;
	};
}


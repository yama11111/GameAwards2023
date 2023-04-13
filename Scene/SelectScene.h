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

		// �X�e�[�W�ݒ�
		StageConfig* stageConfig_;

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
		SelectScene() = default;
		
		// �f�X�g���N�^
		~SelectScene() = default;

	};
}


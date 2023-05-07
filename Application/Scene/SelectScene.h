#pragma once
#include "BaseScene.h"
#include "SelectDrawer.h"
#include "InputDrawer.h"
#include "PauseDrawer.h"
#include "Camera.h"

namespace YScene
{
	// �Z���N�g�V�[��
	class SelectScene : public BaseScene
	{

	private:

#pragma region ���\�[�X

		// �Z���N�g�V�[��BGM
		YGame::Audio* pSelectBGM_ = nullptr;

#pragma endregion

#pragma region �Q�[���I�u�W�F�N�g

		// �X�e�[�W�Z���N�g�`��N���X
		SelectDrawer dra_;
		
		// input
		InputDrawer inputDra_;
		
		// pause
		PauseDrawer pauseDra_;


		// �X�e�[�W�ݒ�
		StageConfig* stageConfig_ = nullptr;


		// �p�[�e�B�N���}�l�[�W���[
		YGame::ParticleManager particleMan_;

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

	public:
		
		// �R���X�g���N�^
		SelectScene() = default;
		
		// �f�X�g���N�^
		~SelectScene() = default;

	};
}

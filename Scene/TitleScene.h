#pragma once
#include "BaseScene.h"
#include "TitleDrawer.h"
#include "InputDrawer.h"
#include "BackgroundDrawer.h"

namespace YScene
{
	// �^�C�g���V�[��
	class TitleScene : public BaseScene
	{

	private:

#pragma region ���\�[�X

		// �^�C�g��BGM
		YGame::Audio* pTitleBGM_ = nullptr;

#pragma endregion

#pragma region �Q�[���I�u�W�F�N�g

		// �^�C�g���`��N���X
		TitleDrawer titleDra_;

		// �w�i
		BackgroundDrawer background_;
		
		// input
		InputDrawer inputDra_;
		

		// �p�[�e�B�N���}�l�[�W���[
		YGame::ParticleManager particleMan_;

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
		TitleScene() = default;
		
		// �f�X�g���N�^
		~TitleScene() = default;
	};
}

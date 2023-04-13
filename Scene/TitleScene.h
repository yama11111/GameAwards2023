#pragma once
#include "BaseScene.h"

namespace YScene
{
	// �^�C�g���V�[��
	class TitleScene : public BaseScene
	{
	public:

#pragma region ���\�[�X

		// ----- �e�N�X�`�� ----- //

		YGame::Texture* pLogoTex_ = nullptr;
		
		YGame::Texture* pBackTex_ = nullptr;

		std::array<YGame::Texture*, 2> pSpaceKeyTex_ = { nullptr, nullptr };

		// ----- �I�[�f�B�I ----- //

		// ----- �X�v���C�g (2D) ----- //

		YGame::Sprite2D* pLogoSpr_ = nullptr;

		YGame::Sprite2D* pBackSpr_ = nullptr;

		std::array<YGame::Sprite2D*, 2> pSpaceKeySpr_ = { nullptr, nullptr };

		// ----- �X�v���C�g (3D) ----- //

		// ----- ���f�� ----- //

#pragma endregion

#pragma region �Q�[���I�u�W�F�N�g

		std::unique_ptr<YGame::Sprite2DObject> logoObj_;

		std::unique_ptr<YGame::Sprite2DObject> backObj_;

		std::unique_ptr<YGame::Sprite2DObject> spaceKeyObj_;
		bool isPush_ = false;

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

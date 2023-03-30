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

		UINT logoTex_ = 0;
		
		UINT backTex_ = 0;

		std::array<UINT, 2> spaceKeyTex_ = { 0, 0 };

		// ----- �I�[�f�B�I ----- //

		// ----- �X�v���C�g (2D) ----- //

		std::unique_ptr<YGame::Sprite2D> logoSpr_;

		std::unique_ptr<YGame::Sprite2D> backSpr_;

		std::array<std::unique_ptr<YGame::Sprite2D>, 2> spaceKeySpr_;

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
		TitleScene() = default;
		// �f�X�g���N�^
		~TitleScene() = default;
	};
}

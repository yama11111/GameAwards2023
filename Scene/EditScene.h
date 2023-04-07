#pragma once
#include "BaseScene.h"

namespace YScene
{
	class EditScene : public BaseScene
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

		bool show_demo_window = true;
		int XS = 0;

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
		EditScene() = default;
		// �f�X�g���N�^
		~EditScene() = default;
	};
}

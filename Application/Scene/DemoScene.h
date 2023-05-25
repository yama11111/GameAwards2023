#pragma once
#include "BaseScene.h"

#include "Level.h"
#include "Camera.h"

namespace YScene
{
	class DemoScene : public BaseScene
	{

	private:

#pragma region ���\�[�X


#pragma endregion

#pragma region �Q�[���I�u�W�F�N�g

		// ���x��
		YGame::Level* pLevel_ = nullptr;

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

	public:

		// �R���X�g���N�^
		DemoScene() = default;

		// �f�X�g���N�^
		~DemoScene() = default;

	};
}


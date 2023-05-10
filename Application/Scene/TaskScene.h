#pragma once

#include "BaseScene.h"

#include "Model.h"
#include "Camera.h"

namespace YScene
{
	// �]���ۑ�V�[��
	class TaskScene : public BaseScene
	{

	private:

#pragma region ���\�[�X
		
		// ���f���|�C���^
		YGame::Model* pCube_ = nullptr;
		YGame::Model* pSphere_ = nullptr;

#pragma endregion


#pragma region �Q�[���I�u�W�F�N�g

		// ���f���I�u�W�F�N�g
		std::unique_ptr<YGame::Model::Object> cubeObj_;
		std::unique_ptr<YGame::Model::Object> sphereObj_;

		// �F
		std::unique_ptr<YGame::Color> color_;

		// �}�e���A��
		std::unique_ptr<YGame::Material> material_;

		// �]���p�r���[�v���W�F�N�V����
		YGame::ViewProjection transferVP_;

		// �����O���[�v
		std::unique_ptr<YGame::LightGroup> lightGroup_;

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
		TaskScene() = default;

		// �f�X�g���N�^
		~TaskScene() = default;

	};
}


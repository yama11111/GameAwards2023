#pragma once
#include "Mesh.h"
#include "IShaderSet.h"
#include "PipelineSet.h"
#include "ModelObject.h"
#include "ObjectConfig.h"

namespace YGame
{
	// ���f���N���X
	class Model
	{

	private:

		// ���b�V���z��
		std::vector<std::unique_ptr<Mesh>> meshes_;

		// �m�[�h�z��
		std::vector<std::unique_ptr<Node>> nodes_;

		// ��\��
		bool isInvisible_ = false;

		// �t�@�C���p�X
		std::string fileName_;

	private:

		// �ÓI���f���i�[�pvector�z��
		static std::vector<std::unique_ptr<Model>> models_;

	public:

		/// <summary>
		/// ����(������)
		/// </summary>
		/// <returns>���f���|�C���^</returns>
		static Model* CreateCube();

		/// <summary>
		/// ����(������)
		/// </summary>
		/// <param name="texFileName"> : �摜�̃t�@�C����</param>
		/// <returns>���f���|�C���^</returns>
		static Model* CreateCube(const std::string& texFileName);

		/// <summary>
		/// ���f��(.obj)�ǂݍ���
		/// </summary>
		/// <param name="modelFileName"> : ���f���̃t�H���_�� (obj�Ɠ������O�̎��̂�) </param>
		/// <param name="isSmoothing"> : �X���[�V���O���邩</param>
		/// <returns>���f���|�C���^</returns>
		static Model* LoadObj(const std::string& modelFileName, const bool isSmoothing);

		/// <summary>
		/// ���f��(.obj)�ǂݍ���
		/// </summary>
		/// <param name="modelFileName"> : ���f���̃t�H���_�� (obj�Ɠ������O�̎��̂�) </param>
		/// <param name="isSmoothing"> : �X���[�V���O���邩</param>
		/// <returns>���f���|�C���^</returns>
		static Model* LoadFbx(const std::string& modelFileName, const bool isSmoothing);

		/// <summary>
		/// �S�폜
		/// </summary>
		static void AllClear();

	public:

		/// <summary>
		/// �`��R�}���h
		/// </summary>
		/// <param name="pObj"> : �I�u�W�F�N�g�|�C���^</param>
		/// <param name="locaiton"> : �`��ꏊ</param>
		void SetDrawCommand(ModelObject* pObj, const DrawLocation& location);


		/// <summary>
		/// ��\���ݒ�
		/// </summary>
		/// <param name="isInvisible"> : ��\����</param>
		void SetInvisible(const bool isInvisible) { isInvisible_ = isInvisible; }


#pragma region FbxLoader

	public:

		// FBX�ǂݍ��ݗp
		class FbxLoader
		{

		public:

			// �ÓIFBX�}�l�[�W���[
			static FbxManager* sFbxMan_;

			// �ÓIFBX�C���|�[�^�[
			static FbxImporter* sFbxImp_;

		public:

			/// <summary>
			/// �ÓI������
			/// </summary>
			static void StaticInitialize();

			/// <summary>
			/// �ÓI�I������
			/// </summary>
			static void StaticFinalize();

		public:

			/// <summary>
			/// �ċA�I�Ƀm�[�h�\�������
			/// </summary>
			/// <param name="pModel"> : ���f���|�C���^</param>
			/// <param name="fbxNode"> : ��͂���m�[�h</param>
			/// <param name="isSmoothing"> : �X���[�V���O���邩</param>
			/// <param name="parent"> : �e�m�[�h</param>
			static void ParseNodeRecursive(Model* pModel, FbxNode* fbxNode, const bool isSmoothing, Node* parent = nullptr);

		};

#pragma endregion


#pragma region Pipeline

	public:

		// �p�C�v���C���N���X
		class Pipeline
		{
		
		public:

			// ���[�g�p�����[�^�ԍ�
			enum class RootParameterIndex
			{
				TransformCB = 0, // �s��
				ColorCB = 1, // �F
				LightCB = 2, // ��
				MaterialCB = 3, // �}�e���A��
				TexDT = 4, // �e�N�X�`��
			};

		private:

			// �V�F�[�_�[�Z�b�g
			class ShaderSet : public YDX::IShaderSet
			{

			public:

				// ���_�V�F�[�_�I�u�W�F�N�g
				Microsoft::WRL::ComPtr<ID3DBlob> vsBlob_ = nullptr;

				// �s�N�Z���V�F�[�_�I�u�W�F�N�g
				Microsoft::WRL::ComPtr<ID3DBlob> psBlob_ = nullptr;

			public:

				/// <summary>
				/// �V�F�[�_�[�t�@�C���ǂݍ���
				/// </summary>
				void Load() override;

			};

		private:

			// �p�C�v���C���ݒ�
			static std::array<YDX::PipelineSet, DrawLocationNum> sPipelineSets_;

		public:

			// �`��Z�b�g
			struct DrawSet
			{

			public:

				// ���f���|�C���^
				Model* pModel_;

				// ���f���p�I�u�W�F�N�g
				ModelObject* pObj_;

			public:

				/// <summary> 
				/// �`��
				/// </summary>
				void Draw();

			};

		private:

			// �`��p���X�g�z��
			static std::array<std::list<std::unique_ptr<DrawSet>>, DrawLocationNum> sDrawSets_;

		public:

			/// <summary>
			/// �ÓI������
			/// </summary>
			static void StaticInitialize();

			/// <summary>
			/// �ÓI�`�惊�X�g�N���A
			/// </summary>
			/// <param name="locaiton"> : �`��ꏊ</param>
			static void StaticClearDrawSet(const DrawLocation& location);

			/// <summary>
			/// �ÓI�`��Z�b�g�}��
			/// </summary>
			/// <param name="drawSet"> : �`��Z�b�g</param>
			/// <param name="locaiton"> : �`��ꏊ</param>
			static void StaticPushBackDrawSet(std::unique_ptr<DrawSet>& drawSet, const DrawLocation& location);

			/// <summary>
			/// �ÓI�`��
			/// </summary>
			/// <param name="locaiton"> : �`��ꏊ</param>
			static void StaticDraw(const DrawLocation& location);

		};

#pragma endregion

	public:

		Model() = default;

		~Model() = default;

	};
}

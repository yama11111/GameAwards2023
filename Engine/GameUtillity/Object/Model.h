#pragma once
#include "Mesh.h"
#include "IShaderSet.h"
#include "PipelineSet.h"
#include "ObjectConfig.h"
#include "ViewProjection.h"
#include "Color.h"
#include "LightGroup.h"
#include "Material.h"

namespace YGame
{
	// ���f���N���X
	class Model
	{
	
	public:

		// �I�u�W�F�N�g�N���X�O���錾
		class Object;

		// �p�C�v���C���N���X�O���錾
		class Pipeline;

		// FBX�ǂݍ��݃N���X�O���錾
		class FbxLoader;

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
		void SetDrawCommand(Model::Object* pObj, const DrawLocation& location);

		/// <summary>
		/// �\�����邩�ݒ�
		/// </summary>
		/// <param name="isVisible"> : �\�����邩</param>
		void SetIsVisible(const bool isVisible);

	public:

		Model() = default;

		~Model() = default;

	private:

		// ���b�V���z��
		std::vector<std::unique_ptr<Mesh>> meshes_;

		// �m�[�h�z��
		std::vector<std::unique_ptr<Node>> nodes_;

		// �\�����邩
		bool isVisible_ = true;

		// �t�@�C���p�X
		std::string fileName_;

	private:

		// �ÓI���f���i�[�pvector�z��
		static std::vector<std::unique_ptr<Model>> sModels_;

	};


#pragma region Object

	// ���f���p�I�u�W�F�N�g�N���X
	class Model::Object : public Transform
	{

	public:

		/// <summary>
		/// ���� + ������ (�f�t�H���g������)
		/// </summary>
		/// <param name="status"> : �ʒu, ��], �傫��</param>
		/// <param name="isMutable"> : �V�[���J�ڎ��ɊJ�����邩</param>
		/// <returns>���I�C���X�^���X (new���ꂽ����)</returns>
		static Object* Create(const Status& status, const bool isMutable = true);

		/// <summary>
		/// ���� + ������ (Transform�ȊO�� null�̎� �f�t�H���g�ŏ�����)
		/// </summary>
		/// <param name="status"> : �ʒu, ��], �傫��</param>
		/// <param name="pVP"> : �r���[�v���W�F�N�V�����|�C���^</param>
		/// <param name="pColor"> : �F�|�C���^</param>
		/// <param name="pLightGroup"> : �����|�C���^</param>
		/// <param name="pMaterial"> : �����|�C���^</param>
		/// <param name="isMutable"> : �V�[���J�ڎ��ɊJ�����邩</param>
		/// <returns>���I�C���X�^���X (new���ꂽ����)</returns>
		static Object* Create(
			const Status& status,
			ViewProjection* pVP,
			Color* pColor,
			LightGroup* pLightGroup,
			Material* pMaterial,
			const bool isMutable = true);

	public:

		/// <summary>
		/// �`��O�R�}���h
		/// </summary>
		/// <param name="transformRPIndex"> : �g�����X�t�H�[�����[�g�p�����[�^�ԍ�</param>
		/// <param name="colorRPIndex"> : �F���[�g�p�����[�^�ԍ�</param>
		/// <param name="lightRPIndex"> : ���C�g�O���[�v���[�g�p�����[�^�ԍ�</param>
		/// <param name="materialRPIndex"> : �}�e���A�����[�g�p�����[�^�ԍ�</param>
		void SetDrawCommand(
			const UINT transformRPIndex,
			const UINT colorRPIndex,
			const UINT lightRPIndex,
			const UINT materialRPIndex);

		/// <summary>
		/// �r���[�v���W�F�N�V�����ݒ� (null = Default)
		/// </summary>
		/// <param name="pVP"> : �r���[�v���W�F�N�V�����|�C���^</param>
		void SetViewProjection(ViewProjection* pVP);

		/// <summary>
		/// �F�ݒ� (null = Default)
		/// </summary>
		/// <param name="pColor"> : �F�|�C���^</param>
		void SetColor(Color* pColor);

		/// <summary>
		/// �����ݒ� (null = Default)
		/// </summary>
		/// <param name="pLightGroup"> : �����|�C���^</param>
		void SetLightGroup(LightGroup* pLightGroup);

		/// <summary>
		/// �}�e���A���ݒ� (null = Default)
		/// </summary>
		/// <param name="pMaterial"> : �}�e���A���|�C���^</param>
		void SetMaterial(Material* pMaterial);

	private:

		Object() = default;

	public:

		~Object() = default;


	private:

		// �萔�o�b�t�@�f�[�^�\����
		struct CBData
		{
			YMath::Matrix4 matWorld_;	 // ���[���h�s��
			YMath::Matrix4 matViewProj_; // �r���[�v���W�F�N�V�����s��
			YMath::Vector3 cameraPos_;	 // �J�������W
		};

	private:

		// �萔�o�b�t�@
		YDX::ConstBuffer<CBData> cBuff_;

		// �r���[�v���W�F�N�V�����|�C���^
		ViewProjection* pVP_ = nullptr;

		// �F�|�C���^
		Color* pColor_ = nullptr;

		// �����|�C���^
		LightGroup* pLightGroup_ = nullptr;

		// �}�e���A���|�C���^
		Material* pMaterial_ = nullptr;

	public:

		// ����l�N���X
		class Default
		{

		public:

			// �r���[�v���W�F�N�V�����|�C���^ (�f�t�H���g)
			static std::unique_ptr<ViewProjection> sVP_;

			// �����|�C���^ (�f�t�H���g)
			static std::unique_ptr<LightGroup> sLightGroup_;

			// �F (�f�t�H���g)
			static std::unique_ptr<Color> sColor_;

			// �}�e���A�� (�f�t�H���g)
			static std::unique_ptr<Material> sMaterial_;

		public:

			/// <summary>
			/// �ÓI������
			/// </summary>
			static void StaticInitialize();

		};

	};

#pragma endregion


#pragma region Pipeline

	// �p�C�v���C���N���X
	class Model::Pipeline
	{

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
		/// <param name="pModel"> : ���f���|�C���^</param>
		/// <param name="pObj"> : �I�u�W�F�N�g�|�C���^</param>
		/// <param name="locaiton"> : �`��ꏊ</param>
		static void StaticPushBackDrawSet(Model* pModel, Model::Object* pObj, const DrawLocation& location);

		/// <summary>
		/// �ÓI�`��
		/// </summary>
		/// <param name="locaiton"> : �`��ꏊ</param>
		static void StaticDraw(const DrawLocation& location);

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

	public:

		// �`��Z�b�g
		struct DrawSet
		{

		public:

			// ���f���|�C���^
			Model* pModel_;

			// ���f���p�I�u�W�F�N�g
			Model::Object* pObj_;

		public:

			/// <summary> 
			/// �`��
			/// </summary>
			void Draw();

		};

	private:

		// �p�C�v���C���ݒ�
		static std::array<YDX::PipelineSet, DrawLocationNum> sPipelineSets_;

		// �`��p���X�g�z��
		static std::array<std::list<std::unique_ptr<DrawSet>>, DrawLocationNum> sDrawSets_;

	};

#pragma endregion


#pragma region FbxLoader

	// FBX�ǂݍ��݃N���X
	class Model::FbxLoader
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

}

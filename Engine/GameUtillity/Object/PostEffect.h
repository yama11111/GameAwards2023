//#pragma once
//#include "Vertices.h"
//#include "IShaderSet.h"
//#include "PipelineSet.h"
//#include "Texture.h"
//#include "Vector2.h"
//#include "ObjectConfig.h"
//#include <list>
//#include <array>
//
//namespace YGame
//{
//	class PostEffect
//	{
//
//	public:
//
//		// �I�u�W�F�N�g�N���X�O���錾
//		class Object;
//
//		// �p�C�v���C���N���X�O���錾
//		class Pipeline;
//	
//	public:
//
//		void Draw();
//
//	public:
//
//		PostEffect() = default;
//
//		~PostEffect() = default;
//
//	};
//
//
//#pragma region Pipeline
//
//	// �p�C�v���C���N���X
//	class Pipeline
//	{
//
//	public:
//
//		/// <summary>
//		/// �ÓI������
//		/// </summary>
//		static void StaticInitialize();
//
//		/// <summary>
//		/// �ÓI�`�惊�X�g�N���A
//		/// </summary>
//		/// <param name="locaiton"> : �`��ꏊ</param>
//		static void StaticClearDrawSet(const DrawLocation& location);
//
//		/// <summary>
//		/// �ÓI�`��Z�b�g�}��
//		/// </summary>
//		/// <param name="drawSet"> : �`��Z�b�g</param>
//		/// <param name="locaiton"> : �`��ꏊ</param>
//		static void StaticPushBackDrawSet(std::unique_ptr<DrawSet>& drawSet, const DrawLocation& location);
//
//		/// <summary>
//		/// �ÓI�`��
//		/// </summary>
//		/// <param name="locaiton"> : �`��ꏊ</param>
//		static void StaticDraw(const DrawLocation& location);
//
//	public:
//
//		// ���[�g�p�����[�^�ԍ�
//		enum class RootParameterIndex
//		{
//			TransformCB = 0, // �s��
//			ColorCB = 1, // �F
//			TexDT = 2, // �e�N�X�`��
//		};
//
//	private:
//
//		// �V�F�[�_�[�Z�b�g
//		class ShaderSet : public YDX::IShaderSet
//		{
//		public:
//
//			// ���_�V�F�[�_�I�u�W�F�N�g
//			Microsoft::WRL::ComPtr<ID3DBlob> vsBlob_ = nullptr;
//
//			// �s�N�Z���V�F�[�_�I�u�W�F�N�g
//			Microsoft::WRL::ComPtr<ID3DBlob> psBlob_ = nullptr;
//
//		public:
//
//			/// <summary>
//			/// �V�F�[�_�[�t�@�C���ǂݍ���
//			/// </summary>
//			void Load() override;
//
//		};
//
//	public:
//
//		// �`��Z�b�g
//		struct DrawSet
//		{
//
//		public:
//
//			// �X�v���C�g2D�|�C���^
//			Sprite2D* pSprite2D_;
//
//			// �X�v���C�g2D�p�I�u�W�F�N�g
//			Sprite2DObject* pObj_;
//
//		public:
//
//			/// <summary> 
//			/// �`��
//			/// </summary>
//			void Draw();
//
//		};
//
//	private:
//
//		// �p�C�v���C���ݒ�
//		static YDX::PipelineSet sPipelineSets_;
//
//		// �`��p���X�g�z��
//		static std::array<std::list<std::unique_ptr<DrawSet>>, DrawLocationNum> sDrawSets_;
//
//	};
//
//#pragma endregion
//
//}

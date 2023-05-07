#pragma once
#include "Vertices.h"
#include "IShaderSet.h"
#include "PipelineSet.h"
#include "Sprite2DObject.h"
#include "Texture.h"
#include "Vector2.h"
#include "ObjectConfig.h"
#include <list>
#include <array>

namespace YGame
{
	// �X�v���C�g2D�N���X
	class Sprite2D
	{

	public:

		// ���_�f�[�^�\����
		struct VData
		{
			YMath::Vector3 pos_; // xyz���W
			YMath::Vector2 uv_;  // uv���W
		};

	private:

		// ���_�f�[�^
		YDX::Vertices<VData> vt_;


		// �T�C�Y
		YMath::Vector2 size_;

		// �A���J�[�|�C���g
		YMath::Vector2 anchor_;

		// ���E���]
		bool isFlipX_ = false;

		// �㉺���]
		bool isFlipY_ = false;


		// �e�N�X�`��
		Texture* pTex_ = nullptr;

		// �e�N�X�`������
		YMath::Vector2 texLeftTop_;

		// �e�N�X�`���T�C�Y
		YMath::Vector2 texSize_;

		// ��\��
		bool isInvisible_ = false;

	private:

		// �ÓI�X�v���C�g2D�i�[�pvector�z��
		static std::vector<std::unique_ptr<Sprite2D>> sprites_;

	public:

		// �ݒ�p�X�e�[�^�X
		struct Status
		{
			bool isDiv_ = true; // �摜�T�C�Y�ɍ��킹�邩
			YMath::Vector2 size_; // �T�C�Y
			YMath::Vector2 anchor_ = { 0.5f, 0.5f }; // �A���J�[�|�C���g
			bool isFlipX_ = false; // ���E���]
			bool isFlipY_ = false; // �㉺���]
		};

		// �e�N�X�`���ݒ�p�X�e�[�^�X
		struct TexStatus
		{
			Texture* pTex_; // �e�N�X�`���|�C���^
			bool isDiv_ = true; // �摜�T�C�Y�ɍ��킹�邩
			YMath::Vector2 leftTop_ = { 0.0f,0.0f }; // �e�N�X�`������
			YMath::Vector2 size_ = { 0.0f,0.0f }; // �e�N�X�`���T�C�Y
		};

	public:

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="status"> : �X�v���C�g�ݒ�</param>
		/// <param name="(bool) isDiv_"> : �摜�T�C�Y�ɍ��킹�邩</param>
		/// <param name="(Vector2) status.size_"> : �傫��</param>
		/// <param name="(Vector2) status.anchor_"> : �A���J�[�|�C���g (�����l�͒��S)</param>
		/// <param name="(bool) status.isFlipX_"> : X���]���邩</param>
		/// <param name="(bool) status.isFlipY_"> : Y���]���邩</param>
		/// <param name="--------------------------------"></param>
		/// <param name="texStatus"> : �e�N�X�`���ݒ�</param>
		/// <param name="(Texture*) texStatus.pTex_"> : �e�N�X�`���|�C���^</param>
		/// <param name="(bool) isDiv_"> : �摜�T�C�Y�ɍ��킹�邩</param>
		/// <param name="(Vector2) texStatus.leftTop_"> : �e�N�X�`������</param>
		/// <param name="(Vector2) texStatus.size_"> : �e�N�X�`���T�C�Y</param>
		/// <param name="--------------------------------"></param>
		/// <returns>�X�v���C�g�|�C���^</returns>
		static Sprite2D* Create(const Status& status, const TexStatus& texStatus);

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
		void SetDrawCommand(Sprite2DObject* pObj, const DrawLocation& location);


		/// <summary>
		/// �X�v���C�g�T�C�Y�ݒ�
		/// </summary>
		/// <param name="size"> : �X�v���C�g�T�C�Y</param>
		void SetSize(const YMath::Vector2& size);

		/// <summary>
		/// �A���J�[�|�C���g�ݒ�
		/// </summary>
		/// <param name="anchor"> : �A���J�[�|�C���g</param>
		void SetAnchorPoint(const YMath::Vector2& anchor);

		/// <summary>
		/// �t���b�v�ݒ�
		/// </summary>
		/// <param name="isFlipX"> : X���t���b�v</param>
		/// <param name="isFlipY"> : Y���t���b�v</param>
		void SetFrip(const bool isFlipX, const bool isFlipY);

		/// <summary>
		/// �e�N�X�`������ݒ�
		/// </summary>
		/// <param name="leftTop"> : ����</param>
		/// <param name="adjust"> : �������邩</param>
		void SetTextureLeftTop(const YMath::Vector2& leftTop, const bool adjust = true);

		/// <summary>
		/// �e�N�X�`���T�C�Y�ݒ�
		/// </summary>
		/// <param name="texSize"> : �e�N�X�`���T�C�Y</param>
		void SetTextureSize(const YMath::Vector2& texSize);

		/// <summary>
		/// �e�N�X�`����`�ݒ�
		/// </summary>
		/// <param name="leftTop"> : �e�N�X�`������</param>
		/// <param name="texSize"> : �e�N�X�`���T�C�Y</param>
		void SetTextureRectangle(const YMath::Vector2& leftTop, const YMath::Vector2& texSize);

		/// <summary>
		/// �S�ݒ�
		/// </summary>
		/// <param name="status"> : �X�v���C�g�ݒ�</param>
		/// <param name="(bool) isDiv_"> : �摜�T�C�Y�ɍ��킹�邩</param>
		/// <param name="(Vector2) status.size_"> : �傫��</param>
		/// <param name="(Vector2) status.anchor_"> : �A���J�[�|�C���g(���S)</param>
		/// <param name="(bool) status.isFlipX_"> : X���]���邩</param>
		/// <param name="(bool) status.isFlipY_"> : Y���]���邩</param>
		/// <param name="--------------------------------"></param>
		/// <param name="texStatus"> : �e�N�X�`���ݒ�</param>
		/// <param name="(UINT) texStatus.index_"> : �e�N�X�`���|�C���^</param>
		/// <param name="(bool) isDiv_"> : �摜�T�C�Y�ɍ��킹�邩</param>
		/// <param name="(Vector2) texStatus.leftTop_"> : �e�N�X�`������</param>
		/// <param name="(Vector2) texStatus.size_"> : �e�N�X�`���T�C�Y</param>
		/// <param name="--------------------------------"></param>
		void SetAllStatus(const Status& status, const TexStatus& texStatus);

		/// <summary>
		/// ��\���ݒ�
		/// </summary>
		/// <param name="isInvisible"> : ��\����</param>
		void SetInvisible(const bool isInvisible) { isInvisible_ = isInvisible; }

	public:

		/// <summary>
		/// �T�C�Y�擾
		/// </summary>
		/// <returns>�T�C�Y</returns>
		YMath::Vector2 Size() const { return size_; }

		/// <summary>
		/// �A���J�[�|�C���g�擾
		/// </summary>
		/// <returns>�A���J�[�|�C���g</returns>
		YMath::Vector2 AnchorPoint() const { return anchor_; }


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
				TexDT = 2, // �e�N�X�`��
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

				// �X�v���C�g2D�|�C���^
				Sprite2D* pSprite2D_;

				// �X�v���C�g2D�p�I�u�W�F�N�g
				Sprite2DObject* pObj_;

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

		Sprite2D() = default;

		~Sprite2D() = default;

	};
}
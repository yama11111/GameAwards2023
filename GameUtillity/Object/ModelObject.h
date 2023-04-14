#pragma once
#include "Transform.h"
#include "ViewProjection.h"
#include "LightGroup.h"
#include "Color.h"
#include <memory>

namespace YGame
{
	// ���f���p�I�u�W�F�N�g�N���X
	class ModelObject : public Transform
	{
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
	
	public:
		
		/// <summary>
		/// ���� + ������ (�f�t�H���g������)
		/// </summary>
		/// <param name="status"> : �ݒ�p�X�e�[�^�X</param>
		/// <param name="(Vector3) status.pos_"> : �ʒu</param>
		/// <param name="(Vector3) status.rota_"> : ��]</param>
		/// <param name="(Vector3) status.scale_"> : �傫��</param>
		/// <param name="isMutable"> : �V�[���J�ڎ��ɊJ�����邩</param>
		/// <returns>���I�C���X�^���X (new���ꂽ����)</returns>
		static ModelObject* Create(const Status& status, const bool isMutable = true);
		
		/// <summary>
		/// ���� + ������ (Transform�ȊO�� null�̎� �f�t�H���g�ŏ�����)
		/// </summary>
		/// <param name="status"> : �ݒ�p�X�e�[�^�X</param>
		/// <param name="(Vector3) status.pos_"> : �ʒu</param>
		/// <param name="(Vector3) status.rota_"> : ��]</param>
		/// <param name="(Vector3) status.scale_"> : �傫��</param>
		/// <param name="-------------------------------------"></param>
		/// <param name="pVP"> : �r���[�v���W�F�N�V�����|�C���^</param>
		/// <param name="pColor"> : �F�|�C���^</param>
		/// <param name="pLightGroup"> : �����|�C���^</param>
		/// <param name="isMutable"> : �V�[���J�ڎ��ɊJ�����邩</param>
		/// <returns>���I�C���X�^���X (new���ꂽ����)</returns>
		static ModelObject* Create(const Status& status, ViewProjection* pVP, Color* pColor, LightGroup* pLightGroup, 
			const bool isMutable = true);
	
	public:
		
		/// <summary>
		/// �`��O�R�}���h
		/// </summary>
		/// <param name="transformRPIndex"></param>
		/// <param name="colorRPIndex"></param>
		/// <param name="lightRPIndex"></param>
		void SetDrawCommand(const UINT transformRPIndex, const UINT colorRPIndex, const UINT lightRPIndex);
		

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
	
#pragma region Common

	public:

		// �R�����N���X
		class Common
		{
		public:

			// �r���[�v���W�F�N�V�����|�C���^ (�f�t�H���g)
			static std::unique_ptr<ViewProjection> sDefVP_;
			
			// �����|�C���^ (�f�t�H���g)
			static std::unique_ptr<LightGroup> sDefLightGroup_;
			
			// �F (�f�t�H���g)
			static std::unique_ptr<Color> sDefColor_;

		public:

			/// <summary>
			/// �ÓI������
			/// </summary>
			static void StaticInitialize();

		};

	private:

		// �R����
		static Common common_;

#pragma endregion

	private:
	
		ModelObject() = default;

	public:
		
		~ModelObject() = default;
	
	};
}

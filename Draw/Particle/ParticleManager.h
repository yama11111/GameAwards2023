#pragma once
#include "Particle.h"
#include <list>

namespace YGame
{
	// �p�[�e�B�N���}�l�[�W���[
	class ParticleManager
	{
	private:
		
		// �p�[�e�B�N�����X�g
		std::list<std::unique_ptr<IParticle>> particles_;
	
	public:

		/// <summary>
		/// ������
		/// </summary>
		void Initialize();

		/// <summary>
		/// �X�V
		/// </summary>
		void Update();

		/// <summary>
		/// �`��
		/// </summary>
		void Draw();
	
	public:
		
		/// <summary>
		/// ����O���b�h�u���b�N����
		/// </summary>
		/// <param name="frame"> : ��������</param>
		/// <param name="pParent"> : �e�s��</param>
		/// <param name="color"> : �F</param>
		void EmitIlluminationGridBlock(
			const uint32_t frame,
			YMath::Matrix4* pParent,
			const YMath::Vector3& color);

		/// <summary>
		/// �ݒu�O���b�h�u���b�N����
		/// </summary>
		/// <param name="frame"> : ��������</param>
		/// <param name="pParent"> : �e�s��</param>
		/// <param name="color"> : �F</param>
		void EmitPlaceGridBlock(
			const uint32_t frame,
			YMath::Matrix4* pParent,
			const YMath::Vector3& color);

	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		/// <param name="pVP"> : �r���[�v���W�F�N�V�����|�C���^</param>
		static void StaticInitialize(YGame::ViewProjection* pVP);
	
	public:
		
		~ParticleManager() = default;
	};
}


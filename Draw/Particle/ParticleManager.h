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
		/// �A�O���b�h����
		/// </summary>
		/// <param name="frame"> : </param>
		/// <param name="status"> : �g�����X�t�H�[���ݒ�X�e�[�^�X</param>
		/// <param name="moveSpeed"> : �ړ��X�s�[�h</param>
		/// <param name="rotaSpeed"> : ��]�X�s�[�h</param>
		/// <param name="color"> : �F</param>
		void EmitBubbleGrid(
			const uint32_t frame,
			const YGame::Transform::Status status,
			const YMath::Vector3& moveSpeed,
			const YMath::Vector3& rotaSpeed,
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


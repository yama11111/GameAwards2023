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
		/// �����[������
		/// </summary>
		/// <param name="emitNum"> : ��</param>
		/// <param name="startToRelayFrame"> : �J�n�n�_ ���� ���p�n�_ �܂ł̎���</param>
		/// <param name="relayToEndFrame"> : ���p�n�_ ���� �I���n�_ �܂ł̎���</param>
		/// <param name="start"> : �J�n�n�_</param>
		/// <param name="end"> : �I���n�_</param>
		/// <param name="relayRange"> : ���p�n�_�͈�</param>
		/// <param name="rota"> : ��]</param>
		/// <param name="scale"> : �傫��</param>
		/// <param name="color"> : �F</param>
		void EmitRelayBug(
			const uint32_t emitNum,
			const uint32_t startToRelayFrame, const uint32_t relayToEndFrame,
			const YMath::Vector3& start, const YMath::Vector3& end,
			const YMath::Vector3& relayRange,
			const YMath::Vector3& minRota, const YMath::Vector3& maxRota,
			const float& minScale, const float& maxScale,
			const YMath::Vector3& color,
			const float& place);
		
		/// <summary>
		/// �A�O���b�h����
		/// </summary>
		/// <param name="emitNum"> : ������</param>
		/// <param name="aliveFrame"> : ��������</param>
		/// <param name="center"> : ���S</param>
		/// <param name="range"> : �͈�</param>
		/// <param name="minScale"> : �ŏ��X�P�[��</param>
		/// <param name="maxScale"> : �ő�X�P�[��</param>
		/// <param name="minMoveSpeed"> : �ŏ��ړ��X�s�[�h</param>
		/// <param name="maxMoveSpeed"> : �ő�ړ��X�s�[�h</param>
		/// <param name="minRotaSpeed"> : �ŏ���]�X�s�[�h</param>
		/// <param name="maxRotaSpeed"> : �ő��]�X�s�[�h</param>
		/// <param name="place"> : �����_���ǂ̈ʂ܂ň�����</param>
		/// <param name="color"> : �F</param>
		void EmitBubbleGrid(
			const uint32_t& emitNum,
			const uint32_t& aliveFrame,
			const YMath::Vector3& center, const YMath::Vector3& range,
			const float& minScale, const float& maxScale,
			const YMath::Vector3& minMoveSpeed, const YMath::Vector3& maxMoveSpeed,
			const YMath::Vector3& minRotaSpeed, const YMath::Vector3& maxRotaSpeed,
			const YMath::Vector3& color,
			const float& place);

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


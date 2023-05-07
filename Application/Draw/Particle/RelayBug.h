#pragma once
#include "IParticle.h"

namespace YGame
{
	// �����[��
	class RelayBug : public IParticleModel
	{

	private:

		// �J�n�n�_ ���� ���p�n�_ �܂ł̃t���O
		bool isStartToRelay_ = false;

		// �J�n�n�_ ���� ���p�n�_ �܂ł̃^�C�}�[
		YMath::Timer startToRelayTim_;


		// ���p�n�_ ���� �I���n�_ �܂ł̃t���O
		bool isRelayToEnd_ = false;

		// ���p�n�_ ���� �I���n�_ �܂ł̃^�C�}�[
		YMath::Timer relayToEndTim_;


		// �ʒu�C�[�W���O
		YMath::Ease<YMath::Vector3> posEas_;

		// �I���n�_�ۑ��p
		YMath::Vector3 end_;

	public:

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="startToRelayFrame"> : �J�n�n�_ ���� ���p�n�_ �܂ł̎���</param>
		/// <param name="relayToEndFrame"> : ���p�n�_ ���� �I���n�_ �܂ł̎���</param>
		/// <param name="start"> : �J�n�n�_</param>
		/// <param name="relay"> : ���p�n�_</param>
		/// <param name="end"> : �I���n�_</param>
		/// <param name="rota"> : ��]</param>
		/// <param name="scale"> : �傫��</param>
		/// <param name="color"> : �F</param>
		/// <param name="pModel"> : ���f���|�C���^</param>
		/// <param name="location"> : �`��ꏊ</param>
		void Emit(
			const uint32_t startToRelayFrame,
			const uint32_t relayToEndFrame,
			const YMath::Vector3& start,
			const YMath::Vector3& relay,
			const YMath::Vector3& end,
			const YMath::Vector3& rota,
			const YMath::Vector3& scale,
			const YMath::Vector3& color,
			Model* pModel, const DrawLocation& location);

		/// <summary>
		/// �X�V
		/// </summary>
		void Update() override;

		/// <summary>
		/// �`��
		/// </summary>
		void Draw() override;

	public:

		~RelayBug() = default;
	};
}

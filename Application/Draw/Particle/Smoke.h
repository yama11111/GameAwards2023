#pragma once
#include "IParticle.h"

namespace YGame
{
	// ��
	class Smoke : public IParticleModel
	{

	private:

		// �ړ��X�s�[�h
		YMath::Vector3 moveSpeed_;

		// ��]�X�s�[�h
		YMath::Vector3 rotaSpeed_;


		// �A���t�@�l�C�[�W���O
		YMath::Ease<float> alphaEas_;

	public:

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="aliveFrame"> : ��������</param>
		/// <param name="status"> : �g�����X�t�H�[���ݒ�X�e�[�^�X</param>
		/// <param name="moveSpeed"> : �ړ��X�s�[�h</param>
		/// <param name="rotaSpeed"> : ��]�X�s�[�h</param>
		/// <param name="color"> : �F</param>
		/// <param name="pModel"> : ���f���|�C���^</param>
		/// <param name="location"> : �`��ꏊ</param>
		void Emit(
			const uint32_t aliveFrame,
			const Transform::Status status,
			const YMath::Vector3& moveSpeed,
			const YMath::Vector3& rotaSpeed,
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

		~Smoke() = default;
	};
}

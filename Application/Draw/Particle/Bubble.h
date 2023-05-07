#pragma once
#include "IParticle.h"

namespace YGame
{
	// �A
	class Bubble : public IParticleSprite3D
	{

	private:

		// �ړ��X�s�[�h
		YMath::Vector3 moveSpeed_;

		// ��]�X�s�[�h
		YMath::Vector3 rotaSpeed_;


		// ���� + ���ŃX�P�[���p�p���[�X�C�b�`
		bool isScalePowerSwitch_ = false;

		// ���� + ���ŗp�X�P�[���p�p���[
		YMath::Power scalePow_;

		// ���� + ���ŗp�X�P�[���C�[�W���O
		YMath::Ease<float> scaleEas_;

	public:

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="aliveTime"> : ��������</param>
		/// <param name="status"> : �g�����X�t�H�[���ݒ�X�e�[�^�X</param>
		/// <param name="moveSpeed"> : �ړ��X�s�[�h</param>
		/// <param name="rotaSpeed"> : ��]�X�s�[�h</param>
		/// <param name="color"> : �F</param>
		/// <param name="pSprite"> : �X�v���C�g3D�|�C���^</param>
		/// <param name="location"> : �`��ꏊ</param>
		void Emit(
			const uint32_t aliveTime,
			const Transform::Status status,
			const YMath::Vector3& moveSpeed,
			const YMath::Vector3& rotaSpeed,
			const YMath::Vector3& color,
			Sprite3D* pSprite, const DrawLocation& location);

		/// <summary>
		/// �X�V
		/// </summary>
		void Update() override;

		/// <summary>
		/// �`��
		/// </summary>
		void Draw() override;

	public:

		~Bubble() = default;

	};
}


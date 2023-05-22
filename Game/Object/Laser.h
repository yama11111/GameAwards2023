#pragma once
#include "LaserDrawer.h"
#include "IObject.h"

class Laser :
	public IObject
{

private:

	// ����
	YMath::Vector3 direction_;
	
	// �r�[���̒���
	float beamLength_ = 0.0f;

	// ������t���O
	bool isColl_ = false;

	// �`��N���X
	LaserDrawer drawer_;

public:

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="signIndex"> : �Ŕԍ�</param>
	/// <param name="pos"> : �����ʒu</param>
	/// <param name="direction"> : ����</param>
	void Initialize(const size_t signIndex, const YMath::Vector3& pos, const YMath::Vector3& direction);

	/// <summary>
	/// ���Z�b�g (���g����������)
	/// </summary>
	/// <param name="signIndex"> : �Ŕԍ�</param>
	/// <param name="pos"> : �����ʒu</param>
	/// <param name="direction"> : ����</param>
	void Reset(const size_t signIndex, const YMath::Vector3& pos, const YMath::Vector3& direction);

	/// <summary>
	/// ����O�X�V
	/// </summary>
	void PreUpdate() override;

	/// <summary>
	/// �����X�V
	/// </summary>
	void PostUpdate() override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;

public:

	/// <summary>
	/// �Փˎ��R�[���o�b�N�֐�
	/// </summary>
	/// <param name="pPair"> : ����R���C�_�[�|�C���^</param>
	void OnCollision(ObjectCollider* pPair) override;

private:

	/// <summary>
	/// �r�[���̒����v�Z
	/// </summary>
	void CalcBeamLength();
};


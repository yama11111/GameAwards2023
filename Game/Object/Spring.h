#pragma once
#include "SpringDrawer.h"
#include "IObject.h"

class Spring :
	public IObject
{

private:

	// �W�����v��
	float jumpPower_;

	// �`��N���X
	SpringDrawer drawer_;

public:

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="signIndex"> : �Ŕԍ�</param>
	/// <param name="pos"> : �����ʒu</param>
	/// <param name="jumpPower"> : �W�����v��</param>
	void Initialize(const size_t signIndex, const YMath::Vector3& pos, const float jumpPower);

	/// <summary>
	/// ���Z�b�g (���g����������)
	/// </summary>
	/// <param name="signIndex"> : �Ŕԍ�</param>
	/// <param name="pos"> : �����ʒu</param>
	/// <param name="jumpPower"> : �W�����v��</param>
	void Reset(const size_t signIndex, const YMath::Vector3& pos, const float jumpPower);

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

};


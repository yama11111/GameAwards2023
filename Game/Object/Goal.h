#pragma once
#include "GoalDrawer.h"
#include "IObject.h"

class Goal :
	public IObject
{

private:

	// �`��N���X
	GoalDrawer drawer_;

	// ���b�N�t���O
	bool isRock_ = false;

public:

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="signIndex"> : �Ŕԍ�</param>
	/// <param name="pos"> : �����ʒu</param>
	/// <param name="isRock"> : ���b�N�t���O</param>
	void Initialize(const size_t signIndex, const YMath::Vector3& pos, const bool isRock);

	/// <summary>
	/// ���Z�b�g (���g����������)
	/// </summary>
	/// <param name="signIndex"> : �Ŕԍ�</param>
	/// <param name="pos"> : �����ʒu</param>
	/// <param name="isRock"> : ���b�N�t���O</param>
	void Reset(const size_t signIndex, const YMath::Vector3& pos, const bool isRock);

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

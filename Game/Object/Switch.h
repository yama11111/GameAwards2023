#pragma once
#include "SwitchDrawer.h"
#include "IObject.h"

class Switch :
	public IObject
{

private:

	// �`��N���X
	SwitchDrawer drawer_;
	
	// �����Ă��邩
	bool isAct_ = false;

public:

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="signIndex"> : �Ŕԍ�</param>
	/// <param name="pos"> : �����ʒu</param>
	/// <param name="isAct"> : ����t���O</param>
	void Initialize(const size_t signIndex, const YMath::Vector3& pos, const bool isAct);

	/// <summary>
	/// ���Z�b�g (���g����������)
	/// </summary>
	/// <param name="signIndex"> : �Ŕԍ�</param>
	/// <param name="pos"> : �����ʒu</param>
	/// <param name="isAct"> : ����t���O</param>
	void Reset(const size_t signIndex, const YMath::Vector3& pos, const bool isAct);

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


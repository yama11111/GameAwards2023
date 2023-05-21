#pragma once
#include "PlatformDrawer.h"
#include "IObject.h"

class Platform :
	public IObject
{

private:

	// �g�����X�t�H�[��
	std::unique_ptr<YGame::Transform> transform_;

	// �`��N���X
	PlatformDrawer drawer_;

public:

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="signIndex"> : �Ŕԍ�</param>
	/// <param name="pos"> : �����ʒu</param>
	/// <param name="length"> : ����</param>
	void Initialize(const size_t signIndex, const YMath::Vector3& pos, const float length);

	/// <summary>
	/// ���Z�b�g (���g����������)
	/// </summary>
	/// <param name="signIndex"> : �Ŕԍ�</param>
	/// <param name="pos"> : �����ʒu</param>
	/// <param name="length"> : ����</param>
	void Reset(const size_t signIndex, const YMath::Vector3& pos, const float length);

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
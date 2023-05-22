#pragma once
#include "BlockDrawer.h"
#include "IObject.h"
#include "YukiMapchipCollider.h"

// �C���N���[�h���p
namespace YInput { class Keys; }

class Block :
	public IObject,
	public YukiMapchipCollider
{

private:

	// �X�s�[�h
	YMath::Vector3 speed_;
	
	// �`��N���X
	BlockDrawer drawer_;

public:

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="signIndex"> : �Ŕԍ�</param>
	/// <param name="pos"> : �����ʒu</param>
	void Initialize(const size_t signIndex, const YMath::Vector3& pos);

	/// <summary>
	/// ���Z�b�g (���g����������)
	/// </summary>
	/// <param name="signIndex"> : �Ŕԍ�</param>
	/// <param name="pos"> : �����ʒu</param>
	void Reset(const size_t signIndex, const YMath::Vector3& pos);

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
	/// �X�V
	/// </summary>
	void Update() override;

public:

	/// <summary>
	/// ���W (�Q�Ɠn��)
	/// </summary>
	/// <returns>���W (�Q�Ɠn��)</returns>
	YMath::Vector3& PosRef() override;

	/// <summary>
	/// �X�s�[�h (�Q�Ɠn��)
	/// </summary>
	/// <returns>�X�s�[�h (�Q�Ɠn��)</returns>
	YMath::Vector3& SpeedRef() override;

private:

	/// <summary>
	/// �ړ�
	/// </summary>
	void Move();

	/// <summary>
	/// ���n
	/// </summary>
	void Landing();

	/// <summary>
	/// ���������X�V
	/// </summary>
	void UpdatePhysics();

public:

	/// <summary>
	/// �Փˎ��R�[���o�b�N�֐�
	/// </summary>
	/// <param name="pPair"> : ����R���C�_�[�|�C���^</param>
	void OnCollision(ObjectCollider* pPair) override;

private:

	// �L�[
	static YInput::Keys* spKeys_;

public:

	/// <summary>
	/// �ÓI������
	/// </summary>
	static void StaticInitialize();

};


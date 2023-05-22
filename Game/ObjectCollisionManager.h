#pragma once
#include "ObjectCollider.h"
#include <list>

class ObjectCollisionManager
{

private:
	
	// �R���C�_�[�i�[���X�g
	std::list<ObjectCollider*> pColliders_;

public:
	
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
	
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

public: 
	
	/// <summary>
	/// �i�[
	/// </summary>
	/// <param name="pCollider"> : �R���C�_�[�|�C���^</param>
	void PushBack(ObjectCollider* pCollider);
	
	/// <summary>
	/// ���X�g�N���A
	/// </summary>
	void Clear();

private:
	
	/// <summary>
	/// �S�R���W�����m�F
	/// </summary>
	void CheckAllCollision();

private:
	
	/// <summary>
	/// �A�^������
	/// </summary>
	/// <param name="pColliderA"> : �R���C�_�[�|�C���^A</param>
	/// <param name="pColliderB"> : �R���C�_�[�|�C���^B</param>
	static void CheckCollisionPair(ObjectCollider* pColliderA, ObjectCollider* pColliderB);
	
};


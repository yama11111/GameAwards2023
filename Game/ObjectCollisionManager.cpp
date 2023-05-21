#include "ObjectCollisionManager.h"
#include <cassert>

using YMath::Vector3;
using YGame::Box2D;

void ObjectCollisionManager::Initialize()
{
	Clear();
}

void ObjectCollisionManager::Update()
{
	if (pColliders_.empty()) { return; }
	CheckAllCollision();
	Clear();
}

void ObjectCollisionManager::PushBack(ObjectCollider* pCollider)
{
	assert(pCollider);
	pColliders_.push_back(pCollider);
}

void ObjectCollisionManager::Clear()
{
	if (pColliders_.empty()) { return; }
	pColliders_.clear();
}

void ObjectCollisionManager::CheckAllCollision()
{
	std::list<ObjectCollider*>::iterator itrA = pColliders_.begin();
	for (; itrA != pColliders_.end(); ++itrA)
	{
		ObjectCollider* colA = *itrA;

		std::list<ObjectCollider*>::iterator itrB = itrA;
		itrB++;

		for (; itrB != pColliders_.end(); ++itrB)
		{
			ObjectCollider* colB = *itrB;
			CheckCollisionPair(colA, colB);
		}
	}
}

void ObjectCollisionManager::CheckCollisionPair(ObjectCollider* pColliderA, ObjectCollider* pColliderB)
{
	// �Ŕ��Ⴄ�Ȃ�e��
	if (pColliderA->GetSignIndex() != pColliderB->GetSignIndex()) { return; }

	// �v���C���[
	if (pColliderA->GetColliderType() == ObjectCollider::Type::ePlayer)
	{
		// �v���C���[ �~ �u���b�N
		if (pColliderB->GetColliderType() == ObjectCollider::Type::eBlock)
		{
			pColliderA->PerfectPixelCollision(*pColliderB);
		}
		// �v���C���[ �~ �΂�
		if (pColliderB->GetColliderType() == ObjectCollider::Type::eSpring)
		{
			pColliderA->PerfectPixelCollision(*pColliderB);
		}
		// �v���C���[ �~ ����
		if (pColliderB->GetColliderType() == ObjectCollider::Type::ePlatform)
		{
			pColliderA->PerfectPixelCollisionUpperSide(*pColliderB);
		}
	}

	// �u���b�N
	if (pColliderA->GetColliderType() == ObjectCollider::Type::eBlock)
	{
		// �u���b�N �~ �΂�
		if (pColliderB->GetColliderType() == ObjectCollider::Type::eSpring)
		{
			pColliderA->PerfectPixelCollision(*pColliderB);
		}
		// �u���b�N �~ ����
		if (pColliderB->GetColliderType() == ObjectCollider::Type::ePlatform)
		{
			pColliderA->PerfectPixelCollisionUpperSide(*pColliderB);
		}
	}

	// �S�I�u�W�F�N�g
	if (YGame::CollisionBoxBox2D(*pColliderA, *pColliderB))
	{
		pColliderA->OnCollision(pColliderB);
		pColliderB->OnCollision(pColliderA);
	}
}
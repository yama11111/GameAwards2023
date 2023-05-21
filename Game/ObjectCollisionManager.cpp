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
	// 看板が違うなら弾く
	if (pColliderA->GetSignIndex() != pColliderB->GetSignIndex()) { return; }

	// プレイヤー
	if (pColliderA->GetColliderType() == ObjectCollider::Type::ePlayer)
	{
		// プレイヤー × ブロック
		if (pColliderB->GetColliderType() == ObjectCollider::Type::eBlock)
		{
			pColliderA->PerfectPixelCollision(*pColliderB);
		}
		// プレイヤー × ばね
		if (pColliderB->GetColliderType() == ObjectCollider::Type::eSpring)
		{
			pColliderA->PerfectPixelCollision(*pColliderB);
		}
		// プレイヤー × 足場
		if (pColliderB->GetColliderType() == ObjectCollider::Type::ePlatform)
		{
			pColliderA->PerfectPixelCollisionUpperSide(*pColliderB);
		}
	}

	// ブロック
	if (pColliderA->GetColliderType() == ObjectCollider::Type::eBlock)
	{
		// ブロック × ばね
		if (pColliderB->GetColliderType() == ObjectCollider::Type::eSpring)
		{
			pColliderA->PerfectPixelCollision(*pColliderB);
		}
		// ブロック × 足場
		if (pColliderB->GetColliderType() == ObjectCollider::Type::ePlatform)
		{
			pColliderA->PerfectPixelCollisionUpperSide(*pColliderB);
		}
	}

	// 全オブジェクト
	if (YGame::CollisionBoxBox2D(*pColliderA, *pColliderB))
	{
		pColliderA->OnCollision(pColliderB);
		pColliderB->OnCollision(pColliderA);
	}
}
#include "ObjectCollisionManager.h"
#include <cassert>

using YMath::Vector2;
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
		// 調整用コライダー
		Box2D collA;
		collA.SetBox2DCenter(pColliderA->GetBox2DCenter());
		// 大きさに幅を持たせる
		Vector2 rad = pColliderA->GetBox2DRadSize();
		collA.SetBox2DRadSize(rad + Vector2(rad.x_ / 2.0f, -(rad.y_ / 2.0f)));

		// プレイヤー × ブロック
		if		(pColliderB->GetColliderType() == ObjectCollider::Type::eBlock)
		{
			// アタリ
			if (YGame::CollisionBoxBox2D(collA, *pColliderB))
			{
				pColliderA->OnCollision(pColliderB);
				pColliderB->OnCollision(pColliderA);
			}

			// 押し戻し
			pColliderA->PerfectPixelCollision(*pColliderB);
			pColliderB->PerfectPixelCollision(*pColliderA);
		}
		// プレイヤー × ばね
		else if (pColliderB->GetColliderType() == ObjectCollider::Type::eSpring)
		{
			// アタリ + 押し戻し
			if (pColliderA->PerfectPixelCollision(*pColliderB))
			{
				pColliderA->OnCollision(pColliderB);
				pColliderB->OnCollision(pColliderA);
			}
		}
		// プレイヤー × 足場
		else if (pColliderB->GetColliderType() == ObjectCollider::Type::ePlatform)
		{
			// アタリ + 押し戻し
			if (pColliderA->PerfectPixelCollisionUpperSide(*pColliderB))
			{
				pColliderA->OnCollision(pColliderB);
				pColliderB->OnCollision(pColliderA);
			}
		}
		// プレイヤー × レーザー
		else if (pColliderB->GetColliderType() == ObjectCollider::Type::eLaser)
		{
			// アタリ
			if (YGame::CollisionBoxBox2D(*pColliderA, *pColliderB))
			{
				pColliderA->OnCollision(pColliderB);
				pColliderB->OnCollision(pColliderA);
			}
		}
		// プレイヤー × スイッチ
		else if (pColliderB->GetColliderType() == ObjectCollider::Type::eSwitch)
		{
			// アタリ
			if (YGame::CollisionBoxBox2D(collA, *pColliderB))
			{
				pColliderA->OnCollision(pColliderB);
				pColliderB->OnCollision(pColliderA);
			}
		}
		// プレイヤー × 鍵
		else if (pColliderB->GetColliderType() == ObjectCollider::Type::eKey)
		{
			// アタリ
			if (YGame::CollisionBoxBox2D(collA, *pColliderB))
			{
				pColliderA->OnCollision(pColliderB);
				pColliderB->OnCollision(pColliderA);
			}
		}

		return;
	}

	// ブロック
	if (pColliderA->GetColliderType() == ObjectCollider::Type::eBlock)
	{
		// ブロック × ブロック
		if		(pColliderB->GetColliderType() == ObjectCollider::Type::eBlock)
		{
			// アタリ + 押し戻し
			if (pColliderA->PerfectPixelCollision(*pColliderB))
			{
				pColliderA->OnCollision(pColliderB);
				pColliderB->OnCollision(pColliderA);
			}
		}
		// ブロック × ばね
		else if (pColliderB->GetColliderType() == ObjectCollider::Type::eSpring)
		{
			// アタリ + 押し戻し
			if (pColliderA->PerfectPixelCollision(*pColliderB))
			{
				pColliderA->OnCollision(pColliderB);
				pColliderB->OnCollision(pColliderA);
			}
		}
		// ブロック × 足場
		else if (pColliderB->GetColliderType() == ObjectCollider::Type::ePlatform)
		{
			// アタリ + 押し戻し
			if (pColliderA->PerfectPixelCollisionUpperSide(*pColliderB))
			{
				pColliderA->OnCollision(pColliderB);
				pColliderB->OnCollision(pColliderA);
			}
		}
		// ブロック × レーザー
		else if (pColliderB->GetColliderType() == ObjectCollider::Type::eLaser)
		{
			// アタリ
			if (YGame::CollisionBoxBox2D(*pColliderA, *pColliderB))
			{
				pColliderA->OnCollision(pColliderB);
				pColliderB->OnCollision(pColliderA);
			}
		}

		return;
	}

	// 全オブジェクト
	if (YGame::CollisionBoxBox2D(*pColliderA, *pColliderB))
	{
		pColliderA->OnCollision(pColliderB);
		pColliderB->OnCollision(pColliderA);
	}
}
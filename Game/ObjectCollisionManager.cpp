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
	// �Ŕ��Ⴄ�Ȃ�e��
	if (pColliderA->GetSignIndex() != pColliderB->GetSignIndex()) { return; }

	// �v���C���[
	if (pColliderA->GetColliderType() == ObjectCollider::Type::ePlayer)
	{
		// �����p�R���C�_�[
		Box2D collA;
		collA.SetBox2DCenter(pColliderA->GetBox2DCenter());
		// �傫���ɕ�����������
		Vector2 rad = pColliderA->GetBox2DRadSize();
		collA.SetBox2DRadSize(rad + Vector2(rad.x_ / 2.0f, -(rad.y_ / 2.0f)));

		// �v���C���[ �~ �u���b�N
		if		(pColliderB->GetColliderType() == ObjectCollider::Type::eBlock)
		{
			// �A�^��
			if (YGame::CollisionBoxBox2D(collA, *pColliderB))
			{
				pColliderA->OnCollision(pColliderB);
				pColliderB->OnCollision(pColliderA);
			}

			// �����߂�
			pColliderA->PerfectPixelCollision(*pColliderB);
			pColliderB->PerfectPixelCollision(*pColliderA);
		}
		// �v���C���[ �~ �΂�
		else if (pColliderB->GetColliderType() == ObjectCollider::Type::eSpring)
		{
			// �A�^�� + �����߂�
			if (pColliderA->PerfectPixelCollision(*pColliderB))
			{
				pColliderA->OnCollision(pColliderB);
				pColliderB->OnCollision(pColliderA);
			}
		}
		// �v���C���[ �~ ����
		else if (pColliderB->GetColliderType() == ObjectCollider::Type::ePlatform)
		{
			// �A�^�� + �����߂�
			if (pColliderA->PerfectPixelCollisionUpperSide(*pColliderB))
			{
				pColliderA->OnCollision(pColliderB);
				pColliderB->OnCollision(pColliderA);
			}
		}
		// �v���C���[ �~ ���[�U�[
		else if (pColliderB->GetColliderType() == ObjectCollider::Type::eLaser)
		{
			// �A�^��
			if (YGame::CollisionBoxBox2D(*pColliderA, *pColliderB))
			{
				pColliderA->OnCollision(pColliderB);
				pColliderB->OnCollision(pColliderA);
			}
		}
		// �v���C���[ �~ �X�C�b�`
		else if (pColliderB->GetColliderType() == ObjectCollider::Type::eSwitch)
		{
			// �A�^��
			if (YGame::CollisionBoxBox2D(collA, *pColliderB))
			{
				pColliderA->OnCollision(pColliderB);
				pColliderB->OnCollision(pColliderA);
			}
		}
		// �v���C���[ �~ ��
		else if (pColliderB->GetColliderType() == ObjectCollider::Type::eKey)
		{
			// �A�^��
			if (YGame::CollisionBoxBox2D(collA, *pColliderB))
			{
				pColliderA->OnCollision(pColliderB);
				pColliderB->OnCollision(pColliderA);
			}
		}

		return;
	}

	// �u���b�N
	if (pColliderA->GetColliderType() == ObjectCollider::Type::eBlock)
	{
		// �u���b�N �~ �u���b�N
		if		(pColliderB->GetColliderType() == ObjectCollider::Type::eBlock)
		{
			// �A�^�� + �����߂�
			if (pColliderA->PerfectPixelCollision(*pColliderB))
			{
				pColliderA->OnCollision(pColliderB);
				pColliderB->OnCollision(pColliderA);
			}
		}
		// �u���b�N �~ �΂�
		else if (pColliderB->GetColliderType() == ObjectCollider::Type::eSpring)
		{
			// �A�^�� + �����߂�
			if (pColliderA->PerfectPixelCollision(*pColliderB))
			{
				pColliderA->OnCollision(pColliderB);
				pColliderB->OnCollision(pColliderA);
			}
		}
		// �u���b�N �~ ����
		else if (pColliderB->GetColliderType() == ObjectCollider::Type::ePlatform)
		{
			// �A�^�� + �����߂�
			if (pColliderA->PerfectPixelCollisionUpperSide(*pColliderB))
			{
				pColliderA->OnCollision(pColliderB);
				pColliderB->OnCollision(pColliderA);
			}
		}
		// �u���b�N �~ ���[�U�[
		else if (pColliderB->GetColliderType() == ObjectCollider::Type::eLaser)
		{
			// �A�^��
			if (YGame::CollisionBoxBox2D(*pColliderA, *pColliderB))
			{
				pColliderA->OnCollision(pColliderB);
				pColliderB->OnCollision(pColliderA);
			}
		}

		return;
	}

	// �S�I�u�W�F�N�g
	if (YGame::CollisionBoxBox2D(*pColliderA, *pColliderB))
	{
		pColliderA->OnCollision(pColliderB);
		pColliderB->OnCollision(pColliderA);
	}
}
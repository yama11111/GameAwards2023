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
	// �A�^�����薳�����邩
	if (pColliderA->GetIsExist() == false || pColliderB->GetIsExist() == false) { return; }

	// �Ŕ��Ⴄ�Ȃ�e��
	if (pColliderA->GetSignIndex() != pColliderB->GetSignIndex()) { return; }

	// �v���C���[
	if (pColliderA->GetColliderType() == ObjectCollider::Type::ePlayer)
	{
		// �v���C���[ �~ �u���b�N
		if (pColliderB->GetColliderType() == ObjectCollider::Type::eBlock)
		{		
			// �����p�R���C�_�[
			Box2D collA;
			collA.SetBox2DCenter(pColliderA->GetBox2DCenter());
			// �傫���ɕ�����������
			Vector2 rad = pColliderA->GetBox2DRadSize();
			collA.SetBox2DRadSize(rad + Vector2(rad.x_ * 1.0f, -(rad.y_ * 0.75f)));

			// �A�^��
			if (YGame::CollisionBoxBox2D(collA, *pColliderB))
			{
				pColliderA->OnCollision(pColliderB);
				pColliderB->OnCollision(pColliderA);
			}

			// �����߂�
			pColliderA->PerfectPixelCollision(*pColliderB);
			pColliderB->PerfectPixelCollision(*pColliderA);

			return;
		}
		// �v���C���[ �~ �΂�
		if (pColliderB->GetColliderType() == ObjectCollider::Type::eSpring)
		{
			// �����p�R���C�_�[
			Box2D collA;
			collA.SetBox2DCenter(pColliderA->GetBox2DCenter());
			// �傫���ɕ�����������
			Vector2 rad = pColliderA->GetBox2DRadSize();
			collA.SetBox2DRadSize(rad + Vector2(rad.x_ * -0.2f, rad.y_ * +0.5f));

			// �A�^��
			if (YGame::CollisionBoxBox2D(collA, *pColliderB))
			{
				pColliderA->OnCollision(pColliderB);
				pColliderB->OnCollision(pColliderA);

				return;
			}

			// �����߂�
			pColliderA->PerfectPixelCollision(*pColliderB);
			pColliderB->PerfectPixelCollision(*pColliderA);

			return;
		}
		// �v���C���[ �~ ����
		if (pColliderB->GetColliderType() == ObjectCollider::Type::ePlatform)
		{
			// �A�^�� + �����߂�
			if (pColliderA->PerfectPixelCollisionUpperSide(*pColliderB))
			{
				pColliderA->OnCollision(pColliderB);
				pColliderB->OnCollision(pColliderA);
			}

			return;
		}
		// �v���C���[ �~ ���[�U�[
		if (pColliderB->GetColliderType() == ObjectCollider::Type::eLaser)
		{
			// �A�^��
			if (YGame::CollisionBoxBox2D(*pColliderA, *pColliderB))
			{
				pColliderA->OnCollision(pColliderB);
				pColliderB->OnCollision(pColliderA);
			}

			return;
		}
		// �v���C���[ �~ �X�C�b�`
		if (pColliderB->GetColliderType() == ObjectCollider::Type::eSwitch)
		{
			// �����p�R���C�_�[
			Box2D collA;
			collA.SetBox2DCenter(pColliderA->GetBox2DCenter());
			// �傫���ɕ�����������
			Vector2 rad = pColliderA->GetBox2DRadSize();
			collA.SetBox2DRadSize(rad + Vector2(rad.x_ * 0.5f, -(rad.y_ * 0.75f)));

			// �A�^��
			if (YGame::CollisionBoxBox2D(collA, *pColliderB))
			{
				pColliderA->OnCollision(pColliderB);
				pColliderB->OnCollision(pColliderA);
			}

			return;
		}
		// �v���C���[ �~ ��
		if (pColliderB->GetColliderType() == ObjectCollider::Type::eKey)
		{
			// �A�^��
			if (YGame::CollisionBoxBox2D(*pColliderA, *pColliderB))
			{
				pColliderA->OnCollision(pColliderB);
				pColliderB->OnCollision(pColliderA);
			}

			return;
		}
		// �v���C���[ �~ �S�[��
		if (pColliderB->GetColliderType() == ObjectCollider::Type::eGoal)
		{
			// �A�^��
			if (YGame::CollisionBoxBox2D(*pColliderA, *pColliderB))
			{
				pColliderA->OnCollision(pColliderB);
				pColliderB->OnCollision(pColliderA);
			}

			return;
		}
	}

	// �u���b�N
	if (pColliderA->GetColliderType() == ObjectCollider::Type::eBlock)
	{
		// �u���b�N �~ �u���b�N
		if (pColliderB->GetColliderType() == ObjectCollider::Type::eBlock)
		{
			// �A�^�� + �����߂�
			pColliderA->PerfectPixelCollision(*pColliderB);
			pColliderB->PerfectPixelCollision(*pColliderA);

			return;
		}
		// �u���b�N �~ �΂�
		if (pColliderB->GetColliderType() == ObjectCollider::Type::eSpring)
		{
			// �����p�R���C�_�[
			Box2D collA;
			collA.SetBox2DCenter(pColliderA->GetBox2DCenter());
			// �傫���ɕ�����������
			Vector2 rad = pColliderA->GetBox2DRadSize();
			collA.SetBox2DRadSize(rad + Vector2(rad.x_ * -0.2f, rad.y_ * +0.5f));

			// �A�^��
			if (YGame::CollisionBoxBox2D(collA, *pColliderB))
			{
				pColliderA->OnCollision(pColliderB);
				pColliderB->OnCollision(pColliderA);

				return;
			}

			// �����߂�
			pColliderA->PerfectPixelCollision(*pColliderB);
			pColliderB->PerfectPixelCollision(*pColliderA);

			return;
		}
		// �u���b�N �~ ����
		if (pColliderB->GetColliderType() == ObjectCollider::Type::ePlatform)
		{
			// �A�^�� + �����߂�
			if (pColliderA->PerfectPixelCollisionUpperSide(*pColliderB))
			{
				pColliderA->OnCollision(pColliderB);
				pColliderB->OnCollision(pColliderA);
			}

			return;
		}
		// �u���b�N �~ ���[�U�[
		if (pColliderB->GetColliderType() == ObjectCollider::Type::eLaser)
		{
			// �A�^��
			if (YGame::CollisionBoxBox2D(*pColliderA, *pColliderB))
			{
				pColliderA->OnCollision(pColliderB);
				pColliderB->OnCollision(pColliderA);
			}

			return;
		}
	}

	// ��
	if (pColliderA->GetColliderType() == ObjectCollider::Type::eKey)
	{
		// �� �~ �S�[��
		if (pColliderB->GetColliderType() == ObjectCollider::Type::eGoal)
		{
			// �����p�R���C�_�[
			Box2D collA;
			collA.SetBox2DCenter(pColliderA->GetBox2DCenter());
			// �傫���ɕ�����������
			Vector2 rad = pColliderA->GetBox2DRadSize();
			collA.SetBox2DRadSize(rad + Vector2(rad.x_ * +0.5f, rad.y_ * +0.5f));

			// �A�^��
			if (YGame::CollisionBoxBox2D(collA, *pColliderB))
			{
				pColliderA->OnCollision(pColliderB);
				pColliderB->OnCollision(pColliderA);
			}

			return;
		}
	}
}
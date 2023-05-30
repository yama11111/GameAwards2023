#include "Goal.h"
#include "MathUtillity.h"
#include <cassert>
#include <cmath>

#include "Stage.h"
#include "LevelData.h"

using YGame::Transform;
using YMath::Vector3;
using YMath::Clamp;

void Goal::Initialize(const size_t signIndex, const YMath::Vector3& pos, const bool isRock)
{
	// �g�����X�t�H�[������
	transform_.reset(new Transform());

	// �`��N���X������
	drawer_.Initialize(transform_.get(), isRock);

	// ���Z�b�g
	Reset(signIndex, pos, isRock);
}

void Goal::Reset(const size_t signIndex, const YMath::Vector3& pos, const bool isRock)
{
	// �g�����X�t�H�[��������
	transform_->Initialize({ pos + spStageMan_->GetTopLeftPos(signIndex), {}, {1.0f,1.0f,1.0f} });
	
	// �O�񍶏�ʒu������
	elderLeftTop_ = spStageMan_->GetTopLeftPos(signIndex);

	// ���b�N�t���O�ݒ�
	isRock_ = isRock;

	// �R���C�_�[�ʒu������
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });

	// �R���C�_�[�T�C�Y������
	Box2D::SetBox2DRadSize({ transform_->scale_.x_, transform_->scale_.y_ });

	// �R���C�_�[�^�C�v�ݒ�
	ObjectCollider::SetColliderType(ObjectCollider::Type::eGoal);

	// �R���C�_�[�Ŕԍ��ݒ�
	ObjectCollider::SetSignIndex(signIndex);

	// �`��N���X���Z�b�g
	drawer_.Reset(isRock);
}

void Goal::PreUpdate()
{
	// ����X�V
	UpdateLeftTop();

	// �R���C�_�[�ʒu�X�V
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });
}

void Goal::PostUpdate()
{
	// �g�����X�t�H�[���s��X�V
	transform_->UpdateMatrix();

	// �`��N���X�X�V
	drawer_.Update();
}

void Goal::Draw()
{
	// �`��
	drawer_.Draw();
}

void Goal::OnCollision(ObjectCollider* pPair)
{
	// �Q�[���N���A���e��
	if (isGameClear_) { return; }

	// �v���C���[�Ȃ�
	if (pPair->GetColliderType() == ObjectCollider::Type::ePlayer)
	{
		// �X�L��������
		if (GetIsActSkill())
		{
			if (isRock_)
			{
				drawer_.Unlock();
			}

			// �N���A
			drawer_.ActivateClearAnimation(pPair->PosRef());

			// �Q�[���N���A
			isGameClear_ = true;
		}
	}
}

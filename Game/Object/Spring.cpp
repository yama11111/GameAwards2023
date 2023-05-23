#include "Spring.h"
#include "MathUtillity.h"
#include <cassert>
#include <cmath>

#include "Stage.h"
#include "LevelData.h"

using YGame::Transform;
using YMath::Vector3;
using YMath::Clamp;

void Spring::Initialize(const size_t signIndex, const YMath::Vector3& pos, const float jumpPower)
{
	// �g�����X�t�H�[������
	transform_.reset(new Transform());

	// �`��N���X������
	drawer_.Initialize(transform_.get());

	// ���Z�b�g
	Reset(signIndex, pos, jumpPower);
}

void Spring::Reset(const size_t signIndex, const YMath::Vector3& pos, const float jumpPower)
{
	// �g�����X�t�H�[��������
	transform_->Initialize({ pos + spStageMan_->GetTopLeftPos(signIndex), {}, {1.0f,1.0f,1.0f} });

	// �W�����v��
	jumpPower_ = jumpPower;

	// �R���C�_�[�ʒu������
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });

	// �R���C�_�[�T�C�Y������
	Box2D::SetBox2DRadSize({ LevelData::Spring::CollRadSize });
	
	// �R���C�_�[�^�C�v�ݒ�
	ObjectCollider::SetColliderType(ObjectCollider::Type::eSpring);

	// �R���C�_�[�Ŕԍ��ݒ�
	ObjectCollider::SetSignIndex(signIndex);

	// �`��N���X���Z�b�g
	drawer_.Reset();
}

void Spring::PreUpdate()
{
	// �R���C�_�[�ʒu�X�V
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });
}

void Spring::PostUpdate()
{
	// �g�����X�t�H�[���s��X�V
	transform_->UpdateMatrix();

	// �`��N���X�X�V
	drawer_.Update();
}

void Spring::Draw()
{
	// �`��
	drawer_.Draw();
}

void Spring::OnCollision(ObjectCollider* pPair)
{
	// �v���C���[���u���b�N�Ȃ�
	if (pPair->GetColliderType() == ObjectCollider::Type::eBlock)
	{
		// ������
		bool isUnder = transform_->pos_.y_ >= (pPair->GetBox2DCenter().y_ - pPair->GetBox2DRadSize().y_);

		// ��������Ȃ��Ȃ�e��
		if (isUnder == false || pPair->SpeedRef().y_ > 0.0f) { return; }

		// �W�����v
		pPair->SpeedRef().y_ = 3.0f;
	}
}

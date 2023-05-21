#include "Laser.h"
#include "MathUtillity.h"
#include <cassert>
#include <cmath>

using YGame::Transform;
using YMath::Vector3;
using YMath::Clamp;

void Laser::Initialize(const size_t signIndex, const YMath::Vector3& pos, const YMath::Vector3& direction)
{
	// �g�����X�t�H�[������
	transform_.reset(new Transform());

	// �`��N���X������
	drawer_.Initialize(transform_.get(), &beamLength_);

	// ���Z�b�g
	Reset(signIndex, pos, direction);
}

void Laser::Reset(const size_t signIndex, const YMath::Vector3& pos, const YMath::Vector3& direction)
{
	// �g�����X�t�H�[��������
	transform_->Initialize({ pos, {}, {1.0f,1.0f,1.0f} });
	
	// �R���C�_�[�ʒu������
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });

	// �R���C�_�[�T�C�Y������
	Box2D::SetBox2DRadSize({ transform_->scale_.x_, transform_->scale_.y_ });

	// �R���C�_�[�^�C�v�ݒ�
	ObjectCollider::SetColliderType(ObjectCollider::Type::eLaser);

	// �R���C�_�[�Ŕԍ��ݒ�
	ObjectCollider::SetSignIndex(signIndex);

	// �`��N���X���Z�b�g
	drawer_.Reset();
}

void Laser::PreUpdate()
{
	// �R���C�_�[�ʒu�X�V
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });
}

void Laser::PostUpdate()
{
	// �g�����X�t�H�[���s��X�V
	transform_->UpdateMatrix();

	// �`��N���X�X�V
	drawer_.Update();
}

void Laser::Draw()
{
	// �`��
	drawer_.Draw();
}

void Laser::OnCollision(ObjectCollider* pPair)
{
}

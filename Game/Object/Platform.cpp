#include "Platform.h"
#include "MathUtillity.h"
#include <cassert>
#include <cmath>

using YGame::Transform;
using YMath::Vector3;
using YMath::Clamp;

void Platform::Initialize(const size_t signIndex, const YMath::Vector3& pos, const float length)
{
	// �g�����X�t�H�[������
	transform_.reset(new Transform());

	// �`��N���X������
	drawer_.Initialize(transform_.get());

	// ���Z�b�g
	Reset(signIndex, pos, length);
}

void Platform::Reset(const size_t signIndex, const YMath::Vector3& pos, const float length)
{
	// �g�����X�t�H�[��������
	transform_->Initialize({ pos, {}, {length,1.0f,1.0f} });

	// �R���C�_�[�ʒu������
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });

	// �R���C�_�[�T�C�Y������
	Box2D::SetBox2DRadSize({ transform_->scale_.x_, 0.1f });

	// �R���C�_�[�^�C�v�ݒ�
	ObjectCollider::SetColliderType(ObjectCollider::Type::ePlatform);

	// �`��N���X���Z�b�g
	drawer_.Reset();
}

void Platform::PreUpdate()
{
	// �R���C�_�[�ʒu�X�V
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });
}

void Platform::PostUpdate()
{
	// �g�����X�t�H�[���s��X�V
	transform_->UpdateMatrix();

	// �`��N���X�X�V
	drawer_.Update();
}

void Platform::Draw()
{
	// �`��
	drawer_.Draw();
}

void Platform::OnCollision(ObjectCollider* pPair)
{
}

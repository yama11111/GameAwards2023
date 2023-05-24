#include "Laser.h"
#include "MathUtillity.h"
#include "CalcTransform.h"
#include "LevelData.h"
#include <cassert>
#include <cmath>

#include "Stage.h"
#include "LevelData.h"

using YGame::Transform;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Clamp;

// �f�t�H���g��]��
static Vector3 defRota = YMath::AdjustAngle(Vector3(0.0f, -1.0f, 0.0f).Normalized());

void Laser::Initialize(const size_t signIndex, const YMath::Vector3& pos, const YMath::Vector3& direction, const float length)
{
	// �g�����X�t�H�[������
	transform_.reset(new Transform());

	// �`��N���X������
	drawer_.Initialize(transform_.get(), &beamLength_);

	// ���Z�b�g
	Reset(signIndex, pos, direction, length);
}

void Laser::Reset(const size_t signIndex, const YMath::Vector3& pos, const YMath::Vector3& direction, const float length)
{
	// �g�����X�t�H�[��������
	transform_->Initialize({ pos + spStageMan_->GetTopLeftPos(signIndex), {}, {1.0f,1.0f,1.0f} });

	// �O�񍶏�ʒu������
	elderLeftTop_ = spStageMan_->GetTopLeftPos(signIndex);

	// ����������
	direction_ = direction;
	
	// �r�[���̒���
	beamLength_ = 0.0f;

	// �r�[���̍ő�̒���
	beamMaxLength_ = length / 2.0f;

	// �r�[���̒����v�Z
	CalcBeamLength();

	// �R���C�_�[�^�C�v�ݒ�
	ObjectCollider::SetColliderType(ObjectCollider::Type::eLaser);

	// �R���C�_�[�Ŕԍ��ݒ�
	ObjectCollider::SetSignIndex(signIndex);

	// �`��N���X���Z�b�g
	drawer_.Reset();
}

void Laser::PreUpdate()
{
	// ����X�V
	UpdateLeftTop();

	// �r�[�������ύX
	if (isColl_ == false) 
	{
		// �r�[���L�΂�
		beamLength_ += 0.2f;
		
		// �r�[������
		beamLength_ = (std::min)(beamLength_, beamMaxLength_);
	}
	isColl_ = false;

	// �r�[���̒����v�Z
	CalcBeamLength();
}

void Laser::PostUpdate()
{
	// �����v�Z
	Vector3 rota = YMath::AdjustAngle(direction_.Normalized());
	
	// �g�����X�t�H�[���s��X�V
	transform_->UpdateMatrix({ {}, defRota + rota, {} });

	// �r�[���̒����v�Z
	CalcBeamLength();

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
	// �u���b�N�Ȃ�
	if (pPair->GetColliderType() == ObjectCollider::Type::eBlock ||
		pPair->GetColliderType() == ObjectCollider::Type::eSpring ||
		pPair->GetColliderType() == ObjectCollider::Type::ePlatform)
	{
		// ���S���W�ƃT�C�Y�擾
		Vector2 center = pPair->GetBox2DCenter();
		Vector2 radSize = pPair->GetBox2DRadSize();

		// �������ɒ����v�Z
		if		(direction_.x_ > 0.0f)
		{
			beamLength_ = ((center.x_ - radSize.x_) - transform_->pos_.x_) / 2.0f;
		}
		else if (direction_.x_ < 0.0f)
		{
			beamLength_ = (transform_->pos_.x_ - (center.x_ + radSize.x_)) / 2.0f;
		}
		else if (direction_.y_ > 0.0f)
		{
			beamLength_ = ((center.y_ - radSize.y_) - transform_->pos_.y_) / 2.0f;
		}
		else if (direction_.y_ < 0.0f)
		{
			beamLength_ = (transform_->pos_.y_ - (center.y_ - radSize.y_)) / 2.0f;
		}

		isColl_ = true;

		CalcBeamLength();
	}
}

void Laser::CalcBeamLength()
{
	// ��������ʒu�ƃT�C�Y�v�Z
	Vector2 center = { transform_->pos_.x_, transform_->pos_.y_ };
	Vector2 radSize = {};

	if (direction_.x_ != 0.0f) 
	{
		radSize.x_ = transform_->scale_.y_ * beamLength_;
		radSize.y_ = transform_->scale_.x_ / 10.0f;

		if (direction_.x_ > 0.0f)
		{
			center.x_ += radSize.x_;
		}
		else if (direction_.x_ < 0.0f)
		{
			center.x_ -= radSize.x_;
		}
	}
	else if (direction_.y_ != 0.0f) 
	{
		radSize.x_ = transform_->scale_.x_ / 10.0f;
		radSize.y_ = transform_->scale_.y_ * beamLength_;

		if (direction_.y_ > 0.0f)
		{
			center.y_ += radSize.y_;
		}
		else if (direction_.y_ < 0.0f)
		{
			center.y_ -= radSize.y_;
		}
	}

	// �R���C�_�[�ʒu������
	Box2D::SetBox2DCenter(center);

	// �R���C�_�[�T�C�Y������
	Box2D::SetBox2DRadSize(radSize);
}

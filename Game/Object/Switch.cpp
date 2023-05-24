#include "Switch.h"
#include "MathUtillity.h"
#include <cassert>
#include <cmath>

#include "Stage.h"
#include "LevelData.h"

using YGame::Transform;
using YMath::Vector3;
using YMath::Clamp;

void Switch::Initialize(const size_t signIndex, const YMath::Vector3& pos, const bool isAct)
{
	// �g�����X�t�H�[������
	transform_.reset(new Transform());

	// �`��N���X������
	drawer_.Initialize(transform_.get(), SwitchDrawerCommon::Type::eGreen);

	// ���Z�b�g
	Reset(signIndex, pos, isAct);
}

void Switch::Reset(const size_t signIndex, const YMath::Vector3& pos, const bool isAct)
{
	// �g�����X�t�H�[��������
	transform_->Initialize({ pos + spStageMan_->GetTopLeftPos(signIndex), {}, {1.0f,1.0f,1.0f} });

	// �O�񍶏�ʒu������
	elderLeftTop_ = spStageMan_->GetTopLeftPos(signIndex);

	// ����t���O�ݒ�
	isAct_ = isAct;

	// �R���C�_�[�ʒu������
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });

	// �R���C�_�[�T�C�Y������
	Box2D::SetBox2DRadSize({ transform_->scale_.x_, transform_->scale_.y_ });

	// �R���C�_�[�^�C�v�ݒ�
	ObjectCollider::SetColliderType(ObjectCollider::Type::eSwitch);

	// �R���C�_�[�Ŕԍ��ݒ�
	ObjectCollider::SetSignIndex(signIndex);


	// �`��N���X���Z�b�g
	drawer_.Reset(SwitchDrawerCommon::Type::eGreen);
}

void Switch::PreUpdate()
{
	// ����X�V
	UpdateLeftTop();

	// �R���C�_�[�ʒu�X�V
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });
}

void Switch::PostUpdate()
{
	// �g�����X�t�H�[���s��X�V
	transform_->UpdateMatrix();

	// �X�L��������
	if (GetIsActSkill())
	{
		// �X�C�b�`�؂�ւ�
		isAct_ = !isAct_;
		
		// �X�L���I��
		SetIsActSkill(false);
	}

	// ����A�j��
	drawer_.AnimateSwitch(isAct_);

	// �`��N���X�X�V
	drawer_.Update();
}

void Switch::Draw()
{
	// �`��
	drawer_.Draw();
}

void Switch::OnCollision(ObjectCollider* pPair)
{
}

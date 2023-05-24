#include "Key.h"
#include "MathUtillity.h"
#include <cassert>
#include <cmath>

#include "Stage.h"
#include "LevelData.h"

using YGame::Transform;
using YMath::Vector3;
using YMath::Clamp;

void Key::Initialize(const size_t signIndex, const YMath::Vector3& pos)
{
	// �g�����X�t�H�[������
	transform_.reset(new Transform());

	// �`��N���X������
	drawer_.Initialize(transform_.get());

	// ���Z�b�g
	Reset(signIndex, pos);
}

void Key::Reset(const size_t signIndex, const YMath::Vector3& pos)
{
	// �g�����X�t�H�[��������
	transform_->Initialize({ pos + spStageMan_->GetTopLeftPos(signIndex), {}, {1.0f,1.0f,1.0f} });
	
	// �O�񍶏�ʒu������
	elderLeftTop_ = spStageMan_->GetTopLeftPos(signIndex);

	// �v���C���[�|�C���^
	pPlayerPos_ = nullptr;

	// �R���C�_�[�ʒu������
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });

	// �R���C�_�[�T�C�Y������
	Box2D::SetBox2DRadSize({ transform_->scale_.x_, transform_->scale_.y_ });

	// �R���C�_�[�^�C�v�ݒ�
	ObjectCollider::SetColliderType(ObjectCollider::Type::eKey);

	// �R���C�_�[�Ŕԍ��ݒ�
	ObjectCollider::SetSignIndex(signIndex);


	// �`��N���X���Z�b�g
	drawer_.Reset();
}

void Key::PreUpdate()
{
	// ����X�V
	UpdateLeftTop();

	// �R���C�_�[�ʒu�X�V
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });
}

void Key::PostUpdate()
{
	// �v���C���[�Ǐ]
	UpdateFollowPlayer();

	// �g�����X�t�H�[���s��X�V
	transform_->UpdateMatrix();

	// �`��N���X�X�V
	drawer_.Update();
}

void Key::Draw()
{
	// �`��
	drawer_.Draw();
}

void Key::UpdateFollowPlayer()
{
	// null�Ȃ�e��
	if (pPlayerPos_ == nullptr) { return; }

	transform_->pos_ = *pPlayerPos_ + Vector3(0, 1.5f, 0);
}

void Key::OnCollision(ObjectCollider* pPair)
{
	// �u���b�N�Ȃ�
	if (pPair->GetColliderType() == ObjectCollider::Type::ePlayer)
	{
		// ���W�|�C���^�ɑ��
		pPlayerPos_ = pPair->PosPointer();
	}
}

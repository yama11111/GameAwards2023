#include "DemoPlayer.h"
#include "MathUtillity.h"
#include <cassert>
#include <cmath>

using YGame::Transform;
using YMath::Vector3;
using YMath::Clamp;

YInput::Keys* DemoPlayer::spKeys_ = nullptr;
YGame::MapChip* DemoPlayer::spMapChip_ = nullptr;

void DemoPlayer::StaticInitialize()
{
	// �L�[�C���X�^���X�擾
	spKeys_ = YInput::Keys::GetInstance();
}

void DemoPlayer::StaticSetMapChip(YGame::MapChip* pMapChip)
{
	// null�`�F�b�N
	assert(pMapChip);

	// ���
	spMapChip_ = pMapChip;
}

void DemoPlayer::Initialize(const YMath::Vector3& pos)
{
	// �g�����X�t�H�[������
	transform_.reset(new Transform());

	// �`��N���X������
	drawer_.Initialize(transform_.get(), &direction_);

	// ���Z�b�g
	Reset(pos);
}

void DemoPlayer::Reset(const YMath::Vector3& pos)
{
	// �g�����X�t�H�[��������
	transform_->Initialize({ pos });

	// �R���C�_�[������
	YGame::MapChipCollider::Initialize({ transform_->scale_ });

	// ���� (�E)
	direction_ = Vector3(+1, 0, 0);

	// �`��N���X���Z�b�g
	drawer_.Reset();
}

void DemoPlayer::Move()
{
	// x���ړ�
	speed_.x_ += spKeys_->Horizontal();

	// �N�����v
	speed_.x_ = Clamp(speed_.x_, -0.5f, +0.5f);
}

void DemoPlayer::Jump()
{
	// �W�����v�񐔂��ő�Ȃ�e��
	if (1 <= jumpCount_) { return; }

	// SPACE�L�[��������
	if (spKeys_->IsTrigger(DIK_SPACE))
	{
		// �W�����v
		speed_.y_ = 2.0f;

		// �W�����v�A�j���[�V����
		drawer_.JumpAnimation();

		// �W�����v�J�E���g
		jumpCount_++;
	}
}

void DemoPlayer::Update()
{
	// �ړ�
	Move();

	// �W�����v
	Jump();

	// ���C��
	if (speed_.x_ > 0)
	{
		speed_.x_ -= 0.1f;
		speed_.x_ = (std::max)(0.0f, speed_.x_);;
	}
	if (speed_.x_ < 0)
	{
		speed_.x_ += 0.1f;
		speed_.x_ = (std::min)(0.0f, speed_.x_);
	}

	// �d��
	speed_.y_ -= 0.2f;

	// �}�b�v�`�b�v�Ƃ̃A�^������
	spMapChip_->PerfectPixelCollision(*this);

	// ���n��
	if (IsLanding())
	{
		// ���n�A�j���[�V����
		drawer_.LandingAnimation();

		// �W�����v�J�E���g���Z�b�g
		jumpCount_ = 0;
	}

	// �ړ�
	transform_->pos_ += speed_;

	// �g�����X�t�H�[���s��X�V
	transform_->UpdateMatrix();

	// �`��N���X�X�V
	drawer_.Update();
}

void DemoPlayer::Draw()
{
	// �`��
	drawer_.Draw();
}

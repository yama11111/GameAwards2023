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
	transform_->Initialize({ pos, {}, {1.0f,1.5f,1.0f} });

	// �ʒu���
	center_ = transform_->pos_;

	// ���a�ݒ�
	SafeSetRadius(1.5f);

	// �R���C�_�[������
	YGame::MapChipCollider::Initialize({ {1.5f,2.0f,1.5f} });

	// ���� (�E)
	direction_ = Vector3(+1, 0, 0);

	// �W�����v�J�E���g���Z�b�g
	jumpCount_ = 0;

	// �S�[���t���O���Z�b�g
	isGoal_ = false;

	// �`��N���X���Z�b�g
	drawer_.Reset();
}

void DemoPlayer::Move()
{
	// x���ړ�
	speed_.x_ += spKeys_->Horizontal();

	// �N�����v
	speed_.x_ = Clamp(speed_.x_, -0.5f, +0.5f);

	// �ۑ��p�t���O
	bool isMove = false;

	// �ړ����Ă���Ȃ�
	if (spKeys_->Horizontal() != 0)
	{
		// �t���O��true��
		isMove = true;

		// �����ύX
		if (speed_.x_ > 0) { direction_.x_ = +1.0f; }
		if (speed_.x_ < 0) { direction_.x_ = -1.0f; }
	}
	
	// �ړ��A�j���[�V����
	drawer_.SetActMoveAnimation(isMove);
}

void DemoPlayer::Jump()
{
	// �W�����v�񐔂��ő�Ȃ�e��
	if (1 <= jumpCount_) { return; }

	// SPACE�L�[��������
	if (spKeys_->IsTrigger(DIK_SPACE))
	{
		// �W�����v
		speed_.y_ = 1.0f;

		// �W�����v�A�j���[�V����
		drawer_.JumpAnimation();

		// �W�����v�J�E���g
		jumpCount_++;
	}
}

void DemoPlayer::UpdatePhysics()
{
	// �S�[��������͖���
	if (isGoal_) { return; }

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
	speed_.y_ -= 0.1f;

	// �}�b�v�`�b�v�Ƃ̃A�^������
	spMapChip_->PerfectPixelCollision(*this);

	// ���n��
	if (IsLanding() && IsElderLanding() == false)
	{
		// ���n�A�j���[�V����
		drawer_.LandingAnimation();

		// �W�����v�J�E���g���Z�b�g
		jumpCount_ = 0;
	}

	// �ړ�
	transform_->pos_ += speed_;
}

void DemoPlayer::Goal()
{
	// �S�[���A�j���[�V����
	drawer_.GoalAnimation();

	// �S�[��
	isGoal_ = true;
}

void DemoPlayer::Update()
{
	// ���������X�V
	UpdatePhysics();

	// �g�����X�t�H�[���s��X�V
	transform_->UpdateMatrix();

	// �ʒu���
	center_ = transform_->pos_;

	// �`��N���X�X�V
	drawer_.Update();
}

void DemoPlayer::Draw()
{
	// �`��
	drawer_.Draw();
}


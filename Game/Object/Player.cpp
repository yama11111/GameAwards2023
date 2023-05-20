#include "Player.h"
#include "MathUtillity.h"
#include "Keys.h"
#include <cassert>
#include <cmath>

using YGame::Transform;
using YMath::Vector3;
using YMath::Clamp;

YInput::Keys* Player::spKeys_ = nullptr;

void Player::StaticInitialize()
{
	// �L�[�C���X�^���X�擾
	spKeys_ = YInput::Keys::GetInstance();
}

void Player::Initialize(const YMath::Vector3& pos)
{
	// �g�����X�t�H�[������
	transform_.reset(new Transform());

	// �`��N���X������
	drawer_.Initialize(transform_.get(), &direction_);

	// ���Z�b�g
	Reset(pos);
}

void Player::Reset(const YMath::Vector3& pos)
{
	// �g�����X�t�H�[��������
	transform_->Initialize({ pos, {}, {1.0f,1.5f,1.0f} });

	// ���� (�E)
	direction_ = Vector3(+1, 0, 0);

	// �W�����v�J�E���g���Z�b�g
	jumpCount_ = 0;

	// �R���C�_�[�T�C�Y������
	Box2D::SetBox2DRadSize({ transform_->scale_.x_, transform_->scale_.y_ });

	// �`��N���X���Z�b�g
	drawer_.Reset();
}

void Player::Move()
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

void Player::Jump()
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

void Player::UpdatePhysics()
{
	// �S�[��������͖���
	//if (isGoal_) { return; }

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
	//speed_.y_ -= 0.1f;
	
	// ���n��
	//if (IsLanding() && IsElderLanding() == false)
	//{
	//	// ���n�A�j���[�V����
	//	drawer_.LandingAnimation();

	//	// �W�����v�J�E���g���Z�b�g
	//	jumpCount_ = 0;
	//}

	// �ړ�
	transform_->pos_ += speed_;
}

void Player::Update()
{
	// ���������X�V
	UpdatePhysics();

	// �g�����X�t�H�[���s��X�V
	transform_->UpdateMatrix();

	// �`��N���X�X�V
	drawer_.Update();

	// �R���C�_�[�ʒu�X�V
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });
}

void Player::Draw()
{
	// �`��
	drawer_.Draw();
}


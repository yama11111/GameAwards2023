#include "Player.h"
#include "MathUtillity.h"
#include "Keys.h"
#include <cassert>
#include <cmath>
#include <imgui.h>

#include "Stage.h"
#include "LevelData.h"

using YGame::Transform;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Clamp;

YInput::Keys* Player::spKeys_ = nullptr;

void Player::StaticInitialize()
{
	// �L�[�C���X�^���X�擾
	spKeys_ = YInput::Keys::GetInstance();
}

void Player::Initialize(const size_t signIndex, const YMath::Vector3& pos)
{
	// �g�����X�t�H�[������
	transform_.reset(new Transform());

	// �`��N���X������
	drawer_.Initialize(transform_.get(), &direction_);

	// ���Z�b�g
	Reset(signIndex, pos);
}

void Player::Reset(const size_t signIndex, const YMath::Vector3& pos)
{
	// �g�����X�t�H�[��������
	transform_->Initialize({ pos, {}, {1.0f,1.0f,1.0f} });

	// �X�s�[�h������
	speed_ = {};
	
	// ���� (�E)
	direction_ = Vector3(+1, 0, 0);

	// �W�����v�J�E���g���Z�b�g
	jumpCount_ = 0;


	// �R���C�_�[�ʒu������
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });

	// �R���C�_�[�T�C�Y������
	Box2D::SetBox2DRadSize({ LevelData::Player::CollRadSize });

	// �R���C�_�[�^�C�v�ݒ�
	ObjectCollider::SetColliderType(ObjectCollider::Type::ePlayer);

	// �R���C�_�[�Ŕԍ��ݒ�
	ObjectCollider::SetSignIndex(signIndex);


	// �}�b�v�`�b�v�R���C�_�[������
	YukiMapchipCollider::Initialize();
	trfm_ = *transform_;
	
	// �}�b�v�`�b�v�R���C�_�[���a�ݒ�
	radius_ = { GetBox2DRadSize().x_, GetBox2DRadSize().y_, 0.0f };


	// �����t���O������������
	isGetOffAct_ = false;

	// �����t���O�^�C�}�[
	isGetOffTimer_.Initialize(5);
	isGetOffTimer_.SetActive(false);

	// �`��N���X���Z�b�g
	drawer_.Reset();
}

void Player::Move()
{
	// x���ړ�
	speed_.x_ += spKeys_->Horizontal() * LevelData::Player::Acceleration;

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

	// ����A�N�V�������Ȃ�e��
	if (spKeys_->IsDown(DIK_E)) { return; }

	// SPACE�L�[��������
	if (spKeys_->IsTrigger(DIK_SPACE))
	{
		// �W�����v
		speed_.y_ = LevelData::Player::JumpPower;

		// �W�����v�A�j���[�V����
		drawer_.JumpAnimation();

		// �W�����v�J�E���g
		jumpCount_++;
	}
}

void Player::Landing()
{
	// �d�͂��Ȃ���
	speed_.y_ = 0.0f;

	// �W�����v�J�E���g���Z�b�g
	jumpCount_ = 0;

	// ���n�����u�ԂȂ�
	if (IsLandingMoment() || (isGrounded_ && isOldGrounded_ == false))
	{
		// ���n�A�j���[�V����
		drawer_.LandingAnimation();
	}
}

void Player::UpdatePhysics()
{
	// �S�[��������͖���
	if (isGameClear_) { return; }

	// �ړ�
	Move();

	// �W�����v
	Jump();

	// ���C��
	if (speed_.x_ > 0.0f)
	{
		speed_.x_ -= LevelData::Player::Friction;
		speed_.x_ = (std::max)(0.0f, speed_.x_);
	}
	if (speed_.x_ < 0.0f)
	{
		speed_.x_ += LevelData::Player::Friction;
		speed_.x_ = (std::min)(0.0f, speed_.x_);
	}

	// �d��
	speed_.y_ -= gravity_;

	// �N�����v
	speed_.x_ = Clamp(speed_.x_, -LevelData::Player::MaxSpeed.x_, +LevelData::Player::MaxSpeed.x_);
	speed_.y_ = Clamp(speed_.y_, -LevelData::Player::MaxGravity, +LevelData::Player::MaxSpeed.y_);
}

Vector3& Player::PosRef()
{
	return transform_->pos_;
}

Vector3& Player::SpeedRef()
{
	return speed_;
}

void Player::OnCollision(ObjectCollider* pPair)
{
	// �u���b�N�Ȃ�
	if (pPair->GetColliderType() == ObjectCollider::Type::eBlock)
	{
		// E �ŃA�N�V����
		pPair->SetIsActSkill(spKeys_->IsDown(DIK_E));
	}
	// �΂˂Ȃ�
	else if (pPair->GetColliderType() == ObjectCollider::Type::eSpring)
	{
		// �㑤��
		bool isUp = transform_->pos_.y_ >= (pPair->GetBox2DCenter().y_ + pPair->GetBox2DRadSize().y_);

		// �㑤����Ȃ��Ȃ�e��
		if (isUp == false || speed_.y_ > 0.0f) { return; }

		// �W�����v
		speed_.y_ = 3.0f;

		// �A�N�V����
		pPair->SetIsActSkill(true);

		// ���n�t���O������
		ResetIsLanding();
		isGrounded_ = false;
	}
	// ���[�U�[�Ȃ�
	else if (pPair->GetColliderType() == ObjectCollider::Type::eLaser)
	{
		// ����
		isAlive_ = false;

		// �A�j���[�V����
		drawer_.DeadAnimation();
	}
	// �X�C�b�`�Ȃ�
	else if (pPair->GetColliderType() == ObjectCollider::Type::eSwitch)
	{
		// E �ŃA�N�V����
		if (spKeys_->IsTrigger(DIK_E))
		{
			pPair->SetIsActSkill(true);
		}
	}
	// �S�[���Ȃ�
	else if (pPair->GetColliderType() == ObjectCollider::Type::eGoal)
	{
		// �A�N�V����
		pPair->SetIsActSkill(true);
	}
}

void Player::Draw()
{
	// �`��
	drawer_.Draw();
}

void Player::Update()
{
	// ���
	trfm_ = *transform_;
	velocity_ = speed_;
	
	// ����
	spStageMan_->PPC(this);
	
	// �߂�
	transform_->pos_ = trfm_.pos_;
	speed_ = velocity_;
}

void Player::PreUpdate()
{
	// ���W�X�V
	YukiMapchipCollider::UpdatePos();

	// ���������X�V
	UpdatePhysics();
	

	// ������ ���� �^�C�}�[�I���܂ō~���
	if (spKeys_->IsUnder())
	{
		isGetOffAct_ = true;
		isGetOffTimer_.Reset(true);
	}
	isGetOffTimer_.Update();
	if (isGetOffTimer_.IsEnd())
	{
		isGetOffAct_ = false;
	}

	// �~��邩
	SetIsGetOff(isGetOffAct_);


	// ���n�t���O������
	ResetIsLanding();

	// �}�b�v�`�b�v�R���C�_�[�X�V
	Update();
	
	
	// �R���C�_�[�ʒu�X�V
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });
}

void Player::PostUpdate()
{
	// ���n��
	if (IsLanding() || isGrounded_)
	{
		// ���n
 		Landing();
	}

	// �ړ�
	transform_->pos_ += speed_;

	// �g�����X�t�H�[���s��X�V
	transform_->UpdateMatrix();

	// �`��N���X�X�V
	drawer_.Update();
}


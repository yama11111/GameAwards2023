#include "Block.h"
#include "MathUtillity.h"
#include "Keys.h"
#include <cassert>
#include <cmath>

#include "Stage.h"

using YGame::Transform;
using YMath::Vector3;
using YMath::Clamp;

YInput::Keys* Block::spKeys_ = nullptr;
void Block::StaticInitialize()
{
	// �L�[�C���X�^���X�擾
	spKeys_ = YInput::Keys::GetInstance();
}

void Block::Initialize(const size_t signIndex, const YMath::Vector3& pos)
{
	// �g�����X�t�H�[������
	transform_.reset(new Transform());

	// �`��N���X������
	drawer_.Initialize(transform_.get(), BlockDrawerCommon::Type::eWhite);

	// ���Z�b�g
	Reset(signIndex, pos);
}

void Block::Reset(const size_t signIndex, const YMath::Vector3& pos)
{
	// �g�����X�t�H�[��������
	transform_->Initialize({ pos, {}, {1.0f,1.0f,1.0f} });

	// �X�s�[�h������
	speed_ = {};


	// �R���C�_�[�ʒu������
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });

	// �R���C�_�[�T�C�Y������
	Box2D::SetBox2DRadSize({ transform_->scale_.x_ - 0.1f, transform_->scale_.y_ - 0.1f });

	// �R���C�_�[�^�C�v�ݒ�
	ObjectCollider::SetColliderType(ObjectCollider::Type::eBlock);

	// �R���C�_�[�Ŕԍ��ݒ�
	ObjectCollider::SetSignIndex(signIndex);


	// �}�b�v�`�b�v�R���C�_�[������
	YukiMapchipCollider::Initialize();
	trfm_ = *transform_;

	// �}�b�v�`�b�v�R���C�_�[���a�ݒ�
	radius_ = { GetBox2DRadSize().x_, GetBox2DRadSize().y_, 0.0f};


	// �`��N���X���Z�b�g
	drawer_.Reset(BlockDrawerCommon::Type::eWhite);
}

Vector3& Block::PosRef()
{
	return transform_->pos_;
}

Vector3& Block::SpeedRef()
{
	return speed_;
}

void Block::Move()
{
	// �X�L���������̂�
	if (GetIsActSkill() == false) { return; }

	// x���ړ�
	speed_.x_ += spKeys_->Horizontal();

	// �N�����v
	speed_.x_ = Clamp(speed_.x_, -0.5f, +0.5f);

	// �����邩
	SetIsActSkill(spKeys_->IsDown(DIK_E));
}

void Block::Landing()
{
	// �d�͂��Ȃ���
	speed_.y_ = 0.0f;

	// ���n�����u�ԂȂ�
	if (IsLandingMoment())
	{

	}
}

void Block::UpdatePhysics()
{
	// �S�[��������͖���
	//if (isGoal_) { return; }

	// �ړ�
	Move();

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

	// �N�����v
	speed_.x_ = Clamp(speed_.x_, -1.5f, +1.5f);
	speed_.y_ = Clamp(speed_.y_, -1.5f, +1.5f);
}

void Block::OnCollision(ObjectCollider* pPair)
{

}

void Block::Draw()
{
	// �`��
	drawer_.Draw();
}

void Block::Update()
{
	// ���
	trfm_ = *transform_;
	velocity_ = speed_;

	// ����
	spStageMan_->PPC(this);

	// �߂�
	*transform_ = trfm_;
	speed_ = velocity_;
}

void Block::PreUpdate()
{
	// ���W�X�V
	YukiMapchipCollider::UpdatePos();

	// ���������X�V
	UpdatePhysics();
	

	// ���n�t���O������
	ResetIsLanding();

	// �}�b�v�`�b�v�R���C�_�[�X�V
	Update();


	// �R���C�_�[�ʒu�X�V
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });
}

void Block::PostUpdate()
{
	// ���n��
	if (IsLanding())
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

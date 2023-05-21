#include "Player.h"
#include "MathUtillity.h"
#include <cassert>
#include <cmath>
#include "Player.h"
YInput::Keys* Player::spKeys_ = nullptr;

void Player::StaticInitialize()
{
	// �L�[�C���X�^���X�擾
	spKeys_ = YInput::Keys::GetInstance();
}

void Player::Initialize(const YMath::Vector3& pos)
{
	// �g�����X�t�H�[������
	transform_.reset(new YGame::Transform());

	// �`��N���X������
	drawer_.Initialize(transform_.get(), &direction_);

	// ���Z�b�g
	Reset(pos);
}

void Player::Reset(const YMath::Vector3& pos)
{
	transform_->pos_ = pos;

	// �`��N���X���Z�b�g
	drawer_.Reset();
}

void Player::Update()
{
	int spd = 0.2f;

	transform_->pos_.x_ += spKeys_->Horizontal() * spd;

	transform_->UpdateMatrix();

	drawer_.Update();
}

void Player::Draw()
{
	drawer_.Draw();
}

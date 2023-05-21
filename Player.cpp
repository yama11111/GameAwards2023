#include "Player.h"
#include "MathUtillity.h"
#include <cassert>
#include <cmath>
#include "Player.h"
YInput::Keys* Player::spKeys_ = nullptr;

void Player::StaticInitialize()
{
	// キーインスタンス取得
	spKeys_ = YInput::Keys::GetInstance();
}

void Player::Initialize(const YMath::Vector3& pos)
{
	// トランスフォーム生成
	transform_.reset(new YGame::Transform());

	// 描画クラス初期化
	drawer_.Initialize(transform_.get(), &direction_);

	// リセット
	Reset(pos);
}

void Player::Reset(const YMath::Vector3& pos)
{
	transform_->pos_ = pos;

	// 描画クラスリセット
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

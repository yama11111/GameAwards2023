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
	// キーインスタンス取得
	spKeys_ = YInput::Keys::GetInstance();
}

void Player::Initialize(const YMath::Vector3& pos)
{
	// トランスフォーム生成
	transform_.reset(new Transform());

	// 描画クラス初期化
	drawer_.Initialize(transform_.get(), &direction_);

	// リセット
	Reset(pos);
}

void Player::Reset(const YMath::Vector3& pos)
{
	// トランスフォーム初期化
	transform_->Initialize({ pos, {}, {1.0f,1.5f,1.0f} });

	// 向き (右)
	direction_ = Vector3(+1, 0, 0);

	// ジャンプカウントリセット
	jumpCount_ = 0;

	// コライダーサイズ初期化
	Box2D::SetBox2DRadSize({ transform_->scale_.x_, transform_->scale_.y_ });

	// 描画クラスリセット
	drawer_.Reset();
}

void Player::Move()
{
	// x軸移動
	speed_.x_ += spKeys_->Horizontal();

	// クランプ
	speed_.x_ = Clamp(speed_.x_, -0.5f, +0.5f);

	// 保存用フラグ
	bool isMove = false;

	// 移動しているなら
	if (spKeys_->Horizontal() != 0)
	{
		// フラグをtrueに
		isMove = true;

		// 向き変更
		if (speed_.x_ > 0) { direction_.x_ = +1.0f; }
		if (speed_.x_ < 0) { direction_.x_ = -1.0f; }
	}

	// 移動アニメーション
	drawer_.SetActMoveAnimation(isMove);
}

void Player::Jump()
{
	// ジャンプ回数が最大なら弾く
	if (1 <= jumpCount_) { return; }

	// SPACEキー押したら
	if (spKeys_->IsTrigger(DIK_SPACE))
	{
		// ジャンプ
		speed_.y_ = 1.0f;

		// ジャンプアニメーション
		drawer_.JumpAnimation();

		// ジャンプカウント
		jumpCount_++;
	}
}

void Player::UpdatePhysics()
{
	// ゴールした後は無視
	//if (isGoal_) { return; }

	// 移動
	Move();

	// ジャンプ
	Jump();

	// 摩擦力
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

	// 重力
	//speed_.y_ -= 0.1f;
	
	// 着地時
	//if (IsLanding() && IsElderLanding() == false)
	//{
	//	// 着地アニメーション
	//	drawer_.LandingAnimation();

	//	// ジャンプカウントリセット
	//	jumpCount_ = 0;
	//}

	// 移動
	transform_->pos_ += speed_;
}

void Player::Update()
{
	// 物理挙動更新
	UpdatePhysics();

	// トランスフォーム行列更新
	transform_->UpdateMatrix();

	// 描画クラス更新
	drawer_.Update();

	// コライダー位置更新
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });
}

void Player::Draw()
{
	// 描画
	drawer_.Draw();
}


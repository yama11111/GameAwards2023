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
	// キーインスタンス取得
	spKeys_ = YInput::Keys::GetInstance();
}

void DemoPlayer::StaticSetMapChip(YGame::MapChip* pMapChip)
{
	// nullチェック
	assert(pMapChip);

	// 代入
	spMapChip_ = pMapChip;
}

void DemoPlayer::Initialize(const YMath::Vector3& pos)
{
	// トランスフォーム生成
	transform_.reset(new Transform());

	// 描画クラス初期化
	drawer_.Initialize(transform_.get(), &direction_);

	// リセット
	Reset(pos);
}

void DemoPlayer::Reset(const YMath::Vector3& pos)
{
	// トランスフォーム初期化
	transform_->Initialize({ pos });

	// コライダー初期化
	YGame::MapChipCollider::Initialize({ transform_->scale_ });

	// 向き (右)
	direction_ = Vector3(+1, 0, 0);

	// 描画クラスリセット
	drawer_.Reset();
}

void DemoPlayer::Move()
{
	// x軸移動
	speed_.x_ += spKeys_->Horizontal();

	// クランプ
	speed_.x_ = Clamp(speed_.x_, -0.5f, +0.5f);
}

void DemoPlayer::Jump()
{
	// ジャンプ回数が最大なら弾く
	if (1 <= jumpCount_) { return; }

	// SPACEキー押したら
	if (spKeys_->IsTrigger(DIK_SPACE))
	{
		// ジャンプ
		speed_.y_ = 2.0f;

		// ジャンプアニメーション
		drawer_.JumpAnimation();

		// ジャンプカウント
		jumpCount_++;
	}
}

void DemoPlayer::Update()
{
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
	speed_.y_ -= 0.2f;

	// マップチップとのアタリ判定
	spMapChip_->PerfectPixelCollision(*this);

	// 着地時
	if (IsLanding())
	{
		// 着地アニメーション
		drawer_.LandingAnimation();

		// ジャンプカウントリセット
		jumpCount_ = 0;
	}

	// 移動
	transform_->pos_ += speed_;

	// トランスフォーム行列更新
	transform_->UpdateMatrix();

	// 描画クラス更新
	drawer_.Update();
}

void DemoPlayer::Draw()
{
	// 描画
	drawer_.Draw();
}

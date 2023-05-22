#include "Block.h"
#include "MathUtillity.h"
#include "Keys.h"
#include <cassert>
#include <cmath>

using YGame::Transform;
using YMath::Vector3;
using YMath::Clamp;

YInput::Keys* Block::spKeys_ = nullptr;
void Block::StaticInitialize()
{
	// キーインスタンス取得
	spKeys_ = YInput::Keys::GetInstance();
}

void Block::Initialize(const size_t signIndex, const YMath::Vector3& pos)
{
	// トランスフォーム生成
	transform_.reset(new Transform());

	// 描画クラス初期化
	drawer_.Initialize(transform_.get(), BlockDrawerCommon::Type::eWhite);

	// リセット
	Reset(signIndex, pos);
}

void Block::Reset(const size_t signIndex, const YMath::Vector3& pos)
{
	// トランスフォーム初期化
	transform_->Initialize({ pos, {}, {1.0f,1.0f,1.0f} });

	// スピード初期化
	speed_ = {};

	// コライダー位置初期化
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });

	// コライダーサイズ初期化
	Box2D::SetBox2DRadSize({ transform_->scale_.x_, transform_->scale_.y_ });

	// コライダータイプ設定
	ObjectCollider::SetColliderType(ObjectCollider::Type::eBlock);

	// コライダー看板番号設定
	ObjectCollider::SetSignIndex(signIndex);

	// 描画クラスリセット
	drawer_.Reset(BlockDrawerCommon::Type::eWhite);
}

void Block::PreUpdate()
{
	// 物理挙動更新
	UpdatePhysics();
	
	// 着地フラグ初期化
	ResetIsLanding();

	// コライダー位置更新
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });
}

void Block::PostUpdate()
{
	// 着地時
	if (IsLanding())
	{
		// 着地
		Landing();
	}

	// 移動
	transform_->pos_ += speed_;

	// トランスフォーム行列更新
	transform_->UpdateMatrix();

	// 描画クラス更新
	drawer_.Update();
}

void Block::Draw()
{
	// 描画
	drawer_.Draw();
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
	// スキル発動時のみ
	if (GetIsActSkill() == false) { return; }

	// x軸移動
	speed_.x_ += spKeys_->Horizontal();

	// クランプ
	speed_.x_ = Clamp(speed_.x_, -0.5f, +0.5f);

	// 続けるか
	SetIsActSkill(spKeys_->IsDown(DIK_E));
}

void Block::Landing()
{
	// 重力をなくす
	speed_.y_ = 0.0f;

	// 着地した瞬間なら
	if (IsLandingMoment())
	{

	}
}

void Block::UpdatePhysics()
{
	// ゴールした後は無視
	//if (isGoal_) { return; }

	// 移動
	Move();

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

}

void Block::OnCollision(ObjectCollider* pPair)
{

}
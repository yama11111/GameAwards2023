#include "Goal.h"
#include "MathUtillity.h"
#include <cassert>
#include <cmath>

using YGame::Transform;
using YMath::Vector3;
using YMath::Clamp;

void Goal::Initialize(const size_t signIndex, const YMath::Vector3& pos, const bool isRock)
{
	// トランスフォーム生成
	transform_.reset(new Transform());

	// 描画クラス初期化
	drawer_.Initialize(transform_.get());

	// リセット
	Reset(signIndex, pos, isRock);
}

void Goal::Reset(const size_t signIndex, const YMath::Vector3& pos, const bool isRock)
{
	// トランスフォーム初期化
	transform_->Initialize({ pos, {}, {1.0f,1.0f,1.0f} });
	
	// ロックフラグ設定
	isRock_ = isRock;

	// コライダー位置初期化
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });

	// コライダーサイズ初期化
	Box2D::SetBox2DRadSize({ transform_->scale_.x_, transform_->scale_.y_ });

	// コライダータイプ設定
	ObjectCollider::SetColliderType(ObjectCollider::Type::eGoal);

	// コライダー看板番号設定
	ObjectCollider::SetSignIndex(signIndex);

	// 描画クラスリセット
	drawer_.Reset();
}

void Goal::PreUpdate()
{
	// コライダー位置更新
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });
}

void Goal::PostUpdate()
{
	// トランスフォーム行列更新
	transform_->UpdateMatrix();

	// 描画クラス更新
	drawer_.Update();
}

void Goal::Draw()
{
	// 描画
	drawer_.Draw();
}

void Goal::OnCollision(ObjectCollider* pPair)
{
}

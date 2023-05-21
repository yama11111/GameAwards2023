#include "Block.h"
#include "MathUtillity.h"
#include "Keys.h"
#include <cassert>
#include <cmath>

using YGame::Transform;
using YMath::Vector3;
using YMath::Clamp;

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
	// コライダー位置更新
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });
}

void Block::PostUpdate()
{
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

void Block::OnCollision(ObjectCollider* pPair)
{

}

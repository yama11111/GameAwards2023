#include "Platform.h"
#include "MathUtillity.h"
#include <cassert>
#include <cmath>

#include "Stage.h"
#include "LevelData.h"

using YGame::Transform;
using YMath::Vector3;
using YMath::Clamp;

void Platform::Initialize(const size_t signIndex, const YMath::Vector3& pos, const float length)
{
	// トランスフォーム生成
	transform_.reset(new Transform());

	// 描画クラス初期化
	drawer_.Initialize(transform_.get());

	// リセット
	Reset(signIndex, pos, length);
}

void Platform::Reset(const size_t signIndex, const YMath::Vector3& pos, const float length)
{
	// トランスフォーム初期化
	transform_->Initialize({ pos + spStageMan_->GetTopLeftPos(signIndex), {}, {length,1.0f,1.0f} });

	// 前回左上位置初期化
	elderLeftTop_ = spStageMan_->GetTopLeftPos(signIndex);


	// コライダー位置初期化
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });

	// コライダーサイズ初期化
	Box2D::SetBox2DRadSize({ transform_->scale_.x_, LevelData::Platform::Thickness_ });

	// コライダータイプ設定
	ObjectCollider::SetColliderType(ObjectCollider::Type::ePlatform);

	// 描画クラスリセット
	drawer_.Reset();
}

void Platform::PreUpdate()
{
	// 左上更新
	UpdateLeftTop();

	// コライダー位置更新
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });
}

void Platform::PostUpdate()
{
	// トランスフォーム行列更新
	transform_->UpdateMatrix();

	// 描画クラス更新
	drawer_.Update();
}

void Platform::Draw()
{
	// 描画
	drawer_.Draw();
}

void Platform::OnCollision(ObjectCollider* pPair)
{
}

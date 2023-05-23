#include "Spring.h"
#include "MathUtillity.h"
#include <cassert>
#include <cmath>

#include "Stage.h"
#include "LevelData.h"

using YGame::Transform;
using YMath::Vector3;
using YMath::Clamp;

void Spring::Initialize(const size_t signIndex, const YMath::Vector3& pos, const float jumpPower)
{
	// トランスフォーム生成
	transform_.reset(new Transform());

	// 描画クラス初期化
	drawer_.Initialize(transform_.get());

	// リセット
	Reset(signIndex, pos, jumpPower);
}

void Spring::Reset(const size_t signIndex, const YMath::Vector3& pos, const float jumpPower)
{
	// トランスフォーム初期化
	transform_->Initialize({ pos + spStageMan_->GetTopLeftPos(signIndex), {}, {1.0f,1.0f,1.0f} });

	// ジャンプ力
	jumpPower_ = jumpPower;

	// コライダー位置初期化
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });

	// コライダーサイズ初期化
	Box2D::SetBox2DRadSize({ LevelData::Spring::CollRadSize });
	
	// コライダータイプ設定
	ObjectCollider::SetColliderType(ObjectCollider::Type::eSpring);

	// コライダー看板番号設定
	ObjectCollider::SetSignIndex(signIndex);

	// 描画クラスリセット
	drawer_.Reset();
}

void Spring::PreUpdate()
{
	// コライダー位置更新
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });
}

void Spring::PostUpdate()
{
	// トランスフォーム行列更新
	transform_->UpdateMatrix();

	// 描画クラス更新
	drawer_.Update();
}

void Spring::Draw()
{
	// 描画
	drawer_.Draw();
}

void Spring::OnCollision(ObjectCollider* pPair)
{
	// プレイヤーかブロックなら
	if (pPair->GetColliderType() == ObjectCollider::Type::eBlock)
	{
		// 下側か
		bool isUnder = transform_->pos_.y_ >= (pPair->GetBox2DCenter().y_ - pPair->GetBox2DRadSize().y_);

		// 下側じゃないなら弾く
		if (isUnder == false || pPair->SpeedRef().y_ > 0.0f) { return; }

		// ジャンプ
		pPair->SpeedRef().y_ = 3.0f;
	}
}

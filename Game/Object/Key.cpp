#include "Key.h"
#include "MathUtillity.h"
#include <cassert>
#include <cmath>

#include "Stage.h"
#include "LevelData.h"

using YGame::Transform;
using YMath::Vector3;
using YMath::Clamp;

void Key::Initialize(const size_t signIndex, const YMath::Vector3& pos)
{
	// トランスフォーム生成
	transform_.reset(new Transform());

	// 描画クラス初期化
	drawer_.Initialize(transform_.get());

	// リセット
	Reset(signIndex, pos);
}

void Key::Reset(const size_t signIndex, const YMath::Vector3& pos)
{
	// トランスフォーム初期化
	transform_->Initialize({ pos + spStageMan_->GetTopLeftPos(signIndex), {}, {1.5f,1.5f,1.5f} });
	
	// 前回左上位置初期化
	elderLeftTop_ = spStageMan_->GetTopLeftPos(signIndex);

	// プレイヤーポインタ
	pPlayerPos_ = nullptr;

	// コライダー位置初期化
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });

	// コライダーサイズ初期化
	Box2D::SetBox2DRadSize({ transform_->scale_.x_, transform_->scale_.y_ });

	// コライダータイプ設定
	ObjectCollider::SetColliderType(ObjectCollider::Type::eKey);

	// コライダー看板番号設定
	ObjectCollider::SetSignIndex(signIndex);


	// 描画クラスリセット
	drawer_.Reset();
}

void Key::PreUpdate()
{
	// 左上更新
	UpdateLeftTop();

	// コライダー位置更新
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });
}

void Key::PostUpdate()
{
	// プレイヤー追従
	UpdateFollowPlayer();

	// トランスフォーム行列更新
	transform_->UpdateMatrix();

	if (GetIsActSkill())
	{
		drawer_.AnimateGoal();
	}

	// 描画クラス更新
	drawer_.Update();
}

void Key::Draw()
{
	// 描画
	drawer_.Draw();
}

void Key::UpdateFollowPlayer()
{
	// nullなら弾く
	if (pPlayerPos_ == nullptr) { return; }

	transform_->pos_ = *pPlayerPos_ + Vector3(0.0f, 2.0f, 0);
}

void Key::OnCollision(ObjectCollider* pPair)
{
	// ブロックなら
	if (pPair->GetColliderType() == ObjectCollider::Type::ePlayer)
	{
		// 座標ポインタに代入
		pPlayerPos_ = pPair->PosPointer();
	}
	else if (pPair->GetColliderType() == ObjectCollider::Type::eGoal)
	{
		SetIsActSkill(true);
		pPair->SetIsActSkill(true);
	}
}

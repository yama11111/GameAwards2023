#include "Switch.h"
#include "MathUtillity.h"
#include <cassert>
#include <cmath>

#include "Stage.h"
#include "LevelData.h"

using YGame::Transform;
using YMath::Vector3;
using YMath::Clamp;

void Switch::Initialize(const size_t signIndex, const YMath::Vector3& pos, const bool isAct)
{
	// トランスフォーム生成
	transform_.reset(new Transform());

	// 描画クラス初期化
	drawer_.Initialize(transform_.get(), SwitchDrawerCommon::Type::eGreen);

	// リセット
	Reset(signIndex, pos, isAct);
}

void Switch::Reset(const size_t signIndex, const YMath::Vector3& pos, const bool isAct)
{
	// トランスフォーム初期化
	transform_->Initialize({ pos + spStageMan_->GetTopLeftPos(signIndex), {}, {1.0f,1.0f,1.0f} });

	// 前回左上位置初期化
	elderLeftTop_ = spStageMan_->GetTopLeftPos(signIndex);

	// 動作フラグ設定
	isAct_ = isAct;

	// コライダー位置初期化
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });

	// コライダーサイズ初期化
	Box2D::SetBox2DRadSize({ transform_->scale_.x_, transform_->scale_.y_ });

	// コライダータイプ設定
	ObjectCollider::SetColliderType(ObjectCollider::Type::eSwitch);

	// コライダー看板番号設定
	ObjectCollider::SetSignIndex(signIndex);


	// 描画クラスリセット
	drawer_.Reset(SwitchDrawerCommon::Type::eGreen);
}

void Switch::PreUpdate()
{
	// 左上更新
	UpdateLeftTop();

	// コライダー位置更新
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });
}

void Switch::PostUpdate()
{
	// トランスフォーム行列更新
	transform_->UpdateMatrix();

	// スキル発動時
	if (GetIsActSkill())
	{
		// スイッチ切り替え
		isAct_ = !isAct_;
		
		// スキル終了
		SetIsActSkill(false);
	}

	// 動作アニメ
	drawer_.AnimateSwitch(isAct_);

	// 描画クラス更新
	drawer_.Update();
}

void Switch::Draw()
{
	// 描画
	drawer_.Draw();
}

void Switch::OnCollision(ObjectCollider* pPair)
{
}

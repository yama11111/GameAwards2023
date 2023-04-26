#include "DemoGoal.h"

using YGame::Transform;
using YMath::Vector3;

void DemoGoal::Initialize(const YMath::Vector3& pos)
{
	// トランスフォーム生成
	transform_.reset(new Transform());

	// 描画クラス初期化
	drawer_.Initialize(transform_.get());

	// リセット
	Reset(pos);
}

void DemoGoal::Reset(const YMath::Vector3& pos)
{
	// トランスフォーム初期化
	transform_->Initialize({ pos, {0.0f,+0.8f,0.0f} });

	// 描画クラスリセット
	drawer_.Reset();
}

void DemoGoal::Update()
{
	// トランスフォーム行列更新
	transform_->UpdateMatrix();

	// 描画クラス更新
	drawer_.Update();
}

void DemoGoal::Draw()
{
	// 描画
	drawer_.Draw();
}

void DemoGoal::Goal(const YMath::Vector3& playerPos)
{
	// ゴール
	isGoal_ = true;

	// ゴールモーション開始
	drawer_.ActivateClearAnimation(playerPos);
}

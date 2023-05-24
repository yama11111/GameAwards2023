#include "IObject.h"
#include <cassert>

#include "Stage.h"

using YMath::Vector2;
using YMath::Vector3;
using YGame::Box2D;

Stage* IObject::spStageMan_ = nullptr;

void IObject::UpdateLeftTop()
{
	// 左上位置
	Vector3 ltPos = spStageMan_->GetTopLeftPos(GetSignIndex());

	// 場所が違うとき
	if (ltPos.x_ != elderLeftTop_.x_ || ltPos.y_ != elderLeftTop_.y_)
	{
		// 差分計算
		Vector3 difference = ltPos - elderLeftTop_;

		// 代入
		transform_->pos_ += difference;
	}

	// 記録
	elderLeftTop_ = ltPos;
}

void IObject::StaticInitialize(Stage* pStageMan)
{
	// null チェック
	assert(pStageMan);
	// 代入
	spStageMan_ = pStageMan;
}

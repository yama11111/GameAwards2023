#include "IObject.h"
#include <cassert>

#include "Stage.h"

using YMath::Vector2;
using YMath::Vector3;
using YGame::Box2D;

Stage* IObject::spStageMan_ = nullptr;

void IObject::UpdateLeftTop()
{
	// ����ʒu
	Vector3 ltPos = spStageMan_->GetTopLeftPos(GetSignIndex());

	// �ꏊ���Ⴄ�Ƃ�
	if (ltPos.x_ != elderLeftTop_.x_ || ltPos.y_ != elderLeftTop_.y_)
	{
		// �����v�Z
		Vector3 difference = ltPos - elderLeftTop_;

		// ���
		transform_->pos_ += difference;
	}

	// �L�^
	elderLeftTop_ = ltPos;
}

void IObject::StaticInitialize(Stage* pStageMan)
{
	// null �`�F�b�N
	assert(pStageMan);
	// ���
	spStageMan_ = pStageMan;
}

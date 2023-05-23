#include "IObject.h"
#include <cassert>

using YMath::Vector2;
using YMath::Vector3;
using YGame::Box2D;

Stage* IObject::spStageMan_ = nullptr;

void IObject::StaticInitialize(Stage* pStageMan)
{
	// null �`�F�b�N
	assert(pStageMan);
	// ���
	spStageMan_ = pStageMan;
}

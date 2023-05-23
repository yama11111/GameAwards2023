#include "IObject.h"
#include <cassert>

using YMath::Vector2;
using YMath::Vector3;
using YGame::Box2D;

Stage* IObject::spStageMan_ = nullptr;

void IObject::StaticInitialize(Stage* pStageMan)
{
	// null チェック
	assert(pStageMan);
	// 代入
	spStageMan_ = pStageMan;
}

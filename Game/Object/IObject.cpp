#include "IObject.h"
#include <cassert>

using YMath::Vector2;
using YMath::Vector3;
using YGame::Box2D;

//maruyama::Stage* IObject::spStageMan_ = nullptr;
maruyama::Sign* IObject::spStageMan_ = nullptr;

//void IObject::StaticInitialize(maruyama::Stage* pStageMan)
void IObject::StaticInitialize(maruyama::Sign* pStageMan)
{
	// null �`�F�b�N
	assert(pStageMan);
	// ���
	spStageMan_ = pStageMan;
}

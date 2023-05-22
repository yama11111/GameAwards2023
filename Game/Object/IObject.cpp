#include "IObject.h"
#include <cassert>

using YMath::Vector2;
using YMath::Vector3;
using YGame::Box2D;

maruyama::Sign* IObject::spSignMan_ = nullptr;

void IObject::StaticInitialize(maruyama::Sign* pSignMan)
{
	// null �`�F�b�N
	assert(pSignMan);
	// ���
	spSignMan_ = pSignMan;
}

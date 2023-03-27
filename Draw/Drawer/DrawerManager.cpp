#include "DrawerManager.h"
#include <cassert>

#include "PlayerDrawer.h"
#include "FilterDrawer.h"
#include "GateDrawer.h"
#include "GoalDrawer.h"
#include "BlockDrawer.h"
#include "BuildingDrawer.h"
#include "SkydomeDrawer.h"

using YGame::Model;

void DrawerManager::StaticInitialize(YGame::ViewProjection* pVP)
{
	// null�`�F�b�N
	assert(pVP);

	// ----- �ÓI������ ----- // 
	
	// �v���C���[
	PlayerDrawerCommon::StaticInitialize(pVP);
	
	// �t�B���^�[
	FilterDrawerCommon::StaticInitialize(pVP);
	
	// �Q�[�g
	GateDrawerCommon::StaticInitialize(pVP);
	
	// �S�[��
	GoalDrawerCommon::StaticInitialize(pVP);
	
	// �u���b�N
	BlockDrawerCommon::StaticInitialize(pVP);
	
	// �r��
	BuildingDrawerCommon::StaticInitialize(pVP);
	
	// �V��
	SkydomeDrawerCommon::StaticInitialize();
}

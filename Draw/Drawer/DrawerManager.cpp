#include "DrawerManager.h"
#include <cassert>

#include "PlayerDrawer.h"
#include "FilterDrawer.h"
#include "GateDrawer.h"
#include "GoalDrawer.h"
#include "BlockDrawer.h"
#include "BuildingDrawer.h"
#include "SkydomeDrawer.h"
#include "hUDDrawer.h"

using YGame::Model;

void DrawerManager::StaticInitialize(YGame::ViewProjection* pVP, YGame::ParticleManager* pParticleMan)
{
	// null�`�F�b�N
	assert(pVP);

	// ----- �ÓI������ ----- // 
	
	// ���N���X
	IDrawer::StaticInitialize(pParticleMan);

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

	// HUD
	HUDDrawerCommon::StaticInitialize();
}

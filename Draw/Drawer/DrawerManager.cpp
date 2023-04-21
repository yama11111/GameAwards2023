#include "DrawerManager.h"
#include <cassert>

#include "PlayerDrawer.h"
#include "FilterDrawer.h"
#include "BlockDrawer.h"
#include "GridDrawer.h"
#include "GateDrawer.h"
#include "GoalDrawer.h"
#include "BuildingDrawer.h"
#include "SkydomeDrawer.h"
#include "hUDDrawer.h"

using YGame::Model;

void DrawerManager::StaticInitialize(YGame::ViewProjection* pVP, YGame::Camera* pCamera, YGame::ParticleManager* pParticleMan)
{
	// null�`�F�b�N
	assert(pVP);
	assert(pCamera);
	assert(pParticleMan);

	// ----- �ÓI������ ----- // 
	
	// ���N���X
	IDrawer::StaticInitialize(pCamera, pParticleMan);

	// �v���C���[
	PlayerDrawerCommon::StaticInitialize(pVP);
	
	// �t�B���^�[
	FilterDrawerCommon::StaticInitialize(pVP);
	
	// �u���b�N
	BlockDrawerCommon::StaticInitialize(pVP);
	
	// �Q�[�g
	GateDrawerCommon::StaticInitialize(pVP);
	
	// �S�[��
	GoalDrawerCommon::StaticInitialize(pVP);


	// �O���b�h
	GridDrawerCommon::StaticInitialize(pVP);
	
	// �r��
	BuildingDrawerCommon::StaticInitialize(pVP);
	
	// �V��
	SkydomeDrawerCommon::StaticInitialize();

	// HUD
	HUDDrawerCommon::StaticInitialize();
}

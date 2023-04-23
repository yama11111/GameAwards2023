#include "DrawerHelper.h"
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

std::unique_ptr<YGame::Material> DrawerHelper::sDefMate_;

void DrawerHelper::StaticInitialize(YGame::ViewProjection* pVP, YGame::Camera* pCamera, YGame::ParticleManager* pParticleMan)
{
	// null�`�F�b�N
	assert(pVP);
	assert(pCamera);
	assert(pParticleMan);

	// ����
	sDefMate_.reset(YGame::Material::Create());

	// ----- �ÓI������ ----- // 
	
	// ���N���X
	IDrawer::StaticInitialize(pVP, sDefMate_.get(), pCamera, pParticleMan);

	// �v���C���[
	PlayerDrawerCommon::StaticInitialize();
	
	// �t�B���^�[
	FilterDrawerCommon::StaticInitialize();
	
	// �u���b�N
	BlockDrawerCommon::StaticInitialize();
	
	// �Q�[�g
	GateDrawerCommon::StaticInitialize();
	
	// �S�[��
	GoalDrawerCommon::StaticInitialize();


	// �O���b�h
	GridDrawerCommon::StaticInitialize(pVP);
	
	// �r��
	BuildingDrawerCommon::StaticInitialize(pVP);
	
	// �V��
	SkydomeDrawerCommon::StaticInitialize();

	// HUD
	HUDDrawerCommon::StaticInitialize();
}

void DrawerHelper::StaticReset()
{
	// �u���b�N
	BlockDrawerCommon::StaticReset();
}

void DrawerHelper::StaticUpdate()
{
	// �u���b�N
	BlockDrawerCommon::StaticUpdate();
}

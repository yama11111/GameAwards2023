#include "DrawerHelper.h"
#include <cassert>

#include "PlayerDrawer.h"
#include "FilterDrawer.h"
#include "BlockDrawer.h"
#include "GridDrawer.h"
#include "GateDrawer.h"
#include "GoalDrawer.h"
#include "BackgroundDrawer.h"
#include "hUDDrawer.h"

using YGame::Model;

std::unique_ptr<YGame::Material> DrawerHelper::sDefMate_;
std::unique_ptr<YGame::Material> DrawerHelper::sBackMate_;

void DrawerHelper::StaticInitialize(YGame::ViewProjection* pVP, YGame::Camera* pCamera, YGame::ParticleManager* pParticleMan)
{
	// null�`�F�b�N
	assert(pVP);
	assert(pCamera);
	assert(pParticleMan);

	// ����
	sDefMate_.reset(YGame::Material::Create());

	// ����
	sBackMate_.reset(YGame::Material::Create({ 0.4f,0.3f,0.3f }));

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
	
	// �^���[
	TowerDrawerCommon::StaticInitialize(pVP, sBackMate_.get());
	
	// �V��
	SkydomeDrawerCommon::StaticInitialize();

	// �w�i
	BackgroundDrawerCommon::StaticInitialize(pParticleMan);

	// HUD
	HUDDrawerCommon::StaticInitialize();
}

void DrawerHelper::StaticReset()
{
	// �u���b�N
	BlockDrawerCommon::StaticReset();

	// �^���[
	TowerDrawerCommon::StaticReset();
}

void DrawerHelper::StaticUpdate()
{
	// �u���b�N
	BlockDrawerCommon::StaticUpdate();

	// �^���[
	TowerDrawerCommon::StaticUpdate();
}

#include "DrawerHelper.h"

#include "DrawerConfig.h"

#include "CoreColor.h"
#include "PlayerDrawer.h"
#include "BlockDrawer.h"
#include "GridDrawer.h"
#include "GateDrawer.h"
#include "GoalDrawer.h"
#include "BackgroundDrawer.h"
#include "HUDDrawer.h"

#include <cassert>

#pragma region ���O���

using std::array;
using std::unique_ptr;

using YGame::Transform;
using YGame::ModelObject;
using YGame::Model;
using YGame::Color;
using YGame::Material;

using YGame::SlimeActor;

using YMath::Ease;
using YMath::Power;
using YMath::Vector3;
using YMath::Vector4;

using namespace DrawerConfig;

#pragma endregion

#pragma region Static

unique_ptr<Material> DrawerHelper::sDefMate_;
unique_ptr<Material> DrawerHelper::sBackMate_;

#pragma endregion

void DrawerHelper::StaticInitialize(YGame::ViewProjection* pVP, YGame::Camera* pCamera, YGame::ParticleManager* pParticleMan)
{
	// null�`�F�b�N
	assert(pVP);
	assert(pCamera);
	assert(pParticleMan);

	// ����
	sDefMate_.reset(YGame::Material::Create());

	// ����
	sBackMate_.reset(YGame::Material::Create(Background::Ambient));


	// ----- �ÓI������ ----- // 
	{
		// ���N���X
		IDrawer::StaticInitialize(pVP, sDefMate_.get(), pCamera, pParticleMan);

		// �j�F
		CoreColor::StaticInitialize();

		// �v���C���[
		PlayerDrawerCommon::StaticInitialize();

		// �u���b�N
		BlockDrawerCommon::StaticInitialize();

		// �Q�[�g
		GateDrawerCommon::StaticInitialize();

		// �S�[��
		GoalDrawerCommon::StaticInitialize();


		// �^���[
		TowerDrawerCommon::StaticInitialize(pVP, sBackMate_.get());

		// �V��
		SkydomeDrawerCommon::StaticInitialize();

		// �w�i
		BackgroundDrawerCommon::StaticInitialize(pParticleMan);


		// �O���b�h
		GridDrawerCommon::StaticInitialize(pVP);


		// HUD
		HUDDrawerCommon::StaticInitialize();
	}

	// ���Z�b�g
	StaticReset();
}

void DrawerHelper::StaticReset()
{
	// �j�F���Z�b�g
	CoreColor::StaticReset();
}

void DrawerHelper::StaticUpdate()
{
	// �j�F�X�V
	CoreColor::StaticUpdate();
}

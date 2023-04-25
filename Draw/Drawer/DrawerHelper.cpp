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

bool DrawerHelper::sIsGoal_ = false;
bool DrawerHelper::sIsElderGoal_ = false;

#pragma endregion

void DrawerHelper::StaticInitialize(YGame::ViewProjection* pVP, YGame::Camera* pCamera, YGame::ParticleManager* pParticleMan)
{
	// null�`�F�b�N
	assert(pVP);
	assert(pCamera);
	assert(pParticleMan);

	// ����
	sDefMate_.reset(YGame::Material::Create());

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


		// �w�i
		BackgroundDrawerCommon::StaticInitialize(pVP, pParticleMan);


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
	// �S�[���t���O
	sIsGoal_ = false;

	// �O��S�[���t���O
	sIsElderGoal_ = false;

	// �j�F���Z�b�g
	CoreColor::StaticReset();

	// �w�i���Z�b�g
	BackgroundDrawerCommon::StaticReset();
}

void DrawerHelper::StaticUpdate()
{
	// �S�[�������u��
	if (sIsGoal_ && sIsElderGoal_ == false)
	{
		// �F����
		CoreColor::StaticUnify(CoreColor::ColorType::Blue);

		// �w�i�̃}�e���A������
		BackgroundDrawerCommon::StaticUnify();
	}

	// �j�F�X�V
	CoreColor::StaticUpdate();

	// �w�i�X�V
	BackgroundDrawerCommon::StaticUpdate();

	// �O��S�[���t���O�ۑ�
	sIsElderGoal_ = sIsGoal_;
}

#include "DrawerHelper.h"

#include "DrawerConfig.h"

#include "CoreColor.h"
#include "PlayerDrawer.h"
#include "BlockDrawer.h"
#include "GateDrawer.h"
#include "GoalDrawer.h"
#include "BackgroundDrawer.h"
#include "HUDDrawer.h"

#include <cassert>

#pragma region ���O���

using std::array;
using std::unique_ptr;

using YGame::Transform;
using YGame::Model;
using YGame::CBColor;
using YGame::CBMaterial;

using YGame::SlimeActor;

using YMath::Ease;
using YMath::Power;
using YMath::Vector3;
using YMath::Vector4;

using namespace DrawerConfig;

#pragma endregion

#pragma region Static

unique_ptr<CBMaterial> DrawerHelper::sDefMate_;

bool DrawerHelper::sIsClear_ = false;
bool DrawerHelper::sIsElderClear_ = false;

#pragma endregion

void DrawerHelper::StaticInitialize(YGame::ViewProjection* pVP, YGame::Camera* pCamera, YGame::ParticleManager* pParticleMan)
{
	// null�`�F�b�N
	assert(pVP);
	assert(pCamera);
	assert(pParticleMan);

	// ����
	sDefMate_.reset(YGame::CBMaterial::Create());

	// ----- �ÓI������ ----- // 
	{
		// ���N���X
		IDrawer::StaticInitialize(pVP, sDefMate_.get(), nullptr, pCamera, pParticleMan);

		// �j�F
		CoreColor::StaticInitialize(true);


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



		// HUD
		HUDDrawerCommon::StaticInitialize();
	}

	// ���Z�b�g
	StaticReset();
}

void DrawerHelper::StaticReset()
{
	// �N���A�t���O
	sIsClear_ = false;

	// �O��N���A�t���O
	sIsElderClear_ = false;

	// �j�F���Z�b�g
	CoreColor::StaticReset();

	// �w�i���Z�b�g
	BackgroundDrawerCommon::StaticReset();
}

void DrawerHelper::StaticUpdate()
{
	// �S�[�������u��
	if (sIsClear_ && sIsElderClear_ == false)
	{
		// �F����
		CoreColor::StaticClearAnimation(CoreColor::ColorType::eBlue);

		// �w�i�̃}�e���A������
		BackgroundDrawerCommon::StaticUnify();
	}

	// �j�F�X�V
	CoreColor::StaticUpdate();

	// �w�i�X�V
	BackgroundDrawerCommon::StaticUpdate();

	// �O��S�[���t���O�ۑ�
	sIsElderClear_ = sIsClear_;
}

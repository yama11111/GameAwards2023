#include "IDrawer.h"
#include <cassert>

#pragma region ���O���

using YGame::Transform;
using YGame::CBColor;
using YGame::SlimeActor;
using YMath::Vector3;

#pragma endregion

#pragma region Static

YGame::ViewProjection* IDrawer::spVP_ = nullptr;
YGame::CBMaterial* IDrawer::spMate_ = nullptr;
YGame::CBLightGroup* IDrawer::spLightGroup_ = nullptr;
YGame::Camera* IDrawer::spCamera_ = nullptr;
YGame::ParticleManager* IDrawer::spParticleMan_ = nullptr;

#pragma endregion

void IDrawer::StaticInitialize(
	YGame::ViewProjection* pVP,
	YGame::CBMaterial* pMate,
	YGame::CBLightGroup* pLightGroup,
	YGame::Camera* pCamera,
	YGame::ParticleManager* pParticleMan)
{
	// null�`�F�b�N
	assert(pVP);
	assert(pCamera);
	assert(pParticleMan);

	// ���
	spVP_ = pVP;
	spMate_ = pMate;
	spLightGroup_ = pLightGroup;
	spCamera_ = pCamera;
	spParticleMan_ = pParticleMan;
}

void IDrawer::Initialze(YGame::Transform* pParent)
{
	// null�`�F�b�N
	assert(pParent);
	// ���
	pParent_ = pParent;

	// �I�u�W�F�N�g���� + �e�s��}��
	core_.reset(new Transform());
	core_->parent_ = &pParent->m_;

	// ���Z�b�g
	Reset();
}

void IDrawer::Reset()
{
	// ������
	SlimeActor::Initialize();

	// �I�u�W�F�N�g������
	core_->Initialize();
}

void IDrawer::Update(const YGame::Transform::Status& status)
{
	// �X�V
	SlimeActor::Update();
	
	// �s��X�V (�e)
	core_->UpdateMatrix(
		{
			Vector3(0.0f, SlimeActor::JiggleValue().y_, 0.0f) + status.pos_,
			status.rota_,
			SlimeActor::JiggleValue() + status.scale_
		}
	);
}

#include "IDrawer.h"
#include <cassert>

#pragma region ���O���

using YGame::Transform;
using YGame::Color;
using YGame::SlimeActor;
using YMath::Vector3;

#pragma endregion

YGame::ViewProjection* IDrawer::spVP_ = nullptr;
YGame::Material* IDrawer::spMate_ = nullptr;
YGame::Camera* IDrawer::spCamera_ = nullptr;
YGame::ParticleManager* IDrawer::spParticleMan_ = nullptr;

void IDrawer::StaticInitialize(
	YGame::ViewProjection* pVP,
	YGame::Material* pMate,
	YGame::Camera* pCamera,
	YGame::ParticleManager* pParticleMan)
{
	// null�`�F�b�N
	assert(pVP);
	assert(pMate);	
	assert(pCamera);
	assert(pParticleMan);

	// ���
	spVP_ = pVP;
	spMate_ = pMate;
	spCamera_ = pCamera;
	spParticleMan_ = pParticleMan;
}

void IDrawer::Initialze(YGame::Transform* pParent, const UINT intervalTime)
{
	// null�`�F�b�N
	assert(pParent);
	// ���
	pParent_ = pParent;

	// �I�u�W�F�N�g���� + �e�s��}��
	core_.reset(new Transform());
	core_->Initialize({});
	core_->parent_ = &pParent->m_;

	// �������[�V�����^�C�}�[������
	idleTim_.Initialize(intervalTime);

	// ���Z�b�g
	Reset();
}

void IDrawer::Reset()
{
	// ������
	SlimeActor::Initialize();

	// �I�u�W�F�N�g������
	core_->Initialize({});

	// �������[�V�����^�C�}�[���Z�b�g
	idleTim_.Reset(true);
}

void IDrawer::Update(const YGame::Transform::Status& status)
{
	// �X�V
	SlimeActor::Update();

	// �������[�V�����^�C�}�[�X�V
	idleTim_.Update();

	// �^�C�}�[���I�������
	if (idleTim_.IsEnd())
	{
		// �������[�V�����Đ�
		IdleAnimation();
		// �^�C�}�[���Z�b�g
		idleTim_.Reset(true);
	}
	
	// �s��X�V (�e)
	core_->UpdateMatrix(
		{
			Vector3(0.0f, SlimeActor::JiggleValue().y_, 0.0f) + status.pos_,
			status.rota_,
			SlimeActor::JiggleValue() + status.scale_
		}
	);
}

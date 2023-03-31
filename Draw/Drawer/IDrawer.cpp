#include "IDrawer.h"
#include <cassert>

#pragma region ���O���

using YGame::Transform;
using YGame::Color;
using YGame::SlimeActor;

#pragma endregion

YGame::ParticleManager* IDrawer::spParticleMan_ = nullptr;

void IDrawer::StaticInitialize(YGame::ParticleManager* pParticleMan)
{
	// null�`�F�b�N
	assert(pParticleMan);
	// ���
	spParticleMan_ = pParticleMan;
}

void IDrawer::Initialze(YGame::Transform* pParent, const Mode& mode, const UINT intervalTime)
{
	// null�`�F�b�N
	assert(pParent);
	// ���
	pParent_ = pParent;

	// �I�u�W�F�N�g���� + �e�s��}��
	core_.reset(new Transform());
	core_->Initialize({});
	core_->parent_ = &pParent->m_;

	// �F����
	color_.reset(Color::Create());

	// �������[�V�����^�C�}�[������
	idleTim_.Initialize(intervalTime);

	// ���Z�b�g
	Reset(mode);
}

void IDrawer::Reset(const Mode& mode)
{
	// ������
	SlimeActor::Initialize();

	// �I�u�W�F�N�g������
	core_->Initialize({});

	// ���݂̏��
	current_ = mode;
	// �ύX��̏��
	next_ = Mode::None;

	// �������[�V�����^�C�}�[���Z�b�g
	idleTim_.Reset(true);
}

void IDrawer::Update(const YGame::Transform::Status& status)
{
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
			-SlimeActor::JiggleValue() + status.pos_,
			status.rota_,
			SlimeActor::JiggleValue() + status.scale_
		}
	);
}

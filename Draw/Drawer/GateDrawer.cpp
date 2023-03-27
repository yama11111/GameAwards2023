#include "GateDrawer.h"
#include "CalcTransform.h"
#include "DrawerConfig.h"
#include <cassert>

#pragma region ���O���

using YGame::Transform;
using YGame::ModelObject;
using YGame::Model;
using YGame::Color;
using YGame::SlimeActor;
using YMath::Vector3;

#pragma endregion

#pragma region Static

// �ÓI ���f���z�� ������
std::array<std::unique_ptr<Model>, GateDrawerCommon::PartsNum_> GateDrawerCommon::sModels_ =
{ nullptr, nullptr, };
YGame::ViewProjection* GateDrawerCommon::spVP_ = nullptr;

void GateDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP)
{
	// null�`�F�b�N
	assert(pVP);
	// ���
	spVP_ = pVP;

	// ----- ���f���ǂݍ��� ----- //

	// ��
	sModels_[static_cast<size_t>(Parts::Frame)].reset(Model::LoadObj("player/player_body", true));
	sModels_[static_cast<size_t>(1)].reset(Model::LoadObj("player/player_body", true));
}

#pragma endregion

void GateDrawer::Initialize(YMath::Matrix4* pParent)
{
	// null�`�F�b�N
	assert(pParent);

	// �I�u�W�F�N�g���� + �e�s��}��
	core_.reset(new Transform());
	core_->Initialize({});
	core_->parent_ = pParent;

	// �F����
	color_.reset(Color::Create());

	// �I�u�W�F�N�g���� + �e�s��}�� (�p�[�c�̐�)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i].reset(ModelObject::Create({}, spVP_, color_.get(), nullptr));
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// ���Z�b�g
	Reset();
}

void GateDrawer::Reset()
{
	// ������
	SlimeActor::Initialize();

	core_->Initialize({});

	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->Initialize({});
	}

	idelTim_.Initialize(DrawerConfig::Gate::Idle::IntervalTime);
	idelTim_.SetActive(true);
}

void GateDrawer::Update()
{
	// �������[�V�����^�C�}�[�X�V
	idelTim_.Update();

	// �^�C�}�[���I�������
	if (idelTim_.IsEnd())
	{
		// �������[�V�����Đ�
		IdleAnimation();
		// �^�C�}�[���Z�b�g
		idelTim_.Reset(true);
	}

	// �s��X�V (�e)
	core_->UpdateMatrix(
		{
			-SlimeActor::JiggleValue(),
			{},
			SlimeActor::JiggleValue()
		}
	);

	// �s��X�V (�q)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix();
	}
}

void GateDrawer::Draw()
{
	// �`��
	for (size_t i = 0; i < sModels_.size(); i++)
	{
		sModels_[i]->Draw(modelObjs_[i].get());
	}
}

void GateDrawer::IdleAnimation()
{
}

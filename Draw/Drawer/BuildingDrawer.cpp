#include "BuildingDrawer.h"
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
std::array<Model*, BuildingDrawerCommon::PartsNum_> BuildingDrawerCommon::spModels_ = 
{ nullptr, nullptr, };
YGame::ViewProjection* BuildingDrawerCommon::spVP_ = nullptr;

void BuildingDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP)
{
	// null�`�F�b�N
	assert(pVP);
	// ���
	spVP_ = pVP;

	// ----- ���f���ǂݍ��� ----- //

	// ��
	spModels_[static_cast<size_t>(Parts::Building)] = Model::Load("building", true);
	spModels_[static_cast<size_t>(1)] = Model::Load("building", true);
}

#pragma endregion

void BuildingDrawer::Initialize(YMath::Matrix4* pParent)
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

void BuildingDrawer::Reset()
{
	// ������
	SlimeActor::Initialize();

	core_->Initialize({});

	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->Initialize({});
	}

	idleTim_.Initialize(DrawerConfig::Block::Idle::IntervalTime);
	idleTim_.SetActive(true);
}

void BuildingDrawer::Update()
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

void BuildingDrawer::Draw()
{
	// �`��
	for (size_t i = 0; i < spModels_.size(); i++)
	{
		spModels_[i]->Draw(modelObjs_[i].get());
	}
}

void BuildingDrawer::IdleAnimation()
{
}

#include "BlockDrawer.h"
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
using namespace DrawerConfig::Block;

#pragma endregion

#pragma region Static

// �ÓI ���f���z�� ������
std::array<std::unique_ptr<Model>, BlockDrawerCommon::PartsNum_> BlockDrawerCommon::sModels_ =
{ nullptr, nullptr, };
YGame::ViewProjection* BlockDrawerCommon::spVP_ = nullptr;

void BlockDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP)
{
	// null�`�F�b�N
	assert(pVP);
	// ���
	spVP_ = pVP;

	// ----- ���f���ǂݍ��� ----- //

	// ��
	sModels_[static_cast<size_t>(Parts::Normal)].reset(Model::Create("blockNormal.png"));
	sModels_[static_cast<size_t>(Parts::Red)]	.reset(Model::Create("blockRed.png"));
}

#pragma endregion

void BlockDrawer::Initialize(YMath::Matrix4* pParent, const Mode& mode)
{
	// ���N���X������
	IDrawer::Initialze(pParent, mode, Idle::IntervalTime);

	// �I�u�W�F�N�g���� + �e�s��}�� (�p�[�c�̐�)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i].reset(ModelObject::Create({}, spVP_, color_.get(), nullptr));
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// ���Z�b�g
	Reset(mode);
}

void BlockDrawer::Reset(const Mode& mode)
{
	// ���Z�b�g
	IDrawer::Reset(mode);

	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->Initialize({});
	}

	current_ = mode;
}

void BlockDrawer::Update()
{
	// ���N���X�X�V 
	IDrawer::Update({});

	// �s��X�V (�q)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix();
	}
}

void BlockDrawer::Draw()
{
	// �`��
	//for (size_t i = 0; i < sModels_.size(); i++)
	//{
	//	sModels_[i]->Draw(modelObjs_[i].get());
	//}

	sModels_[static_cast<size_t>(current_)]->Draw(modelObjs_[static_cast<size_t>(current_)].get());
}

void BlockDrawer::IdleAnimation()
{
}

#include "FilterDrawer.h"
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
using namespace DrawerConfig::Filter;

#pragma endregion

#pragma region Static

// �ÓI ���f���z�� ������
std::array<std::unique_ptr<Model>, FilterDrawerCommon::PartsNum_> FilterDrawerCommon::sModels_ =
{ nullptr, nullptr, };
YGame::ViewProjection* FilterDrawerCommon::spVP_ = nullptr;

void FilterDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP)
{
	// null�`�F�b�N
	assert(pVP);
	// ���
	spVP_ = pVP;

	// ----- ���f���ǂݍ��� ----- //

	// ��
	sModels_[static_cast<size_t>(Parts::Monitor)].reset(Model::Create());
	sModels_[static_cast<size_t>(1)].reset(Model::Create());
}

#pragma endregion

void FilterDrawer::Initialize(YMath::Matrix4* pParent)
{
	// ���N���X������
	IDrawer::Initialze(pParent, Mode::Red, Idle::IntervalTime);

	// �I�u�W�F�N�g���� + �e�s��}�� (�p�[�c�̐�)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i].reset(ModelObject::Create({}, spVP_, color_.get(), nullptr));
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// ���Z�b�g
	Reset();
}

void FilterDrawer::Reset()
{
	// ���Z�b�g
	IDrawer::Reset(Mode::Red);

	// ----- ���f���p�I�u�W�F�N�g������ ----- //
	
	// ���j�^�[
	modelObjs_[static_cast<size_t>(Parts::Monitor)]->Initialize(
		{
			{0,0,-5.0f},
			{},
			{1.0f,1.0f,0.0001f},
		}
	);

	color_->SetRGBA({ 1.0f,0.0f,0.0f,0.25f });
}

void FilterDrawer::Update()
{
	// ���N���X�X�V 
	IDrawer::Update({});

	// �s��X�V (�q)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix();
	}
}

void FilterDrawer::Draw()
{
	// �`��
	sModels_[static_cast<size_t>(Parts::Monitor)]->Draw(modelObjs_[static_cast<size_t>(Parts::Monitor)].get());
}

void FilterDrawer::ChangeColorAnimation(const Mode& mode)
{
	current_ = mode;
}

void FilterDrawer::IdleAnimation()
{
}

#include "GoalDrawer.h"
#include "CalcTransform.h"
#include "DrawerConfig.h"
#include "Def.h"
#include <cassert>

#pragma region ���O���

using std::array;
using std::unique_ptr;
using YGame::Transform;
using YGame::ModelObject;
using YGame::Model;
using YGame::Color;
using YGame::SlimeActor;
using YMath::Vector3;
using namespace DrawerConfig::Goal;

#pragma endregion

#pragma region Static

// �C���f�b�N�X
static const size_t CoreIdx = static_cast<size_t>(GoalDrawerCommon::Parts::Core); // �j
static const size_t InsideIdx = static_cast<size_t>(GoalDrawerCommon::Parts::Inside); // ���g
static const size_t OutsideIdx = static_cast<size_t>(GoalDrawerCommon::Parts::Outside); // �O�g
static const size_t BaseIdx = static_cast<size_t>(GoalDrawerCommon::Parts::Base); // ���

// �ÓI ���f���z�� ������
array<unique_ptr<Model>, GoalDrawerCommon::PartsNum_> GoalDrawerCommon::sModels_ =
{
	nullptr, nullptr, nullptr, nullptr,
};

// �ÓI�r���[�v���W�F�N�V����
YGame::ViewProjection* GoalDrawerCommon::spVP_ = nullptr;

void GoalDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP)
{
	// null�`�F�b�N
	assert(pVP);
	// ���
	spVP_ = pVP;

	// ----- ���f���ǂݍ��� ----- //

	sModels_[CoreIdx].reset(Model::LoadObj("goal/core", true)); // �j
	sModels_[InsideIdx].reset(Model::LoadObj("goal/inside", true)); // ���g
	sModels_[OutsideIdx].reset(Model::LoadObj("goal/outside", true)); // �O�g
	sModels_[BaseIdx].reset(Model::LoadObj("goal/base", true)); // ���
}

#pragma endregion

void GoalDrawer::Initialize(YGame::Transform* pParent)
{
	// ���N���X������
	IDrawer::Initialze(pParent, Mode::Normal, Idle::IntervalTime);

	// �I�u�W�F�N�g���� + �e�s��}�� (�p�[�c�̐�)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i].reset(ModelObject::Create({}, spVP_, color_.get(), nullptr));
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// ���Z�b�g
	Reset();
}

void GoalDrawer::Reset()
{
	// ���Z�b�g
	IDrawer::Reset(Mode::Red);

	// ----- ���f���p�I�u�W�F�N�g������ ----- //

	core_->Initialize({ {0.0f,+3.0f,0.0f}, {0.0f,-PI / 4.0f,0.0f}, {0.5f,0.5f,0.5f} });

	modelObjs_[CoreIdx]->	Initialize({}); // �j
	modelObjs_[InsideIdx]->	Initialize({}); // ���g
	modelObjs_[OutsideIdx]->Initialize({}); // �O�g
	modelObjs_[BaseIdx]->	Initialize({}); // ���
}

void GoalDrawer::Update()
{
	// ���N���X�X�V 
	IDrawer::Update({});

	// �s��X�V (�q)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix();
	}
}

void GoalDrawer::Draw()
{
	// �`��
	for (size_t i = 0; i < sModels_.size(); i++)
	{
		sModels_[i]->Draw(modelObjs_[i].get());
	}
}

void GoalDrawer::IdleAnimation()
{
}

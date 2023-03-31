#include "GoalDrawer.h"
#include "CalcTransform.h"
#include "DrawerConfig.h"
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


// �ÓI ���f���z�� ������
array<unique_ptr<Model>, GoalDrawerCommon::PartsNum_> GoalDrawerCommon::sModels_ =
{
	nullptr, nullptr,
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

	// ��
	sModels_[CoreIdx].reset(Model::Create("goal.png"));
	sModels_[1].reset(Model::Create());
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

	// �j
	modelObjs_[CoreIdx]->Initialize({});
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
	sModels_[CoreIdx]->Draw(modelObjs_[CoreIdx].get());
}

void GoalDrawer::IdleAnimation()
{
}

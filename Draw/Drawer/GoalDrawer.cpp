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
array<Model*, GoalDrawerCommon::PartsNum_> GoalDrawerCommon::spModels_ =
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

	spModels_[CoreIdx] = Model::Load("goal/core", true); // �j
	spModels_[InsideIdx] = Model::Load("goal/inside", true); // ���g
	spModels_[OutsideIdx] = Model::Load("goal/outside", true); // �O�g
	spModels_[BaseIdx] = Model::Load("goal/base", true); // ���
}

#pragma endregion

void GoalDrawer::Initialize(YGame::Transform* pParent)
{
	// ���N���X������
	IDrawer::Initialze(pParent, Mode::Normal, Idle::IntervalTime);

	// �I�u�W�F�N�g���� + �e�s��}�� (�p�[�c�̐�)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i].reset(ModelObject::Create({}, spVP_, nullptr, nullptr));
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// ��] (��)
	inRotaEas.Initialize(Rota::Inside::Start, Rota::Inside::End, Rota::Exponent);
	// ��] (�O)
	outRotaEas.Initialize(Rota::Outside::Start, Rota::Outside::End, Rota::Exponent);

	// ��]�^�C�}�[
	rotaTim_.Initialize(Rota::Frame);

	// ���Z�b�g
	Reset();
}

void GoalDrawer::Reset()
{
	// ���Z�b�g
	IDrawer::Reset(Mode::Red);

	// ----- ���f���p�I�u�W�F�N�g������ ----- //

	core_->Initialize({ {0.0f,0.0f,0.0f}, {0.0f,+PI / 6.0f,0.0f}, {1.0f,1.0f,1.0f} });

	modelObjs_[CoreIdx]->Initialize({ {0.0f,+2.0f,0.0f } }); // �j
	modelObjs_[InsideIdx]->Initialize({ {0.0f,+2.0f,0.0f } }); // ���g
	modelObjs_[OutsideIdx]->Initialize({ {0.0f,+2.0f,0.0f } }); // �O�g
	modelObjs_[BaseIdx]->Initialize({}); // ���

	// ----- �^�C�}�[������ ----- //
	
	// ��]�^�C�}�[
	rotaTim_.Reset(true);
}

void GoalDrawer::IdleAnimation()
{
}

void GoalDrawer::RotaAnimation()
{
	// ��]�^�C�}�[�X�V
	rotaTim_.Update();
	// �^�C�}�[�I��������
	if (rotaTim_.IsEnd())
	{
		// �^�C�}�[���Z�b�g
		rotaTim_.Reset(true);
	}

	// ��] (��)
	modelObjs_[InsideIdx]->rota_ = inRotaEas.In(rotaTim_.Ratio());
	// ��] (�O)
	modelObjs_[OutsideIdx]->rota_ = outRotaEas.In(rotaTim_.Ratio());
}

void GoalDrawer::Update()
{
	// ���N���X�X�V 
	IDrawer::Update({});

	// ��]�A�j���[�V����
	RotaAnimation();

	// �s��X�V (�q)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix();
	}
}

void GoalDrawer::Draw()
{
	// �`��
	for (size_t i = 0; i < spModels_.size(); i++)
	{
		spModels_[i]->Draw(modelObjs_[i].get());
	}
}

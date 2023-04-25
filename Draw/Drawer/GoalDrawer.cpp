#include "GoalDrawer.h"
#include "CalcTransform.h"
#include "DrawerConfig.h"
#include "CoreColor.h"
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
using YMath::Vector4;

using namespace DrawerConfig::Goal;

#pragma endregion

#pragma region Static

array<Model*, GoalDrawerCommon::PartsNum_> GoalDrawerCommon::spModels_ =
{
	nullptr, nullptr, nullptr, nullptr, nullptr,
};

#pragma endregion

#pragma region �C���f�b�N�X

static const size_t CoreIdx = static_cast<size_t>(GoalDrawerCommon::Parts::Core); // �j
static const size_t InsideIdx = static_cast<size_t>(GoalDrawerCommon::Parts::InsideCore); // ���g�j
static const size_t InsideCoreIdx = static_cast<size_t>(GoalDrawerCommon::Parts::Inside); // ���g
static const size_t OutsideIdx = static_cast<size_t>(GoalDrawerCommon::Parts::OutsideCore); // �O�g�j
static const size_t OutsideCoreIdx = static_cast<size_t>(GoalDrawerCommon::Parts::Outside); // �O�g

#pragma endregion

#pragma region Common

void GoalDrawerCommon::StaticInitialize()
{
	// ----- ���f���ǂݍ��� ----- //

	spModels_[CoreIdx] = Model::Load("goal/core", true); // �j
	spModels_[InsideIdx] = Model::Load("goal/inside", true); // ���g�j
	spModels_[InsideCoreIdx] = Model::Load("goal/insideCore", true); // ���g
	spModels_[OutsideIdx] = Model::Load("goal/outside", true); // �O�g�j
	spModels_[OutsideCoreIdx] = Model::Load("goal/outsideCore", true); // �O�g
}

#pragma endregion

#pragma region Drawer

void GoalDrawer::Initialize(YGame::Transform* pParent)
{
	// ���N���X������
	IDrawer::Initialze(pParent, Idle::IntervalTime);

	// �I�u�W�F�N�g���� + �e�s��}�� (�p�[�c�̐�)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i].reset(ModelObject::Create({}, spVP_, nullptr, nullptr, spMate_));
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
	IDrawer::Reset();

	// ----- ���f���p�I�u�W�F�N�g������ ----- //

	// �e�g�����X�t�H�[��������
	core_->Initialize({ {0.0f,0.0f,0.0f}, {0.0f,+PI / 6.0f,0.0f}, {1.0f,1.0f,1.0f} });

	// ���f�����Ƃɏ�����
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->Initialize({});
	}

	// �j�̐F�ݒ�
	modelObjs_[CoreIdx]->SetColor(CoreColor::ColorPtr(CoreColor::ColorType::Blue));
	modelObjs_[InsideCoreIdx] ->SetColor(CoreColor::ColorPtr(CoreColor::ColorType::Blue));
	modelObjs_[OutsideCoreIdx]->SetColor(CoreColor::ColorPtr(CoreColor::ColorType::Blue));

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
	modelObjs_[InsideCoreIdx]->rota_ = inRotaEas.In(rotaTim_.Ratio());
	modelObjs_[InsideIdx]->rota_ = inRotaEas.In(rotaTim_.Ratio());
	// ��] (�O)
	modelObjs_[OutsideCoreIdx]->rota_ = outRotaEas.In(rotaTim_.Ratio());
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

#pragma endregion

#include "GateDrawer.h"
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
using YMath::Vector4;

using namespace DrawerConfig::Gate;

#pragma endregion

#pragma region Static

array<Model*, GateDrawerCommon::PartsNum_> GateDrawerCommon::spModels_ =
{
	nullptr, nullptr, nullptr, nullptr,
};

#pragma endregion

// �C���f�b�N�X
static const size_t InsideIdx	 = static_cast<size_t>(GateDrawerCommon::Parts::Inside); // ���g
static const size_t InLightIdx	 = static_cast<size_t>(GateDrawerCommon::Parts::InsideLight); // ���g (��)
static const size_t OutsideIdx	 = static_cast<size_t>(GateDrawerCommon::Parts::Outside); // �O�g
static const size_t OutLightIdx	 = static_cast<size_t>(GateDrawerCommon::Parts::OutsideLight); // �O�g (��)

void GateDrawerCommon::StaticInitialize()
{
	// ----- ���f���ǂݍ��� ----- //

	spModels_[InsideIdx]   = Model::Load("gate/inside", true); // ���g
	spModels_[InLightIdx]  = Model::Load("gate/insideLight", true); // ���g (��)
	spModels_[OutsideIdx]  = Model::Load("gate/outside", true); // �O�g
	spModels_[OutLightIdx] = Model::Load("gate/outsideLight", true); // �O�g (��)
}


void GateDrawer::Initialize(YGame::Transform* pParent)
{
	// ���N���X������
	IDrawer::Initialze(pParent, Mode::Normal, Idle::IntervalTime);

	// �F����
	color_.reset(Color::Create());

	// �I�u�W�F�N�g���� + �e�s��}�� (�p�[�c�̐�)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		// ����
		modelObjs_[i].reset(ModelObject::Create({}, spVP_, color_.get(), nullptr, spMate_));

		// �e�s��}��
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// ���Z�b�g
	Reset();
}

void GateDrawer::Reset()
{
	// ���Z�b�g
	IDrawer::Reset(Mode::Normal);

	// ----- ���f���p�I�u�W�F�N�g������ ----- //

	core_->Initialize({ {0.0f,0.0f,0.0f}, {0.0f,+PI / 6.0f,0.0f}, {1.0f,1.0f,1.0f} }); // �j

	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->Initialize({ {}, {}, DefScale });
	}

	// �F������
	color_->SetRGB(DefColor);
}

void GateDrawer::Update()
{
	// ���N���X�X�V 
	IDrawer::Update({});

	// �s��X�V (�q)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix();
	}
}

void GateDrawer::Draw()
{
	// ���f���̐��`��
	for (size_t i = 0; i < spModels_.size(); i++)
	{
		spModels_[i]->Draw(modelObjs_[i].get());
	}
}

void GateDrawer::IdleAnimation()
{
}

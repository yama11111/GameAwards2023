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
using namespace DrawerConfig::Gate;

#pragma endregion

#pragma region Static

// �C���f�b�N�X
static const size_t NormalIdx = 0; // �ʏ�
static const size_t RedIdx = 1; // ��
static const size_t InvisibleIdx = 2; // ����

static const size_t InsideIdx	 = static_cast<size_t>(GateDrawerCommon::Parts::Inside); // ���g
static const size_t InLightIdx	 = static_cast<size_t>(GateDrawerCommon::Parts::InsideLight); // ���g (��)
static const size_t OutsideIdx	 = static_cast<size_t>(GateDrawerCommon::Parts::Outside); // �O�g
static const size_t OutLightIdx	 = static_cast<size_t>(GateDrawerCommon::Parts::OutsideLight); // �O�g (��)

// �ÓI ���f���z�� ������
array<unique_ptr<Model>, GateDrawerCommon::PartsNum_> GateDrawerCommon::sModels_ =
{
	nullptr, nullptr, nullptr, nullptr,
};

// �ÓI�r���[�v���W�F�N�V����
YGame::ViewProjection* GateDrawerCommon::spVP_ = nullptr;

void GateDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP)
{
	// null�`�F�b�N
	assert(pVP);
	// ���
	spVP_ = pVP;

	// ----- ���f���ǂݍ��� ----- //

	sModels_[InsideIdx]	 .reset(Model::LoadObj("gate/inside", true)); // ���g
	sModels_[InLightIdx] .reset(Model::LoadObj("gate/insideLight", true)); // ���g (��)
	sModels_[OutsideIdx] .reset(Model::LoadObj("gate/outside", true)); // �O�g
	sModels_[OutLightIdx].reset(Model::LoadObj("gate/outsideLight", true)); // �O�g (��)
}

#pragma endregion

void GateDrawer::Initialize(YGame::Transform* pParent, const Mode& mode)
{
	// ���N���X������
	IDrawer::Initialze(pParent, mode, Idle::IntervalTime);

	// �F����
	colors_[NormalIdx].reset(Color::Create());
	colors_[RedIdx].reset(Color::Create());
	colors_[InvisibleIdx].reset(Color::Create());

	// �I�u�W�F�N�g���� + �e�s��}�� (�p�[�c�̐�)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		for (size_t j = 0; j < modelObjs_[i].size(); j++)
		{
			// ����
			modelObjs_[i][j].reset(ModelObject::Create({}, spVP_, colors_[i].get(), nullptr));

			// �e�s��}��
			modelObjs_[i][j]->parent_ = &core_->m_;
		}
	}

	// ���Z�b�g
	Reset(mode);
}

void GateDrawer::Reset(const Mode& mode)
{
	// ���Z�b�g
	IDrawer::Reset(mode);

	// ----- ���f���p�I�u�W�F�N�g������ ----- //

	core_->Initialize({ {0.0f,0.0f,0.0f}, {0.0f,+PI / 6.0f,0.0f}, {1.0f,1.0f,1.0f} }); // �j

	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		// �傫��
		Vector3 scale = Vector3(1.0f, 1.0f, 1.0f);
		
		// �����Ȃ�
		if (i == InvisibleIdx)
		{
			scale *= DrawerConfig::InvisibleScale;
		}

		modelObjs_[i][InsideIdx]->Initialize({ {}, {}, scale }); // ���g
		modelObjs_[i][InLightIdx]->Initialize({ {}, {}, scale }); // ���g (��)
		modelObjs_[i][OutsideIdx]->Initialize({ {}, {}, scale }); // �O�g
		modelObjs_[i][OutLightIdx]->Initialize({ {}, {}, scale }); // �O�g (��)
	}

	// �F������
	colors_[NormalIdx]->Initialize();
	colors_[RedIdx]->Initialize();
	colors_[InvisibleIdx]->Initialize();
}

void GateDrawer::Update()
{
	// ���N���X�X�V 
	IDrawer::Update({});

	// �s��X�V (�q)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		for (size_t j = 0; j < modelObjs_[i].size(); j++)
		{
			modelObjs_[i][j]->UpdateMatrix();
		}
	}
}

void GateDrawer::PreDraw()
{
	// �����`��
	for (size_t i = 0; i < sModels_.size(); i++)
	{
		sModels_[i]->Draw(modelObjs_[InvisibleIdx][i].get());
	}

	// �ʏ�Ȃ�
	if (current_ == Mode::Normal)
	{
		// �`��
		for (size_t i = 0; i < sModels_.size(); i++)
		{
			sModels_[i]->Draw(modelObjs_[NormalIdx][i].get());
		}
	}
}

void GateDrawer::PostDraw()
{
	// �ԂȂ�
	if (current_ == Mode::Red)
	{
		// �`��
		for (size_t i = 0; i < sModels_.size(); i++)
		{
			sModels_[i]->Draw(modelObjs_[RedIdx][i].get());
		}
	}
}

void GateDrawer::IdleAnimation()
{
}

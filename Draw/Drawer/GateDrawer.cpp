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
static const size_t FrameIdx = static_cast<size_t>(GateDrawerCommon::Parts::Frame); // �g


// �ÓI ���f���z�� ������
array<array<unique_ptr<Model>, GateDrawerCommon::PartsNum_>, GateDrawerCommon::ModeNum_> GateDrawerCommon::sModels_ =
{
	nullptr, nullptr,
	nullptr, nullptr,
	nullptr, nullptr
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

	// �ʏ�
	sModels_[NormalIdx][FrameIdx].reset(Model::Create("GateNormal.png")); // �g
	sModels_[NormalIdx][1].reset(Model::Create());

	// ��
	sModels_[RedIdx][FrameIdx].reset(Model::Create("GateRed.png")); // �g
	sModels_[RedIdx][1].reset(Model::Create());

	// ����
	sModels_[InvisibleIdx][FrameIdx].reset(Model::Create("GateInvisible.png")); // �g
	sModels_[InvisibleIdx][1].reset(Model::Create());
}

#pragma endregion

void GateDrawer::Initialize(YGame::Transform* pParent, const Mode& mode)
{
	// ���N���X������
	IDrawer::Initialze(pParent, mode, Idle::IntervalTime);

	// �����F����
	invisibleColor_.reset(Color::Create({ 1.0f,1.0f,1.0f,0.25f }));

	// �I�u�W�F�N�g���� + �e�s��}�� (�p�[�c�̐�)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		for (size_t j = 0; j < modelObjs_[i].size(); j++)
		{
			// ����ver
			if (i == InvisibleIdx)
			{
				modelObjs_[i][j].reset(ModelObject::Create({}, spVP_, invisibleColor_.get(), nullptr));
			}
			// �ʏ�A��ver
			else
			{
				modelObjs_[i][j].reset(ModelObject::Create({}, spVP_, color_.get(), nullptr));
			}

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

	// �傫��
	Vector3 scale = { 0.25f,2.0f,1.0f };

	// ���f���p�I�u�W�F�N�g������
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		for (size_t j = 0; j < modelObjs_[i].size(); j++)
		{
			// ����ver
			if (i == InvisibleIdx)
			{
				Vector3 scaleVal = { 
					scale.x_ - 0.01f,
					scale.y_ - 0.01f,
					DrawerConfig::InvisibleScale 
				};

				modelObjs_[i][j]->Initialize({ {}, {}, scaleVal });
			}
			// �ʏ�A��ver
			else
			{
				modelObjs_[i][j]->Initialize({ {}, {}, scale });
			}
		}
	}

	current_ = mode;
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
	sModels_[InvisibleIdx][FrameIdx]->Draw(modelObjs_[InvisibleIdx][FrameIdx].get());

	// �ʏ�Ȃ�
	if (current_ == Mode::Normal)
	{
		// �`��
		sModels_[NormalIdx][FrameIdx]->Draw(modelObjs_[NormalIdx][FrameIdx].get());
	}
}

void GateDrawer::PostDraw()
{
	// �ԂȂ�
	if (current_ == Mode::Red)
	{
		// �`��
		sModels_[RedIdx][FrameIdx]->Draw(modelObjs_[RedIdx][FrameIdx].get());
	}
}

void GateDrawer::IdleAnimation()
{
}

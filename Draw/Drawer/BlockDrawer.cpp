#include "BlockDrawer.h"
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
using namespace DrawerConfig::Block;

#pragma endregion

#pragma region Static

// �C���f�b�N�X
static const size_t NormalIdx = 0; // �ʏ�
static const size_t RedIdx = 1; // ��
static const size_t InvisibleIdx = 2; // ����
static const size_t CubeIdx = static_cast<size_t>(BlockDrawerCommon::Parts::Cube); // ��


// �ÓI ���f���z�� ������
array<array<unique_ptr<Model>, BlockDrawerCommon::PartsNum_>, BlockDrawerCommon::ModeNum_> BlockDrawerCommon::sModels_ =
{
	nullptr, nullptr,
	nullptr, nullptr,
	nullptr, nullptr
};

// �ÓI�r���[�v���W�F�N�V����
YGame::ViewProjection* BlockDrawerCommon::spVP_ = nullptr;

void BlockDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP)
{
	// null�`�F�b�N
	assert(pVP);
	// ���
	spVP_ = pVP;

	// ----- ���f���ǂݍ��� ----- //

	// �ʏ�
	sModels_[NormalIdx][CubeIdx].reset(Model::Create("blockNormal.png")); // ������
	sModels_[NormalIdx][1].reset(Model::Create());

	// ��
	sModels_[RedIdx][CubeIdx].reset(Model::Create("blockRed.png")); // ������
	sModels_[RedIdx][1].reset(Model::Create());

	// ����
	sModels_[InvisibleIdx][CubeIdx].reset(Model::Create("blockInvisible.png")); // ������
	sModels_[InvisibleIdx][1].reset(Model::Create());
}

#pragma endregion

void BlockDrawer::Initialize(YMath::Matrix4* pParent, const Mode& mode)
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

void BlockDrawer::Reset(const Mode& mode)
{
	// ���Z�b�g
	IDrawer::Reset(mode);

	// ���f���p�I�u�W�F�N�g������
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		for (size_t j = 0; j < modelObjs_[i].size(); j++)
		{
			// ����ver
			if (i == InvisibleIdx)
			{
				Vector3 scaleVal = {
					DrawerConfig::InvisibleScale,
					DrawerConfig::InvisibleScale,
					DrawerConfig::InvisibleScale
				};

				modelObjs_[i][j]->Initialize({ {},{},scaleVal });
			}
			// �ʏ�A��ver
			else
			{
				modelObjs_[i][j]->Initialize({});
			}
		}
	}
}

void BlockDrawer::Update()
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

void BlockDrawer::PreDraw()
{
	// �����`��
	sModels_[InvisibleIdx][CubeIdx]->Draw(modelObjs_[InvisibleIdx][CubeIdx].get());

	// �ʏ�Ȃ�
	if (current_ == Mode::Normal)
	{
		// �`��
		sModels_[NormalIdx][CubeIdx]->Draw(modelObjs_[NormalIdx][CubeIdx].get());
	}
}

void BlockDrawer::PostDraw()
{
	// �ԂȂ�
	if (current_ == Mode::Red)
	{
		// �`��
		sModels_[RedIdx][CubeIdx]->Draw(modelObjs_[RedIdx][CubeIdx].get());
	}
}

void BlockDrawer::IdleAnimation()
{
}

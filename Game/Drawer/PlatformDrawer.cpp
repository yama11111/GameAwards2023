#include "PlatformDrawer.h"
#include "CalcTransform.h"
#include "DrawerConfig.h"
#include "CoreColor.h"
#include <cassert>

#pragma region ���O���

using std::array;
using std::unique_ptr;

using YGame::Transform;
using YGame::Model;
using YGame::CBColor;
using YGame::CBMaterial;

using YGame::SlimeActor;

using YMath::Ease;
using YMath::Power;
using YMath::Vector3;
using YMath::Vector4;

using namespace DrawerConfig::Block;

#pragma endregion

#pragma region Static

array<Model*, PlatformDrawerCommon::sPartsNum_> PlatformDrawerCommon::spModels_ =
{
	nullptr, nullptr,
};

unique_ptr<CBMaterial> PlatformDrawerCommon::sHologramMate_ = nullptr;

#pragma endregion

#pragma region �C���f�b�N�X

static const size_t HologramIdx = static_cast<size_t>(PlatformDrawerCommon::Parts::eHologram); // �z���O����
static const size_t LeftIdx = static_cast<size_t>(PlatformDrawerCommon::Parts::eLeft); // ��
static const size_t RightIdx = static_cast<size_t>(PlatformDrawerCommon::Parts::eRight); // �E

#pragma endregion

#pragma region Common

void PlatformDrawerCommon::StaticInitialize()
{
	// ----- ���f���ǂݍ��� ----- //

	// �u���b�N (��)
	spModels_[HologramIdx]	 = Model::LoadObj("platform/hologram", true); // �z���O����
	spModels_[LeftIdx]		 = Model::LoadObj("platform/left", true); // ��
	spModels_[RightIdx]		 = Model::LoadObj("platform/right", true); // �E

	// ----- �I�u�W�F�N�g ----- //

	sHologramMate_.reset(CBMaterial::Create());
	sHologramMate_->SetAlpha(0.25f);
}

#pragma endregion

#pragma region Drawer

void PlatformDrawer::Initialize(Transform* pParent)
{
	// ���N���X������
	IDrawer::Initialze(pParent);

	// �I�u�W�F�N�g���� + �e�s��}�� (�p�[�c�̐�)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		// ����
		modelObjs_[i].reset(Model::Object::Create(Transform::Status::Default(), spVP_));

		// �e�s��}��
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// ���Z�b�g
	Reset();
}

void PlatformDrawer::Reset()
{
	// ���Z�b�g
	IDrawer::Reset();


	// �j�̐F�ƃ}�e���A���ݒ�
	CBColor* pColor = nullptr;
	CBMaterial* pMaterial = nullptr;
		
	pColor = CoreColor::ColorPtr(CoreColor::ColorType::eGreen);
	pMaterial = sHologramMate_.get();

	modelObjs_[HologramIdx]->SetColor(pColor);
	modelObjs_[HologramIdx]->SetMaterial(pMaterial);
}

void PlatformDrawer::Update()
{
	// ���N���X�X�V 
	IDrawer::Update({});

	// �s��X�V (�q)
	modelObjs_[HologramIdx]->UpdateMatrix();

	float pos = 1.0f - (1.6f / pParent_->scale_.x_);
	float sca = pParent_->scale_.y_ / pParent_->scale_.x_;
	
	modelObjs_[LeftIdx]->pos_.x_ = -pos;
	modelObjs_[LeftIdx]->scale_.x_ = sca;
	modelObjs_[LeftIdx]->UpdateMatrix({ {}, {}, {} });

	modelObjs_[RightIdx]->pos_.x_ = +pos;
	modelObjs_[RightIdx]->scale_.x_ = sca;
	modelObjs_[RightIdx]->UpdateMatrix({ {}, {}, {} });
}

void PlatformDrawer::Draw()
{
	// ���f���̐��`��
	spModels_[LeftIdx]->SetDrawCommand(modelObjs_[LeftIdx].get(), YGame::DrawLocation::Center);
	spModels_[RightIdx]->SetDrawCommand(modelObjs_[RightIdx].get(), YGame::DrawLocation::Center);
	spModels_[HologramIdx]->SetDrawCommand(modelObjs_[HologramIdx].get(), YGame::DrawLocation::Center);
}

#pragma endregion
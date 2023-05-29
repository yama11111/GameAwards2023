#include "KeyDrawer.h"
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

using namespace DrawerConfig::Key;

#pragma endregion

#pragma region Static

array<Model*, KeyDrawerCommon::sPartsNum_> KeyDrawerCommon::spModels_ =
{
	nullptr, nullptr,
};
Ease<float> KeyDrawerCommon::sIdleHeightEase_;

#pragma endregion

#pragma region �C���f�b�N�X

static const size_t BladeIdx = static_cast<size_t>(KeyDrawerCommon::Parts::eBlade); // �n
static const size_t RingCoreIdx = static_cast<size_t>(KeyDrawerCommon::Parts::eRingCore); // �����O�j
static const size_t RingShellIdx = static_cast<size_t>(KeyDrawerCommon::Parts::eRingShell); // �����O�k

#pragma endregion

#pragma region Common

void KeyDrawerCommon::StaticInitialize()
{
	// ----- ���f���ǂݍ��� ----- //

	spModels_[BladeIdx] = Model::LoadObj("key/blade", true); // �n
	spModels_[RingCoreIdx] = Model::LoadObj("key/ring/core", true); // �����O�j
	spModels_[RingShellIdx] = Model::LoadObj("key/ring/shell", true); // �����O�k


	// ----- �A�j���[�V���� ----- //

	// ���������C�[�W���O������
	sIdleHeightEase_.Initialize(Idle::Height::Start, Idle::Height::End, Idle::Height::Exponent);
}

#pragma endregion

#pragma region Drawer

void KeyDrawer::Initialize(Transform* pParent)
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

void KeyDrawer::Reset()
{
	// ���Z�b�g
	IDrawer::Reset();

	// �j�̐F�ƃ}�e���A���ݒ�
	CoreColor::ColorType color = CoreColor::ColorType::eBlue;
	CoreColor::PartsType coreParts = CoreColor::PartsType::eCore;
	CoreColor::PartsType shellParts = CoreColor::PartsType::eShell;

	modelObjs_[BladeIdx]->SetColor(CoreColor::ColorPtr(color, coreParts));
	modelObjs_[BladeIdx]->SetMaterial(CoreColor::MaterialPtr(color, coreParts));

	modelObjs_[RingCoreIdx]->SetColor(CoreColor::ColorPtr(color, coreParts));
	modelObjs_[RingCoreIdx]->SetMaterial(CoreColor::MaterialPtr(color, coreParts));
	
	modelObjs_[RingShellIdx]->SetColor(CoreColor::ColorPtr(color, shellParts));
	modelObjs_[RingShellIdx]->SetMaterial(CoreColor::MaterialPtr(color, shellParts));

	// �I�u�W�F�N�g������(�p�[�c�̐�)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->Initialize();
	}


	// ----- �A�j���[�V���� ----- //

	// ����
	isAct_ = true;
	

	// �A�j���p������
	animeBladePos_ = animeRingPos_ = animeRingRota_ = {};

	
	// �������[�V��������
	isIdle_ = true;

	// �����^�C�}�[������
	for (size_t i = 0; i < idlePowers_.size(); i++)
	{
		idlePowers_[i].Initialize(Idle::Frame);
	}

}

void KeyDrawer::Update()
{
	// ���N���X�X�V 
	IDrawer::Update({});


	// �A�j���p������
	animeBladePos_ = animeRingPos_ = animeRingRota_ = {};

	// �����O�ʒu
	animeRingPos_ = Vector3(0.0f, RingHeight, 0.0f);

	// �������[�V�����X�V
	UpdateIdleAnimation();


	// �s��X�V (�q)
	modelObjs_[BladeIdx]->UpdateMatrix({ animeBladePos_ });
	modelObjs_[RingCoreIdx]->UpdateMatrix({ animeRingPos_, animeRingRota_ });
	modelObjs_[RingShellIdx]->UpdateMatrix({ animeRingPos_, animeRingRota_ });
}

void KeyDrawer::Draw()
{
	// ���f���̐��`��
	for (size_t i = 0; i < spModels_.size(); i++)
	{
		spModels_[i]->SetDrawCommand(modelObjs_[i].get(), YGame::DrawLocation::Center);
	}
}

void KeyDrawer::UpdateIdleAnimation()
{
	// �����Ă��Ȃ��Ȃ�e��
	if (isAct_ == false) { return; }

	// �������[�V��������Ȃ��Ȃ�e��
	if (isIdle_ == false) { return; }


	for (size_t i = 0; i < sSetNum_; i++)
	{
		// �p���[�X�V
		idlePowers_[i].Update(isIdlePowerSwitches_[i]);

		// 0�̎�
		if (i == 0)
		{
			// �X�C�b�`�I���Ȃ�
			if (isIdlePowerSwitches_[i])
			{

				// �ʒu
				animeRingPos_.y_ += sIdleHeightEase_.In(idlePowers_[i].Ratio());
			}
			// �X�C�b�`�I�t�Ȃ�
			else
			{

				// �ʒu
				animeRingPos_.y_ += sIdleHeightEase_.Out(idlePowers_[i].Ratio());
			}

		}
		// 1 �̎�
		else if (i == 1)
		{
			// �X�C�b�`�I���Ȃ�
			if (isIdlePowerSwitches_[i])
			{
				// �ʒu
				animeBladePos_.y_ += sIdleHeightEase_.In(idlePowers_[i].Ratio());
			}
			// �X�C�b�`�I�t�Ȃ�
			else
			{
				// �ʒu
				animeBladePos_.y_ += sIdleHeightEase_.Out(idlePowers_[i].Ratio());
			}
		}

		// �X�C�b�`
		if (idlePowers_[i].IsMax()) { isIdlePowerSwitches_[i] = false; }
		else if (idlePowers_[i].IsZero()) { isIdlePowerSwitches_[i] = true; }
	}
}

#pragma endregion
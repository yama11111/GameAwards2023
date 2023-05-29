#include "SwitchDrawer.h"
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

using namespace DrawerConfig::Switch;

#pragma endregion

#pragma region Static

array<Model*, SwitchDrawerCommon::sPartsNum_> SwitchDrawerCommon::spModels_ =
{
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
};
Ease<float> SwitchDrawerCommon::sSwitchOnRotaSpeedEase_;

#pragma endregion

#pragma region �C���f�b�N�X

static const size_t BaseOnCoreIdx = static_cast<size_t>(SwitchDrawerCommon::Parts::eBaseOnCore); // ����I���j
static const size_t BaseOnShellIdx = static_cast<size_t>(SwitchDrawerCommon::Parts::eBaseOnShell); // ����I���k
static const size_t BaseOffCoreIdx = static_cast<size_t>(SwitchDrawerCommon::Parts::eBaseOffCore); // ����I�t�j
static const size_t BaseOffShellIdx = static_cast<size_t>(SwitchDrawerCommon::Parts::eBaseOffShell); // ����I�t�k
static const size_t LeverCoreIdx = static_cast<size_t>(SwitchDrawerCommon::Parts::eLeverCore); // ���o�[�j
static const size_t LeverShellIdx = static_cast<size_t>(SwitchDrawerCommon::Parts::eLeverShell); // ���o�[�k

static const size_t BlueIdx = static_cast<size_t>(SwitchDrawerCommon::Type::eBlue); // ��

#pragma endregion

#pragma region Common

void SwitchDrawerCommon::StaticInitialize()
{
	// ----- ���f���ǂݍ��� ----- //

	spModels_[BaseOnCoreIdx]	 = Model::LoadObj("switch/base/on/core", true); // ����I���j
	spModels_[BaseOnShellIdx]	 = Model::LoadObj("switch/base/on/shell", true); // ����I���k
	spModels_[BaseOffCoreIdx]	 = Model::LoadObj("switch/base/off/core", true); // ����I�t�j
	spModels_[BaseOffShellIdx]	 = Model::LoadObj("switch/base/off/shell", true); // ����I�t�k
	spModels_[LeverCoreIdx]		 = Model::LoadObj("switch/lever/core", true); // ���o�[�j
	spModels_[LeverShellIdx]	 = Model::LoadObj("switch/lever/shell", true); // ���o�[�k

	// ----- �A�j���[�V���� ----- //

	// �X�C�b�`�I����]�X�s�[�h�C�[�W���O
	sSwitchOnRotaSpeedEase_.Initialize(RotaSpeed::Start, RotaSpeed::End, RotaSpeed::Exponent);
}

#pragma endregion

#pragma region Drawer

void SwitchDrawer::Initialize(Transform* pParent, const Type& type)
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
	Reset(type);
}

void SwitchDrawer::Reset(const Type& type)
{
	// ���Z�b�g
	IDrawer::Reset();

	// ���
	type_ = type;

	// �C���f�b�N�X���v�Z
	typeIndex_ = static_cast<size_t>(type);

	// �j�̐F�ƃ}�e���A���ݒ�
	CoreColor::ColorType color = CoreColor::ColorType::eBlue;
	CoreColor::PartsType coreParts = CoreColor::PartsType::eCore;
	CoreColor::PartsType shellParts = CoreColor::PartsType::eShell;

	modelObjs_[BaseOnCoreIdx]->SetColor(CoreColor::ColorPtr(color, coreParts));
	modelObjs_[BaseOnCoreIdx]->SetMaterial(CoreColor::MaterialPtr(color, coreParts));
	
	modelObjs_[BaseOnShellIdx]->SetColor(CoreColor::ColorPtr(color, shellParts));
	modelObjs_[BaseOnShellIdx]->SetMaterial(CoreColor::MaterialPtr(color, shellParts));
	
	modelObjs_[BaseOffCoreIdx]->SetColor(CoreColor::ColorPtr(color, coreParts));
	modelObjs_[BaseOffCoreIdx]->SetMaterial(CoreColor::MaterialPtr(color, coreParts));
	
	modelObjs_[BaseOffShellIdx]->SetColor(CoreColor::ColorPtr(color, shellParts));
	modelObjs_[BaseOffShellIdx]->SetMaterial(CoreColor::MaterialPtr(color, shellParts));
	
	modelObjs_[LeverCoreIdx]->SetColor(CoreColor::ColorPtr(color, coreParts));
	modelObjs_[LeverCoreIdx]->SetMaterial(CoreColor::MaterialPtr(color, coreParts));
	
	modelObjs_[LeverShellIdx]->SetColor(CoreColor::ColorPtr(color, shellParts));
	modelObjs_[LeverShellIdx]->SetMaterial(CoreColor::MaterialPtr(color, shellParts));

	// �I�u�W�F�N�g������(�p�[�c�̐�)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->Initialize();
	}


	// ----- �A�j���[�V���� ----- //

	// ����
	isAct_ = true;

	// �A�j���p������
	animeBasePos_ = {};
	animeLeverPos_= animeLeverRota_ = {};


	// �X�C�b�`�I����
	isSwitchOn_ = false;

	// �X�C�b�`�I���p���[
	switchOnPower_.Initialize(RotaSpeed::Frame);
}

void SwitchDrawer::Update()
{
	// ���N���X�X�V 
	IDrawer::Update({});


	// �A�j���p������
	animeBasePos_ = {};
	animeLeverPos_ = animeLeverRota_ = {};

	animeBasePos_ = Vector3(0.0f, BaseHeight, 0.0f);
	animeLeverPos_ = Vector3(0.0f, LeverHeight, 0.0f);


	// �X�C�b�`�A�j���[�V����
	UpdateSwitchAnimation();


	// �s��X�V (�q)
	modelObjs_[BaseOnCoreIdx]->UpdateMatrix({ animeBasePos_ });
	modelObjs_[BaseOnShellIdx]->UpdateMatrix({ animeBasePos_ });
	modelObjs_[BaseOffCoreIdx]->UpdateMatrix({ animeBasePos_ });
	modelObjs_[BaseOffShellIdx]->UpdateMatrix({ animeBasePos_ });
	modelObjs_[LeverCoreIdx]->UpdateMatrix({ animeLeverPos_, animeLeverRota_ });
	modelObjs_[LeverShellIdx]->UpdateMatrix({ animeLeverPos_, animeLeverRota_ });
}

void SwitchDrawer::Draw()
{
	// ���f���̐��`��
	for (size_t i = 0; i < spModels_.size(); i++)
	{
		spModels_[i]->SetDrawCommand(modelObjs_[i].get(), YGame::DrawLocation::Center);
	}
}

void SwitchDrawer::AnimateSwitch(const bool isSwitchOn)
{
	// ���
	isSwitchOn_ = isSwitchOn;
}

void SwitchDrawer::UpdateSwitchAnimation()
{
	// �����Ă��Ȃ��Ȃ�e��
	if (isAct_ == false) { return; }


	// �X�C�b�`�I���p���[�X�V
	switchOnPower_.Update(isSwitchOn_);


	// �X�C�b�`�I���Ȃ�
	if (isSwitchOn_)
	{
		// �C�[�Y�C��
		animeLeverRota_.z_ += sSwitchOnRotaSpeedEase_.In(switchOnPower_.Ratio());
	}
	// ����ȊO�Ȃ�
	else 
	{
		// �C�[�Y�A�E�g
		animeLeverRota_.z_ += sSwitchOnRotaSpeedEase_.Out(switchOnPower_.Ratio());
	}


	// �F�ύX
	CoreColor::ColorType color = CoreColor::ColorType::eGray;

	if (switchOnPower_.IsMax())
	{
		if (type_ == Type::eBlue)
		{
			color = CoreColor::ColorType::eBlue;
		}
	}

	// �j�̐F�ƃ}�e���A���ݒ�
	CoreColor::PartsType coreParts = CoreColor::PartsType::eCore;
	CoreColor::PartsType shellParts = CoreColor::PartsType::eShell;

	modelObjs_[BaseOnCoreIdx]->SetColor(CoreColor::ColorPtr(color, coreParts));
	modelObjs_[BaseOnCoreIdx]->SetMaterial(CoreColor::MaterialPtr(color, coreParts));

	modelObjs_[BaseOnShellIdx]->SetColor(CoreColor::ColorPtr(color, shellParts));
	modelObjs_[BaseOnShellIdx]->SetMaterial(CoreColor::MaterialPtr(color, shellParts));

	modelObjs_[BaseOffCoreIdx]->SetColor(CoreColor::ColorPtr(color, coreParts));
	modelObjs_[BaseOffCoreIdx]->SetMaterial(CoreColor::MaterialPtr(color, coreParts));

	modelObjs_[BaseOffShellIdx]->SetColor(CoreColor::ColorPtr(color, shellParts));
	modelObjs_[BaseOffShellIdx]->SetMaterial(CoreColor::MaterialPtr(color, shellParts));

	modelObjs_[LeverCoreIdx]->SetColor(CoreColor::ColorPtr(color, coreParts));
	modelObjs_[LeverCoreIdx]->SetMaterial(CoreColor::MaterialPtr(color, coreParts));

	modelObjs_[LeverShellIdx]->SetColor(CoreColor::ColorPtr(color, shellParts));
	modelObjs_[LeverShellIdx]->SetMaterial(CoreColor::MaterialPtr(color, shellParts));
}

#pragma endregion
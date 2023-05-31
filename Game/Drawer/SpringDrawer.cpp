#include "SpringDrawer.h"
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
using YGame::Audio;

using YMath::Ease;
using YMath::Power;
using YMath::Vector3;
using YMath::Vector4;

using namespace DrawerConfig::Spring;

#pragma endregion

#pragma region Static

array<Model*, SpringDrawerCommon::sPartsNum_> SpringDrawerCommon::spModels_ =
{
	nullptr, nullptr,
};

array<Ease<float>, SpringDrawerCommon::sRingNum_> SpringDrawerCommon::sIdleHeightEases_;
Ease<float> SpringDrawerCommon::sIdleRotaSpeedEase_;
Ease<float>SpringDrawerCommon::sJumpAnticipationHeightEase_;
array<Ease<float>, SpringDrawerCommon::sRingNum_> SpringDrawerCommon::sJumpHeightEases_;
Ease<Vector3>SpringDrawerCommon::sJumpAnticipationScaleEase_;
array<Ease<Vector3>, SpringDrawerCommon::sRingNum_> SpringDrawerCommon::sJumpScaleEases_;
Audio* SpringDrawerCommon::spJumpSE_ = nullptr;

#pragma endregion

#pragma region �C���f�b�N�X

static const size_t BaseIdx = static_cast<size_t>(SpringDrawerCommon::Parts::eBase); // ���
static const size_t CoreIdx = static_cast<size_t>(SpringDrawerCommon::Parts::eCore); // �j
static const size_t TopCoreIdx = static_cast<size_t>(SpringDrawerCommon::Parts::eTopCore); // ��j
static const size_t TopShellIdx = static_cast<size_t>(SpringDrawerCommon::Parts::eTopShell); // ��k
static const size_t BottomCoreIdx = static_cast<size_t>(SpringDrawerCommon::Parts::eBottomCore); // ���j
static const size_t BottomShellIdx = static_cast<size_t>(SpringDrawerCommon::Parts::eBottomShell); // ���k

static const size_t TopRingIdx = 0; // ��ւ���
static const size_t BottomRingIdx = 1; // ���ւ���

#pragma endregion

#pragma region Common

void SpringDrawerCommon::StaticInitialize()
{
	// ----- ���f���ǂݍ��� ----- //

	// �΂�
	spModels_[BaseIdx] = Model::LoadObj("spring/base", true); // ���
	spModels_[CoreIdx] = Model::LoadObj("spring/core", true); // �j
	spModels_[TopCoreIdx] = Model::LoadObj("spring/top/core", true); // ��j
	spModels_[TopShellIdx] = Model::LoadObj("spring/top/shell", true); // ��k
	spModels_[BottomCoreIdx] = Model::LoadObj("spring/bottom/core", true); // ���j
	spModels_[BottomShellIdx] = Model::LoadObj("spring/bottom/shell", true); // ���k

	// ----- �A�j���[�V���� ----- //
	
	// ���������C�[�W���O
	sIdleHeightEases_[TopRingIdx].Initialize(Idle::Height::Top::Start, Idle::Height::Top::End, Idle::Height::Top::Exponent);
	sIdleHeightEases_[BottomRingIdx].Initialize(Idle::Height::Bottom::Start, Idle::Height::Bottom::End, Idle::Height::Bottom::Exponent);
	
	// ������]�X�s�[�h�C�[�W���O
	sIdleRotaSpeedEase_.Initialize(Idle::RotaSpeed::Start, Idle::RotaSpeed::End, Idle::RotaSpeed::Exponent);
	

	// �W�����v�\�����썂���C�[�W���O
	sJumpAnticipationHeightEase_.Initialize(
		Jump::Height::Anticipation::Start, Jump::Height::Anticipation::End, Jump::Height::Anticipation::Exponent);
	
	// �W�����v�����C�[�W���O
	sJumpHeightEases_[TopRingIdx].Initialize(
		Jump::Height::Performance::Top::Start, Jump::Height::Performance::Top::End, Jump::Height::Performance::Top::Exponent);
	sJumpHeightEases_[BottomRingIdx].Initialize(
		Jump::Height::Performance::Bottom::Start, Jump::Height::Performance::Bottom::End, Jump::Height::Performance::Bottom::Exponent);

	// �W�����v�\������傫���C�[�W���O
	sJumpAnticipationScaleEase_.Initialize(
		Jump::Scale::Anticipation::Start, Jump::Scale::Anticipation::End, Jump::Scale::Anticipation::Exponent);

	// �W�����v�傫���C�[�W���O
	sJumpScaleEases_[TopRingIdx].Initialize(
		Jump::Scale::Performance::Top::Start, Jump::Scale::Performance::Top::End, Jump::Scale::Performance::Top::Exponent);
	sJumpScaleEases_[BottomRingIdx].Initialize(
		Jump::Scale::Performance::Bottom::Start, Jump::Scale::Performance::Bottom::End, Jump::Scale::Performance::Bottom::Exponent);


	spJumpSE_ = Audio::Load("SE/SE_spring.wav");
}

#pragma endregion

#pragma region Drawer

void SpringDrawer::Initialize(Transform* pParent)
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

void SpringDrawer::Reset()
{
	// ���Z�b�g
	IDrawer::Reset();

	// �j�̐F�ƃ}�e���A���ݒ�
	CoreColor::ColorType color = CoreColor::ColorType::eBlue;
	CoreColor::PartsType coreParts = CoreColor::PartsType::eCore;
	CoreColor::PartsType shellParts = CoreColor::PartsType::eShell;

	modelObjs_[BaseIdx]->SetColor(CoreColor::ColorPtr(color, shellParts));
	modelObjs_[BaseIdx]->SetMaterial(CoreColor::MaterialPtr(color, shellParts));

	modelObjs_[CoreIdx]->SetColor(CoreColor::ColorPtr(color, coreParts));
	modelObjs_[CoreIdx]->SetMaterial(CoreColor::MaterialPtr(color, coreParts));

	modelObjs_[TopCoreIdx]->SetColor(CoreColor::ColorPtr(color, coreParts));
	modelObjs_[TopCoreIdx]->SetMaterial(CoreColor::MaterialPtr(color, coreParts));
	
	modelObjs_[TopShellIdx]->SetColor(CoreColor::ColorPtr(color, shellParts));
	modelObjs_[TopShellIdx]->SetMaterial(CoreColor::MaterialPtr(color, shellParts));

	modelObjs_[BottomCoreIdx]->SetColor(CoreColor::ColorPtr(color, coreParts));
	modelObjs_[BottomCoreIdx]->SetMaterial(CoreColor::MaterialPtr(color, coreParts));

	modelObjs_[BottomShellIdx]->SetColor(CoreColor::ColorPtr(color, shellParts));
	modelObjs_[BottomShellIdx]->SetMaterial(CoreColor::MaterialPtr(color, shellParts));


	// ----- �A�j���[�V���� ----- //

	// ����
	isAct_ = true;

	// �A�j���p������
	for (size_t i = 0; i < sRingNum_; i++)
	{
		animePoss_[i] = animeRotas_[i] = animeScales_[i] = {};
	}


	// �������[�V��������
	isIdle_ = true;

	// �����������[�V��������
	isIdleHeight_ = true;

	// �������[�V�����^�C�}�[������ + �J�n
	idleTimer_.Initialize(Idle::RotaSpeed::Frame);
	idleTimer_.SetActive(true);

	// �������[�V�����p���[������
	idlePowers_[TopRingIdx].Initialize(Idle::Height::Frame);
	idlePowers_[BottomRingIdx].Initialize(Idle::Height::Frame);
	
	// �������[�V�����X�C�b�`������
	isIdlePowerSwitches_[TopRingIdx] = false;
	isIdlePowerSwitches_[BottomRingIdx] = false;


	// �W�����v���Ă��Ȃ�
	isJumped_ = false;

	// �W�����v�\������p���[������
	jumpAnticipationPower_.Initialize(Jump::Frame::Anticipation);

	// �W�����v�\������p���[�X�C�b�`������
	isJumpedAnticipationSwitch_ = false;

	// �W�����v�A�j���[�V�����p���[������
	jumpPowers_[TopRingIdx].Initialize(Jump::Frame::Performance);
	jumpPowers_[BottomRingIdx].Initialize(Jump::Frame::Performance);

	// �W�����v�A�j���[�V�����p���[�X�C�b�`������
	isJumpedSwitch_ = false;
}

void SpringDrawer::Update()
{
	// ���N���X�X�V 
	IDrawer::Update({});


	// �A�j���p������
	for (size_t i = 0; i < sRingNum_; i++)
	{
		animePoss_[i] = animeRotas_[i] = animeScales_[i] = {};
	}


	// �������[�V�����X�V
	UpdateIdle();

	// �W�����v�A�j���[�V�����X�V
	UpdateJump();


	// �s��X�V (�q)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		// �A�j���p
		Vector3 pos = {};
		Vector3 rota = {};
		Vector3 scale = {};

		// �ナ���O
		if (i == TopCoreIdx || i == TopShellIdx)
		{
			pos = animePoss_[TopRingIdx];
			rota = animeRotas_[TopRingIdx];
			scale = animeScales_[TopRingIdx];
		}
		// �������O
		else if (i == BottomCoreIdx || i == BottomShellIdx)
		{
			pos = animePoss_[BottomRingIdx];
			rota = animeRotas_[BottomRingIdx];
			scale = animeScales_[BottomRingIdx];
		}

		// ��]�ʒ���
		if (rota.y_ >= +PI * 4) { rota.y_ -= PI * 4; }
		if (rota.y_ <= -PI * 4) { rota.y_ += PI * 4; }

		modelObjs_[i]->UpdateMatrix({ pos, rota, scale });
	}
}

void SpringDrawer::Draw()
{
	// ���f���̐��`��
	for (size_t i = 0; i < spModels_.size(); i++)
	{
		spModels_[i]->SetDrawCommand(modelObjs_[i].get(), YGame::DrawLocation::Center);
	}
}

void SpringDrawer::AnimateJump()
{
	// �����������[�V�����I��
	isIdleHeight_ = false;

	// �W�����v�\������X�C�b�`�I��
	isJumpedAnticipationSwitch_ = true;

	// �W�����v����
	isJumped_ = true;

	spJumpSE_->Stop();
	spJumpSE_->Play(false);
}

void SpringDrawer::UpdateIdle()
{
	// �����Ă��Ȃ��Ȃ�e��
	if (isAct_ == false) { return; }

	// �������[�V��������Ȃ��Ȃ�e��
	if (isIdle_ == false) { return; }


	// �^�C�}�[�X�V
	idleTimer_.Update();

	// ��]
	float rota = sIdleRotaSpeedEase_.In(idleTimer_.Ratio());
	
	// ��]
	animeRotas_[TopRingIdx].y_ += rota;
	animeRotas_[BottomRingIdx].y_ += rota + BottomRingDefaultRotaValue;

	// �^�C�}�[�I�������
	if (idleTimer_.IsEnd())
	{
		// �^�C�}�[���Z�b�g
		idleTimer_.Reset(true);
	}


	// �����������[�V�������Ȃ��Ȃ�e��
	if (isIdleHeight_ == false) { return; }


	// �ナ���O�̃p���[�̔䗦���K��l�ȏ��
	if(idlePowers_[TopRingIdx].Ratio() >= 0.2f)
	{
		// �������O�̃��[�V�����J�n
		isIdleHeightBottomStart_ = true;
	}

	// �����O�̐�
	for (size_t i = 0; i < sRingNum_; i++)
	{
		// �������O�̎� && ���[�V�����J�n���Ȃ��Ȃ�
		if (i == BottomRingIdx && isIdleHeightBottomStart_ == false)
		{
			// ������΂�
			continue;
		}

		// �p���[�X�V
		idlePowers_[i].Update(isIdlePowerSwitches_[i]);

		// �X�C�b�`
		if (idlePowers_[i].IsZero())
		{
			isIdlePowerSwitches_[i] = true; 
		}
		else if (idlePowers_[i].IsMax()) 
		{
			isIdlePowerSwitches_[i] = false; 
		}

		// �ʒu
		if (isIdlePowerSwitches_[i]) 
		{
			animePoss_[i].y_ += sIdleHeightEases_[i].Out(idlePowers_[i].Ratio()); 
		}
		else 
		{
			animePoss_[i].y_ += sIdleHeightEases_[i].In(idlePowers_[i].Ratio()); 
		}
	}
}

void SpringDrawer::UpdateJump()
{
	// �����Ă��Ȃ��Ȃ�e��
	if (isAct_ == false) { return; }

	// �W�����v���Ă��Ȃ��Ȃ�e��
	if (isJumped_ == false) { return; }


	// �\������p���[�X�V
	jumpAnticipationPower_.Update(isJumpedAnticipationSwitch_);

	// ����
	if (isJumpedAnticipationSwitch_)
	{
		animePoss_[TopRingIdx].y_ += sJumpAnticipationHeightEase_.Out(jumpAnticipationPower_.Ratio());
		animePoss_[BottomRingIdx].y_ += sJumpAnticipationHeightEase_.Out(jumpAnticipationPower_.Ratio());
		
		animeScales_[TopRingIdx] += sJumpAnticipationScaleEase_.Out(jumpAnticipationPower_.Ratio());
		animeScales_[BottomRingIdx] += sJumpAnticipationScaleEase_.Out(jumpAnticipationPower_.Ratio());
	}
	else
	{
		animePoss_[TopRingIdx].y_ += sJumpAnticipationHeightEase_.In(jumpAnticipationPower_.Ratio());
		animePoss_[BottomRingIdx].y_ += sJumpAnticipationHeightEase_.In(jumpAnticipationPower_.Ratio());
		
		animeScales_[TopRingIdx] += sJumpAnticipationScaleEase_.In(jumpAnticipationPower_.Ratio());
		animeScales_[BottomRingIdx] += sJumpAnticipationScaleEase_.In(jumpAnticipationPower_.Ratio());
	}

	// �\������p���[�ő�Ȃ�
	if (jumpAnticipationPower_.IsMax())
	{
		// �X�C�b�`�I�t
		isJumpedAnticipationSwitch_ = false;

		// �W�����v�X�C�b�`�I��
		isJumpedSwitch_ = true;
	}


	for (size_t i = 0; i < sRingNum_; i++)
	{
		// �p���[�X�V
		jumpPowers_[i].Update(isJumpedSwitch_);

		// ����
		if (isJumpedSwitch_) 
		{
			animePoss_[i].y_ += sJumpHeightEases_[i].Out(jumpPowers_[i].Ratio()); 
			animeScales_[i] += sJumpScaleEases_[i].Out(jumpPowers_[i].Ratio());
		}
		else
		{ 
			animePoss_[i].y_ += sJumpHeightEases_[i].In(jumpPowers_[i].Ratio()); 
			animeScales_[i] += sJumpScaleEases_[i].In(jumpPowers_[i].Ratio());
		}
	}
	
	// �p���[�ő�Ȃ�
	if (jumpPowers_[BottomRingIdx].IsMax()) 
	{
		// �X�C�b�`�I�t
		isJumpedSwitch_ = false; 
	}
	// �\���܂߃p���[�[���Ȃ�
	else if (jumpPowers_[BottomRingIdx].IsZero() && jumpAnticipationPower_.IsZero())
	{
		// �W�����v�I��
		isJumped_ = false;

		// �����������[�V�����J�n
		isIdleHeight_ = true;
	}
}

#pragma endregion
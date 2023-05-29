#include "JunctionDrawer.h"
#include "CalcTransform.h"
#include "DrawerConfig.h"
#include "CoreColor.h"
#include <cassert>
#include <imgui.h>

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

using namespace DrawerConfig::Junction;

#pragma endregion

#pragma region Static

array<array<Model*, JunctionDrawerCommon::sPartsNum_>, JunctionDrawerCommon::sTypeNum_> JunctionDrawerCommon::spModels_ =
{
	nullptr, nullptr,
	//nullptr, nullptr,
};
Model* JunctionDrawerCommon::spGridModel_ = nullptr;
Ease<float> JunctionDrawerCommon::sIdleRotaSpeedEase_{};
Ease<float> JunctionDrawerCommon::sConnectPushScaleFactorEase_{};
Ease<float> JunctionDrawerCommon::sConnectPosFactorEase_{};
Ease<float> JunctionDrawerCommon::sConnectRotaFactorEase_{};
Ease<float> JunctionDrawerCommon::sConnectRotaSpeedEase_{};
Ease<Vector3> JunctionDrawerCommon::sConnectScaleEase_{};

#pragma endregion

#pragma region �C���f�b�N�X

static const size_t CoreIdx = static_cast<size_t>(JunctionDrawerCommon::Parts::eCore); // �j
static const size_t ShellIdx = static_cast<size_t>(JunctionDrawerCommon::Parts::eShell); // �k

static const size_t GreenIdx = static_cast<size_t>(JunctionDrawerCommon::Type::eGreen); // ��
static const size_t RedIdx = static_cast<size_t>(JunctionDrawerCommon::Type::eRed); // ��

#pragma endregion

#pragma region Common

void JunctionDrawerCommon::StaticInitialize()
{
	// ----- ���f���ǂݍ��� ----- //

	// �u���b�N (��)
	spModels_[GreenIdx][CoreIdx] = Model::LoadObj("junction/core", true); // �j
	spModels_[GreenIdx][ShellIdx] = Model::LoadObj("junction/shell", true); // �k

	spModels_[RedIdx][ShellIdx] = Model::LoadObj("junction/core", true); // �k
	spModels_[RedIdx][ShellIdx] = Model::LoadObj("junction/shell", true); // �k

	spGridModel_ = Model::LoadObj("grid", true); // �O���b�h

	// ----- �A�j���[�V���� ----- //

	// ������]�X�s�[�h�C�[�W���O
	sIdleRotaSpeedEase_.Initialize(Idle::RotaSpeed::Start, Idle::RotaSpeed::End, Idle::RotaSpeed::Exponent);

	sConnectPushScaleFactorEase_.Initialize(0.25f, 1.0f, Connect::PosFactor::Exponent);
	
	// �ڑ��ʒu�W���C�[�W���O
	sConnectPosFactorEase_.Initialize(Connect::PosFactor::Start, Connect::PosFactor::End, Connect::PosFactor::Exponent);

	// �ڑ��ʒu�W���C�[�W���O
	sConnectRotaFactorEase_.Initialize(Connect::RotaFactor::Start, Connect::RotaFactor::End, Connect::RotaFactor::Exponent);
	
	// �ڑ���]�X�s�[�h�C�[�W���O
	sConnectRotaSpeedEase_.Initialize(Connect::RotaSpeed::Start, Connect::RotaSpeed::End, Connect::RotaSpeed::Exponent);

	// �ڑ��傫���C�[�W���O
	sConnectScaleEase_.Initialize(Connect::Scale::Start, Connect::Scale::End, Connect::Scale::Exponent);
}

#pragma endregion

#pragma region Drawer

void JunctionDrawer::Initialize(Transform* pParent, const Vector3& direction, const Type& type)
{
	// ���N���X������
	IDrawer::Initialze(pParent);

	// �I�u�W�F�N�g���� + �e�s��}�� (�p�[�c�̐�)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		// �q������
		for (size_t j = 0; j < modelObjs_[i].size(); j++)
		{
			// �傫��
			Vector3 scale = Vector3(1.0f, 1.0f, 1.0f);
			scale -= ScaleDifference * static_cast<float>(i);

			// ����
			modelObjs_[i][j].reset(Model::Object::Create({ {}, {}, scale }, spVP_));

			// �e�s��}��
			modelObjs_[i][j]->parent_ = &core_->m_;
		}
	}

	gridModelObjs_.reset(Model::Object::Create(Transform::Status::Default(), spVP_));
	gridModelObjs_->parent_ = &pParent->m_;

	// ���Z�b�g
	Reset(direction, type);
}

void JunctionDrawer::Reset(const Vector3& direction, const Type& type)
{
	// ���Z�b�g
	IDrawer::Reset();

	// �������
	direction_ = direction.Normalized();

	// ���
	type_ = type;

	// �C���f�b�N�X���v�Z
	typeIndex_ = static_cast<size_t>(type);

	// �j�̐F�ƃ}�e���A���ݒ�
	CoreColor::ColorType color = CoreColor::ColorType::eBlue;
	CoreColor::PartsType coreParts = CoreColor::PartsType::eCore;
	CoreColor::PartsType shellParts = CoreColor::PartsType::eShell;
	
	if (type == Type::eGreen)
	{
		color = CoreColor::ColorType::eGreen;
	}
	else if (type == Type::eRed)
	{
		color = CoreColor::ColorType::eRed;
	}

	// �J���[�ƃ}�e���A���ݒ�
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i][CoreIdx]->SetColor(CoreColor::ColorPtr(color, coreParts));
		modelObjs_[i][CoreIdx]->SetMaterial(CoreColor::MaterialPtr(color, coreParts));
		
		modelObjs_[i][ShellIdx]->SetColor(CoreColor::ColorPtr(color, shellParts));
		modelObjs_[i][ShellIdx]->SetMaterial(CoreColor::MaterialPtr(color, shellParts));
	}

	gridModelObjs_->SetColor(CoreColor::ColorPtr(color, shellParts));
	gridModelObjs_->SetMaterial(CoreColor::MaterialPtr(color, shellParts));

	// �p�[�g�i�[����
	pPartner_ = nullptr;


	// ----- �A�j���[�V���� ----- //

	// ����
	isAct_ = true;

	// �A�j���p������
	for (size_t i = 0; i < sFrameNum_; i++)
	{
		animePoss_[i] = animeRotas_[i] = animeScales_[i] = {};
	}

	// �������[�V��������
	isIdle_ = true;

	// �����^�C�}�[������
	for (size_t i = 0; i < idleTimers_.size(); i++)
	{
		idleTimers_[i].Initialize(Idle::Frame);
		idleTimers_[i].SetActive(true);
	}

	// �ڑ����Ȃ�
	isConnected_ = false;

	// �ڑ��^�C�}�[������
	connectTimer_.Initialize(Connect::Frame);

	// �������킹�^�C�}�[������
	alignDirectionTimer_.Initialize(Connect::AlignDirection::Frame);
}

void JunctionDrawer::Update()
{
	//ImGui::Begin("Junction");
	//ImGui::Text("%p", this);
	//ImGui::Text("%p", pParent_);
	//ImGui::Text("%f, %f, %f", direction_.x_, direction_.y_, direction_.z_);
	//ImGui::End();

	// �A�j���[�V�����p
	Vector3 pos{}, rota{}, scale{};

	// �������킹
	rota = YMath::AdjustAngle(direction_);


	// ���N���X�X�V 
	IDrawer::Update({ pos, rota, scale });


	// �A�j���p������
	for (size_t i = 0; i < sFrameNum_; i++)
	{
		animePoss_[i] = animeRotas_[i] = animeScales_[i] = {};
	}

	// �������[�V�����X�V
	UpdateIdleAnimation();

	// �ڑ����[�V�����X�V
	UpdateConnectAnimation();

	gridModelObjs_->UpdateMatrix();

	// �s��X�V (�q)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		// �q������
		for (size_t j = 0; j < modelObjs_[i].size(); j++)
		{
			// ��]�ʒ���
			if (animeRotas_[i].z_ >= +PI * 4) { animeRotas_[i].z_ -= PI * 4; }
			else if (animeRotas_[i].z_ <= -PI * 4) { animeRotas_[i].z_ += PI * 4; }
			
			modelObjs_[i][j]->UpdateMatrix({animePoss_[i], animeRotas_[i], animeScales_[i]});
		}
	}
}

void JunctionDrawer::Draw()
{
	spGridModel_->SetDrawCommand(gridModelObjs_.get(), YGame::DrawLocation::Center);

	// ���f���̐��`��
	for (size_t i = 0; i < spModels_[typeIndex_].size(); i++)
	{
		for (size_t j = 0; j < modelObjs_.size(); j++)
		{
			spModels_[typeIndex_][i]->SetDrawCommand(modelObjs_[j][i].get(), YGame::DrawLocation::Center);
		}
	}
}

void JunctionDrawer::SetPartner(JunctionDrawer* pPartner)
{
	// null�`�F�b�N
	assert(pPartner);
	// ���
	pPartner_ = pPartner;
}

Vector3 JunctionDrawer::GetDirection()
{
	// �����Ԃ�
	return direction_;
}

void JunctionDrawer::AnimateConnection(JunctionDrawer* pPartner)
{
	// �p�[�g�i�[�ݒ�
	SetPartner(pPartner);

	// �����C�[�W���O������
	Vector3 d = -Vector3(pParent_->pos_ - pPartner_->pParent_->pos_);
	alignDirectionEase_.Initialize(direction_, d.Normalized(), Connect::AlignDirection::Exponent);

	// �����^�C�}�[���Z�b�g
	alignDirectionTimer_.Reset(true);

	// �ڑ�����
	isConnected_ = true;

	// �������[�V�������Ȃ�
	isIdle_ = false;

	// �^�C�}�[������
	connectTimer_.Reset(true);
}

void JunctionDrawer::UpdateIdleAnimation()
{
	// �����Ă��Ȃ��Ȃ�e��
	if (isAct_ == false) { return; }

	// �������[�V��������Ȃ��Ȃ�e��
	if (isIdle_ == false) { return; }


	for (size_t i = 0; i < sFrameNum_; i++)
	{
		// �^�C�}�[�X�V
		idleTimers_[i].Update();
		
		// ��]
		animeRotas_[i].z_ += sIdleRotaSpeedEase_.In(idleTimers_[i].Ratio());

		// �^�C�}�[�I�������
		if (idleTimers_[i].IsEnd())
		{
			// �^�C�}�[���Z�b�g
			idleTimers_[i].Reset(true);
		}

		// �Ō�Ȃ�ʂ�Ȃ�
		if (i + 1 == sFrameNum_) { break; }

		// �ڑ���
		if (isConnected_)
		{
			// ����
			bool b = (idleTimers_[i].Ratio() >= 0.25f);
			
			// �����������߂�
			idleTimers_[i + 1].SetActive(b);
		}
	}
}

void JunctionDrawer::UpdateConnectAnimation()
{
	// �����Ă��Ȃ��Ȃ�e��
	if (isAct_ == false) { return; }

	// �����Ă��Ȃ��Ȃ�e��
	if (isConnected_ == false) { return; }


	// �ڑ��^�C�}�[�X�V
	connectTimer_.Update();

	// �x�N�g���̑傫���擾
	float len = Vector3(pParent_->pos_ - pPartner_->pParent_->pos_).Length() / 25.0f;

	// �����C�[�W���O������
	Vector3 d = -Vector3(pParent_->pos_ - pPartner_->pParent_->pos_);
	alignDirectionEase_.SetEnd(d.Normalized());

	// �A�j��
	for (size_t i = 0; i < sFrameNum_; i++)
	{
		// �ʒu�W��
		animePoss_[i].z_ += sConnectPosFactorEase_.Out(connectTimer_.Ratio()) * (len * (i + 1));

		// ��]�W��
		animeRotas_[i].z_ += sConnectRotaFactorEase_.Out(connectTimer_.Ratio()) * i;


		// ��]
		animeRotas_[i].z_ += sConnectRotaSpeedEase_.Out(connectTimer_.Ratio());

		// �傫��
		animeScales_[i] += sConnectScaleEase_.Out(connectTimer_.Ratio()) * sConnectPushScaleFactorEase_.Out(connectTimer_.Ratio());
	}


	// �^�C�}�[�I�������
	if (connectTimer_.IsEnd())
	{
		// ���Z�b�g���ĂȂ��Ȃ�
		if (isIdle_ == false)
		{
			// �����^�C�}�[���Z�b�g
			idleTimers_[0].Reset(true);
			float frame1 = static_cast<float>(Idle::Frame) * 0.75f;
			float frame2 = static_cast<float>(Idle::Frame) * 0.75f * 0.75f;

			idleTimers_[1].Initialize(static_cast<unsigned int>(frame1));
			idleTimers_[2].Initialize(static_cast<unsigned int>(frame2));
		}

		// �������[�V�����J�n
		isIdle_ = true;
	}


	// �������킹�^�C�}�[�X�V
	alignDirectionTimer_.Update();

	// �������킹
	direction_ = alignDirectionEase_.In(alignDirectionTimer_.Ratio());
}

#pragma endregion
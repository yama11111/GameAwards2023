#include "LaserDrawer.h"
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

using namespace DrawerConfig::Laser;

#pragma endregion

#pragma region Static

array<Model*, LaserDrawerCommon::sPartsNum_> LaserDrawerCommon::spModels_ =
{
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
};

Ease<float> LaserDrawerCommon::sIdleBeamRotaEase_;
Ease<float> LaserDrawerCommon::sIdleFannelRotaEase_;
Ease<float> LaserDrawerCommon::sShootFannelHeightEase_;
Ease<float> LaserDrawerCommon::sShootFannelPosFactorEase_;
Ease<float> LaserDrawerCommon::sShootFannelRotaEase_;

#pragma endregion

#pragma region �C���f�b�N�X

static const size_t BaseIdx		 = static_cast<size_t>(LaserDrawerCommon::Parts::eBase); // ���
static const size_t CoreIdx		 = static_cast<size_t>(LaserDrawerCommon::Parts::eCore); // �j
static const size_t Funnel1Idx	 = static_cast<size_t>(LaserDrawerCommon::Parts::eFunnel1); // �t�@���l��1
static const size_t Funnel2Idx	 = static_cast<size_t>(LaserDrawerCommon::Parts::eFunnel2); // �t�@���l��2
static const size_t Funnel3Idx	 = static_cast<size_t>(LaserDrawerCommon::Parts::eFunnel3); // �t�@���l��3
static const size_t Funnel4Idx	 = static_cast<size_t>(LaserDrawerCommon::Parts::eFunnel4); // �t�@���l��4
static const size_t BeamIdx		 = static_cast<size_t>(LaserDrawerCommon::Parts::eBeam); // �r�[��

#pragma endregion

#pragma region Common

void LaserDrawerCommon::StaticInitialize()
{
	// ----- ���f���ǂݍ��� ----- //

	// �ˏo�@
	spModels_[BaseIdx] = Model::LoadObj("laser/base", true); // ���
	spModels_[CoreIdx] = Model::LoadObj("laser/core", true); // �j
	spModels_[Funnel1Idx] = Model::LoadObj("laser/funnel/01", true); // �t�@���l��1
	spModels_[Funnel2Idx] = Model::LoadObj("laser/funnel/02", true); // �t�@���l��2
	spModels_[Funnel3Idx] = Model::LoadObj("laser/funnel/03", true); // �t�@���l��3
	spModels_[Funnel4Idx] = Model::LoadObj("laser/funnel/04", true); // �t�@���l��4
	spModels_[BeamIdx] = Model::CreateCube(); // ���[�U�[


	// ----- ���o ----- //
	
	// �r�[��������]�C�[�W���O������
	sIdleBeamRotaEase_.Initialize(Idle::BeamRota::Start, Idle::BeamRota::End, Idle::BeamRota::Exponent);

	// �t�@���l��������]�C�[�W���O
	sIdleFannelRotaEase_.Initialize(Idle::FannelRota::Start, Idle::FannelRota::End, Idle::FannelRota::Exponent);


	// �t�@���l�����ˍ��x�C�[�W���O
	sShootFannelHeightEase_.Initialize(Shoot::Height::Start, Shoot::Height::End, Shoot::Height::Exponent);

	// �t�@���l�����ˈʒu�W���C�[�W���O
	sShootFannelPosFactorEase_.Initialize(Shoot::PosFactor::Start, Shoot::PosFactor::End, Shoot::PosFactor::Exponent);
	
	// �t�@���l�����ˉ�]�C�[�W���O
	sShootFannelRotaEase_.Initialize(Shoot::Rota::Start, Shoot::Rota::End, Shoot::Rota::Exponent);
}

#pragma endregion

#pragma region Drawer

void LaserDrawer::Initialize(Transform* pParent, float* pLength)
{
	// null�`�F�b�N
	assert(pLength);
	// ���
	pLength_ = pLength;

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

void LaserDrawer::Reset()
{
	// ���Z�b�g
	IDrawer::Reset();

	// �j�̐F�ƃ}�e���A���ݒ�
	CBColor* pColor = nullptr;
	CBMaterial* pMaterial = nullptr;

	pColor = CoreColor::ColorPtr(CoreColor::ColorType::eBlue);
	pMaterial = CoreColor::MaterialPtr();

	modelObjs_[CoreIdx]->SetColor(pColor);
	modelObjs_[CoreIdx]->SetMaterial(pMaterial);
	
	modelObjs_[BeamIdx]->SetColor(pColor);
	modelObjs_[BeamIdx]->SetMaterial(pMaterial);


	// ----- ���o ----- //

	// ������
	isAct_ = true;

	// �A�j���p������
	animeFunnelPoss_[0] = animeFunnelPoss_[1] = animeFunnelPoss_[2] = animeFunnelPoss_[3] = {};
	animeFunnelRota_ = {};
	animeBeamPos_ = animeBeamRota_ = animeBeamSca_ = {};


	// �����Ă��Ȃ�
	isShooted_ = false;

	// �����[�V�����^�C�}�[������
	shootTimer_.Initialize(Shoot::Frame);

	// �r�[�����ˑ傫���C�[�W���O������
	shootBeamScaEase_.Initialize({}, {}, 0.0f);


	// �������[�V��������
	isIdle_ = true;

	// �������[�V�����^�C�}�[������
	idleTimer_.Initialize(Idle::Frame);
	idleTimer_.SetActive(true);


	// ����
	AnimateShoot();
}

void LaserDrawer::Update()
{
	// ���N���X�X�V 
	IDrawer::Update({});
	

	// �A�j���p������
	animeFunnelPoss_[0] = animeFunnelPoss_[1] = animeFunnelPoss_[2] = animeFunnelPoss_[3] = {};
	animeFunnelRota_ = {};
	animeBeamPos_ = animeBeamRota_ = animeBeamSca_ = {};


	// �r�[���ʒu
	animeBeamPos_.y_ = *pLength_ + BeamHeight;

	// �������[�V�����X�V
	UpdateIdleAnimation();

	// ���˃��[�V�����X�V
	UpdateShootAnimation();


	// �s��X�V (�q)
	modelObjs_[BaseIdx]->UpdateMatrix();
	modelObjs_[CoreIdx]->UpdateMatrix();
	modelObjs_[Funnel1Idx]->UpdateMatrix({ animeFunnelPoss_[0], animeFunnelRota_, {} });
	modelObjs_[Funnel2Idx]->UpdateMatrix({ animeFunnelPoss_[1], animeFunnelRota_, {} });
	modelObjs_[Funnel3Idx]->UpdateMatrix({ animeFunnelPoss_[2], animeFunnelRota_, {} });
	modelObjs_[Funnel4Idx]->UpdateMatrix({ animeFunnelPoss_[3], animeFunnelRota_, {} });
	modelObjs_[BeamIdx]->UpdateMatrix({ animeBeamPos_, animeBeamRota_, animeBeamSca_ });
}

void LaserDrawer::Draw()
{
	// ���f���̐��`��
	for (size_t i = 0; i < spModels_.size(); i++)
	{
		spModels_[i]->SetDrawCommand(modelObjs_[i].get(), YGame::DrawLocation::Center);
	}
}

void LaserDrawer::AnimateShoot()
{
	// �傫���C�[�W���O������
	shootBeamScaEase_.Initialize(
		{ Shoot::Scale::Start,*pLength_,Shoot::Scale::Start }, 
		{ Shoot::Scale::End,*pLength_,Shoot::Scale::End },
		Shoot::Scale::Exponent);

	// ���˂���
	isShooted_ = true;

	// �^�C�}�[���Z�b�g + �J�n
	shootTimer_.Reset(true);
}

void LaserDrawer::UpdateIdleAnimation()
{
	// �����Ă��Ȃ��Ȃ�e��
	if (isAct_ == false) { return; }

	// �������[�V��������Ȃ��Ȃ�e��
	if (isIdle_ == false) { return; }


	// �^�C�}�[�X�V
	idleTimer_.Update();
	
	// �r�[����]
	animeBeamRota_.y_ += sIdleBeamRotaEase_.In(idleTimer_.Ratio());
	
	// �t�@���l����]
	animeFunnelRota_.y_ += sIdleFannelRotaEase_.In(idleTimer_.Ratio());

	
	// �^�C�}�[�I�������
	if (idleTimer_.IsEnd())
	{
		// �^�C�}�[���Z�b�g
		idleTimer_.Reset(true);
	}

}

void LaserDrawer::UpdateShootAnimation()
{
	// �����Ă��Ȃ��Ȃ�e��
	if (isAct_ == false) { return; }

	// ���˃A�j���[�V��������Ȃ��Ȃ�e��
	if (isShooted_ == false) { return; }


	// �^�C�}�[�X�V
	shootTimer_.Update();

	// �傫���C�[�W���O������
	shootBeamScaEase_.Initialize(
		{ Shoot::Scale::Start,*pLength_,Shoot::Scale::Start },
		{ Shoot::Scale::End,*pLength_,Shoot::Scale::End },
		Shoot::Scale::Exponent);

	// �傫��
	animeBeamSca_ = shootBeamScaEase_.Out(shootTimer_.Ratio());

	// �ʒu�W��
	float posFactor = sShootFannelPosFactorEase_.Out(shootTimer_.Ratio());

	// ��]��
	float rotaVal = animeFunnelRota_.y_;
	float rotaRange = PI / 2.0f;

	// �t�@���l���̌���
	Vector3 vec0 = Vector3(sinf(rotaVal + (rotaRange * 0.0f)), 0.0f, cosf(rotaVal + (rotaRange * 0.0f))).Normalized();
	Vector3 vec1 = Vector3(sinf(rotaVal + (rotaRange * 1.0f)), 0.0f, cosf(rotaVal + (rotaRange * 1.0f))).Normalized();
	Vector3 vec2 = Vector3(sinf(rotaVal + (rotaRange * 2.0f)), 0.0f, cosf(rotaVal + (rotaRange * 2.0f))).Normalized();
	Vector3 vec3 = Vector3(sinf(rotaVal + (rotaRange * 3.0f)), 0.0f, cosf(rotaVal + (rotaRange * 3.0f))).Normalized();
	
	// ����
	float height = sShootFannelHeightEase_.Out(shootTimer_.Ratio());

	// �t�@���l���̈ʒu
	animeFunnelPoss_[0] = (vec2 * posFactor) + Vector3(0.0f, height, 0.0f);
	animeFunnelPoss_[1] = (vec0 * posFactor) + Vector3(0.0f, height, 0.0f);
	animeFunnelPoss_[2] = (vec1 * posFactor) + Vector3(0.0f, height, 0.0f);
	animeFunnelPoss_[3] = (vec3 * posFactor) + Vector3(0.0f, height, 0.0f);


	// �^�C�}�[���I�������
	if (shootTimer_.IsEnd())
	{

	}
}

#pragma endregion
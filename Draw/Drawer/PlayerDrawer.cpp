#include "PlayerDrawer.h"
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

using namespace DrawerConfig::Player;

#pragma endregion

#pragma region Static

array<Model*, PlayerDrawerCommon::PartsNum_> PlayerDrawerCommon::spModels_ =
{
	nullptr, nullptr
};

#pragma endregion

// �C���f�b�N�X
static const size_t BodyIdx = static_cast<size_t>(PlayerDrawerCommon::Parts::Body); // ��

void PlayerDrawerCommon::StaticInitialize()
{
	// ----- ���f���ǂݍ��� ----- //

	spModels_[BodyIdx] = Model::Load("player", true); // ��
	spModels_[1] = Model::CreateCube();
}


void PlayerDrawer::Initialize(Transform* pParent, Vector3* pDirection)
{
	// null�`�F�b�N
	assert(pDirection);

	// ���N���X������
	IDrawer::Initialze(pParent, Mode::Normal, Idle::IntervalTime);

	// �F����
	color_.reset(Color::Create());

	// �I�u�W�F�N�g���� + �e�s��}�� (�p�[�c�̐�)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		// ����
		modelObjs_[i].reset(ModelObject::Create({}, spVP_, color_.get(), nullptr, spMate_));

		// �e�s����
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// �����|�C���^�}��
	pDirection_ = pDirection;

	// ���Z�b�g
	Reset();
}

void PlayerDrawer::Reset()
{
	// ���Z�b�g
	IDrawer::Reset(Mode::Normal);

	// ���f���p�I�u�W�F�N�g������
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		// ������
		modelObjs_[i]->Initialize({ {}, {}, DefScale });
	}

	// �F������
	color_->SetRGB(DefColor);

	// ----- �A�j���[�V���� ----- //
	
	// ���X�|�[���t���O
	isRespawn_ = false;
	// ���X�|�[���p�^�C�}�[
	respawnTim_.Initialize(Respawn::Frame);
	// ���X�|�[���p�X�P�[���C�[�W���O
	respScaleEas_.Initialize(-1.0f,0.0f,Respawn::Exponent);
	// ���X�|�[���p�A���t�@�l�C�[�W���O
	respAlphaEas_.Initialize(0.0f,1.0f,Respawn::Exponent);
}

void PlayerDrawer::ResetAnimation()
{
	// �u���u���A�j���[�V����������
	SlimeActor::Initialize();

	// �������[�V�����^�C�}�[���Z�b�g
	idleTim_.Reset(true);

	// ���X�|�[���p�^�C�}�[���Z�b�g
	respawnTim_.Reset(false);
}

void PlayerDrawer::Update()
{
	// �A�j���[�V�����p
	Vector3 pos{}, rota{}, scale{};

	// �������킹
	rota = YMath::AdjustAngle(*pDirection_);

	// ���X�|�[�����Ȃ�
	if (isRespawn_)
	{
		// ���X�|�[���p�^�C�}�[�X�V
		respawnTim_.Update();
		// ���X�|�[���p�̃X�P�[���v�Z
		float respSca = respScaleEas_.In(respawnTim_.Ratio());
		
		// ���
		scale = Vector3(respSca, respSca, respSca);

		// ���X�|�[���p�̃A���t�@�l�v�Z
		float respAlpha = respAlphaEas_.In(respawnTim_.Ratio());

		// ���
		color_->SetAlpha(respAlpha);
	}

	// ���N���X�X�V 
	IDrawer::Update({ pos, rota, scale });

	// �s��X�V (�q)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix();
	}
}

void PlayerDrawer::Draw()
{
	//// ���f���̐��`��
	//for (size_t i = 0; i < spModels_.size(); i++)
	//{
	//	spModels_[i]->Draw(modelObjs_[i].get());
	//}
	spModels_[BodyIdx]->Draw(modelObjs_[BodyIdx].get());
}

void PlayerDrawer::JumpAnimation()
{
	// �L�k��
	Vector3 val = core_->scale_ * DrawerConfig::Player::Jump::SlimeAction::Value;
	val.y_ *= -1.0f;

	// �Ԃ���
	Vector3 squash = +val;
	// �̂т��
	Vector3 streach = -val;

	// ���� (�t���[��)
	unsigned int frame = DrawerConfig::Player::Jump::SlimeAction::Frame;
	// �w�� (�ɋ})
	float pow = DrawerConfig::Player::Jump::SlimeAction::Exponent;

	// �Ղ�Ղ�A�j���[�V����
	SlimeActor::Activate(
		{
			{{}, frame, pow},
			{squash, frame, pow},
			{streach, frame, pow},
			{{}, frame, pow },
		}
	);
}
void PlayerDrawer::LandingAnimation()
{
	// �Ԃ���
	Vector3 squash = core_->scale_ * DrawerConfig::Player::Landing::SlimeAction::Value;
	squash.y_ *= -1.0f;

	// ���� (�t���[��)
	unsigned int frame = DrawerConfig::Player::Landing::SlimeAction::Frame;
	// �w�� (�ɋ})
	float exponent = DrawerConfig::Player::Landing::SlimeAction::Exponent;

	// �Ղ�Ղ�A�j���[�V����
	SlimeActor::Activate(
		{
			{{}, frame, exponent},
			{squash, frame, exponent},
			{{}, frame, exponent}
		}
	);
}

void PlayerDrawer::RespawnAnimation()
{
	// �A�j���[�V�������Z�b�g
	ResetAnimation();

	// ���X�|�[���^�C�}�[�J�n
	respawnTim_.SetActive(true);

	// �Ԃ���
	Vector3 squash = core_->scale_ * DrawerConfig::Player::Respawn::SlimeAction::Value;

	// ���� (�t���[��)
	unsigned int frame = DrawerConfig::Player::Respawn::SlimeAction::Frame;
	// �w�� (�ɋ})
	float exponent = DrawerConfig::Player::Respawn::SlimeAction::Exponent;

	// �Ղ�Ղ�A�j���[�V����
	SlimeActor::Activate(
		{
			{{}, frame, exponent},
			{squash, frame, exponent},
			{{}, frame, exponent}
		}
	);

	// ���X�|�[���A�j���[�V�����J�n
	isRespawn_ = true;
}

void PlayerDrawer::IdleAnimation()
{
}

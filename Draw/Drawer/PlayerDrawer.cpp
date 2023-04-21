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
using namespace DrawerConfig::Player;

#pragma endregion

#pragma region Static

// �C���f�b�N�X
static const size_t NormalIdx = static_cast<size_t>(IDrawer::Mode::Normal); // �ʏ�
static const size_t RedIdx = static_cast<size_t>(IDrawer::Mode::Red); // ��
static const size_t InvisibleIdx = static_cast<size_t>(IDrawer::Mode::Invisivle); // ����

static const size_t BodyIdx = static_cast<size_t>(PlayerDrawerCommon::Parts::Body); // ��


// �ÓI ���f���z�� ������
array<Model*, PlayerDrawerCommon::PartsNum_> PlayerDrawerCommon::spModels_ =
{
	nullptr, nullptr
};

// �ÓI�r���[�v���W�F�N�V����
YGame::ViewProjection* PlayerDrawerCommon::spVP_ = nullptr;

void PlayerDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP)
{
	// null�`�F�b�N
	assert(pVP);
	// ���
	spVP_ = pVP;

	// ----- ���f���ǂݍ��� ----- //

	spModels_[BodyIdx] = Model::Load("player", true); // ��
	spModels_[1] = Model::CreateCube();
}

#pragma endregion

void PlayerDrawer::Initialize(YGame::Transform* pParent, Vector3* pDirection, const Mode& mode)
{
	// null�`�F�b�N
	assert(pDirection);

	// ���N���X������
	IDrawer::Initialze(pParent, mode, Idle::IntervalTime);

	// �F����
	colors_[NormalIdx]	 .reset(Color::Create());
	colors_[RedIdx]		 .reset(Color::Create());
	colors_[InvisibleIdx].reset(Color::Create());

	// �I�u�W�F�N�g���� + �e�s��}�� (�p�[�c�̐�)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		for (size_t j = 0; j < modelObjs_[i].size(); j++)
		{
			// ����
			modelObjs_[i][j].reset(ModelObject::Create({}, spVP_, colors_[i].get(), nullptr));
			
			// �e�s����
			modelObjs_[i][j]->parent_ = &core_->m_;
		}
	}

	// �����|�C���^�}��
	pDirection_ = pDirection;

	// ���Z�b�g
	Reset(mode);
}

void PlayerDrawer::Reset(const Mode& mode)
{
	// ���Z�b�g
	IDrawer::Reset(mode);

	// ���f���p�I�u�W�F�N�g������
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		for (size_t j = 0; j < modelObjs_[i].size(); j++)
		{
			// �傫��
			Vector3 scale = DefScale;

			// �����Ȃ�
			if (i == InvisibleIdx)
			{
				// �傫������
				scale *= DrawerConfig::InvisibleScale;
			}

			// ������
			modelObjs_[i][j]->Initialize({ {}, {}, scale });
		}
	}

	// �F������
	colors_[NormalIdx]->Initialize(DefColor::Normal, DefColor::Normal);
	colors_[RedIdx]->Initialize(DefColor::Red, DefColor::Red);
	colors_[InvisibleIdx]->Initialize(DefColor::Invisible);

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
		colors_[NormalIdx]->SetAlpha(respAlpha);
		colors_[RedIdx]->SetAlpha(respAlpha);
		colors_[InvisibleIdx]->SetAlpha(respAlpha);
	}

	// ���N���X�X�V 
	IDrawer::Update({ pos, rota, scale });

	// �s��X�V (�q)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		for (size_t j = 0; j < modelObjs_[i].size(); j++)
		{
			modelObjs_[i][j]->UpdateMatrix();
		}
	}
}

void PlayerDrawer::PreDraw()
{
	// �����`��
	spModels_[BodyIdx]->Draw(modelObjs_[InvisibleIdx][BodyIdx].get());

	// �ʏ�Ȃ�
	if (current_ == Mode::Normal)
	{
		// �`��
		spModels_[BodyIdx]->Draw(modelObjs_[NormalIdx][BodyIdx].get());
	}
}

void PlayerDrawer::PostDraw()
{
	// �ԂȂ�
	if (current_ == Mode::Red)
	{
		// �`��
		spModels_[BodyIdx]->Draw(modelObjs_[RedIdx][BodyIdx].get());
	}
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

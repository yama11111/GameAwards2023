#include "PlayerDrawer.h"
#include "CalcTransform.h"
#include "MathUtillity.h"
#include "DrawerConfig.h"
#include <cassert>

#pragma region ���O���

using std::array;
using std::unique_ptr;

using YGame::Transform;
using YGame::Model;
using YGame::CBColor;

using YGame::SlimeActor;

using YMath::Vector3;
using YMath::Vector4;
using YMath::GetRand;

using namespace DrawerConfig::Player;

#pragma endregion

#pragma region Static

array<Model*, PlayerDrawerCommon::sPartsNum_> PlayerDrawerCommon::spModels_ =
{
	nullptr
};

#pragma endregion

// �C���f�b�N�X
static const size_t BodyIdx = static_cast<size_t>(PlayerDrawerCommon::Parts::eBody); // ��

void PlayerDrawerCommon::StaticInitialize()
{
	// ----- ���f���ǂݍ��� ----- //

	spModels_[BodyIdx] = Model::LoadObj("player", true); // ��
}


void PlayerDrawer::Initialize(Transform* pParent, Vector3* pDirection)
{
	// null�`�F�b�N
	assert(pDirection);

	// ���N���X������
	IDrawer::Initialze(pParent);

	// �F����
	color_.reset(CBColor::Create());
	teleportColor_.reset(CBColor::Create());

	// �I�u�W�F�N�g���� + �e�s��}�� (�p�[�c�̐�)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		// ����
		modelObjs_[i].reset(Model::Object::Create(Transform::Status::Default(), spVP_, color_.get(), spMate_));

		// �e�s����
		modelObjs_[i]->parent_ = &core_->m_;
	}
	for (size_t i = 0; i < teleportModelObjs_.size(); i++)
	{
		// ����
		teleportModelObjs_[i].reset(Model::Object::Create(
			{ pParent_->pos_, pParent_->rota_, pParent_->scale_ },
			spVP_, teleportColor_.get(), spMate_));
	}

	// �����|�C���^�}��
	pDirection_ = pDirection;

	// ���Z�b�g
	Reset();
}

void PlayerDrawer::Reset()
{
	// ���Z�b�g
	IDrawer::Reset();

	// ���f���p�I�u�W�F�N�g������
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		// ������
		modelObjs_[i]->Initialize({ {}, {}, DefScale });
	}

	// �F������
	color_->SetRGB(DefColor);
	teleportColor_->SetRGB(DefColor);

	// ----- �A�j���[�V���� ----- //
	
	// �ړ�����
	isMove_ = false;
	// �ړ����Ă�����
	isElderMove_ = false;
	// �ړ��p��]�p���[
	moveRotaPow_.Initialize(Move::Rota::Frame);
	// �ړ��p��]�C�[�W���O
	moveRotaEas_.Initialize(0.0f, Move::Rota::Value, Move::Rota::Exponent);
	// �ړ��p�G�~�b�g�^�C�}�[
	moveEmitTimer_.Initialize(Move::Smoke::IntervalFrame);

	// �e���|�[�g�t���O
	isTeleport_ = false;
	// �e���|�[�g�p�^�C�}�[
	teleportTim_.Initialize(5);
	// �e���|�[�g�p�X�P�[���C�[�W���O
	teleportScaleEas_.Initialize(0.0f, -1.0f, Respawn::Exponent);
	// �e���|�[�g�p�A���t�@�l�C�[�W���O
	teleportAlphaEas_.Initialize(0.5f, 0.0f, Respawn::Exponent);

	// ���X�|�[���t���O
	isRespawn_ = false;
	// ���X�|�[���p�^�C�}�[
	respawnTim_.Initialize(Respawn::Frame);
	// ���X�|�[���p�X�P�[���C�[�W���O
	respScaleEas_.Initialize(-0.25f, 0.0f, Respawn::Exponent);
	// ���X�|�[���p�A���t�@�l�C�[�W���O
	respAlphaEas_.Initialize(0.0f, 1.0f, Respawn::Exponent);

	// �S�[���t���O
	isGoal_ = false;
	// �S�[���p�^�C�}�[
	goalTim_.Initialize(Respawn::Frame);
	// �S�[���p�X�P�[���C�[�W���O
	goalScaleEas_.Initialize(0.0f, -1.0f, Respawn::Exponent);
	// �S�[���p�A���t�@�l�C�[�W���O
	goalAlphaEas_.Initialize(1.0f, 0.0f, Respawn::Exponent);;
}

void PlayerDrawer::ResetAnimation()
{
	// �u���u���A�j���[�V����������
	SlimeActor::Initialize();

	// �ړ��^�C�}�[���Z�b�g
	moveEmitTimer_.Reset(false);

	// �e���|�[�g�p�^�C�}�[���Z�b�g
	teleportTim_.Reset(false);

	// ���X�|�[���p�^�C�}�[���Z�b�g
	respawnTim_.Reset(false);

	// �S�[���p�^�C�}�[���Z�b�g
	goalTim_.Reset(false);
}

void PlayerDrawer::Update()
{
	// �A�j���[�V�����p
	Vector3 pos{}, rota{}, scale{};
	// �������킹
	rota = YMath::AdjustAngle(*pDirection_);

	// ���N���X�X�V 
	IDrawer::Update({ pos, rota, scale });

	// �A�j���[�V�����p
	animePos = animeRota = animeScale = {};
	teleportAnimePos = teleportAnimeRota = teleportAnimeScale = {};	

	UpdateMoveAnimation();
	UpdateTeleportAnimation();
	UpdateDeadAnimation();
	UpdateRespawnAnimation();
	UpdateGoalAnimation();

	// �s��X�V (�q)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix({ animePos, animeRota, animeScale });
	}
	for (size_t i = 0; i < teleportModelObjs_.size(); i++)
	{
		teleportModelObjs_[i]->UpdateMatrix({ teleportAnimePos, teleportAnimeRota, teleportAnimeScale });
	}
}

void PlayerDrawer::Draw()
{
	// ���f���̐��`��
	for (size_t i = 0; i < spModels_.size(); i++)
	{
		spModels_[i]->SetDrawCommand(modelObjs_[i].get(), YGame::DrawLocation::Center);
		if (isTeleport_)
		{
			spModels_[i]->SetDrawCommand(teleportModelObjs_[i].get(), YGame::DrawLocation::Center);
		}
	}
}

void PlayerDrawer::UpdateSmokeEmitter()
{
	// �ړ����Ȃ�
	if (isMove_)
	{
		// �O��ړ����Ă��Ȃ�������
		if (isElderMove_ == false)
		{
			// �G�~�b�g�^�C�}�[���Z�b�g
			moveEmitTimer_.Reset(true);
		}

		// �G�~�b�g�^�C�}�[�X�V
		moveEmitTimer_.Update();

		// �^�C�}�[�I��������
		if (moveEmitTimer_.IsEnd())
		{
			// �G�~�b�g�^�C�}�[���Z�b�g
			moveEmitTimer_.Reset(true);

			// ����
			float dire = 0.0f;

			// �E�����Ȃ�
			if (pDirection_->x_ > 0)
			{
				// �}�C�i�X
				dire = -1.0f;
			}
			// �������Ȃ�
			else if (pDirection_->x_ < 0)
			{
				// �v���X
				dire = +1.0f;
			}

			// ������
			size_t emitNum = GetRand(Move::Smoke::MinNum, Move::Smoke::MaxNum);
			
			
			// �ŏ��ړ��X�s�[�h
			Vector3 minMoveSpeed = Move::Smoke::MinMoveSpeed;
			minMoveSpeed.x_ *= dire;
			
			// �ő�ړ��X�s�[�h
			Vector3 maxMoveSpeed = Move::Smoke::MaxMoveSpeed;
			maxMoveSpeed.x_ *= dire;

			// �ŏ��l���ő�l�𒴂�����
			if (maxMoveSpeed.x_ < minMoveSpeed.x_)
			{
				// ����ւ���
				float sp = maxMoveSpeed.x_;
				maxMoveSpeed.x_ = minMoveSpeed.x_;
				minMoveSpeed.x_ = sp;
			}

			// ������
			spParticleMan_->EmitSmoke(
				emitNum,
				Move::Smoke::AliveFrame,
				pParent_->pos_, Move::Smoke::Range,
				Move::Smoke::MinScaleSize, Move::Smoke::MaxScaleSize,
				minMoveSpeed, maxMoveSpeed,
				Move::Smoke::MinRotaSpeed, Move::Smoke::MaxRotaSpeed,
				Move::Smoke::Color,
				Move::Smoke::Place,
				YGame::DrawLocation::Center);
		}
	}
}

void PlayerDrawer::AnimateJump()
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
void PlayerDrawer::AnimateLanding()
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

void PlayerDrawer::AnimateTeleport()
{
	// �^�C�}�[���Z�b�g + �J�n
	teleportTim_.Reset(true);

	for (size_t i = 0; i < teleportModelObjs_.size(); i++)
	{
		// ������
		teleportModelObjs_[i]->Initialize({ pParent_->pos_, pParent_->rota_, pParent_->scale_ });
	}

	// �e���|�[�g
	isTeleport_ = true;
}

void PlayerDrawer::AnimateDead()
{
	// �J�����u��
	spCamera_->Shaking(0.5f, 0.1f, 100.0f);
}

void PlayerDrawer::AnimateRespawn()
{
	// �A�j���[�V�������Z�b�g
	ResetAnimation();

	// ���X�|�[���^�C�}�[�J�n
	respawnTim_.SetActive(true);

	// ���X�|�[���A�j���[�V�����J�n
	isRespawn_ = true;
}

void PlayerDrawer::AnimateGoal()
{
	// �A�j���[�V�������Z�b�g
	ResetAnimation();

	// �S�[���^�C�}�[�J�n
	goalTim_.SetActive(true);

	// �S�[���A�j���[�V�����J�n
	isGoal_ = true;
}


void PlayerDrawer::UpdateMoveAnimation()
{
	// ������
	UpdateSmokeEmitter();

	// ��]�p���[�X�V
	moveRotaPow_.Update(isMove_);

	// ��]�ۑ��p
	float moveRota = 0.0f;

	// �ړ����Ȃ�
	if (isMove_)
	{
		// �C�[�Y�C��
		moveRota += moveRotaEas_.In(moveRotaPow_.Ratio());
	}
	// ����ȊO�Ȃ�
	else
	{
		// �C�[�Y�A�E�g
		moveRota += moveRotaEas_.Out(moveRotaPow_.Ratio());
	}

	// ��]
	animeRota.x_ = moveRota;

	// �ړ��t���O�ۑ�
	isElderMove_ = isMove_;
}

void PlayerDrawer::UpdateTeleportAnimation()
{
	if (isTeleport_ == false) { return; }

	// �e���|�[�g�p�^�C�}�[�X�V
	teleportTim_.Update();
	// �e���|�[�g�p�̃X�P�[���v�Z
	float teleportSca = teleportScaleEas_.In(teleportTim_.Ratio());

	// ���
	teleportAnimeScale += Vector3(teleportSca, teleportSca, teleportSca);

	// �e���|�[�g�p�̃A���t�@�l�v�Z
	float teleportAlpha = teleportAlphaEas_.In(teleportTim_.Ratio());

	// ���
	teleportColor_->SetAlpha(teleportAlpha);

	if (teleportTim_.IsEnd())
	{
		isTeleport_ = false;
	}
}

void PlayerDrawer::UpdateDeadAnimation()
{
	if (isDead_ == false) { return; }
}

void PlayerDrawer::UpdateRespawnAnimation()
{
	if (isRespawn_ == false) { return; }
	
	// ���X�|�[���p�^�C�}�[�X�V
	respawnTim_.Update();
	// ���X�|�[���p�̃X�P�[���v�Z
	float respSca = respScaleEas_.In(respawnTim_.Ratio());

	// ���
	animeScale += Vector3(respSca, respSca, respSca);

	// ���X�|�[���p�̃A���t�@�l�v�Z
	float respAlpha = respAlphaEas_.In(respawnTim_.Ratio());

	// ���
	color_->SetAlpha(respAlpha);

	if (respawnTim_.IsEnd())
	{
		isRespawn_ = false;
	}
}

void PlayerDrawer::UpdateGoalAnimation()
{
	if (isGoal_ == false) { return; }

	// ���X�|�[���p�^�C�}�[�X�V
	goalTim_.Update();
	// ���X�|�[���p�̃X�P�[���v�Z
	float goalSca = goalScaleEas_.In(goalTim_.Ratio());

	// ���
	animeScale += Vector3(goalSca, goalSca, goalSca);

	// ���X�|�[���p�̃A���t�@�l�v�Z
	float goalAlpha = goalAlphaEas_.In(goalTim_.Ratio());

	// ���
	color_->SetAlpha(goalAlpha);
}
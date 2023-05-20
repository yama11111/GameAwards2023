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
	nullptr, nullptr
};

#pragma endregion

// �C���f�b�N�X
static const size_t BodyIdx = static_cast<size_t>(PlayerDrawerCommon::Parts::Body); // ��

void PlayerDrawerCommon::StaticInitialize()
{
	// ----- ���f���ǂݍ��� ----- //

	spModels_[BodyIdx] = Model::LoadObj("player", true); // ��
	spModels_[1] = Model::CreateCube();
}


void PlayerDrawer::Initialize(Transform* pParent, Vector3* pDirection)
{
	// null�`�F�b�N
	assert(pDirection);

	// ���N���X������
	IDrawer::Initialze(pParent);

	// �F����
	color_.reset(CBColor::Create());

	// �I�u�W�F�N�g���� + �e�s��}�� (�p�[�c�̐�)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		// ����
		modelObjs_[i].reset(Model::Object::Create(Transform::Status::Default(), spVP_, color_.get(), spMate_));

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
	IDrawer::Reset();

	// ���f���p�I�u�W�F�N�g������
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		// ������
		modelObjs_[i]->Initialize({ {}, {}, DefScale });
	}

	// �F������
	color_->SetRGB(DefColor);

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

	// ���X�|�[���t���O
	isRespawn_ = false;
	// ���X�|�[���p�^�C�}�[
	respawnTim_.Initialize(Respawn::Frame);
	// ���X�|�[���p�X�P�[���C�[�W���O
	respScaleEas_.Initialize(-1.0f, 0.0f, Respawn::Exponent);
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
	rota.x_ = moveRota;
	
	// �ړ��t���O�ۑ�
	isElderMove_ = isMove_;


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
	// �S�[�����Ȃ�
	if (isGoal_)
	{
		// ���X�|�[���p�^�C�}�[�X�V
		goalTim_.Update();
		// ���X�|�[���p�̃X�P�[���v�Z
		float goalSca = goalScaleEas_.In(goalTim_.Ratio());

		// ���
		scale = Vector3(goalSca, goalSca, goalSca);

		// ���X�|�[���p�̃A���t�@�l�v�Z
		float goalAlpha = goalAlphaEas_.In(goalTim_.Ratio());

		// ���
		color_->SetAlpha(goalAlpha);
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
	spModels_[BodyIdx]->SetDrawCommand(modelObjs_[BodyIdx].get(), YGame::DrawLocation::Center);
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

void PlayerDrawer::GoalAnimation()
{
	// �A�j���[�V�������Z�b�g
	ResetAnimation();

	// �S�[���^�C�}�[�J�n
	goalTim_.SetActive(true);

	// �S�[���A�j���[�V�����J�n
	isGoal_ = true;
}
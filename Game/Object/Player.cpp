#include "Player.h"
#include "MathUtillity.h"
#include "Keys.h"
#include <cassert>
#include <cmath>
#include <imgui.h>

#include "Stage.h"
#include "LevelData.h"

#include "PilotManager.h"
#include "TransitionManager.h"

using YGame::Transform;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Clamp;

YInput::Keys* Player::spKeys_ = nullptr;

void Player::StaticInitialize()
{
	// �L�[�C���X�^���X�擾
	spKeys_ = YInput::Keys::GetInstance();
}

void Player::Initialize(const size_t signIndex, const YMath::Vector3& pos, const bool isExistKey)
{
	// �g�����X�t�H�[������
	transform_.reset(new Transform());

	// �`��N���X������
	drawer_.Initialize(transform_.get(), &direction_);

	// ���Z�b�g
	Reset(signIndex, pos, isExistKey);
}

void Player::Reset(const size_t signIndex, const YMath::Vector3& pos, const bool isExistKey)
{
	// �g�����X�t�H�[��������
	transform_->Initialize({ pos + spStageMan_->GetTopLeftPos(signIndex), {}, {1.0f,1.0f,1.0f} });

	// �O�񍶏�ʒu������
	elderLeftTop_ = spStageMan_->GetTopLeftPos(signIndex);

	// �X�s�[�h������
	speed_ = {};
	
	// ���� (�E)
	direction_ = Vector3(+1, 0, 0);

	// �W�����v�J�E���g���Z�b�g
	jumpCount_ = 0;


	// �R���C�_�[�ʒu������
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });

	// �R���C�_�[�T�C�Y������
	Box2D::SetBox2DRadSize({ LevelData::Player::CollRadSize });

	// �R���C�_�[�^�C�v�ݒ�
	ObjectCollider::SetColliderType(ObjectCollider::Type::ePlayer);

	// �R���C�_�[�Ŕԍ��ݒ�
	ObjectCollider::SetSignIndex(signIndex);


	// �}�b�v�`�b�v�R���C�_�[������
	YukiMapchipCollider::Initialize();
	trfm_ = *transform_;
	radius_ = { LevelData::Player::CollRadSize.x_, LevelData::Player::CollRadSize.y_, 0.0f };
	idxSign_ = signIndex;
	YukiMapchipCollider::UpdatePos();
	

	// �����Ă���
	isAlive_ = true;

	// �����t���O������������
	isGetOffAct_ = false;

	// �����t���O�^�C�}�[
	isGetOffTimer_.Initialize(5);
	isGetOffTimer_.SetActive(false);


	// ���������Ă��邩
	isKeyHolder_ = !isExistKey;

	// �N���A��
	isGameClear_ = false;


	// �`��N���X���Z�b�g
	drawer_.Reset();

	drawer_.AnimateRespawn();
}

void Player::Move()
{
	if (PilotManager::StaticGetIsActInit()) { return; }

	// �S�[��������͖���
	if (isGameClear_) { return; }

	// x���ړ�
	speed_.x_ += spKeys_->Horizontal() * LevelData::Player::Acceleration;

	// �ۑ��p�t���O
	bool isMove = false;

	// �ړ����Ă���Ȃ�
	if (spKeys_->Horizontal() != 0)
	{
		// �t���O��true��
		isMove = true;

		// �����ύX
		if (speed_.x_ > 0) { direction_.x_ = +1.0f; }
		if (speed_.x_ < 0) { direction_.x_ = -1.0f; }
	}

	// �ړ��A�j���[�V����
	drawer_.SetActMoveAnimation(isMove);
}

void Player::Jump()
{
	if (PilotManager::StaticGetIsActInit()) { return; }

	// �S�[��������͖���
	if (isGameClear_) { return; }

	// �W�����v�񐔂��ő�Ȃ�e��
	if (1 <= jumpCount_) { return; }

	// ����A�N�V�������Ȃ�e��
	if (spKeys_->IsDown(DIK_E)) { return; }

	// SPACE�L�[��������
	if (spKeys_->IsTrigger(DIK_SPACE) || spKeys_->IsTrigger(DIK_W))
	{
		// �W�����v
		speed_.y_ = LevelData::Player::JumpPower;

		// �W�����v�A�j���[�V����
		drawer_.AnimateJump();

		// �W�����v�J�E���g
		jumpCount_++;
	}
}

void Player::Landing()
{
	// �d�͂��Ȃ���
	speed_.y_ = 0.0f;

	// �W�����v�J�E���g���Z�b�g
	jumpCount_ = 0;

	// ���n�����u�ԂȂ�
	if (IsLandingMoment() || (isGrounded_ && isOldGrounded_ == false) && 
		spStageMan_->isHoldSignVector_[idxSign_] == false)
	{
		// ���n�A�j���[�V����
		drawer_.AnimateLanding();
	}
}

void Player::UpdatePhysics()
{
	if (PilotManager::StaticGetCurrentPilot() != PilotManager::PilotType::ePlayer) { return; }
	
	// �����Ă���e��
	if (spStageMan_->isHoldSignVector_[idxSign_]) { return; }

	// �ړ�
	Move();

	// �W�����v
	Jump();

	// ���C��
	if (speed_.x_ > 0.0f)
	{
		speed_.x_ -= LevelData::Player::Friction;
		speed_.x_ = (std::max)(0.0f, speed_.x_);
	}
	if (speed_.x_ < 0.0f)
	{
		speed_.x_ += LevelData::Player::Friction;
		speed_.x_ = (std::min)(0.0f, speed_.x_);
	}

	// �d��
	speed_.y_ -= LevelData::Player::Gravity;

	// �N�����v
	speed_.x_ = Clamp(speed_.x_, -LevelData::Player::MaxSpeed.x_, +LevelData::Player::MaxSpeed.x_);
	speed_.y_ = Clamp(speed_.y_, -LevelData::Player::MaxGravity, +LevelData::Player::MaxSpeed.y_);
}

Vector3& Player::PosRef()
{
	return transform_->pos_;
}

Vector3& Player::SpeedRef()
{
	return speed_;
}

Vector3* Player::PosPointer()
{
	return &transform_->pos_;
}

void Player::OnCollision(ObjectCollider* pPair)
{
	// �Q�[���N���A���e��
	if (isGameClear_) { return; }

	// �����Ă���e��
	if (spStageMan_->isHoldSignVector_[idxSign_]) { return; }

	// �u���b�N�Ȃ�
	if (pPair->GetColliderType() == ObjectCollider::Type::eBlock)
	{
		// E �ŃA�N�V����
		pPair->SetIsActSkill(spKeys_->IsDown(DIK_E));
	}
	// ���[�U�[�Ȃ�
	else if (pPair->GetColliderType() == ObjectCollider::Type::eLaser)
	{
		if (isAlive_ == false) { return; }

		// ����
		isAlive_ = false;
		
		// �A�j���[�V����
		drawer_.AnimateDead();
	}
	// �X�C�b�`�Ȃ�
	else if (pPair->GetColliderType() == ObjectCollider::Type::eSwitch)
	{
		// E �ŃA�N�V����
		if (spKeys_->IsTrigger(DIK_E))
		{
			pPair->SetIsActSkill(true);
		}
	}
	// ���Ȃ�
	else if (pPair->GetColliderType() == ObjectCollider::Type::eKey)
	{
		// ������������
		isKeyHolder_ = true;
	}
	// �S�[���Ȃ�
	else if (pPair->GetColliderType() == ObjectCollider::Type::eGoal)
	{
		// �������ĂȂ��Ȃ�
		if (isKeyHolder_ == false) { return; }

		pPair->SetIsActSkill(true);

		// �S�[��
		drawer_.AnimateGoal();

		// �Q�[���N���A
		isGameClear_ = true;
	}
}

void Player::Draw()
{
	// �`��
	drawer_.Draw();
}

void Player::DrawDebug(void)
{
    //ImGui::Begin("p");
    //ImGui::Text("trfm:%f,%f,%f", trfm_.pos_.x_, trfm_.pos_.y_, trfm_.pos_.z_);
    //ImGui::Text("speed:%f,%f,%f", speed_.x_, speed_.y_, speed_.z_);
    //ImGui::End();
}

void Player::Update()
{
	// ���
	trfm_.pos_ = transform_->pos_;
	velocity_ = speed_;
	
	// ����
	spStageMan_->CallPPC(this);
	if (isTeleport_)
	{
		isTeleport_ = false;
		isGrounded_ = false;
		trfm_.pos_ = { roundToDecimal(teleportedPos_.x_, decimalPlace_),roundToDecimal(teleportedPos_.y_,  decimalPlace_),roundToDecimal(teleportedPos_.z_,  decimalPlace_) };
		idxSign_ = teleportedIdxSign_;

		// �ŔC���f�b�N�X�X�V
		SetSignIndex(idxSign_);
		elderLeftTop_ = spStageMan_->GetTopLeftPos(GetSignIndex());

		// �e���|�[�g�A�j���[�V����
		drawer_.AnimateTeleport();

		PilotManager::StaticSetFollowStage(idxSign_);
	}
	
	// �߂�
	transform_->pos_ = trfm_.pos_;
	speed_ = velocity_;
}

void Player::PreUpdate()
{
	// ���W�X�V
	YukiMapchipCollider::UpdatePos();
    DrawDebug();
	
	// �ŔC���f�b�N�X�X�V
	SetSignIndex(idxSign_);

	// ����X�V
	UpdateLeftTop();

	// ���������X�V
	UpdatePhysics();
	

	// ������ ���� �^�C�}�[�I���܂ō~���
	if (spKeys_->IsUnder())
	{
		isGetOffAct_ = true;
		isGetOffTimer_.Reset(true);
	}
	isGetOffTimer_.Update();
	if (isGetOffTimer_.IsEnd())
	{
		isGetOffAct_ = false;
	}

	// �~��邩
	SetIsGetOff(isGetOffAct_);

	// �����Ă���e��
	if (spStageMan_->isHoldSignVector_[idxSign_] == false)
	{
		// ���n�t���O������
		ResetIsLanding();
	}

	// �}�b�v�`�b�v�R���C�_�[�X�V
	Update();
	
	
	// �R���C�_�[�ʒu�X�V
	Box2D::SetBox2DCenter({ transform_->pos_.x_, transform_->pos_.y_ });
}

void Player::PostUpdate()
{
	// ���n��
	if (IsLanding() || isGrounded_)
	{
		// ���n
 		Landing();
	}

	// �����Ă���e��
	if (spStageMan_->isHoldSignVector_[idxSign_] == false && 
		PilotManager::StaticGetCurrentPilot() == PilotManager::PilotType::ePlayer)
	{
		// �ړ�
		transform_->pos_ += speed_;
	}

	// �g�����X�t�H�[���s��X�V
	transform_->UpdateMatrix();

	// �`��N���X�X�V
	drawer_.Update();
}


#include "DemoScene.h"
#include "SceneExecutive.h"
#include "DrawerHelper.h"
#include "StageConfig.h"
#include "Def.h"

#include "MouseCollider.h"
#include "LevelData.h"

#pragma region ���O��Ԑ錾

using YScene::DemoScene;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;

#pragma endregion 


#pragma region Static�֘A

#pragma endregion 


#pragma region �ǂݍ���

void DemoScene::Load()
{
	// ----- �I�[�f�B�I ----- //

	// �v���CBGM
	pPlayBGM_ = Audio::Load("BGM/select.wav");
	
	// ----- �ÓI������ ----- //

	// �}�E�X�R���C�_�[�ÓI������
	MouseColliderCommon::StaticInitialize();

	// �}�E�X�R���C�_�[�Ƀr���[�v���W�F�N�V�����ݒ�
	MouseColliderCommon::StaticSetViewProjectionPointer(&transferVP_);

	// �p�[�e�B�N��
	ParticleManager::StaticInitialize(&transferVP_);

	// �`��N���X�S��
	DrawerHelper::StaticInitialize(&transferVP_, &camera_, &particleMan_);

	// �v���C���[
	Player::StaticInitialize();
}

#pragma endregion


#pragma region ������

void DemoScene::Initialize()
{
	// �p�[�e�B�N��������
	particleMan_.Initialize();

	// �I�u�W�F�N�g�}�l�[�W���[������
	objMan_.Initialize();


	// �X�e�[�W�ԍ�
	uint32_t stageIdx = static_cast<uint32_t>(StageConfig::GetInstance()->GetCurrentStageIndex() - 1);


	// �v���C���[
	{
		// �v���C���[����
		player_ = std::make_unique<Player>();

		// �v���C���[������
		player_->Initialize(
			LevelData::Player::InitStatuses[stageIdx].signIndex_,
			{
				LevelData::Player::InitStatuses[stageIdx].pos_.x_,
				LevelData::Player::InitStatuses[stageIdx].pos_.y_,
				0.0f
			});

		// �}��
		objMan_.PushBack(player_.get());
	}

	// �u���b�N
	{
		for (size_t i = 0; i < LevelData::Block::InitStatuses[stageIdx].size(); i++)
		{
			// �C���X�^���X����
			std::unique_ptr<Block> newBlock = std::make_unique<Block>();

			// ������
			newBlock->Initialize(
				LevelData::Block::InitStatuses[stageIdx][i].signIndex_,
				{
					LevelData::Block::InitStatuses[stageIdx][i].pos_.x_,
					LevelData::Block::InitStatuses[stageIdx][i].pos_.y_,
					0.0f,
				});

			// �}��
			objMan_.PushBack(newBlock.get());

			// �}��
			blocks_.push_back(std::move(newBlock));
		}
	}

	// �΂�
	{
		for (size_t i = 0; i < LevelData::Spring::InitStatuses[stageIdx].size(); i++)
		{
			// �C���X�^���X����
			std::unique_ptr<Spring> newSpring = std::make_unique<Spring>();

			// ������
			newSpring->Initialize(
				LevelData::Spring::InitStatuses[stageIdx][i].signIndex_,
				{
					LevelData::Spring::InitStatuses[stageIdx][i].pos_.x_,
					LevelData::Spring::InitStatuses[stageIdx][i].pos_.y_,
					0.0f,
				});

			// �}��
			objMan_.PushBack(newSpring.get());

			// �}��
			springs_.push_back(std::move(newSpring));
		}
	}

	// ����
	{
		for (size_t i = 0; i < LevelData::Platform::InitStatuses[stageIdx].size(); i++)
		{
			// �C���X�^���X����
			std::unique_ptr<Platform> newPlatform = std::make_unique<Platform>();

			// ������
			newPlatform->Initialize(
				LevelData::Platform::InitStatuses[stageIdx][i].signIndex_,
				{
					LevelData::Platform::InitStatuses[stageIdx][i].pos_.x_,
					LevelData::Platform::InitStatuses[stageIdx][i].pos_.y_,
					0.0f,
				},
				LevelData::Platform::InitStatuses[stageIdx][i].length_);

			// �}��
			objMan_.PushBack(newPlatform.get());

			// �}��
			platforms_.push_back(std::move(newPlatform));
		}
	}

	// ���[�U�[
	{
		for (size_t i = 0; i < LevelData::Laser::InitStatuses[stageIdx].size(); i++)
		{
			// �C���X�^���X����
			std::unique_ptr<Laser> newLaser = std::make_unique<Laser>();

			// ������
			newLaser->Initialize(
				LevelData::Laser::InitStatuses[stageIdx][i].signIndex_,
				{
					LevelData::Laser::InitStatuses[stageIdx][i].pos_.x_,
					LevelData::Laser::InitStatuses[stageIdx][i].pos_.y_,
					0.0f,
				},
				{
					LevelData::Laser::InitStatuses[stageIdx][i].direction_.x_,
					LevelData::Laser::InitStatuses[stageIdx][i].direction_.y_,
					0.0f,
				});

			// �}��
			objMan_.PushBack(newLaser.get());

			// �}��
			lasers_.push_back(std::move(newLaser));
		}
	}

	// �X�C�b�`
	{
		for (size_t i = 0; i < LevelData::Switch::InitStatuses[stageIdx].size(); i++)
		{
			// �C���X�^���X����
			std::unique_ptr<Switch> newSwitch = std::make_unique<Switch>();

			// ������
			newSwitch->Initialize(
				LevelData::Switch::InitStatuses[stageIdx][i].signIndex_,
				{
					LevelData::Switch::InitStatuses[stageIdx][i].pos_.x_,
					LevelData::Switch::InitStatuses[stageIdx][i].pos_.y_,
					0.0f,
				},
				LevelData::Switch::InitStatuses[stageIdx][i].isAct_);

			// �}��
			objMan_.PushBack(newSwitch.get());

			// �}��
			switches_.push_back(std::move(newSwitch));
		}
	}

	// ��
	{
		// �C���X�^���X����
		key_ = std::make_unique<Key>();

		// ������
		key_->Initialize(
			LevelData::Key::InitStatuses[stageIdx].signIndex_,
			{
				LevelData::Key::InitStatuses[stageIdx].pos_.x_,
				LevelData::Key::InitStatuses[stageIdx].pos_.y_,
				0.0f,
			});

		// �}��
		objMan_.PushBack(key_.get());
	}

	// �S�[��
	{
		// �S�[������
		goal_ = std::make_unique<Goal>();

		// �S�[��������
		goal_->Initialize(
			LevelData::Goal::InitStatuses[stageIdx].signIndex_,
			{
				LevelData::Goal::InitStatuses[stageIdx].pos_.x_,
				LevelData::Goal::InitStatuses[stageIdx].pos_.y_,
				0.0f
			},
			LevelData::Goal::InitStatuses[stageIdx].isRock_);

		// �}��
		objMan_.PushBack(goal_.get());
	}


	// �w�i������
	background_.Initialize();

	// HUD������
	hud_.Initialize();

	
	// �J����
	camera_.Initialize({ 0.0f,0.0f,-50.0f }, {});

	// �r���[�v���W�F�N�V����������
	transferVP_.Initialize();

	// �r���[�v���W�F�N�V�����ɃJ�������
	transferVP_ = camera_.GetViewProjection();


	// �v���CBGM�J�n
	//pPlayBGM_->Play(true);
}

#pragma endregion


#pragma region �I������

void DemoScene::Finalize()
{
	// �v���CBGM��~
	pPlayBGM_->Stop();
}

#pragma endregion


#pragma region �X�V

void DemoScene::Update()
{
	// �}�E�X�R���C�_�[�ÓI�X�V
	MouseColliderCommon::StaticUpdate();

	// HUD�X�V
	hud_.Update();

	// �|�[�Y���Ȃ�e��
	if (hud_.IsElderPause()) { return; }


	// �I�u�W�F�N�g�}�l�[�W���[�X�V
	objMan_.Update();


	// �w�i�X�V
	background_.Update();

	// DrawerHelper�X�V
	DrawerHelper::StaticUpdate();


	// �p�[�e�B�N���X�V
	particleMan_.Update();


	// �J�����X�V
	camera_.Update();

	// �r���[�v���W�F�N�V�����ɃJ�������
	transferVP_ = camera_.GetViewProjection();

	// �r���[�v���W�F�N�V����
	transferVP_.UpdateMatrix();


	//�S�[������
	//if ()
	//{
	//	StageConfig::GetInstance()->ClearStage(StageConfig::GetInstance()->GetCurrentStageIndex() - 1);
	//	SceneExecutive::GetInstance()->Change("SELECT", "INFECTION", 5, 10);
	//}


	// ���Z�b�g
	if (sKeys_->IsTrigger(DIK_R))
	{
		SceneManager::GetInstance()->Change("DEMO");
	}
}

#pragma endregion


#pragma region �`��

void DemoScene::Draw()
{
	// �w�i�`��
	background_.Draw();

	// �I�u�W�F�N�g�`��
	objMan_.Draw();

	// HUD�`��
	hud_.Draw();

	// �p�[�e�B�N���`��
	particleMan_.Draw();

}
#pragma endregion
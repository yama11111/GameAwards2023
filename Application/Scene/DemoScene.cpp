#include "DemoScene.h"
#include "SceneExecutive.h"
#include "DrawerHelper.h"
#include "StageConfig.h"
#include "Def.h"

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
	pPlayBGM_ = Audio::Load("vigilante.wav");
	
	// ----- �ÓI������ ----- //

	// �p�[�e�B�N��
	ParticleManager::StaticInitialize(&transferVP_);

	// �`��N���X�S��
	DrawerHelper::StaticInitialize(&transferVP_, &camera_, &particleMan_);

	// �v���C���[
	DemoPlayer::StaticInitialize();

	// �}�b�v�`�b�v
	mapChipMan_.Load();

	fontSpr_ = Sprite2D::Create({}, { Texture::Load("Goal/stageClear.png") });
}

#pragma endregion


#pragma region ������

void DemoScene::Initialize()
{
	// �p�[�e�B�N��������
	particleMan_.Initialize();


	// �X�e�[�W�ԍ�
	uint32_t stageIdx = static_cast<uint32_t>(StageConfig::GetInstance()->GetCurrentStageIndex());

	// �}�b�v�`�b�v�}�l�[�W���[������
	mapChipMan_.Initialize({ 0, {}, {1.0f,1.0f,1.0f} });

	
	// �v���C���[������
	player_.Initialize({ +10.0f,-10.0f,0.0f });
	
	// �}�b�v�`�b�v�ݒ�
	DemoPlayer::StaticSetMapChip(mapChipMan_.CurrentMapPointer());


	// �S�[��
	goal_.Initialize({ +25.0f,-7.0f,0.0f });


	goalTim_.Initialize(160);

	fontScaleTim_.Initialize(30);

	afterglowTim_.Initialize(60);

	fontScaleEas_.Initialize(Vector3(4.0f, 0.0f, 0.0f), Vector3(2.0f, 2.0f, 0.0f), 3.0f);

	fontAlphaEas_.Initialize(0.0f, 1.0f, 3.0f);

	fontColor_.reset(CBColor::Create());

	fontObj_.reset(Sprite2D::Object::Create({ {WinSize.x_ / 2.0f, WinSize.y_ / 2.0f, 0.0f} }, fontColor_.get()));


	// �w�i������
	background_.Initialize();

	// HUD������
	hud_.Initialize();

	
	// �J����
	camera_.Initialize({ +17.0f,-11.0f,-21.0f }, {});

	// �r���[�v���W�F�N�V����������
	transferVP_.Initialize({});

	// �v���CBGM�J�n
	pPlayBGM_->Play(true);
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
	// HUD�X�V
	hud_.Update();

	// �|�[�Y���Ȃ�e��
	if (hud_.IsElderPause()) { return; }

	// �v���C���[�X�V
	player_.Update();

	// �S�[��
	goal_.Update();
	
	// �S�[�����ĂȂ��Ȃ�
	if (isGoal_ == false)
	{
		// �v���C���[�ƃS�[���ŃA�^������
		if (CollisionSphereSphere(player_, goal_))
		{
			// �v���C���[
			player_.Goal();

			// �S�[��
			goal_.Goal(player_.center_);

			// �S�[���t���O��true��
			isGoal_ = true;

			goalTim_.Reset(true);
		}
	}

	goalTim_.Update();
	if (goalTim_.IsEnd())
	{
		fontScaleTim_.SetActive(true);
	}

	fontScaleTim_.Update();
	if (fontScaleTim_.IsEnd())
	{
		afterglowTim_.SetActive(true);
		if(isAfterglow_ == false)
		{
			isAfterglow_ = true;
			particleMan_.EmitBubbleCharacter(
				24, static_cast<size_t>(afterglowTim_.End()),
				camera_.pos_ + Vector3(0.0f, 0.0f, +20.0f), Vector3(1.0f, 1.0f, 1.0f),
				0.3f, 0.6f,
				Vector3(-0.5f, -0.25f, -0.1f), Vector3(0.5f, 0.25f, 0.1f),
				Vector3(-0.5f, -0.5f, -0.5f), Vector3(+0.5f, +0.5f, +0.5f),
				Vector3(1.0f, 0.9f, 0.1f), 100.0f, YGame::DrawLocation::Center);
		}
	}

	fontObj_->scale_ = fontScaleEas_.In(fontScaleTim_.Ratio());
	fontObj_->UpdateMatrix();

	fontColor_->SetAlpha(fontAlphaEas_.In(fontScaleTim_.Ratio()));

	afterglowTim_.Update();

	// �}�b�v�`�b�v�X�V
	mapChipMan_.Update();


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
	if (afterglowTim_.IsEnd())
	{
		SceneExecutive::GetInstance()->Change("SELECT", "INFECTION", 5, 10);
	}
}

#pragma endregion


#pragma region �`��

void DemoScene::Draw()
{
	// �w�i�`��
	background_.Draw();


	// �v���C���[�`��
	player_.Draw();

	// �S�[���`��
	goal_.Draw();


	// �}�b�v�`�b�v�`��
	mapChipMan_.Draw();


	// HUD�`��
	hud_.Draw();

	if (isGoal_) { fontSpr_->SetDrawCommand(fontObj_.get(), YGame::DrawLocation::Front); }

	// �p�[�e�B�N��
	particleMan_.Draw();

}
#pragma endregion
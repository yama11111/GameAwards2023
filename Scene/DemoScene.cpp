#include "DemoScene.h"
#include "DrawerHelper.h"
#include "StageConfig.h"

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
	// �p�[�e�B�N��
	ParticleManager::StaticInitialize(&transferVP_);

	// �`��N���X�S��
	DrawerHelper::StaticInitialize(&transferVP_, &camera_, &particleMan_);

	// �v���C���[
	DemoPlayer::StaticInitialize();

	// �}�b�v�`�b�v
	mapChipMan_.Load();
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
	goal_.Initialize({ +25.0f,-15.0f,0.0f });


	// �w�i������
	background_.Initialize();

	// HUD������
	hud_.Initialize();

	
	// �J����
	camera_.Initialize({ +17.0f,-11.0f,-21.0f }, {});

	// �r���[�v���W�F�N�V����������
	transferVP_.Initialize({});
}

#pragma endregion


#pragma region �I������

void DemoScene::Finalize()
{

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


	////�S�[������
	//if (BoxCollision(player->GetTransform(), goal_, false))
	//{
	//	SceneManager::GetInstance()->Change("SELECT", "INFECTION");
	//}

	////���S����
	//if (player->GetPos().y_ < -15)
	//{
	//	SceneManager::GetInstance()->Change("PLAY", "BLACKOUT");
	//}
}

#pragma endregion


#pragma region �`��

void DemoScene::DrawBackSprite2Ds()
{

}

void DemoScene::DrawModels()
{
	// �w�i�`��
	background_.Draw();


	// �v���C���[�`��
	player_.Draw();

	// �S�[���`��
	goal_.Draw();


	// �}�b�v�`�b�v�`��
	mapChipMan_.Draw();


	// �p�[�e�B�N��
	particleMan_.Draw();
}

void DemoScene::DrawSprite3Ds()
{

}

void DemoScene::DrawFrontSprite2Ds()
{
	// HUD�`��
	hud_.Draw();
}

void DemoScene::Draw()
{
	// -------------------------- //
	Sprite2D::Pipeline::StaticSetDrawCommond();
	// ----- �w�i�X�v���C�g ----- //

	DrawBackSprite2Ds();

	// -------------------------- //
	Model::Pipeline::StaticSetDrawCommond();
	// --------- ���f�� --------- //

	DrawModels();

	// -------------------------- //
	Sprite3D::Pipeline::StaticSetDrawCommond();
	// ------- �r���{�[�h ------- //

	DrawSprite3Ds();

	// -------------------------- //
	Sprite2D::Pipeline::StaticSetDrawCommond();
	// ----- �O�i�X�v���C�g ----- //

	DrawFrontSprite2Ds();

	// -------------------------- //
}
#pragma endregion
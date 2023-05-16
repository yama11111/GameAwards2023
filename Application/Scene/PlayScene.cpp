#include "PlayScene.h"
#include "SceneExecutive.h"
#include "MathUtillity.h"
#include "CalcTransform.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#include "DrawerHelper.h"

#pragma region ���O��Ԑ錾

using YScene::PlayScene;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;

#pragma endregion 


#pragma region Static�֘A

#pragma endregion 


#pragma region �ǂݍ���

void PlayScene::Load()
{
	// ----- �I�[�f�B�I ----- //

	// �v���CBGM
	pPlayBGM_ = Audio::Load("BGM/select.wav");

	// ----- �ÓI������ ----- //

	// �p�[�e�B�N��
	ParticleManager::StaticInitialize(&transferVP_);

	// �`��N���X�S��
	DrawerHelper::StaticInitialize(&transferVP_, &camera_, &particleMan_);
}

#pragma endregion


#pragma region ������

void PlayScene::Initialize()
{
	// �p�[�e�B�N��������
	particleMan_.Initialize();


	// �X�e�[�W�ԍ�
	uint32_t stageIdx = static_cast<uint32_t>(StageConfig::GetInstance()->GetCurrentStageIndex());

	

	// �w�i������
	background_.Initialize();

	// HUD������
	hud_.Initialize();


	// �J����
	camera_.Initialize({ +0.0f,0.0f,-1000.0f }, {});

	// �r���[�v���W�F�N�V����������
	transferVP_.Initialize({});

    // �r���[�v���W�F�N�V�����ɃJ�������
    transferVP_ = camera_.GetViewProjection();
    // �r���[�v���W�F�N�V����
    transferVP_.UpdateMatrix();

	// �v���CBGM�J�n
	pPlayBGM_->Play(true);

    piecePtr_ = new Piece{ {-200,10},{5,5} };
    piecePtr_->RegisterTab(true, 4);
    piecePtr_->RegisterTab(true, 18);
    piecePtr_->RegisterTab(true, 27);
    piecePtr_->RegisterTab(true, 35);
    piecePtr_->RegisterTab(true, 43);
    piecePtr_->RegisterBlock(new BasicBlock{ Vector2{},Vector2{} }, Vector2{ -12,-20 }, Vector2{ 60,2 });
    piecePtr_->RegisterBlock(new BasicBlock{ Vector2{},Vector2{} }, Vector2{ -12,70 }, Vector2{ 60,2 });
    piecePtr_->RegisterBlock(new SpringBlock{ Vector2{},Vector2{} }, Vector2{ 50,-120 }, Vector2{ 8,8 });
    piecePtr_->SetFixity(true);
    piecePtr_->SetState(Piece::State::ROOT);
    stage_.AddPiece(piecePtr_);

    piece2Ptr_ = new Piece{ {150,200},{3,3} };
    piece2Ptr_->RegisterTab(false, 4);
    piece2Ptr_->RegisterTab(false, 10);
    piece2Ptr_->RegisterTab(false, 14);
    piece2Ptr_->RegisterTab(false, 20);
    piece2Ptr_->RegisterTab(false, 26);
    piece2Ptr_->RegisterBlock(new BasicBlock{ Vector2{},Vector2{} }, Vector2{ -80,60 }, Vector2{ 30,2 });
    piece2Ptr_->RegisterBlock(new BasicBlock{ Vector2{},Vector2{} }, Vector2{ -50,10 }, Vector2{ 20,2 });
    piece2Ptr_->RegisterBlock(new BasicBlock{ Vector2{},Vector2{} }, Vector2{ -10, -60 }, Vector2{ 60,2 });
    piece2Ptr_->RegisterBlock(new WoodenBlock{ Vector2{},Vector2{} }, Vector2{ 50,-30 }, Vector2{ 8,8 });
    stage_.AddPiece(piece2Ptr_);

    piece3Ptr_ = new Piece{ {400,0},{2,6} };
    piece3Ptr_->RegisterTab(false, 0);
    piece3Ptr_->RegisterTab(true, 9);
    piece3Ptr_->RegisterTab(false, 15);
    piece3Ptr_->RegisterTab(true, 26);
    piece3Ptr_->RegisterBlock(new BasicBlock{ Vector2{},Vector2{} }, Vector2{ 20,15 }, Vector2{ 2,60 });
    piece3Ptr_->RegisterBlock(new BasicBlock{ Vector2{},Vector2{} }, Vector2{ -20,-35 }, Vector2{ 60,2 });
    stage_.AddPiece(piece3Ptr_);

    player_ = std::make_unique<Player>(&stage_);
    player_->SetPos(Vector2{ -100,0 });
}

#pragma endregion


#pragma region �I������

void PlayScene::Finalize()
{
	// �v���CBGM��~
	pPlayBGM_->Stop();
}

#pragma endregion


#pragma region �X�V

void PlayScene::Update()
{
	// ���͕`��ÓI�X�V
	InputDrawerCommon::StaticUpdate();

	// HUD�X�V
	hud_.Update();

	// �|�[�Y���Ȃ�e��
	if (hud_.IsElderPause()) { return; }

	// ------------ �� �v���C�V�[���̏��� �� ------------//

	//���Z�b�g
	//if (���Z�b�g����Ȃ�)
	//{
	//	// �V�[���܂邲�ƃ��Z�b�g
	//	SceneExecutive::GetInstance()->Change("PLAY", "INFECTION", 5, 10);
	//}

    stage_.Update();
    player_->Update();
    stage_.DrawDebug();
    player_->DrawDebug();

	//�S�[������
	if (stage_.GetIsGoal())
	{
		StageConfig::GetInstance()->ClearStage(StageConfig::GetInstance()->GetCurrentStageIndex() - 1);
		// �Z���N�g�V�[���ɍs��
		SceneExecutive::GetInstance()->Change("SELECT", "INFECTION", 5, 10);
	}
	
	// ------------ �� �v���C�V�[���̏��� �� ------------//

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


}
#pragma endregion


#pragma region �`��

void PlayScene::Draw()
{
	// �w�i�`��
	//background_.Draw();

    // game�`��
    stage_.Draw();
    player_->Draw();

	// HUD�`��
	//hud_.Draw();

	// �p�[�e�B�N��
	//particleMan_.Draw();
}

#pragma endregion
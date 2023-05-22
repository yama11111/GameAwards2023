#include "PlayScene.h"
#include "SceneExecutive.h"
#include "MathUtillity.h"
#include "CalcTransform.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>
#include "Sign.h"

#include "DrawerHelper.h"

#pragma region ���O��Ԑ錾

using YScene::PlayScene;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;
using Sign = maruyama::Sign;

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

    tp_.Initialize();
    tp_.transform_.pos_ = { 4,-4,0 };

	// �X�e�[�W�ԍ�
	uint32_t stageIdx = static_cast<uint32_t>(StageConfig::GetInstance()->GetCurrentStageIndex());

	sign_.Initialize({ 10,20 });
    sign_.ReWriteBlock(7, 18, Sign::BlockType::SPRING);
    sign_.ReWriteBlock(8, 17, Sign::BlockType::BASIC);

	// �w�i������
	background_.Initialize();

	// HUD������
	hud_.Initialize();

	// �J����
	camera_.Initialize({ 0.0f,0.0f,-300.0f }, {});

	// �r���[�v���W�F�N�V����������
	transferVP_.Initialize();

	// �v���CBGM�J�n
	pPlayBGM_->Play(true);
	transferVP_.Initialize();
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

    if (sKeys_->IsDown(DIK_LSHIFT)) {
        if (sKeys_->IsDown(DIK_W)) camera_.pos_.y_ += 5;
        if (sKeys_->IsDown(DIK_S)) camera_.pos_.y_ -= 5;
        if (sKeys_->IsDown(DIK_A)) camera_.pos_.x_ -= 5;
        if (sKeys_->IsDown(DIK_D)) camera_.pos_.x_ += 5;
        if (sKeys_->IsDown(DIK_UP)) camera_.pos_.z_ += 5;
        if (sKeys_->IsDown(DIK_DOWN)) camera_.pos_.z_ -= 5;
    }

	sign_.Update();
    tp_.Update();

    sign_.PPC(&tp_);

	//���Z�b�g
	//if (���Z�b�g����Ȃ�)
	//{
	//	// �V�[���܂邲�ƃ��Z�b�g
	//	SceneExecutive::GetInstance()->Change("PLAY", "INFECTION", 5, 10);
	//}

	//�S�[������
	//if (�S�[��������)
	//{
	//	StageConfig::GetInstance()->ClearStage(StageConfig::GetInstance()->GetCurrentStageIndex() - 1);
	//	// �Z���N�g�V�[���ɍs��
	//	SceneExecutive::GetInstance()->Change("SELECT", "INFECTION", 5, 10);
	//}

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
    tp_.Draw();

	// �w�i�`��
	background_.Draw();

	sign_.Draw();

	// HUD�`��
	hud_.Draw();

	// �p�[�e�B�N��
	particleMan_.Draw();
}

#pragma endregion
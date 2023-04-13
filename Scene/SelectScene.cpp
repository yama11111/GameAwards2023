#include "SelectScene.h"
#include "SceneManager.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#pragma region ���O��Ԑ錾
using YScene::SelectScene;
using namespace YGame;
#pragma endregion 

#pragma region Static�֘A
#pragma endregion 

#pragma region �ǂݍ���
void SelectScene::Load()
{
	// ----- �e�N�X�`�� ----- //

	// ----- �I�[�f�B�I ----- //

	// ----- �X�v���C�g (2D) ----- //

	// ----- �X�v���C�g (3D) ----- //

	// ------- ���f�� ------- //

	// ----- �ÓI������ ----- //

	InputDrawerCommon::StaticInitialize();
	PauseDrawerCommon::StaticInitialize();

	SkydomeDrawerCommon::StaticInitialize();
	
	LetterBoxDrawerCommon::StaticInitialize();
	StageDrawerCommon::StaticInitialize(&transferVP_);
	CardDrawerCommon::StaticInitialize();
	SelectDrawerCommon::StaticInitialize(&transferVP_);
}
#pragma endregion


#pragma region ������
void SelectScene::Initialize()
{
	// input
	inputDra_.Initalize(InputDrawer::SceneType::Select);
	// pause
	pauseDra_.Initalize();

	// �X�e�[�W�ݒ�
	stageConfig_ = StageConfig::GetInstance();
	stageConfig_->SetCurrentStageIndex(1);

	// �`��p�N���X������
	dra_.Initalize();
	dra_.SetActive(true);

	// �V��������
	skydome_.Initialize();

	// �J����������
	camera_.Initialize({ +4.0f,+31.0f,-15.0f }, { -PI / 15.0f,-PI / 30.0f,-PI / 45.0f });
	//camera_.Initialize({ {0,0,-100}, {} });

	// �r���[�v���W�F�N�V����������
	transferVP_.Initialize({});
}
#pragma endregion

#pragma region �I������
void SelectScene::Finalize()
{

}
#pragma endregion

#pragma region �X�V
void SelectScene::Update()
{
	// input�X�V
	inputDra_.Update();
	// pause�X�V
	pauseDra_.Update();


	// �X�e�[�W�ԍ��擾
	int stageIdx = stageConfig_->GetCurrentStageIndex();

	// �X�e�[�W�I�� (A or D)
	stageIdx += 
		+ (sKeys_->IsTrigger(DIK_D) + sKeys_->IsTrigger(DIK_W))
		- (sKeys_->IsTrigger(DIK_A) + sKeys_->IsTrigger(DIK_S));

	// �X�e�[�W�ԍ��ݒ�
	stageConfig_->SetCurrentStageIndex(stageIdx);

	ImGui::Begin("StageIdx");
	ImGui::Text("%d", stageIdx);
	ImGui::End();

	// ���̃V�[���� (SPACE)
	if (sKeys_->IsTrigger(DIK_SPACE))
	{
		SceneManager::GetInstance()->Change("PLAY", "INFECTION");
	}


	// �`��p�N���X�X�V
	dra_.Update();

	// �V���X�V
	skydome_.Update();

	// �J�����X�V + ���
	camera_.Update();
	transferVP_ = camera_.GetViewProjection();
}
#pragma endregion


#pragma region �`��
void SelectScene::DrawBackSprite2Ds()
{

}

void SelectScene::DrawModels()
{
	// �V���`��
	skydome_.Draw();

	// �`��p�N���X�X�V
	dra_.DrawModel();
}

void SelectScene::DrawSprite3Ds()
{
	// �`��p�N���X�X�V
	dra_.DrawSprite3D();
}

void SelectScene::DrawFrontSprite2Ds()
{
	// �`��
	dra_.DrawSprite2D();

	// input�`��
	inputDra_.Draw(false);
	// pause�`��
	pauseDra_.Draw();
}

void SelectScene::Draw()
{
	// -------------------------- //
	Sprite2D::Common::StaticSetPipeline();
	// ----- �w�i�X�v���C�g ----- //

	DrawBackSprite2Ds();

	// -------------------------- //
	Model::Common::StaticSetPipeline();
	// --------- ���f�� --------- //

	DrawModels();

	// -------------------------- //
	Sprite3D::Common::StaticSetPipeline();
	// ------- �r���{�[�h ------- //

	DrawSprite3Ds();

	// -------------------------- //
	Sprite2D::Common::StaticSetPipeline();
	// ----- �O�i�X�v���C�g ----- //

	DrawFrontSprite2Ds();

	// -------------------------- //
}
#pragma endregion
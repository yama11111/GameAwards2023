#include "SelectScene.h"
#include "SceneManager.h"
#include "TransitionManager.h"
#include "CoreColor.h"
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

	// �p�[�e�B�N��
	ParticleManager::StaticInitialize(&transferVP_);

	// input
	InputDrawerCommon::StaticInitialize();
	
	// pause
	PauseDrawerCommon::StaticInitialize();
	
	// �X�e�[�W�Z���N�g
	SelectDrawerCommon::StaticInitialize(&transferVP_, &particleMan_);
}
#pragma endregion


#pragma region ������
void SelectScene::Initialize()
{
	// �p�[�e�B�N��������
	particleMan_.Initialize();

	// input
	inputDra_.Initialize(InputDrawer::SceneType::Select);
	
	// pause
	pauseDra_.Initialize();

	// �X�e�[�W�ݒ�
	stageConfig_ = StageConfig::GetInstance();

	// �`��p�N���X������
	dra_.Initialize();
	dra_.SetActive(true);

	// �J����������
	camera_.Initialize({ +4.0f,+31.0f,-15.0f }, { -PI / 15.0f,-PI / 30.0f,-PI / 45.0f });
	//camera_.Initialize({ 0,0,-100 }, {});

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


	// �|�[�Y���Ȃ�e��
	if (pauseDra_.IsPause()) { return; }

	// �X�e�[�W�ԍ��擾
	int stageIdx = stageConfig_->GetCurrentStageIndex();

	// �J�ڒ�����Ȃ��Ȃ�
	if (TransitionManager::GetInstance()->IsPreChange() == false)
	{
		// �X�e�[�W�I�� (A or D)
		stageIdx +=
			+(sKeys_->IsTrigger(DIK_D) + sKeys_->IsTrigger(DIK_W))
			- (sKeys_->IsTrigger(DIK_A) + sKeys_->IsTrigger(DIK_S));

		// �X�e�[�W�ԍ��ݒ�
		stageConfig_->SetCurrentStageIndex(stageIdx);

		// ���̃V�[���� (SPACE)
		if (sKeys_->IsTrigger(DIK_SPACE))
		{
			SceneManager::GetInstance()->Change("PLAY", "INFECTION");
		}
	}

	ImGui::Begin("StageIdx");
	ImGui::Text("%d", stageIdx);
	ImGui::End();


	// �`��p�N���X�X�V
	dra_.Update();

	// �j�̐F�X�V
	CoreColor::StaticUpdate();

	// �p�[�e�B�N���X�V
	particleMan_.Update();

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
	// �`��p�N���X�X�V
	dra_.DrawModel();

	// �p�[�e�B�N���`��
	particleMan_.Draw();
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
	inputDra_.Draw();
	
	// pause�`��
	pauseDra_.Draw();
}

void SelectScene::Draw()
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
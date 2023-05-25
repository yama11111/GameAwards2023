#include "SelectScene.h"
#include "SceneExecutive.h"
#include "TransitionManager.h"
#include "CoreColor.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#include "MouseCollider.h"

#pragma region ���O��Ԑ錾

using YScene::SelectScene;
using namespace YGame;

#pragma endregion 

#pragma region Static�֘A
#pragma endregion 

#pragma region �ǂݍ���
void SelectScene::Load()
{
	// ----- �I�[�f�B�I ----- //

	// �Z���N�g�V�[��BGM
	pSelectBGM_ = Audio::Load("BGM/select.wav");


	//// �Z���N�gSE
	//pSelectSE_ = Audio::Load("SE/select.wav");

	//// ����SE
	//pDecisionSE_ = Audio::Load("SE/decision.wav");
	
	// ----- �ÓI������ ----- //

	// �}�E�X�R���C�_�[�ÓI������
	MouseColliderCommon::StaticInitialize();

	// �}�E�X�R���C�_�[�Ƀr���[�v���W�F�N�V�����ݒ�
	MouseColliderCommon::StaticSetViewProjectionPointer(&transferVP_);

	// �p�[�e�B�N��
	ParticleManager::StaticInitialize(&transferVP_);

	// input
	InputDrawerCommon::StaticInitialize();
	
	// pause
	PauseDrawerCommon::StaticInitialize();

	// ���`��N���X
	IDrawer::StaticInitialize(&transferVP_, nullptr, nullptr, &camera_, &particleMan_);
	
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
	inputDra_.Initialize();
	
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
	transferVP_.Initialize();

	// �Z���N�g�V�[��BGM�J�n
	pSelectBGM_->Play(true);
}
#pragma endregion

#pragma region �I������
void SelectScene::Finalize()
{
	// �Z���N�g�V�[��BGM��~
	pSelectBGM_->Stop();
}
#pragma endregion

#pragma region �X�V
void SelectScene::Update()
{
	// �}�E�X�R���C�_�[�ÓI�X�V
	MouseColliderCommon::StaticUpdate();

	// input�ÓI�X�V
	InputDrawerCommon::StaticUpdate();

	// pause�X�V
	pauseDra_.Update();

	// �|�[�Y���Ȃ�e��
	if (pauseDra_.IsElderPause()) { return; }

	// input�X�V
	inputDra_.Update();

	// �X�e�[�W�ԍ��擾
	int stageIdx = stageConfig_->GetCurrentStageIndex();

	// �L�[�擾
	bool up		 = (sKeys_->IsTrigger(DIK_W) || sKeys_->IsTrigger(DIK_UP));
	bool left	 = (sKeys_->IsTrigger(DIK_A) || sKeys_->IsTrigger(DIK_LEFT));
	bool down	 = (sKeys_->IsTrigger(DIK_S) || sKeys_->IsTrigger(DIK_DOWN));
	bool right	 = (sKeys_->IsTrigger(DIK_D) || sKeys_->IsTrigger(DIK_RIGHT));

	// �X�e�[�W�I��
	stageIdx += up + right - down - left;

	// SE
	if (TransitionManager::GetInstance()->IsFalling() == false)
	{
		if (up || right || left || down)
		{
			//pSelectSE_->Play(false);
		}
	}

	// �X�e�[�W�ԍ��ݒ�
	stageConfig_->SetCurrentStageIndex(stageIdx);

	// ���̃V�[���� (SPACE)
	if (sKeys_->IsTrigger(DIK_SPACE))
	{
		// SE
		//pDecisionSE_->Play(false);

		SceneExecutive::GetInstance()->Change("PLAY", "INFECTION", 5, 10);
		//SceneExecutive::GetInstance()->Change("DEMO", "INFECTION", 5, 10);
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

void SelectScene::Draw()
{
	// �`��
	dra_.Draw();

	// input�`��
	inputDra_.Draw();

	// pause�`��
	pauseDra_.Draw();


	// �p�[�e�B�N���`��
	particleMan_.Draw();
}
#pragma endregion
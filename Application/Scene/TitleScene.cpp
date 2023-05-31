#include "TitleScene.h"
#include "SceneExecutive.h"
#include "CoreColor.h"
#include "Def.h"
#include <cassert>

#include "MouseCollider.h"
#include "AudioConfig.h"

#pragma region ���O��Ԑ錾

using YScene::TitleScene;
using namespace YInput;
using namespace YGame;
using namespace YMath;

#pragma endregion 

#pragma region Static�֘A
#pragma endregion 

#pragma region �ǂݍ���
void TitleScene::Load()
{
	// ----- �I�[�f�B�I ----- //

	// �^�C�g��BGM
	pTitleBGM_ = Audio::Load("BGM/title.wav");
	pTitleBGM_->SetVolume(AudioConfig::BGM::Title);

	// �Z���N�gSE
	pSelectSE_ = Audio::Load("SE/SE_select.wav");
	pSelectSE_->SetVolume(AudioConfig::SE::Select);

	// ����SE
	pDecisionSE_ = Audio::Load("SE/SE_decision.wav");
	pDecisionSE_->SetVolume(AudioConfig::SE::Decition);

	// ----- �ÓI������ ----- //

	// �}�E�X�R���C�_�[�ÓI������
	MouseColliderCommon::StaticInitialize();

	// �}�E�X�R���C�_�[�Ƀr���[�v���W�F�N�V�����ݒ�
	MouseColliderCommon::StaticSetViewProjectionPointer(&transferVP_);

	// �p�[�e�B�N��
	ParticleManager::StaticInitialize(&transferVP_);

	// �j�F
	CoreColor::StaticInitialize();
	
	// ���`��N���X
	IDrawer::StaticInitialize(&transferVP_, nullptr, nullptr, &camera_, &particleMan_);
	
	// �w�i
	BackgroundDrawerCommon::StaticInitialize(&particleMan_);

	// ����
	InputDrawerCommon::StaticInitialize();
	
	// �^�C�g��
	TitleDrawerCommon::StaticInitialize();
}
#pragma endregion


#pragma region ������
void TitleScene::Initialize()
{
	// �p�[�e�B�N��������
	particleMan_.Initialize();

	// �w�i������
	background_.Initialize();

	// ���͕`�揉����
	inputDra_.Initialize();

	// �^�C�g���`�揉����
	titleDra_.Initialize();

	// �^�C�g��BGM�J�n
	pTitleBGM_->Play(true);
}
#pragma endregion

#pragma region �I������
void TitleScene::Finalize()
{
	// �^�C�g��BGM��~
	pTitleBGM_->Stop();
}
#pragma endregion

#pragma region �X�V
void TitleScene::Update()
{
	// �}�E�X�R���C�_�[�ÓI�X�V
	MouseColliderCommon::StaticUpdate();

	// ���͕`��ÓI�X�V
	InputDrawerCommon::StaticUpdate();

	// ���͕`��X�V
	inputDra_.Update();

	// �L�[�擾
	bool up		 = (sKeys_->IsTrigger(DIK_W) || sKeys_->IsTrigger(DIK_UP));
	bool left	 = (sKeys_->IsTrigger(DIK_A) || sKeys_->IsTrigger(DIK_LEFT));
	bool down	 = (sKeys_->IsTrigger(DIK_S) || sKeys_->IsTrigger(DIK_DOWN));
	bool right	 = (sKeys_->IsTrigger(DIK_D) || sKeys_->IsTrigger(DIK_RIGHT));

	// �I��ύX
	titleDra_.Select(up || right, left || down);

	// SE
	if (TransitionManager::GetInstance()->IsFalling() == false)
	{
		if (up || right || left || down)
		{
			pSelectSE_->Stop();
			pSelectSE_->Play(false);
		}
	}

	// �I���X�V
	titleDra_.Update();

	// �w�i�X�V
	background_.Update();

	// �j�F�ÓI�X�V
	CoreColor::StaticUpdate();
	// �w�i�ÓI�X�V
	BackgroundDrawerCommon::StaticUpdate();

	// �p�[�e�B�N���X�V
	particleMan_.Update();

	// ���̃V�[����
	if (sKeys_->IsTrigger(DIK_SPACE))
	{
		// Start�Ȃ�
		if (titleDra_.GetSelection() == TitleDrawerCommon::Selection::Start)
		{
			// SE
			pDecisionSE_->Stop();
			pDecisionSE_->Play(false);

			// �Z���N�g�V�[����
			SceneExecutive::GetInstance()->Change("SELECT", "INFECTION", 5, 10);
		}
		// Exit�Ȃ�
		else if (titleDra_.GetSelection() == TitleDrawerCommon::Selection::Exit)
		{
			// �I��
			SceneManager::GetInstance()->SetEnd(true);
		}
	}
}
#pragma endregion


#pragma region �`��

void TitleScene::Draw()
{
	background_.Draw();

	titleDra_.Draw();

	inputDra_.Draw();
	
	particleMan_.Draw();
}
#pragma endregion
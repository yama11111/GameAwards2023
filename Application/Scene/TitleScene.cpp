#include "TitleScene.h"
#include "SceneExecutive.h"
#include "CoreColor.h"
#include "Def.h"
#include <cassert>

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
	pTitleBGM_ = Audio::Load("vigilante.wav");
	//pTitleBGM_ = Audio::Load("fanfare.wav");

	// ----- �ÓI������ ----- //

	// �p�[�e�B�N��
	ParticleManager::StaticInitialize(&transferVP_);

	// �j�F
	CoreColor::StaticInitialize();
	// �w�i
	BackgroundDrawerCommon::StaticInitialize(&transferVP_, &particleMan_);

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
	// ���͕`��ÓI�X�V
	InputDrawerCommon::StaticUpdate();

	// ���͕`��X�V
	inputDra_.Update();

	// �I��ύX
	titleDra_.Select(
		sKeys_->IsTrigger(DIK_W) || sKeys_->IsTrigger(DIK_D),
		sKeys_->IsTrigger(DIK_S) || sKeys_->IsTrigger(DIK_A));

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
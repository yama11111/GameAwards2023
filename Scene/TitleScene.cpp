#include "TitleScene.h"
#include "SceneManager.h"
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
	// ----- �e�N�X�`�� ----- //

	// ----- �I�[�f�B�I ----- //

	// ----- �X�v���C�g (2D) ----- //
	
	// ----- �X�v���C�g (3D) ----- //

	// ------- ���f�� ------- //

	// ----- �ÓI������ ----- //

	TitleDrawerCommon::StaticInitialize();
	InputDrawerCommon::StaticInitialize();
}
#pragma endregion


#pragma region ������
void TitleScene::Initialize()
{
	inputDra_.Initalize(InputDrawer::SceneType::Title);
	
	dra_.Initalize();
}
#pragma endregion

#pragma region �I������
void TitleScene::Finalize()
{

}
#pragma endregion

#pragma region �X�V
void TitleScene::Update()
{
	inputDra_.Update();

	// �I��ύX
	dra_.Select(
		sKeys_->IsTrigger(DIK_W) || sKeys_->IsTrigger(DIK_D),
		sKeys_->IsTrigger(DIK_S) || sKeys_->IsTrigger(DIK_A));

	dra_.Update();


	// ���̃V�[����
	if (sKeys_->IsTrigger(DIK_SPACE))
	{
		if (dra_.GetSelection() == TitleDrawer::Selection::Start)
		{
			SceneManager::GetInstance()->Change("SELECT", "INFECTION");
		}
		else if (dra_.GetSelection() == TitleDrawer::Selection::Exit)
		{
			SceneManager::GetInstance()->SetEnd(true);
		}
	}
}
#pragma endregion


#pragma region �`��
void TitleScene::DrawBackSprite2Ds()
{
	
}

void TitleScene::DrawModels()
{
	dra_.DrawModel();
	
}

void TitleScene::DrawSprite3Ds()
{

}

void TitleScene::DrawFrontSprite2Ds()
{
	dra_.DrawSprite2D();

	inputDra_.Draw(false);
}

void TitleScene::Draw()
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
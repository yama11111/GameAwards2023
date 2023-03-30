#include "SelectScene.h"
#include "SceneManager.h"
#include "Def.h"
#include <cassert>

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
}
#pragma endregion


#pragma region ������
void SelectScene::Initialize()
{

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
	// ���̃V�[����
	if (sKeys_->IsTrigger(DIK_0))
	{
		SceneManager::GetInstance()->Change("PLAY", "BLACKOUT");
	}
}
#pragma endregion


#pragma region �`��
void SelectScene::DrawBackSprite2Ds()
{

}

void SelectScene::DrawModels()
{

}

void SelectScene::DrawSprite3Ds()
{

}

void SelectScene::DrawFrontSprite2Ds()
{

}

void SelectScene::Draw()
{
	// -------------------------- //
	Sprite2DCommon::StaticSetDrawCommand();
	// ----- �w�i�X�v���C�g ----- //

	DrawBackSprite2Ds();

	// -------------------------- //
	ModelCommon::StaticSetDrawCommand();
	// --------- ���f�� --------- //

	DrawModels();

	// -------------------------- //
	Sprite3DCommon::StaticSetDrawCommand();
	// ------- �r���{�[�h ------- //

	DrawSprite3Ds();

	// -------------------------- //
	Sprite2DCommon::StaticSetDrawCommand();
	// ----- �O�i�X�v���C�g ----- //

	DrawFrontSprite2Ds();

	// -------------------------- //
}
#pragma endregion
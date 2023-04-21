#include "EditScene.h"
#include "SceneManager.h"
#include "MathUtillity.h"
#include "Def.h"
#include "StageConfig.h"
#include <cassert>
#include <imgui.h>

#pragma region ���O��Ԑ錾
using YScene::EditScene;
using namespace YGame;
#pragma endregion 

#pragma region Static�֘A
#pragma endregion 

#pragma region �ǂݍ���
void EditScene::Load()
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
void EditScene::Initialize()
{

}
#pragma endregion

#pragma region �I������
void EditScene::Finalize()
{

}
#pragma endregion

#pragma region �X�V
void EditScene::Update()
{
	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	ImGui::Begin("X");
	ImGui::SliderInt("X", &XS, 0, 12);
	ImGui::End();

	// ���̃V�[���� (SPACE)
	if (sKeys_->IsTrigger(DIK_SPACE))
	{
		SceneManager::GetInstance()->Change("PLAY", "BLACKOUT");
	}
}
#pragma endregion


#pragma region �`��
void EditScene::DrawBackSprite2Ds()
{

}

void EditScene::DrawModels()
{

}

void EditScene::DrawSprite3Ds()
{

}

void EditScene::DrawFrontSprite2Ds()
{

}

void EditScene::Draw()
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
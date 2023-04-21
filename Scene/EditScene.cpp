#include "EditScene.h"
#include "SceneManager.h"
#include "MathUtillity.h"
#include "Def.h"
#include "StageConfig.h"
#include <cassert>
#include <imgui.h>

#pragma region 名前空間宣言
using YScene::EditScene;
using namespace YGame;
#pragma endregion 

#pragma region Static関連
#pragma endregion 

#pragma region 読み込み
void EditScene::Load()
{
	// ----- テクスチャ ----- //

	// ----- オーディオ ----- //

	// ----- スプライト (2D) ----- //

	// ----- スプライト (3D) ----- //

	// ------- モデル ------- //

	// ----- 静的初期化 ----- //
}
#pragma endregion


#pragma region 初期化
void EditScene::Initialize()
{

}
#pragma endregion

#pragma region 終了処理
void EditScene::Finalize()
{

}
#pragma endregion

#pragma region 更新
void EditScene::Update()
{
	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	ImGui::Begin("X");
	ImGui::SliderInt("X", &XS, 0, 12);
	ImGui::End();

	// 次のシーンへ (SPACE)
	if (sKeys_->IsTrigger(DIK_SPACE))
	{
		SceneManager::GetInstance()->Change("PLAY", "BLACKOUT");
	}
}
#pragma endregion


#pragma region 描画
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
	// ----- 背景スプライト ----- //

	DrawBackSprite2Ds();

	// -------------------------- //
	Model::Pipeline::StaticSetDrawCommond();
	// --------- モデル --------- //

	DrawModels();

	// -------------------------- //
	Sprite3D::Pipeline::StaticSetDrawCommond();
	// ------- ビルボード ------- //

	DrawSprite3Ds();

	// -------------------------- //
	Sprite2D::Pipeline::StaticSetDrawCommond();
	// ----- 前景スプライト ----- //

	DrawFrontSprite2Ds();

	// -------------------------- //
}
#pragma endregion
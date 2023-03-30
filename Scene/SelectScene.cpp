#include "SelectScene.h"
#include "SceneManager.h"
#include "Def.h"
#include <cassert>

#pragma region 名前空間宣言
using YScene::SelectScene;
using namespace YGame;
#pragma endregion 

#pragma region Static関連
#pragma endregion 

#pragma region 読み込み
void SelectScene::Load()
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
void SelectScene::Initialize()
{

}
#pragma endregion

#pragma region 終了処理
void SelectScene::Finalize()
{

}
#pragma endregion

#pragma region 更新
void SelectScene::Update()
{
	// 次のシーンへ
	if (sKeys_->IsTrigger(DIK_0))
	{
		SceneManager::GetInstance()->Change("PLAY", "BLACKOUT");
	}
}
#pragma endregion


#pragma region 描画
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
	// ----- 背景スプライト ----- //

	DrawBackSprite2Ds();

	// -------------------------- //
	ModelCommon::StaticSetDrawCommand();
	// --------- モデル --------- //

	DrawModels();

	// -------------------------- //
	Sprite3DCommon::StaticSetDrawCommand();
	// ------- ビルボード ------- //

	DrawSprite3Ds();

	// -------------------------- //
	Sprite2DCommon::StaticSetDrawCommand();
	// ----- 前景スプライト ----- //

	DrawFrontSprite2Ds();

	// -------------------------- //
}
#pragma endregion
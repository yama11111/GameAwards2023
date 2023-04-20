#include "TitleScene.h"
#include "SceneManager.h"
#include "Def.h"
#include <cassert>

#pragma region 名前空間宣言
using YScene::TitleScene;
using namespace YInput;
using namespace YGame;
using namespace YMath;
#pragma endregion 

#pragma region Static関連
#pragma endregion 

#pragma region 読み込み
void TitleScene::Load()
{
	// ----- テクスチャ ----- //

	// ----- オーディオ ----- //

	// ----- スプライト (2D) ----- //
	
	// ----- スプライト (3D) ----- //

	// ------- モデル ------- //

	// ----- 静的初期化 ----- //

	TitleDrawerCommon::StaticInitialize();
	InputDrawerCommon::StaticInitialize();
}
#pragma endregion


#pragma region 初期化
void TitleScene::Initialize()
{
	inputDra_.Initalize(InputDrawer::SceneType::Title);
	
	dra_.Initalize();
}
#pragma endregion

#pragma region 終了処理
void TitleScene::Finalize()
{

}
#pragma endregion

#pragma region 更新
void TitleScene::Update()
{
	inputDra_.Update();

	// 選択変更
	dra_.Select(
		sKeys_->IsTrigger(DIK_W) || sKeys_->IsTrigger(DIK_D),
		sKeys_->IsTrigger(DIK_S) || sKeys_->IsTrigger(DIK_A));

	dra_.Update();


	// 次のシーンへ
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


#pragma region 描画
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
	// ----- 背景スプライト ----- //

	DrawBackSprite2Ds();

	// -------------------------- //
	Model::Common::StaticSetPipeline();
	// --------- モデル --------- //

	DrawModels();

	// -------------------------- //
	Sprite3D::Common::StaticSetPipeline();
	// ------- ビルボード ------- //

	DrawSprite3Ds();

	// -------------------------- //
	Sprite2D::Common::StaticSetPipeline();
	// ----- 前景スプライト ----- //

	DrawFrontSprite2Ds();

	// -------------------------- //
}
#pragma endregion
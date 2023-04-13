#include "SelectScene.h"
#include "SceneManager.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

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

	InputDrawerCommon::StaticInitialize();
	PauseDrawerCommon::StaticInitialize();

	SkydomeDrawerCommon::StaticInitialize();
	
	LetterBoxDrawerCommon::StaticInitialize();
	StageDrawerCommon::StaticInitialize(&transferVP_);
	CardDrawerCommon::StaticInitialize();
	SelectDrawerCommon::StaticInitialize(&transferVP_);
}
#pragma endregion


#pragma region 初期化
void SelectScene::Initialize()
{
	// input
	inputDra_.Initalize(InputDrawer::SceneType::Select);
	// pause
	pauseDra_.Initalize();

	// ステージ設定
	stageConfig_ = StageConfig::GetInstance();
	stageConfig_->SetCurrentStageIndex(1);

	// 描画用クラス初期化
	dra_.Initalize();
	dra_.SetActive(true);

	// 天球初期化
	skydome_.Initialize();

	// カメラ初期化
	camera_.Initialize({ +4.0f,+31.0f,-15.0f }, { -PI / 15.0f,-PI / 30.0f,-PI / 45.0f });
	//camera_.Initialize({ {0,0,-100}, {} });

	// ビュープロジェクション初期化
	transferVP_.Initialize({});
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
	// input更新
	inputDra_.Update();
	// pause更新
	pauseDra_.Update();


	// ステージ番号取得
	int stageIdx = stageConfig_->GetCurrentStageIndex();

	// ステージ選択 (A or D)
	stageIdx += 
		+ (sKeys_->IsTrigger(DIK_D) + sKeys_->IsTrigger(DIK_W))
		- (sKeys_->IsTrigger(DIK_A) + sKeys_->IsTrigger(DIK_S));

	// ステージ番号設定
	stageConfig_->SetCurrentStageIndex(stageIdx);

	ImGui::Begin("StageIdx");
	ImGui::Text("%d", stageIdx);
	ImGui::End();

	// 次のシーンへ (SPACE)
	if (sKeys_->IsTrigger(DIK_SPACE))
	{
		SceneManager::GetInstance()->Change("PLAY", "INFECTION");
	}


	// 描画用クラス更新
	dra_.Update();

	// 天球更新
	skydome_.Update();

	// カメラ更新 + 代入
	camera_.Update();
	transferVP_ = camera_.GetViewProjection();
}
#pragma endregion


#pragma region 描画
void SelectScene::DrawBackSprite2Ds()
{

}

void SelectScene::DrawModels()
{
	// 天球描画
	skydome_.Draw();

	// 描画用クラス更新
	dra_.DrawModel();
}

void SelectScene::DrawSprite3Ds()
{
	// 描画用クラス更新
	dra_.DrawSprite3D();
}

void SelectScene::DrawFrontSprite2Ds()
{
	// 描画
	dra_.DrawSprite2D();

	// input描画
	inputDra_.Draw(false);
	// pause描画
	pauseDra_.Draw();
}

void SelectScene::Draw()
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
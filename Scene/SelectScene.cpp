#include "SelectScene.h"
#include "SceneManager.h"
#include "TransitionManager.h"
#include "CoreColor.h"
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

	// パーティクル
	ParticleManager::StaticInitialize(&transferVP_);

	// input
	InputDrawerCommon::StaticInitialize();
	
	// pause
	PauseDrawerCommon::StaticInitialize();
	
	// ステージセレクト
	SelectDrawerCommon::StaticInitialize(&transferVP_, &particleMan_);
}
#pragma endregion


#pragma region 初期化
void SelectScene::Initialize()
{
	// パーティクル初期化
	particleMan_.Initialize();

	// input
	inputDra_.Initialize(InputDrawer::SceneType::Select);
	
	// pause
	pauseDra_.Initialize(PauseDrawer::SceneType::Select);

	// ステージ設定
	stageConfig_ = StageConfig::GetInstance();

	// 描画用クラス初期化
	dra_.Initialize();
	dra_.SetActive(true);

	// カメラ初期化
	camera_.Initialize({ +4.0f,+31.0f,-15.0f }, { -PI / 15.0f,-PI / 30.0f,-PI / 45.0f });
	//camera_.Initialize({ 0,0,-100 }, {});

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

	// pause更新
	pauseDra_.Update();

	// ポーズ中なら弾く
	if (pauseDra_.IsElderPause()) { return; }

	// input更新
	inputDra_.Update();

	// ステージ番号取得
	int stageIdx = stageConfig_->GetCurrentStageIndex();

	// 遷移中じゃないなら
	if (TransitionManager::GetInstance()->IsPreChange() == false)
	{
		// ステージ選択 (A or D)
		stageIdx +=
			+(sKeys_->IsTrigger(DIK_D) + sKeys_->IsTrigger(DIK_W))
			- (sKeys_->IsTrigger(DIK_A) + sKeys_->IsTrigger(DIK_S));

		// ステージ番号設定
		stageConfig_->SetCurrentStageIndex(stageIdx);

		// 次のシーンへ (SPACE)
		if (sKeys_->IsTrigger(DIK_SPACE))
		{
			//SceneManager::GetInstance()->Change("PLAY", "INFECTION");
			SceneManager::GetInstance()->Change("DEMO", "INFECTION");
		}
	}

	ImGui::Begin("StageIdx");
	ImGui::Text("%d", stageIdx);
	ImGui::End();


	// 描画用クラス更新
	dra_.Update();

	// 核の色更新
	CoreColor::StaticUpdate();

	// パーティクル更新
	particleMan_.Update();

	// カメラ更新 + 代入
	camera_.Update();
	transferVP_ = camera_.GetViewProjection();
}
#pragma endregion


#pragma region 描画
void SelectScene::DrawBackSprite2Ds()
{

}

void SelectScene::DrawBackModels()
{
	// 描画用クラス更新
	dra_.DrawBackModel();
}

void SelectScene::DrawBackSprite3Ds()
{
	// 描画用クラス更新
	dra_.DrawSprite3D();
}

void SelectScene::DrawFrontModels()
{
	// 描画用クラス更新
	dra_.DrawFrontModel();

	// パーティクル描画
	particleMan_.Draw();
}

void SelectScene::DrawFrontSprite3Ds()
{	

}

void SelectScene::DrawFrontSprite2Ds()
{
	// 描画
	dra_.DrawSprite2D();


	// input描画
	inputDra_.Draw();
	
	// pause描画
	pauseDra_.Draw();
}

void SelectScene::Draw()
{
	// -------------------------- //
	Sprite2D::Pipeline::StaticSetDrawCommond();
	// ----- 背景スプライト ----- //

	DrawBackSprite2Ds();
	
	// -------------------------- //
	Model::Pipeline::StaticSetDrawCommond();
	// --------- モデル --------- //

	DrawBackModels();

	// -------------------------- //
	Sprite3D::Pipeline::StaticSetDrawCommond();
	// ------- ビルボード ------- //

	DrawBackSprite3Ds();

	// -------------------------- //
	Model::Pipeline::StaticSetDrawCommond();
	// --------- モデル --------- //

	DrawFrontModels();

	// -------------------------- //
	Sprite3D::Pipeline::StaticSetDrawCommond();
	// ------- ビルボード ------- //

	DrawFrontSprite3Ds();

	// -------------------------- //
	Sprite2D::Pipeline::StaticSetDrawCommond();
	// ----- 前景スプライト ----- //

	DrawFrontSprite2Ds();

	// -------------------------- //
}
#pragma endregion
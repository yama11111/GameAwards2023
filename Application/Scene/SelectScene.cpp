#include "SelectScene.h"
#include "SceneExecutive.h"
#include "TransitionManager.h"
#include "CoreColor.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#include "MouseCollider.h"

#pragma region 名前空間宣言

using YScene::SelectScene;
using namespace YGame;

#pragma endregion 

#pragma region Static関連
#pragma endregion 

#pragma region 読み込み
void SelectScene::Load()
{
	// ----- オーディオ ----- //

	// セレクトシーンBGM
	pSelectBGM_ = Audio::Load("BGM/select.wav");


	//// セレクトSE
	//pSelectSE_ = Audio::Load("SE/select.wav");

	//// 決定SE
	//pDecisionSE_ = Audio::Load("SE/decision.wav");
	
	// ----- 静的初期化 ----- //

	// マウスコライダー静的初期化
	MouseColliderCommon::StaticInitialize();

	// マウスコライダーにビュープロジェクション設定
	MouseColliderCommon::StaticSetViewProjectionPointer(&transferVP_);

	// パーティクル
	ParticleManager::StaticInitialize(&transferVP_);

	// input
	InputDrawerCommon::StaticInitialize();
	
	// pause
	PauseDrawerCommon::StaticInitialize();

	// 基底描画クラス
	IDrawer::StaticInitialize(&transferVP_, nullptr, nullptr, &camera_, &particleMan_);
	
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
	inputDra_.Initialize();
	
	// pause
	pauseDra_.Initialize();

	// ステージ設定
	stageConfig_ = StageConfig::GetInstance();

	// 描画用クラス初期化
	dra_.Initialize();
	dra_.SetActive(true);

	// カメラ初期化
	camera_.Initialize({ +4.0f,+31.0f,-15.0f }, { -PI / 15.0f,-PI / 30.0f,-PI / 45.0f });
	//camera_.Initialize({ 0,0,-100 }, {});

	// ビュープロジェクション初期化
	transferVP_.Initialize();

	// セレクトシーンBGM開始
	pSelectBGM_->Play(true);
}
#pragma endregion

#pragma region 終了処理
void SelectScene::Finalize()
{
	// セレクトシーンBGM停止
	pSelectBGM_->Stop();
}
#pragma endregion

#pragma region 更新
void SelectScene::Update()
{
	// マウスコライダー静的更新
	MouseColliderCommon::StaticUpdate();

	// input静的更新
	InputDrawerCommon::StaticUpdate();

	// pause更新
	pauseDra_.Update();

	// ポーズ中なら弾く
	if (pauseDra_.IsElderPause()) { return; }

	// input更新
	inputDra_.Update();

	// ステージ番号取得
	int stageIdx = stageConfig_->GetCurrentStageIndex();

	// キー取得
	bool up		 = (sKeys_->IsTrigger(DIK_W) || sKeys_->IsTrigger(DIK_UP));
	bool left	 = (sKeys_->IsTrigger(DIK_A) || sKeys_->IsTrigger(DIK_LEFT));
	bool down	 = (sKeys_->IsTrigger(DIK_S) || sKeys_->IsTrigger(DIK_DOWN));
	bool right	 = (sKeys_->IsTrigger(DIK_D) || sKeys_->IsTrigger(DIK_RIGHT));

	// ステージ選択
	stageIdx += up + right - down - left;

	// SE
	if (TransitionManager::GetInstance()->IsFalling() == false)
	{
		if (up || right || left || down)
		{
			//pSelectSE_->Play(false);
		}
	}

	// ステージ番号設定
	stageConfig_->SetCurrentStageIndex(stageIdx);

	// 次のシーンへ (SPACE)
	if (sKeys_->IsTrigger(DIK_SPACE))
	{
		// SE
		//pDecisionSE_->Play(false);

		SceneExecutive::GetInstance()->Change("PLAY", "INFECTION", 5, 10);
		//SceneExecutive::GetInstance()->Change("DEMO", "INFECTION", 5, 10);
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

void SelectScene::Draw()
{
	// 描画
	dra_.Draw();

	// input描画
	inputDra_.Draw();

	// pause描画
	pauseDra_.Draw();


	// パーティクル描画
	particleMan_.Draw();
}
#pragma endregion
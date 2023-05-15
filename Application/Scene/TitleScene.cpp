#include "TitleScene.h"
#include "SceneExecutive.h"
#include "CoreColor.h"
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
	// ----- オーディオ ----- //

	// タイトルBGM
	pTitleBGM_ = Audio::Load("BGM/select.wav");


	//// セレクトSE
	//pSelectSE_ = Audio::Load("SE/select.wav");

	//// 決定SE
	//pDecisionSE_ = Audio::Load("SE/decision.wav");

	// ----- 静的初期化 ----- //

	// パーティクル
	ParticleManager::StaticInitialize(&transferVP_);

	// 核色
	CoreColor::StaticInitialize();
	// 背景
	BackgroundDrawerCommon::StaticInitialize(&transferVP_, &particleMan_);

	// 入力
	InputDrawerCommon::StaticInitialize();
	
	// タイトル
	TitleDrawerCommon::StaticInitialize();
}
#pragma endregion


#pragma region 初期化
void TitleScene::Initialize()
{
	// パーティクル初期化
	particleMan_.Initialize();

	// 背景初期化
	background_.Initialize();

	// 入力描画初期化
	inputDra_.Initialize();

	// タイトル描画初期化
	titleDra_.Initialize();

	// タイトルBGM開始
	pTitleBGM_->Play(true);
}
#pragma endregion

#pragma region 終了処理
void TitleScene::Finalize()
{
	// タイトルBGM停止
	pTitleBGM_->Stop();
}
#pragma endregion

#pragma region 更新
void TitleScene::Update()
{
	// 入力描画静的更新
	InputDrawerCommon::StaticUpdate();

	// 入力描画更新
	inputDra_.Update();

	// キー取得
	bool up		 = (sKeys_->IsTrigger(DIK_W) || sKeys_->IsTrigger(DIK_UP));
	bool left	 = (sKeys_->IsTrigger(DIK_A) || sKeys_->IsTrigger(DIK_LEFT));
	bool down	 = (sKeys_->IsTrigger(DIK_S) || sKeys_->IsTrigger(DIK_DOWN));
	bool right	 = (sKeys_->IsTrigger(DIK_D) || sKeys_->IsTrigger(DIK_RIGHT));

	// 選択変更
	titleDra_.Select(up || right, left || down);

	// SE
	if (TransitionManager::GetInstance()->IsFalling() == false)
	{
		if (up || right || left || down)
		{
			//pSelectSE_->Play(false);
		}
	}

	// 選択更新
	titleDra_.Update();

	// 背景更新
	background_.Update();

	// 核色静的更新
	CoreColor::StaticUpdate();
	// 背景静的更新
	BackgroundDrawerCommon::StaticUpdate();

	// パーティクル更新
	particleMan_.Update();

	// 次のシーンへ
	if (sKeys_->IsTrigger(DIK_SPACE))
	{
		// Startなら
		if (titleDra_.GetSelection() == TitleDrawerCommon::Selection::Start)
		{
			// SE
			//pDecisionSE_->Play(false);

			// セレクトシーンへ
			SceneExecutive::GetInstance()->Change("SELECT", "INFECTION", 5, 10);
		}
		// Exitなら
		else if (titleDra_.GetSelection() == TitleDrawerCommon::Selection::Exit)
		{
			// 終了
			SceneManager::GetInstance()->SetEnd(true);
		}
	}
}
#pragma endregion


#pragma region 描画

void TitleScene::Draw()
{
	background_.Draw();

	titleDra_.Draw();

	inputDra_.Draw();
	
	particleMan_.Draw();
}
#pragma endregion
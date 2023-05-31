#include "TitleScene.h"
#include "SceneExecutive.h"
#include "CoreColor.h"
#include "Def.h"
#include <cassert>

#include "MouseCollider.h"
#include "AudioConfig.h"

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
	pTitleBGM_ = Audio::Load("BGM/title.wav");
	pTitleBGM_->SetVolume(AudioConfig::BGM::Title);

	// セレクトSE
	pSelectSE_ = Audio::Load("SE/SE_select.wav");
	pSelectSE_->SetVolume(AudioConfig::SE::Select);

	// 決定SE
	pDecisionSE_ = Audio::Load("SE/SE_decision.wav");
	pDecisionSE_->SetVolume(AudioConfig::SE::Decition);

	// ----- 静的初期化 ----- //

	// マウスコライダー静的初期化
	MouseColliderCommon::StaticInitialize();

	// マウスコライダーにビュープロジェクション設定
	MouseColliderCommon::StaticSetViewProjectionPointer(&transferVP_);

	// パーティクル
	ParticleManager::StaticInitialize(&transferVP_);

	// 核色
	CoreColor::StaticInitialize();
	
	// 基底描画クラス
	IDrawer::StaticInitialize(&transferVP_, nullptr, nullptr, &camera_, &particleMan_);
	
	// 背景
	BackgroundDrawerCommon::StaticInitialize(&particleMan_);

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
	// マウスコライダー静的更新
	MouseColliderCommon::StaticUpdate();

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
			pSelectSE_->Stop();
			pSelectSE_->Play(false);
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
			pDecisionSE_->Stop();
			pDecisionSE_->Play(false);

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
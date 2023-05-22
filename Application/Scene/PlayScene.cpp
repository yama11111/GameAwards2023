#include "PlayScene.h"
#include "SceneExecutive.h"
#include "MathUtillity.h"
#include "CalcTransform.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>
#include "Sign.h"

#include "DrawerHelper.h"

#pragma region 名前空間宣言

using YScene::PlayScene;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;
using Sign = maruyama::Sign;

#pragma endregion 


#pragma region Static関連

#pragma endregion 


#pragma region 読み込み

void PlayScene::Load()
{
	// ----- オーディオ ----- //

	// プレイBGM
	pPlayBGM_ = Audio::Load("BGM/select.wav");

	// ----- 静的初期化 ----- //

	// パーティクル
	ParticleManager::StaticInitialize(&transferVP_);

	// 描画クラス全て
	DrawerHelper::StaticInitialize(&transferVP_, &camera_, &particleMan_);
}

#pragma endregion


#pragma region 初期化

void PlayScene::Initialize()
{
	// パーティクル初期化
	particleMan_.Initialize();

    tp_.Initialize();
    tp_.transform_.pos_ = { 4,-4,0 };

	// ステージ番号
	uint32_t stageIdx = static_cast<uint32_t>(StageConfig::GetInstance()->GetCurrentStageIndex());

	sign_.Initialize({ 10,20 });
    sign_.ReWriteBlock(7, 18, Sign::BlockType::SPRING);
    sign_.ReWriteBlock(8, 17, Sign::BlockType::BASIC);

	// 背景初期化
	background_.Initialize();

	// HUD初期化
	hud_.Initialize();

	// カメラ
	camera_.Initialize({ 0.0f,0.0f,-300.0f }, {});

	// ビュープロジェクション初期化
	transferVP_.Initialize();

	// プレイBGM開始
	pPlayBGM_->Play(true);
	transferVP_.Initialize();
}

#pragma endregion


#pragma region 終了処理

void PlayScene::Finalize()
{
	// プレイBGM停止
	pPlayBGM_->Stop();
}

#pragma endregion


#pragma region 更新

void PlayScene::Update()
{
	// 入力描画静的更新
	InputDrawerCommon::StaticUpdate();

	// HUD更新
	hud_.Update();

	// ポーズ中なら弾く
	if (hud_.IsElderPause()) { return; }

	// ------------ ↓ プレイシーンの処理 ↓ ------------//

    if (sKeys_->IsDown(DIK_LSHIFT)) {
        if (sKeys_->IsDown(DIK_W)) camera_.pos_.y_ += 5;
        if (sKeys_->IsDown(DIK_S)) camera_.pos_.y_ -= 5;
        if (sKeys_->IsDown(DIK_A)) camera_.pos_.x_ -= 5;
        if (sKeys_->IsDown(DIK_D)) camera_.pos_.x_ += 5;
        if (sKeys_->IsDown(DIK_UP)) camera_.pos_.z_ += 5;
        if (sKeys_->IsDown(DIK_DOWN)) camera_.pos_.z_ -= 5;
    }

	sign_.Update();
    tp_.Update();

    sign_.PPC(&tp_);

	//リセット
	//if (リセットするなら)
	//{
	//	// シーンまるごとリセット
	//	SceneExecutive::GetInstance()->Change("PLAY", "INFECTION", 5, 10);
	//}

	//ゴール判定
	//if (ゴールしたら)
	//{
	//	StageConfig::GetInstance()->ClearStage(StageConfig::GetInstance()->GetCurrentStageIndex() - 1);
	//	// セレクトシーンに行く
	//	SceneExecutive::GetInstance()->Change("SELECT", "INFECTION", 5, 10);
	//}

	// ------------ ↑ プレイシーンの処理 ↑ ------------//

	// 背景更新
	background_.Update();

	// DrawerHelper更新
	DrawerHelper::StaticUpdate();


	// パーティクル更新
	particleMan_.Update();


	// カメラ更新
	camera_.Update();

	// ビュープロジェクションにカメラ代入
	transferVP_ = camera_.GetViewProjection();

	// ビュープロジェクション
	transferVP_.UpdateMatrix();


}
#pragma endregion


#pragma region 描画

void PlayScene::Draw()
{
    tp_.Draw();

	// 背景描画
	background_.Draw();

	sign_.Draw();

	// HUD描画
	hud_.Draw();

	// パーティクル
	particleMan_.Draw();
}

#pragma endregion
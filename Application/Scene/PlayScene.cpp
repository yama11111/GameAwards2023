#include "PlayScene.h"
#include "SceneExecutive.h"
#include "MathUtillity.h"
#include "CalcTransform.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#include "DrawerHelper.h"

#pragma region 名前空間宣言

using YScene::PlayScene;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;

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


	// ステージ番号
	uint32_t stageIdx = static_cast<uint32_t>(StageConfig::GetInstance()->GetCurrentStageIndex());

	

	// 背景初期化
	background_.Initialize();

	// HUD初期化
	hud_.Initialize();


	// カメラ
	camera_.Initialize({ +0.0f,0.0f,-1000.0f }, {});

	// ビュープロジェクション初期化
	transferVP_.Initialize({});

    // ビュープロジェクションにカメラ代入
    transferVP_ = camera_.GetViewProjection();
    // ビュープロジェクション
    transferVP_.UpdateMatrix();

	// プレイBGM開始
	pPlayBGM_->Play(true);

    piecePtr_ = new Piece{ {-200,10},{5,5} };
    piecePtr_->RegisterTab(true, 4);
    piecePtr_->RegisterTab(true, 18);
    piecePtr_->RegisterTab(true, 27);
    piecePtr_->RegisterTab(true, 35);
    piecePtr_->RegisterTab(true, 43);
    piecePtr_->RegisterBlock(new BasicBlock{ Vector2{},Vector2{} }, Vector2{ -12,-20 }, Vector2{ 60,2 });
    piecePtr_->RegisterBlock(new BasicBlock{ Vector2{},Vector2{} }, Vector2{ -12,70 }, Vector2{ 60,2 });
    piecePtr_->RegisterBlock(new SpringBlock{ Vector2{},Vector2{} }, Vector2{ 50,-120 }, Vector2{ 8,8 });
    piecePtr_->SetFixity(true);
    piecePtr_->SetState(Piece::State::ROOT);
    stage_.AddPiece(piecePtr_);

    piece2Ptr_ = new Piece{ {150,200},{3,3} };
    piece2Ptr_->RegisterTab(false, 4);
    piece2Ptr_->RegisterTab(false, 10);
    piece2Ptr_->RegisterTab(false, 14);
    piece2Ptr_->RegisterTab(false, 20);
    piece2Ptr_->RegisterTab(false, 26);
    piece2Ptr_->RegisterBlock(new BasicBlock{ Vector2{},Vector2{} }, Vector2{ -80,60 }, Vector2{ 30,2 });
    piece2Ptr_->RegisterBlock(new BasicBlock{ Vector2{},Vector2{} }, Vector2{ -50,10 }, Vector2{ 20,2 });
    piece2Ptr_->RegisterBlock(new BasicBlock{ Vector2{},Vector2{} }, Vector2{ -10, -60 }, Vector2{ 60,2 });
    piece2Ptr_->RegisterBlock(new WoodenBlock{ Vector2{},Vector2{} }, Vector2{ 50,-30 }, Vector2{ 8,8 });
    stage_.AddPiece(piece2Ptr_);

    piece3Ptr_ = new Piece{ {400,0},{2,6} };
    piece3Ptr_->RegisterTab(false, 0);
    piece3Ptr_->RegisterTab(true, 9);
    piece3Ptr_->RegisterTab(false, 15);
    piece3Ptr_->RegisterTab(true, 26);
    piece3Ptr_->RegisterBlock(new BasicBlock{ Vector2{},Vector2{} }, Vector2{ 20,15 }, Vector2{ 2,60 });
    piece3Ptr_->RegisterBlock(new BasicBlock{ Vector2{},Vector2{} }, Vector2{ -20,-35 }, Vector2{ 60,2 });
    stage_.AddPiece(piece3Ptr_);

    player_ = std::make_unique<Player>(&stage_);
    player_->SetPos(Vector2{ -100,0 });
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

	//リセット
	//if (リセットするなら)
	//{
	//	// シーンまるごとリセット
	//	SceneExecutive::GetInstance()->Change("PLAY", "INFECTION", 5, 10);
	//}

    stage_.Update();
    player_->Update();
    stage_.DrawDebug();
    player_->DrawDebug();

	//ゴール判定
	if (stage_.GetIsGoal())
	{
		StageConfig::GetInstance()->ClearStage(StageConfig::GetInstance()->GetCurrentStageIndex() - 1);
		// セレクトシーンに行く
		SceneExecutive::GetInstance()->Change("SELECT", "INFECTION", 5, 10);
	}
	
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
	// 背景描画
	//background_.Draw();

    // game描画
    stage_.Draw();
    player_->Draw();

	// HUD描画
	//hud_.Draw();

	// パーティクル
	//particleMan_.Draw();
}

#pragma endregion
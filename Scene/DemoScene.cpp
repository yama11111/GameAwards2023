#include "DemoScene.h"
#include "DrawerHelper.h"
#include "StageConfig.h"

#pragma region 名前空間宣言

using YScene::DemoScene;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;

#pragma endregion 


#pragma region Static関連
#pragma endregion 


#pragma region 読み込み

void DemoScene::Load()
{
	// パーティクル
	ParticleManager::StaticInitialize(&transferVP_);

	// 描画クラス全て
	DrawerHelper::StaticInitialize(&transferVP_, &camera_, &particleMan_);

	// プレイヤー
	DemoPlayer::StaticInitialize();

	// マップチップ
	mapChipMan_.Load();
}

#pragma endregion


#pragma region 初期化

void DemoScene::Initialize()
{
	// パーティクル初期化
	particleMan_.Initialize();


	// ステージ番号
	uint32_t stageIdx = static_cast<uint32_t>(StageConfig::GetInstance()->GetCurrentStageIndex());

	// マップチップマネージャー初期化
	mapChipMan_.Initialize({ 0, {}, {1.0f,1.0f,1.0f} });

	
	// プレイヤー初期化
	player_.Initialize({ +10.0f,-10.0f,0.0f });
	
	// マップチップ設定
	DemoPlayer::StaticSetMapChip(mapChipMan_.CurrentMapPointer());


	// ゴール
	goal_.Initialize({ +25.0f,-15.0f,0.0f });


	// 背景初期化
	background_.Initialize();

	// HUD初期化
	hud_.Initialize();

	
	// カメラ
	camera_.Initialize({ +17.0f,-11.0f,-21.0f }, {});

	// ビュープロジェクション初期化
	transferVP_.Initialize({});
}

#pragma endregion


#pragma region 終了処理

void DemoScene::Finalize()
{

}

#pragma endregion


#pragma region 更新

void DemoScene::Update()
{
	// HUD更新
	hud_.Update();

	// ポーズ中なら弾く
	if (hud_.IsElderPause()) { return; }

	// プレイヤー更新
	player_.Update();

	// ゴール
	goal_.Update();
	

	// マップチップ更新
	mapChipMan_.Update();


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


	////ゴール判定
	//if (BoxCollision(player->GetTransform(), goal_, false))
	//{
	//	SceneManager::GetInstance()->Change("SELECT", "INFECTION");
	//}

	////死亡判定
	//if (player->GetPos().y_ < -15)
	//{
	//	SceneManager::GetInstance()->Change("PLAY", "BLACKOUT");
	//}
}

#pragma endregion


#pragma region 描画

void DemoScene::DrawBackSprite2Ds()
{

}

void DemoScene::DrawModels()
{
	// 背景描画
	background_.Draw();


	// プレイヤー描画
	player_.Draw();

	// ゴール描画
	goal_.Draw();


	// マップチップ描画
	mapChipMan_.Draw();


	// パーティクル
	particleMan_.Draw();
}

void DemoScene::DrawSprite3Ds()
{

}

void DemoScene::DrawFrontSprite2Ds()
{
	// HUD描画
	hud_.Draw();
}

void DemoScene::Draw()
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
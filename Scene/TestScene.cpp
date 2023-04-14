#include "TestScene.h"
#include "SceneManager.h"
#include "MathUtillity.h"
#include "CalcTransform.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#include "DrawerManager.h"

#pragma region 名前空間宣言
using YScene::TestScene;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;
#pragma endregion 

#pragma region Static関連
#pragma endregion 

#pragma region 読み込み
void TestScene::Load()
{
	// ----- テクスチャ ----- //

	// ----- オーディオ ----- //

	// ----- スプライト (2D) ----- //

	// ----- スプライト (3D) ----- //

	// ------- モデル ------- //

	// ----- 静的初期化 ----- //

	// パーティクル
	ParticleManager::StaticInitialize(&transferVP_);

	// エフェクト
	EffectManager::StaticInitialize(&particleMan_);

	// 描画クラス全て
	DrawerManager::StaticInitialize(&transferVP_, &particleMan_);
}
#pragma endregion


#pragma region 初期化
void TestScene::Initialize()
{
	// 核初期化
	core_.Initialize({ {}, {}, {3.0f,3.0f,3.0f} });

	// プレイヤーで操作開始
	isPlayer_ = true;

	// プレイヤー描画用クラス初期化
	playerDra_.Initialize(&core_, &direction_, IDrawer::Mode::Normal);
	// 向き
	direction_ = { +1.0f,0.0f,0.0f };
	// プレイヤー描画するか
	isDrawPlayer_ = false;

	// フィルター描画用クラス初期化
	filterDra_.Initialize(&core_);
	// フィルター描画するか
	isDrawFilter_ = false;
	
	// ブロック描画用クラス初期化
	blockDra_.Initialize(&core_, IDrawer::Mode::Normal);
	// ブロック描画するか
	isDrawBlock_ = true;

	// ゲート描画用クラス初期化
	gateDra_.Initialize(&core_, IDrawer::Mode::Red);
	// ゲート描画するか
	isDrawGate_ = false;

	// ゴール描画用クラス初期化
	goalDra_.Initialize(&core_);
	// ゴール描画するか
	isDrawGoal_ = false;


	// 天球初期化
	skydome_.Initialize();
	// 天球描画するか
	isDrawSkydome_ = true;

	// HUD初期化
	hud_.Initalize();
	// HUD描画するか
	isDrawHUD_ = false;

	// パーティクル初期化
	particleMan_.Initialize();
	
	// エフェクト初期化
	effectMan_.Initialize();

	// スクロールカメラ
	scrollCamera_.Initialize({ 0,+10,-50 }, &core_.pos_, { 0.0f,0.0f,0.0f });

	// ビュープロジェクション初期化
	transferVP_.Initialize({});

}
#pragma endregion

#pragma region 終了処理
void TestScene::Finalize()
{

}
#pragma endregion

#pragma region 更新
void TestScene::Update()
{
	// 描画するか
	ImGui::Begin("isDraw");
	ImGui::Checkbox("Player", &isDrawPlayer_);
	ImGui::Checkbox("Filter", &isDrawFilter_);
	ImGui::Checkbox("Block", &isDrawBlock_);
	ImGui::Checkbox("Gate", &isDrawGate_);
	ImGui::Checkbox("Goal", &isDrawGoal_);
	ImGui::Checkbox("Skydome", &isDrawSkydome_);
	ImGui::Checkbox("HUD", &isDrawHUD_);
	ImGui::End();

	// HUD更新
	hud_.Update();

	// ポーズ中なら弾く
	if (hud_.IsPause()) { return; }


	// 操作切り替え
	if (sKeys_->IsTrigger(DIK_SPACE))
	{
		isPlayer_ = !isPlayer_;
		if (isPlayer_)
		{
			hud_.SetPilot(HUDDrawerCommon::Pilot::Player);
		}
		else
		{
			hud_.SetPilot(HUDDrawerCommon::Pilot::Filter);
		}
	}


	// プレイヤー
	if (sKeys_->IsTrigger(DIK_W))
	{
		playerDra_.JumpAnimation();
	}
	if (sKeys_->IsTrigger(DIK_S))
	{
		playerDra_.LandingAnimation();
	}
	if (sKeys_->IsTrigger(DIK_K))
	{
		playerDra_.ChangeColorAnimation(IDrawer::Mode::Normal);
	}
	if (sKeys_->IsTrigger(DIK_L))
	{
		playerDra_.ChangeColorAnimation(IDrawer::Mode::Red);
	}
	if (sKeys_->IsTrigger(DIK_N))
	{
		playerDra_.RespawnAnimation();
	}

	playerDra_.Update();


	// フィルター

	filterDra_.Update();

	
	// ブロック
	if (sKeys_->IsTrigger(DIK_N))
	{
		blockDra_.FadeInAnimation(40);
	}

	blockDra_.Update();

	
	// ゲート

	gateDra_.Update();

	
	// ゴール

	goalDra_.Update();

	
	// 天球更新
	skydome_.Update();

	// パーティクル更新
	particleMan_.Update();

	// エフェクト更新
	effectMan_.Update();

	// カメラ更新
	scrollCamera_.Update();

	// ビュープロジェクションにカメラ代入
	transferVP_ = scrollCamera_.GetViewProjection();

	// ビュープロジェクション
	transferVP_.UpdateMatrix();


	// 次のシーンへ
	if (sKeys_->IsTrigger(DIK_0))
	{
		SceneManager::GetInstance()->Change("RESULT", "INFECTION");
	}
}
#pragma endregion


#pragma region 描画
void TestScene::DrawBackSprite2Ds()
{

}

void TestScene::DrawModels()
{
	// 天球描画
	if (isDrawSkydome_) { skydome_.Draw(); }

	// ----- Pre ----- // 

	// プレイヤー前描画
	if (isDrawPlayer_) { playerDra_.PreDraw(); }

	// ブロック前描画
	if (isDrawBlock_) { blockDra_.Draw(); }
	
	// ゲート前描画
	if (isDrawGate_) { gateDra_.PreDraw(); }

	// ゴール描画
	if (isDrawGoal_) { goalDra_.Draw(); }


	// パーティクル
	particleMan_.Draw();

	// エフェクト
	effectMan_.Draw();

	// --------------- //


	// フィルター描画
	if (isDrawFilter_) { filterDra_.Draw(); }


	// ----- Post ----- //

	// プレイヤー後描画
	if (isDrawPlayer_) { playerDra_.PostDraw(); }

	// ゲート後描画
	if (isDrawGate_) { gateDra_.PostDraw(); }

	// --------------- //
}

void TestScene::DrawSprite3Ds()
{

}

void TestScene::DrawFrontSprite2Ds()
{
	// HUD描画
	if (isDrawHUD_) { hud_.Draw(); }
}

void TestScene::Draw()
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
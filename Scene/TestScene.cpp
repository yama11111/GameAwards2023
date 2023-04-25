#include "TestScene.h"
#include "SceneManager.h"
#include "MathUtillity.h"
#include "CalcTransform.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#include "DrawerHelper.h"

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
	DrawerHelper::StaticInitialize(&transferVP_, &camera_, &particleMan_);
}
#pragma endregion


#pragma region 初期化
void TestScene::Initialize()
{
	// パーティクル初期化
	particleMan_.Initialize();
	// パーティクル描画するか
	isDrawParticle_ = true;

	// エフェクト初期化
	effectMan_.Initialize();
	// エフェクト描画するか
	isDrawEffect_ = true;

	// 核初期化
	core_.Initialize({ {}, {}, {3.0f,3.0f,3.0f} });

	// プレイヤーで操作開始
	isPlayer_ = true;

	// プレイヤー描画用クラス初期化
	playerDra_.Initialize(&core_, &direction_);
	// 向き
	direction_ = { +1.0f,0.0f,0.0f };
	// プレイヤー描画するか
	isDrawPlayer_ = false;
	
	// ブロック描画用クラス初期化
	blockDra_.Initialize(&core_, IMode::Type::Normal);
	// ブロック描画するか
	isDrawBlock_ = false;

	// グリッド
	grid_.Initialize({ 0.0f,0.0f,-0.1f }, { 20.0f,20.0f,1.0f }, 6.0f);
	// グリッド描画するか
	isDrawGrid_ = false;

	// ゲート描画用クラス初期化
	gateDra_.Initialize(&core_);
	// ゲート描画するか
	isDrawGate_ = false;

	// ゴール描画用クラス初期化
	goalDra_.Initialize(&core_);
	// ゴール描画するか
	isDrawGoal_ = true;


	// 背景初期化
	background_.Initialize();
	// 背景描画するか
	isDrawBackground_ = true;

	// HUD初期化
	hud_.Initialize();
	// HUD描画するか
	isDrawHUD_ = false;


	// カメラ無し用
	noneVP_.Initialize({});

	// カメラ
	camera_.Initialize({ 0,0,-50 }, {});

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
	ImGui::Checkbox("Block", &isDrawBlock_);
	ImGui::Checkbox("Grid", &isDrawGrid_);
	ImGui::Checkbox("Gate", &isDrawGate_);
	ImGui::Checkbox("Goal", &isDrawGoal_);
	ImGui::Checkbox("Background", &isDrawBackground_);
	ImGui::Checkbox("HUD", &isDrawHUD_);
	ImGui::Checkbox("Particle", &isDrawParticle_);
	ImGui::Checkbox("Effect", &isDrawEffect_);
	ImGui::End();

#pragma region HUD

	// HUD更新
	hud_.Update();

	// ポーズ中なら弾く
	if (hud_.IsPause()) { return; }

#pragma endregion


#pragma region Object

	// プレイヤー
	if (sKeys_->IsTrigger(DIK_W))
	{
		playerDra_.JumpAnimation();
	}
	if (sKeys_->IsTrigger(DIK_S))
	{
		playerDra_.LandingAnimation();
	}
	if (sKeys_->IsTrigger(DIK_N))
	{
		playerDra_.RespawnAnimation();
	}

	playerDra_.Update();

	
	// ブロック
	if (isDrawBlock_)
	{
		ImGui::Begin("Block");
		
		ImGui::Text("---------------");
		
		if (ImGui::Button("Reset (Normal)"))
		{
			blockDra_.Reset(IMode::Type::Normal);
		}
		if (ImGui::Button("Reset (Movable)"))
		{
			blockDra_.Reset(IMode::Type::Movable);
		}

		ImGui::Text("---------------");

		if (ImGui::Button("Catch"))
		{
			blockDra_.CatchAnimation();
		}
		if (ImGui::Button("FailToCatch"))
		{
			blockDra_.FailToCatchAnimation();
		}

		ImGui::Checkbox("IsCanCatch", &isCanCatch_);
		blockDra_.SetIsCanCatch(isCanCatch_);

		ImGui::Text("---------------");

		if (ImGui::Button("Place"))
		{
			blockDra_.PlaceAnimation();
		}
		if (ImGui::Button("FailToPlace"))
		{
			blockDra_.FailToPlaceAnimation();
		}

		ImGui::Checkbox("IsCanPlace", &isCanPlace_);
		blockDra_.SetIsCanPlace(isCanPlace_);

		ImGui::End();
	}

	blockDra_.Update();

	// グリッド
	if (sKeys_->IsTrigger(DIK_N))
	{
		grid_.ActAlphaAnimation();
	}

	grid_.Update();
	
	// ゲート
	gateDra_.Update();

	
	// ゴール
	if (isDrawGoal_)
	{
		ImGui::Begin("Goal");
		if (ImGui::Button("Reset"))
		{
			// リセット
			goalDra_.Reset();
		}
		if (ImGui::Button("Clear"))
		{
			// クリア
			goalDra_.ActivateClearAnimation(Vector3(+20.0f, 0.0f, 0.0f));
		}
		ImGui::End();
	}

	goalDra_.Update();

	
	// 背景更新
	background_.Update();


	ImGui::Begin("DrawerHelper");
	if (ImGui::Button("Reset"))
	{
		// リセット
		DrawerHelper::StaticReset();
	}
	if(ImGui::Button("Clear"))
	{
		// クリア
		DrawerHelper::StaticClear();
	}
	ImGui::End();

	// 描画クラス静的更新
	DrawerHelper::StaticUpdate();

#pragma endregion


#pragma region Particle

	// パーティクル更新
	particleMan_.Update();

	// エフェクト更新
	effectMan_.Update();

#pragma endregion


#pragma region Camera

	// カメラ設定
	ImGui::Begin("CameraConfig");

	bool isChecks[3] = { false, false, false };

	if (cameraConfig_ == CameraConfig::None)
	{
		ImGui::Text("Current : None (%d)", static_cast<int>(CameraConfig::None));
		isChecks[0] = true;
	}
	else if (cameraConfig_ == CameraConfig::Camera1)
	{
		ImGui::Text("Current : Camera1 (%d)", static_cast<int>(CameraConfig::Camera1));
		isChecks[1] = true;
	}
	else if (cameraConfig_ == CameraConfig::ScrollCamera)
	{
		ImGui::Text("Current : ScrollCamera (%d)", static_cast<int>(CameraConfig::ScrollCamera));
		isChecks[2] = true;
	}

	if (ImGui::Checkbox("None", &isChecks[0])) { cameraConfig_ = CameraConfig::None; }
	if (ImGui::Checkbox("Camera1", &isChecks[1])) { cameraConfig_ = CameraConfig::Camera1; }
	if (ImGui::Checkbox("ScrollCamera", &isChecks[2])) { cameraConfig_ = CameraConfig::ScrollCamera; }

	ImGui::End();

	// カメラ無し用更新
	noneVP_.UpdateMatrix();

	// カメラ更新
	camera_.Update();
	
	// スクロールカメラ更新
	scrollCamera_.Update();
	
	// カメラ1なら
	if (cameraConfig_ == CameraConfig::None)
	{
		// ビュープロジェクションにカメラ代入
		transferVP_ = noneVP_;
	}
	else if (cameraConfig_ == CameraConfig::Camera1)
	{
		// ビュープロジェクションにカメラ代入
		transferVP_ = camera_.GetViewProjection();
	}
	// スクロールカメラなら
	else if (cameraConfig_ == CameraConfig::ScrollCamera)
	{
		// ビュープロジェクションにカメラ代入
		transferVP_ = scrollCamera_.GetViewProjection();
	}

	// ビュープロジェクション
	transferVP_.UpdateMatrix();

#pragma endregion


#pragma region SceneChange

	// 次のシーンへ
	if (sKeys_->IsTrigger(DIK_0))
	{
		SceneManager::GetInstance()->Change("RESULT", "INFECTION");
	}

#pragma endregion


}
#pragma endregion


#pragma region 描画
void TestScene::DrawBackSprite2Ds()
{

}

void TestScene::DrawModels()
{
	// 背景描画
	if (isDrawBackground_) { background_.Draw(); }

	// プレイヤー前描画
	if (isDrawPlayer_) { playerDra_.Draw(); }

	// ブロック前描画
	if (isDrawBlock_) { blockDra_.Draw(); }
	
	// グリッド描画
	if (isDrawGrid_) { grid_.Draw(); }

	// ゲート前描画
	if (isDrawGate_) { gateDra_.Draw(); }

	// ゴール描画
	if (isDrawGoal_) { goalDra_.Draw(); }

	// パーティクル
	if (isDrawParticle_) { particleMan_.Draw(); }

	// エフェクト
	if (isDrawEffect_) { effectMan_.Draw(); }
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
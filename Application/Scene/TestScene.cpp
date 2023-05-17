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

	// エフェクト初期化
	effectMan_.Initialize();
	
	// 核初期化
	core_.Initialize({ {}, {}, {3.0f,3.0f,3.0f} });


	// プレイヤー描画用クラス初期化
	playerDra_.Initialize(&core_, &direction_);
	// 向き
	direction_ = { +1.0f,0.0f,0.0f };
	
	// ブロック描画用クラス初期化
	blockDra_.Initialize(&core_, BlockDrawerCommon::Type::eWhite);

	// ばね描画用クラス初期化
	springDra_.Initialize(&core_, SpringDrawerCommon::Type::eGreen);
	
	// 接続部描画用クラス初期化
	junctionDra_.Initialize(&core_, Vector3(+1, +1, 0), JunctionDrawerCommon::Type::eGreen);

	// ゲート描画用クラス初期化
	gateDra_.Initialize(&core_);

	// ゴール描画用クラス初期化
	goalDra_.Initialize(&core_);


	// 背景初期化
	background_.Initialize();

	// HUD初期化
	hud_.Initialize();

	
	// パーティクル
	isDrawParticle_ = true;
	// エフェクト
	isDrawEffect_ = true;
	
	// プレイヤー
	isDrawPlayer_ = false;
	// ブロック
	isDrawBlock_ = false;
	// ばね
	isDrawSpring_ = false;
	// 接合部
	isDrawJunction_ = true;
	// ゲート
	isDrawGate_ = false;
	// ゴール
	isDrawGoal_ = true;
	// 背景
	isDrawBackground_ = true;
	// HUD
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
		
		if (ImGui::Button("Reset (White)"))
		{
			blockDra_.Reset(BlockDrawerCommon::Type::eWhite);
		}
		if (ImGui::Button("Reset (Red)"))
		{
			blockDra_.Reset(BlockDrawerCommon::Type::eBlack);
		}

		ImGui::End();
	}

	blockDra_.Update();


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
		//SceneManager::GetInstance()->Change("RESULT", "INFECTION");
	}

#pragma endregion


}

#pragma endregion


#pragma region 描画

void TestScene::Draw()
{
	// 背景描画
	if (isDrawBackground_) { background_.Draw(); }

	// プレイヤー前描画
	if (isDrawPlayer_) { playerDra_.Draw(); }

	// ブロック前描画
	if (isDrawBlock_) { blockDra_.Draw(); }

	// ゲート前描画
	if (isDrawGate_) { gateDra_.Draw(); }

	// ゴール描画
	if (isDrawGoal_) { goalDra_.Draw(); }

	// HUD描画
	if (isDrawHUD_) { hud_.Draw(); }
	
	// パーティクル
	if (isDrawParticle_) { particleMan_.Draw(); }

	// エフェクト
	if (isDrawEffect_) { effectMan_.Draw(); }
}

#pragma endregion
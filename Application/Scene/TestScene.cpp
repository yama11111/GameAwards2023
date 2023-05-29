#include "TestScene.h"
#include "SceneManager.h"
#include "MathUtillity.h"
#include "CalcTransform.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#include "DrawerHelper.h"
#include "MouseCollider.h"

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
	ParticleManager::StaticInitialize(&transferVP_);

	// 描画クラス全て
	DrawerHelper::StaticInitialize(&transferVP_, &camera_, &particleMan_);
}

#pragma endregion


#pragma region 初期化

void TestScene::Initialize()
{
	// パーティクル初期化
	particleMan_.Initialize();


	// 大きさ
	Vector3 scale = { 5.0f,5.0f,5.0f };
	
	// 核初期化
	core_.Initialize({ {}, {}, scale });


	// プレイヤー描画用クラス初期化
	playerDra_.Initialize(&core_, &direction_);
	// 向き
	direction_ = { +1.0f,0.0f,0.0f };
	
	// ブロック描画用クラス初期化
	blockDra_.Initialize(&core_, BlockDrawerCommon::Type::eWhite);

	// ばね描画用クラス初期化
	springDra_.Initialize(&core_);
	
	// 足場描画用クラス初期化
	platform_.Initialize({ {},{},Vector3(26.0f, 2.0f, 2.0f) });
	platformDra_.Initialize(&platform_);
	
	// 接続部描画用クラス初期化
	junctions_[0].Initialize({ {-20.0f,+10.0f,0.0f},{},scale });
	junctions_[1].Initialize({ {+20.0f,-10.0f,0.0f},{},scale });
	junctionDras_[0].Initialize(&junctions_[0], Vector3(0, -1, 0), JunctionDrawerCommon::Type::eGreen);
	junctionDras_[1].Initialize(&junctions_[1], Vector3(-1, 0, 0), JunctionDrawerCommon::Type::eGreen);

	// レーザー描画用クラス初期化
	length_ = 3.0f;
	laserDra_.Initialize(&core_, &length_);

	// 鍵描画用クラス初期化
	keyDra_.Initialize(&core_);

	// スイッチ描画用クラス初期化
	switchDra_.Initialize(&core_, SwitchDrawerCommon::Type::eBlue);

	// ゲート描画用クラス初期化
	gateDra_.Initialize(&core_);

	// ゴール描画用クラス初期化
	goalDra_.Initialize(&core_, false);


	// 背景初期化
	background_.Initialize();

	// HUD初期化
	hud_.Initialize();

	
	// パーティクル
	isDrawParticle_ = true;
	
	// プレイヤー
	isDrawPlayer_ = false;
	// ブロック
	isDrawBlock_ = true;
	// 足場
	isDrawPlatform_ = false;
	// ばね
	isDrawSpring_ = false;
	// 接合部
	isDrawJunction_ = false;
	// 接合部
	isDrawLaser_ = false;
	// ゲート
	isDrawGate_ = false;
	// 鍵
	isDrawKey_ = false;
	// スイッチ
	isDrawSwitch_ = false;
	// ゴール
	isDrawGoal_ = false;
	// 背景
	isDrawBackground_ = true;
	// HUD
	isDrawHUD_ = false;


	// カメラ無し用
	noneVP_.Initialize();

	// カメラ
	camera_.Initialize({ 0,0,-50 }, {});

	// スクロールカメラ
	scrollCamera_.Initialize({ 0,+10,-50 }, &core_.pos_, { 0.0f,0.0f,0.0f });

	// ビュープロジェクション初期化
	transferVP_.Initialize();
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
	ImGui::Checkbox("Platform", &isDrawPlatform_);
	ImGui::Checkbox("Spring", &isDrawSpring_);
	ImGui::Checkbox("Junction", &isDrawJunction_);
	ImGui::Checkbox("Laser", &isDrawLaser_);
	ImGui::Checkbox("Key", &isDrawKey_);
	ImGui::Checkbox("Switch", &isDrawSwitch_);
	ImGui::Checkbox("Gate", &isDrawGate_);
	ImGui::Checkbox("Goal", &isDrawGoal_);
	ImGui::Checkbox("Background", &isDrawBackground_);
	ImGui::Checkbox("HUD", &isDrawHUD_);
	ImGui::Checkbox("Particle", &isDrawParticle_);
	
	ImGui::End();

#pragma region HUD

	// HUD更新
	hud_.Update();

	// ポーズ中なら弾く
	if (hud_.IsPause()) { return; }

#pragma endregion


#pragma region Object


#pragma region Player

	// プレイヤー
	if (isDrawPlayer_)
	{
		ImGui::Begin("Player");

		ImGui::Text("---------------");

		if (ImGui::Button("Reset"))
		{
			// リセット
			playerDra_.Reset();
		}

		ImGui::Text("---------------");

		if (ImGui::Button("Jump"))
		{
			playerDra_.JumpAnimation();
		}
		if (ImGui::Button("Landing"))
		{
			playerDra_.LandingAnimation();
		}
		if (ImGui::Button("Respawn"))
		{
			playerDra_.RespawnAnimation();
		}

		ImGui::End();
	}

	playerDra_.Update();

#pragma endregion
	

#pragma region Block

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

#pragma endregion


#pragma region Spring

	// ばね
	if (isDrawSpring_)
	{
		ImGui::Begin("Spring");

		ImGui::Text("---------------");

		if (ImGui::Button("Reset"))
		{
			// リセット
			springDra_.Reset();
		}

		ImGui::Text("---------------");

		if (ImGui::Button("Jump"))
		{
			// ジャンプアニメーション
			springDra_.AnimateJump();
		}

		ImGui::End();
	}

	springDra_.Update();

#pragma endregion


#pragma region Platform

	// 足場
	if (isDrawPlatform_)
	{
		ImGui::Begin("Platform");

		ImGui::Text("---------------");

		if (ImGui::Button("Reset"))
		{
			// リセット
			platformDra_.Reset();
		}

		ImGui::Text("---------------");

		ImGui::SliderFloat("Width", &platform_.scale_.x_, 1.0f, 24.0f);


		ImGui::End();
	}

	platform_.UpdateMatrix();
	platformDra_.Update();

#pragma endregion


#pragma region Junction

	// 接合部
	if (isDrawJunction_)
	{
		ImGui::Begin("Junction");

		ImGui::Text("---------------");

		if (ImGui::Button("Reset"))
		{
			// リセット
			junctionDras_[0].Reset(Vector3(0, -1, 0), JunctionDrawerCommon::Type::eGreen);
			junctionDras_[1].Reset(Vector3(-1, 0, 0), JunctionDrawerCommon::Type::eGreen);
		}

		ImGui::Text("---------------");

		if (ImGui::Button("Connection"))
		{
			// 接続
			junctionDras_[0].AnimateConnection(&junctionDras_[1]);
			junctionDras_[1].AnimateConnection(&junctionDras_[0]);
		}

		ImGui::End();
	}

	junctionDras_[0].Update();
	junctionDras_[1].Update();

#pragma endregion


#pragma region Laser

	// レーザー
	if (isDrawLaser_)
	{
		ImGui::Begin("Laser");

		ImGui::Text("---------------");

		if (ImGui::Button("Reset"))
		{
			// リセット
			laserDra_.Reset();
		}

		ImGui::Text("---------------");

		if (ImGui::Button("Shoot"))
		{
			laserDra_.AnimateShoot();
		}

		ImGui::End();
	}

	laserDra_.Update();

#pragma endregion


#pragma region Key

	// 鍵
	if (isDrawKey_)
	{
		ImGui::Begin("Key");

		ImGui::Text("---------------");

		if (ImGui::Button("Reset"))
		{
			// リセット
			keyDra_.Reset();
		}

		ImGui::End();
	}

	keyDra_.Update();

#pragma endregion


#pragma region Switch

	// スイッチ
	if (isDrawSwitch_)
	{
		ImGui::Begin("Swicth");

		ImGui::Text("---------------");

		if (ImGui::Button("Reset"))
		{
			// リセット
			switchDra_.Reset(SwitchDrawerCommon::Type::eBlue);
		}

		ImGui::Text("---------------");

		if (ImGui::Button("SwitchOn"))
		{
			// スイッチオン
			switchDra_.AnimateSwitch(true);
		}
		if (ImGui::Button("SwitchOff"))
		{
			// スイッチオフ
			switchDra_.AnimateSwitch(false);
		}

		ImGui::End();
	}

	switchDra_.Update();

#pragma endregion


#pragma region Gate

	// ゲート
	if (isDrawGate_)
	{
		ImGui::Begin("Gate");

		ImGui::Text("---------------");

		if (ImGui::Button("Reset"))
		{
			// リセット
			gateDra_.Reset();
		}
		ImGui::End();
	}

	gateDra_.Update();

#pragma endregion

	
#pragma region Goal

	// ゴール
	if (isDrawGoal_)
	{
		ImGui::Begin("Goal");

		ImGui::Text("---------------");

		if (ImGui::Button("Reset"))
		{
			// リセット
			goalDra_.Reset(false);
		}
		if (ImGui::Button("Reset (Rock)"))
		{
			// リセット
			goalDra_.Reset(true);
		}
		if (ImGui::Button("Clear"))
		{
			// クリア
			goalDra_.ActivateClearAnimation(Vector3(+20.0f, 0.0f, 0.0f));
		}
		ImGui::End();
	}

	goalDra_.Update();

#pragma endregion


#pragma region Background

	// 背景
	if (isDrawBackground_)
	{
		ImGui::Begin("Background");

		ImGui::Text("---------------");

		if (ImGui::Button("Reset"))
		{
			// リセット
			background_.Reset();
		}
		ImGui::End();
	}

	background_.Update();

#pragma endregion


	ImGui::Begin("DrawerHelper");

	ImGui::Text("---------------");

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

	// プレイヤー描画
	if (isDrawPlayer_) { playerDra_.Draw(); }

	// ブロック描画
	if (isDrawBlock_) { blockDra_.Draw(); }

	// ばね描画
	if (isDrawSpring_) { springDra_.Draw(); }

	// 接合部描画
	if (isDrawJunction_) 
	{
		junctionDras_[0].Draw();
		junctionDras_[1].Draw();
	}

	// レーザー描画
	if (isDrawLaser_) { laserDra_.Draw(); }

	// 鍵描画
	if (isDrawKey_) { keyDra_.Draw(); }

	// スイッチ描画
	if (isDrawSwitch_) { switchDra_.Draw(); }

	// ゲート前描画
	if (isDrawGate_) { gateDra_.Draw(); }

	// ゴール描画
	if (isDrawGoal_) { goalDra_.Draw(); }

	// HUD描画
	if (isDrawHUD_) { hud_.Draw(); }
	
	// パーティクル
	if (isDrawParticle_) { particleMan_.Draw(); }

	// 足場描画
	if (isDrawPlatform_) { platformDra_.Draw(); }
}

#pragma endregion
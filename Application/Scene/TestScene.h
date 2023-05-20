#pragma once
#include "BaseScene.h"

#include "PlayerDrawer.h"
#include "BlockDrawer.h"
#include "SpringDrawer.h"
#include "JunctionDrawer.h"
#include "PlatformDrawer.h"
#include "LaserDrawer.h"
#include "KeyDrawer.h"
#include "SwitchDrawer.h"
#include "GateDrawer.h"
#include "GoalDrawer.h"

#include "BackgroundDrawer.h"
#include "HUDDrawer.h"

#include "ScrollCamera.h"

#include "Player.h"
#include "Block.h"


namespace YScene
{
	// テストシーン
	class TestScene : public BaseScene
	{

	private:

#pragma region リソース

#pragma endregion


#pragma region ゲームオブジェクト		

		// プレイヤー
		Player player_;

		// ブロック
		Block block_;


		// 核
		YGame::Transform core_;


#pragma region Player

		// プレイヤー描画クラス
		PlayerDrawer playerDra_;
		
		// 向き (プレイヤー用)
		YMath::Vector3 direction_;
		
		// プレイヤー描画するか
		bool isDrawPlayer_ = false;

#pragma endregion


#pragma region Block

		// ブロック描画クラス
		BlockDrawer blockDra_;
		
		// ブロック描画するか
		bool isDrawBlock_ = false;

#pragma endregion


#pragma region Sping

		// ばね描画クラス
		SpringDrawer springDra_;

		// ばね描画するか
		bool isDrawSpring_ = false;

#pragma endregion


#pragma region Platform

		// 核
		YGame::Transform platform_;

		// 足場描画クラス
		PlatformDrawer platformDra_;

		// 足場描画するか
		bool isDrawPlatform_ = false;

#pragma endregion


#pragma region Junction

		// 核
		std::array<YGame::Transform, 2> junctions_;

		// 接合部描画クラス
		std::array<JunctionDrawer, 2> junctionDras_;
		
		// 接続部描画するか
		bool isDrawJunction_ = false;

#pragma endregion


#pragma region Laser

		// 核
		YGame::Transform laser_;
		
		// 長さ
		float length_ = 0.0f;

		// レーザー描画クラス
		LaserDrawer laserDra_;

		// レーザー描画するか
		bool isDrawLaser_ = false;

#pragma endregion


#pragma region Key

		// 鍵描画クラス
		KeyDrawer keyDra_;

		// 鍵描画するか
		bool isDrawKey_ = false;

#pragma endregion


#pragma region Switch

		// スイッチ描画クラス
		SwitchDrawer switchDra_;

		// スイッチ描画するか
		bool isDrawSwitch_ = false;

#pragma endregion


#pragma region Gate

		// ゲート描画クラス
		GateDrawer gateDra_;
		
		// ゲート描画するか
		bool isDrawGate_ = false;

#pragma endregion


#pragma region Goal

		// ゴール描画クラス
		GoalDrawer goalDra_;
		
		// ゴール描画するか
		bool isDrawGoal_ = false;

#pragma endregion


#pragma region BackGround

		// 背景
		BackgroundDrawer background_;
		
		// 背景描画するか
		bool isDrawBackground_ = false;

#pragma endregion


		// HUD
		HUDDrawer hud_;
		
		// HUD描画するか
		bool isDrawHUD_ = false;


		// パーティクルマネージャー
		YGame::ParticleManager particleMan_;
		
		// パーティクル描画するか
		bool isDrawParticle_ = false;


		// カメラ設定
		enum class CameraConfig
		{
			None,
			Camera1,
			ScrollCamera,
		};

		// カメラ設定
		CameraConfig cameraConfig_ = CameraConfig::None;

		// カメラ無し用
		YGame::ViewProjection noneVP_;
		
		// カメラ
		YGame::Camera camera_;
		
		// スクロールカメラ
		YGame::ScrollCamera scrollCamera_;

		// 転送用ビュープロジェクション
		YGame::ViewProjection transferVP_;

#pragma endregion

	public:

		/// <summary>
		/// 読み込み
		/// </summary>
		void Load() override;

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize() override;

		/// <summary>
		/// 終了処理
		/// </summary>
		void Finalize() override;

		/// <summary>
		/// 更新
		/// </summary>
		void Update() override;

		/// <summary>
		/// 描画
		/// </summary>
		void Draw() override;

	public:

		// コンストラクタ
		TestScene() = default;
		
		// デストラクタ
		~TestScene() = default;

	};
}

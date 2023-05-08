#pragma once
#include "BaseScene.h"

#include "PlayerDrawer.h"
#include "BlockDrawer.h"
#include "GateDrawer.h"
#include "GoalDrawer.h"

#include "BackgroundDrawer.h"
#include "HUDDrawer.h"

#include "EffectManager.h"
#include "ScrollCamera.h"


namespace YScene
{
	// テストシーン
	class TestScene : public BaseScene
	{

	private:

#pragma region リソース

#pragma endregion


#pragma region ゲームオブジェクト		

		// 核
		YGame::Transform core_;

		// プレイヤーか
		bool isPlayer_ = false;

		// プレイヤー描画クラス
		PlayerDrawer playerDra_;
		// 向き (プレイヤー用)
		YMath::Vector3 direction_;
		// プレイヤー描画するか
		bool isDrawPlayer_ = false;

		// ブロック描画クラス
		BlockDrawer blockDra_;
		// ブロック描画するか
		bool isDrawBlock_ = false;
		// アニメーション用フラグ
		bool isCanCatch_ = false;
		bool isCanPlace_ = false;

		// ゲート描画クラス
		GateDrawer gateDra_;
		// ゲート描画するか
		bool isDrawGate_ = false;

		// ゴール描画クラス
		GoalDrawer goalDra_;
		// ゴール描画するか
		bool isDrawGoal_ = false;


		// 背景
		BackgroundDrawer background_;
		// 背景描画するか
		bool isDrawBackground_ = false;

		// HUD
		HUDDrawer hud_;
		// HUD描画するか
		bool isDrawHUD_ = false;


		// パーティクルマネージャー
		YGame::ParticleManager particleMan_;
		// パーティクル描画するか
		bool isDrawParticle_ = false;

		// エフェクトマネージャー
		YGame::EffectManager effectMan_;
		// エフェクト描画するか
		bool isDrawEffect_ = false;


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

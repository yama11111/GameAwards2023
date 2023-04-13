#pragma once
#include "BaseScene.h"

#include "PlayerDrawer.h"
#include "FilterDrawer.h"
#include "BlockDrawer.h"
#include "GateDrawer.h"
#include "GoalDrawer.h"

#include "Skydome.h"
#include "HUDDrawer.h"

#include "EffectManager.h"
#include "ScrollCamera.h"

namespace YScene
{
	// テストシーン
	class TestScene : public BaseScene
	{
	public:

#pragma region リソース

		// ----- テクスチャ ----- //

		// ----- オーディオ ----- //

		// ----- スプライト (2D) ----- //

		// ----- スプライト (3D) ----- //

		// ----- モデル ----- //

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

		// フィルター描画クラス
		FilterDrawer filterDra_;
		// フィルター描画するか
		bool isDrawFilter_ = false;

		// ブロック描画クラス
		BlockDrawer blockDra_;
		// ブロック描画するか
		bool isDrawBlock_ = false;

		// ゲート描画クラス
		GateDrawer gateDra_;
		// ゲート描画するか
		bool isDrawGate_ = false;

		// ゴール描画クラス
		GoalDrawer goalDra_;
		// ゴール描画するか
		bool isDrawGoal_ = false;

		// 天球
		Skydome skydome_;
		// 天球描画するか
		bool isDrawSkydome_ = false;

		// HUD
		HUDDrawer hud_;
		// HUD描画するか
		bool isDrawHUD_ = false;

		// パーティクルマネージャー
		YGame::ParticleManager particleMan_;

		// エフェクトマネージャー
		YGame::EffectManager effectMan_;

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

	private:

		/// <summary>
		/// 背景スプライト2D描画
		/// </summary>
		void DrawBackSprite2Ds();

		/// <summary>
		/// モデル描画
		/// </summary>
		void DrawModels();

		/// <summary>
		/// スプライト3D描画
		/// </summary>
		void DrawSprite3Ds();

		/// <summary>
		/// 前景スプライト2D描画
		/// </summary>
		void DrawFrontSprite2Ds();

	public:

		// コンストラクタ
		TestScene() = default;
		
		// デストラクタ
		~TestScene() = default;

	};
}

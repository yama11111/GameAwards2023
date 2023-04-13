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
	// ゲームシーン
	class PlayScene : public BaseScene
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

		// プレイヤー操作か
		bool isPlayer_ = true;
		

		// プレイヤー
		YGame::Transform player_;
		// 向き (プレイヤー用)
		YMath::Vector3 direction_;
		// プレイヤー描画クラス
		PlayerDrawer playerDra_;
		// スピード
		YMath::Vector3 playerSpeed_{};


		// フィルター
		YGame::Transform filter_;
		// フィルター描画クラス
		FilterDrawer filterDra_;


		// ブロック個数
		static const size_t idx = 20;
		// ブロック
		std::array<YGame::Transform, idx> block_;
		// ブロック描画クラス
		std::array<BlockDrawer, idx> blockDra_;


		// ゲート
		YGame::Transform gate_;
		// ゲート描画クラス
		GateDrawer gateDra_;


		// ゴール
		YGame::Transform goal_;
		// ゴール描画クラス
		GoalDrawer goalDra_;


		// 天球
		Skydome skydome_;
		
		// HUD
		HUDDrawer hud_;

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
		PlayScene() = default;
		
		// デストラクタ
		~PlayScene() = default;

	};
}

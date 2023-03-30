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

		// プレイヤー
		YGame::Transform player_;
		// 向き (プレイヤー用)
		YMath::Vector3 direction_;
		// プレイヤー描画クラス
		PlayerDrawer playerDra_;
		

		// フィルター
		YGame::Transform filter_;
		// フィルター描画クラス
		FilterDrawer filterDra_;


		// ブロック
		YGame::Transform block_;
		// ブロック描画クラス
		BlockDrawer blockDra_;


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

		// 転送用ビュープロジェクション
		YGame::ViewProjection transferVP_;

#pragma endregion
	public:
		// 読み込み
		void Load() override;
		// 初期化
		void Initialize() override;
		// 終了処理
		void Finalize() override;
		// 更新
		void Update() override;
		// 描画
		void Draw() override;
	private:
		// 背景スプライト2D描画
		void DrawBackSprite2Ds();
		// スプライト3D描画
		void DrawBackSprite3Ds();
		// モデル描画
		void DrawModels();
		// スプライト3D描画
		void DrawFrontSprite3Ds();
		// 前景スプライト2D描画
		void DrawFrontSprite2Ds();
	public:
		// コンストラクタ
		PlayScene() = default;
		// デストラクタ
		~PlayScene() = default;
	};
}

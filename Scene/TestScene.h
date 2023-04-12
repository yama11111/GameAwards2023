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
		// モデル描画
		void DrawModels();
		// スプライト3D描画
		void DrawSprite3Ds();
		// 前景スプライト2D描画
		void DrawFrontSprite2Ds();
	public:
		// コンストラクタ
		TestScene() = default;
		// デストラクタ
		~TestScene() = default;
	};
}

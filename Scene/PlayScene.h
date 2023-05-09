#pragma once
#include "BaseScene.h"

#include "Player.h"
//#include "Pises.h"
#include "PuzzleMat.h"
#include "Block.h"
#include "GateDrawer.h"
#include "GoalDrawer.h"

#include "BackgroundDrawer.h"
#include "HUDDrawer.h"

#include "EffectManager.h"
#include "ScrollCamera.h"
#include "StageConfig.h"

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
		std::unique_ptr<Player> player;

		//// フィルター
		//std::unique_ptr<Filter> filter;
		std::unique_ptr<Pises> pises;
		//std::vector<std::unique_ptr<Pises>> piseses;

		// プレイヤー
		std::unique_ptr<PuzzleMat> puzzleMat;

		//// ステージ設定
		//StageConfig* stageConfig_;

		//int map[9][9] =
		//{
		//	{0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0},
		//	{0,0,0,0,0,0,0,0,0},
		//};

		////後で治す
		//int map1[9][9] =
		//{
		//	{1,1,1,1,1,1,1,1,1},
		//	{1,0,0,0,0,1,0,0,1},
		//	{1,1,0,0,0,0,0,0,1},
		//	{1,0,0,0,0,0,0,0,1},
		//	{1,0,0,1,0,0,0,0,1},
		//	{1,0,0,0,0,0,1,1,1},
		//	{1,0,0,0,0,0,0,0,1},
		//	{1,1,1,1,1,1,1,1,1},
		//	{1,1,1,1,1,1,1,1,1},
		//};

		//const int blockCountY = 9;
		//const int blockCountX = 9;

		//ブロック格納用変数
		std::vector<std::unique_ptr<Block>> block;

		//中心からの縦横サイズ
		YMath::Vector2 RL = { 0.0f,0.0f };
		YMath::Vector2 WS = { 0.0f,0.0f };

		//入力確認用
		YMath::Vector2 DS = { 0.0f,0.0f };
		YMath::Vector2 AW = { 0.0f,0.0f };

		// ゴール
		YGame::Transform goal_;
		// ゴール描画クラス
		GoalDrawer goalDra_;

		//後で消す
		bool nowMode = false;

		// 背景
		BackgroundDrawer background_;

		// HUD
		HUDDrawer hud_;

		// パーティクルマネージャー
		YGame::ParticleManager particleMan_;

		// エフェクトマネージャー
		YGame::EffectManager effectMan_;

		// カメラ
		YGame::Camera camera_;

		// カメラの追従点
		YMath::Vector3 followPoint_;

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

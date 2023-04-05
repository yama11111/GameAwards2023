#pragma once
#include "BaseScene.h"

//#include "PlayerDrawer.h"
#include "Player.h"
//#include "FilterDrawer.h"
#include "Filter.h"
#include "Block.h"
//#include "BlockDrawer.h"
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

		// プレイヤー操作か
		bool isPlayer_ = true;

		//プレイヤーtrue、フィルターfalse;
		bool nowMode;

		// プレイヤー
		Player player;

		// フィルター
		Filter filter;

		int map[7][40] =
		{
			//0					 10					 20					 30
		  ////0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,
			 //{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},////0
			 //{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},////1
			 //{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},////2
			 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0},////3
			 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0},////4
			 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,6,0,0,0,0,0,0},////5
			 {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,2,0,0,0,0,0,0,1,2,2,2,2,2,1},////6
			 {0,0,0,0,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,2,0,0,0,0,0,1,1,0,0,0,0,0,1},////7
			 {4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1},////8
			 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,5,5,1},////9
		};

		//// ブロック
		//Block block[5];

		const int blockCountY = 7;
		const int blockCountX = 40;

		//const int blockCount = 5;

		std::vector<Block*> block;

		YMath::Vector2 RL = { 0.0f,0.0f };
		YMath::Vector2 WS = { 0.0f,0.0f };

		YMath::Vector2 DS = { 0.0f,0.0f };
		YMath::Vector2 AW = { 0.0f,0.0f };

		YMath::Vector2 filterSize = { 0.0f,0.0f };

		//// プレイヤー
		//YGame::Transform player_;
		//// 向き (プレイヤー用)
		//YMath::Vector3 direction_;
		//// プレイヤー描画クラス
		//PlayerDrawer playerDra_;
		//

		//// フィルター
		//YGame::Transform filter_;
		//// フィルター描画クラス
		//FilterDrawer filterDra_;


		//// ブロック個数
		//static const size_t idx = 20;
		//// ブロック
		//std::array<YGame::Transform, idx> block_;
		//// ブロック描画クラス
		//std::array<BlockDrawer, idx> blockDra_;


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
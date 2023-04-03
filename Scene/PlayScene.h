#pragma once
#include "BaseScene.h"

//#include "PlayerDrawer.h"
#include "Player.h"
//#include "FilterDrawer.h"
#include "Filter.h"
#include "Block.h"
//#include "BlockDrawer.h"
#include "Skydome.h"
#include "EffectManager.h"

namespace YScene
{
	// ゲームシーン
	class PlayScene : public BaseScene
	{
	public:
#pragma region リソース

		// ----- テクスチャ ----- //

		// 無地画像
		UINT plainTex_ = 0;

		// ----- オーディオ ----- //

		// ----- スプライト (2D) ----- //

		// 画面全部
		std::unique_ptr<YGame::Sprite2D> windowSpr_ = nullptr;

		// ----- スプライト (3D) ----- //

		// ----- モデル ----- //

		// 立方体モデル
		std::unique_ptr<YGame::Model> cubeMod_ = nullptr;

#pragma endregion
#pragma region ゲームオブジェクト

		//プレイヤーtrue、フィルターfalse;
		bool nowMode;

		// プレイヤー
		Player player;

		// フィルター
		Filter filter;

		// ブロック
		Block block[20];

		const int blockCount = 5;

		// 天球
		Skydome skydome_;

		// パーティクルマネージャー
		YGame::ParticleManager particleMan_;

		// エフェクトマネージャー
		YGame::EffectManager effectMan_;

		// 転送用ビュープロジェクション
		YGame::ViewProjection transferVP_;

		YMath::Vector2 RL = { 0.0f,0.0f };
		YMath::Vector2 WS = { 0.0f,0.0f };

		YMath::Vector2 DS = { 0.0f,0.0f };
		YMath::Vector2 AW = { 0.0f,0.0f };

		YMath::Vector2 filterSize = { 0.0f,0.0f };

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

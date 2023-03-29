#pragma once
#include "BaseScene.h"

#include "PlayerDrawer.h"
#include "FilterDrawer.h"
#include "BlockDrawer.h"
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

		// プレイヤー
		YGame::Transform player_;
		// 向き
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


		// 天球
		Skydome skydome_;
		
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

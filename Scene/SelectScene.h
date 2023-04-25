#pragma once
#include "BaseScene.h"
#include "SelectDrawer.h"
#include "InputDrawer.h"
#include "PauseDrawer.h"
#include "Camera.h"
#include "Skydome.h"

namespace YScene
{
	// セレクトシーン
	class SelectScene : public BaseScene
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

		// input
		InputDrawer inputDra_;
		
		// pause
		PauseDrawer pauseDra_;


		// ステージ設定
		StageConfig* stageConfig_;


		// ステージセレクト描画クラス
		SelectDrawer dra_;


		// パーティクルマネージャー
		YGame::ParticleManager particleMan_;

		// カメラ
		YGame::Camera camera_;

		// ビュープロジェクション
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
		SelectScene() = default;
		
		// デストラクタ
		~SelectScene() = default;

	};
}


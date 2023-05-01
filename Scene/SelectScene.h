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

	private:

#pragma region リソース

		// セレクトシーンBGM
		YGame::Audio* pSelectBGM_ = nullptr;

#pragma endregion

#pragma region ゲームオブジェクト

		// ステージセレクト描画クラス
		SelectDrawer dra_;
		
		// input
		InputDrawer inputDra_;
		
		// pause
		PauseDrawer pauseDra_;


		// ステージ設定
		StageConfig* stageConfig_ = nullptr;


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
		/// 背景モデル描画
		/// </summary>
		void DrawBackModels();

		/// <summary>
		/// 背景スプライト3D描画
		/// </summary>
		void DrawBackSprite3Ds();

		/// <summary>
		/// 前景モデル描画
		/// </summary>
		void DrawFrontModels();

		/// <summary>
		/// 前景スプライト3D描画
		/// </summary>
		void DrawFrontSprite3Ds();

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


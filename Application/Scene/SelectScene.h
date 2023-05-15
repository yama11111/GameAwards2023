#pragma once
#include "BaseScene.h"
#include "SelectDrawer.h"
#include "InputDrawer.h"
#include "PauseDrawer.h"
#include "Camera.h"

namespace YScene
{
	// セレクトシーン
	class SelectScene : public BaseScene
	{

	private:

#pragma region リソース

		// セレクトシーンBGM
		YGame::Audio* pSelectBGM_ = nullptr;


		// セレクトSE
		YGame::Audio* pSelectSE_ = nullptr;
		
		// 決定SE
		YGame::Audio* pDecisionSE_ = nullptr;

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

	public:
		
		// コンストラクタ
		SelectScene() = default;
		
		// デストラクタ
		~SelectScene() = default;

	};
}


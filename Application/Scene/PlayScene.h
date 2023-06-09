#pragma once
#include "BaseScene.h"

#include "GateDrawer.h"
#include "GoalDrawer.h"

#include "BackgroundDrawer.h"
#include "HUDDrawer.h"

#include "ScrollCamera.h"
#include "StageConfig.h"

namespace YScene
{
	// ゲームシーン
	class PlayScene : public BaseScene
	{
	
	public:

#pragma region リソース

		// プレイBGM
		YGame::Audio* pPlayBGM_ = nullptr;

#pragma endregion

#pragma region ゲームオブジェクト

		// ------------ ↓ プレイシーンの変数 ↓ ------------//
		

		
		// ------------ ↑ プレイシーンの変数 ↑ ------------//


		// ステージ設定
		StageConfig* stageConfig_ = nullptr;


		// 背景
		BackgroundDrawer background_;

		// HUD
		HUDDrawer hud_;


		// パーティクルマネージャー
		YGame::ParticleManager particleMan_;

		// カメラ
		YGame::Camera camera_;

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

	public:

		// コンストラクタ
		PlayScene() = default;

		// デストラクタ
		~PlayScene() = default;

	};
}

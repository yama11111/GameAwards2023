#pragma once
#include "BaseScene.h"

#include "DemoPlayer.h"
#include "DemoGoal.h"
#include "MapChipManager.h"

#include "BackGroundDrawer.h"
#include "HUDDrawer.h"

namespace YScene
{
	class DemoScene : public BaseScene
	{

	private:

#pragma region リソース

		// プレイBGM
		YGame::Audio* pPlayBGM_ = nullptr;

#pragma endregion

#pragma region ゲームオブジェクト

		// プレイヤー
		DemoPlayer player_;

		// ゴール
		DemoGoal goal_;

		// マップチップマネージャー
		YGame::MapChipManager mapChipMan_;

		
		// ゴールフラグ
		bool isGoal_ = false;

		bool isAfterglow_ = false;

		YMath::Timer goalTim_;

		YMath::Timer fontScaleTim_;

		YMath::Timer afterglowTim_;
		
		YMath::Ease<YMath::Vector3> fontScaleEas_;

		YMath::Ease<float> fontAlphaEas_;

		std::unique_ptr<YGame::Sprite2DObject> fontObj_;
		std::unique_ptr<YGame::Color> fontColor_;

		YGame::Sprite2D* fontSpr_ = nullptr;


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
		DemoScene() = default;

		// デストラクタ
		~DemoScene() = default;

	};
}


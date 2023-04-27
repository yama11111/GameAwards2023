#pragma once
#include "BaseScene.h"
#include "TitleDrawer.h"
#include "InputDrawer.h"
#include "BackgroundDrawer.h"

namespace YScene
{
	// タイトルシーン
	class TitleScene : public BaseScene
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

		// 背景
		BackgroundDrawer background_;
		
		// パーティクルマネージャー
		YGame::ParticleManager particleMan_;

		// 転送用ビュープロジェクション
		YGame::ViewProjection transferVP_;


		std::unique_ptr<YGame::Sprite2DObject> syazaiObj_;

		YGame::Sprite2D* syazaiSpr_ = nullptr;
		

		// input
		InputDrawer inputDra_;

		// タイトル描画クラス
		TitleDrawer dra_;

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
		TitleScene() = default;
		
		// デストラクタ
		~TitleScene() = default;
	};
}

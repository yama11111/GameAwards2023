#pragma once
#include "BaseScene.h"

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
		// モデル描画
		void DrawModels();
		// スプライト3D描画
		void DrawSprite3Ds();
		// 前景スプライト2D描画
		void DrawFrontSprite2Ds();
	public:
		// コンストラクタ
		SelectScene() = default;
		// デストラクタ
		~SelectScene() = default;
	};
}


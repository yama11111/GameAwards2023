#pragma once
#include "BaseScene.h"

namespace YScene
{
	// タイトルシーン
	class TitleScene : public BaseScene
	{
	public:
#pragma region リソース

		// ----- テクスチャ ----- //

		UINT logoTex_ = 0;
		
		UINT backTex_ = 0;

		std::array<UINT, 2> spaceKeyTex_ = { 0, 0 };

		// ----- オーディオ ----- //

		// ----- スプライト (2D) ----- //

		std::unique_ptr<YGame::Sprite2D> logoSpr_;

		std::unique_ptr<YGame::Sprite2D> backSpr_;

		std::array<std::unique_ptr<YGame::Sprite2D>, 2> spaceKeySpr_;

		// ----- スプライト (3D) ----- //

		// ----- モデル ----- //

#pragma endregion
#pragma region ゲームオブジェクト

		std::unique_ptr<YGame::Sprite2DObject> logoObj_;

		std::unique_ptr<YGame::Sprite2DObject> backObj_;

		std::unique_ptr<YGame::Sprite2DObject> spaceKeyObj_;
		bool isPush_ = false;

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
		TitleScene() = default;
		// デストラクタ
		~TitleScene() = default;
	};
}

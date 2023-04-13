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

		YGame::Texture* pLogoTex_ = nullptr;
		
		YGame::Texture* pBackTex_ = nullptr;

		std::array<YGame::Texture*, 2> pSpaceKeyTex_ = { nullptr, nullptr };

		// ----- オーディオ ----- //

		// ----- スプライト (2D) ----- //

		YGame::Sprite2D* pLogoSpr_ = nullptr;

		YGame::Sprite2D* pBackSpr_ = nullptr;

		std::array<YGame::Sprite2D*, 2> pSpaceKeySpr_ = { nullptr, nullptr };

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

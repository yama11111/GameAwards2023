#pragma once
#include "BaseScene.h"

#include "Level.h"
#include "Camera.h"

namespace YScene
{
	class DemoScene : public BaseScene
	{

	private:

#pragma region リソース


#pragma endregion

#pragma region ゲームオブジェクト

		// レベル
		YGame::Level* pLevel_ = nullptr;

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
		DemoScene() = default;

		// デストラクタ
		~DemoScene() = default;

	};
}


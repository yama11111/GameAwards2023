#pragma once

#include "BaseScene.h"

#include "Model.h"
#include "Camera.h"

namespace YScene
{
	// 評価課題シーン
	class TaskScene : public BaseScene
	{

	private:

#pragma region リソース
		
		// モデルポインタ
		YGame::Model* pCube_ = nullptr;
		YGame::Model* pSphere_ = nullptr;

#pragma endregion


#pragma region ゲームオブジェクト

		// モデルオブジェクト
		std::unique_ptr<YGame::Model::Object> cubeObj_;
		std::unique_ptr<YGame::Model::Object> sphereObj_;

		// 色
		std::unique_ptr<YGame::Color> color_;

		// マテリアル
		std::unique_ptr<YGame::Material> material_;

		// 転送用ビュープロジェクション
		YGame::ViewProjection transferVP_;

		// 光源グループ
		std::unique_ptr<YGame::LightGroup> lightGroup_;

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
		TaskScene() = default;

		// デストラクタ
		~TaskScene() = default;

	};
}


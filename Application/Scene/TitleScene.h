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

	private:

#pragma region リソース

		// タイトルBGM
		YGame::Audio* pTitleBGM_ = nullptr;


		// セレクトSE
		YGame::Audio* pSelectSE_ = nullptr;

		// 決定SE
		YGame::Audio* pDecisionSE_ = nullptr;

#pragma endregion

#pragma region ゲームオブジェクト

		// タイトル描画クラス
		TitleDrawer titleDra_;

		// 背景
		BackgroundDrawer background_;
		
		// input
		InputDrawer inputDra_;
		

		// パーティクルマネージャー
		YGame::ParticleManager particleMan_;

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
		TitleScene() = default;
		
		// デストラクタ
		~TitleScene() = default;
	};
}

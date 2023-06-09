#pragma once
#include "BaseScene.h"

#include "Player.h"
#include "Block.h"
#include "Spring.h"
#include "Platform.h"
#include "Laser.h"
#include "Switch.h"
#include "Key.h"
#include "Goal.h"

#include "ObjectManager.h"

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
		std::unique_ptr<Player> player_;

		// ブロック
		std::list<std::unique_ptr<Block>> blocks_;

		// ばね
		std::list<std::unique_ptr<Spring>> springs_;
		
		// 足場
		std::list<std::unique_ptr<Platform>> platforms_;
		
		// レーザー
		std::list<std::unique_ptr<Laser>> lasers_;
		
		// スイッチ
		std::list<std::unique_ptr<Switch>> switches_;
		
		// 鍵
		std::unique_ptr<Key> key_;
		
		// ゴール
		std::unique_ptr<Goal> goal_;



		// オブジェクトマネージャー
		ObjectManager objMan_;


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
		DemoScene() = default;

		// デストラクタ
		~DemoScene() = default;

	};
}


#pragma once
#include "BaseScene.h"

#include "PlayerDrawer.h"
#include "FilterDrawer.h"
#include "BlockDrawer.h"
#include "Skydome.h"
#include "EffectManager.h"

namespace YScene
{
	// ゲームシーン
	class PlayScene : public BaseScene
	{
	public:
#pragma region リソース

		// ----- テクスチャ ----- //

		// 無地画像
		UINT plainTex_ = 0;

		// ----- オーディオ ----- //

		// ----- スプライト (2D) ----- //

		// 画面全部
		std::unique_ptr<YGame::Sprite2D> windowSpr_ = nullptr;

		// ----- スプライト (3D) ----- //

		// ----- モデル ----- //

		// 立方体モデル
		std::unique_ptr<YGame::Model> cubeMod_ = nullptr;

#pragma endregion
#pragma region ゲームオブジェクト

		// プレイヤー
		YGame::Transform player_;
		// 向き
		YMath::Vector3 direction_;
		// プレイヤー描画クラス
		PlayerDrawer playerDra_;

		// フィルター
		YGame::Transform filter_;
		// フィルター描画クラス
		FilterDrawer filterDra_;

		// ブロック
		YGame::Transform block_;
		// ブロック描画クラス
		BlockDrawer blockDra_;


		// 天球
		Skydome skydome_;

		// パーティクルマネージャー
		YGame::ParticleManager particleMan_;

		// エフェクトマネージャー
		YGame::EffectManager effectMan_;

		// 転送用ビュープロジェクション
		YGame::ViewProjection transferVP_;

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
		// スプライト3D描画
		void DrawBackSprite3Ds();
		// モデル描画
		void DrawModels();
		// スプライト3D描画
		void DrawFrontSprite3Ds();
		// 前景スプライト2D描画
		void DrawFrontSprite2Ds();
	public:
		// コンストラクタ
		PlayScene() = default;
		// デストラクタ
		~PlayScene() = default;

		//water追加分
	private:
	};

	//class Player
	//{
	//private:
	//	Vector2 playerPos = { 0,0 };
	//	Vector2 playerSize = { 16,32 };

	//	Vector2 playerCheckPos = { 0,0 };
	//	Vector2 playerCheckSize = { 16,64 };

	//	Vector2 playerCheckSizeRL = { 16,64 };
	//	Vector2 playerCheckSizeUD = { 16,64 };

	//	//キーが押されているかどうか
	//	Vector2 DS;
	//	Vector2 AW;

	//	//プレイヤーかフィルターか
	//	bool chengeF = true;

	//	//プレイヤーがすり抜けるか
	//	bool sukeF = false;
	//	//passFlag

	//	//フィルターの角に当たっているかどうか
	//	bool kadoF = false;
	//	//corner

	//public:
	//	Player();
	//	~Player();

	//	void Inilialize();
	//	void Update();
	//	void Draw();

	//	//位置
	//	Vector2 GetPos() { return playerPos; };
	//	void SetPos(Vector2 nowpos) { playerPos = nowpos; };

	//	//最初の大きさ
	//	Vector2 GetSize() { return playerSize; };
	//	void SetSize(Vector2 nowsize) { playerPos = nowsize; };

	//	//今の大きさ
	//	Vector2 GetNowSizeX() { return playerCheckSizeRL; };
	//	Vector2 GetNowSizeY() { return playerCheckSizeUD; };

	//	bool GetmoveFlag() { return chengeF; };
	//	bool GetpassFlag() { return sukeF; };
	//	bool GetcornerFlag() { return kadoF; };

	//	void SetmoveFlag(bool flag) { chengeF = flag; };
	//	void SetpassFlag(bool flag) { sukeF = flag; };
	//	void SetcornerFlag(bool flag) { kadoF = flag; };
	//};

	//class Filter
	//{
	//public:
	//	Filter();
	//	~Filter();

	//	void Inilialize();
	//	void Update();
	//	void Draw();
	//private:
	//	Vector2 filterPos = { 0,0 };
	//	Vector2 filterSize = { 128,64 };
	//};

	//class Box
	//{
	//public:

	//private:
	//	Vector2 box[20];
	//	Vector2 BoxSize = { 16,16 };

	//	//ボックスの数
	//	int boxcount = 20;

	//	////マップ上に配置しているブロック
	//	//for (int i = 0; i < boxcount; i++)
	//	//{
	//	//	box[i].x = (i * 30);
	//	//	box[i].y = (i * 30);
	//	//}

	//	////細かな調整
	//	//box[19].x = (18 * 30);
	//	//box[19].y = (20 * 30);

	//	//box[15].x = (16 * 30) - 5;
	//	//box[15].y = (15 * 30);

	//	//box[2].x = (16 * 30) - 5;
	//	//box[2].y = (14 * 30) - 25;
	//};
}

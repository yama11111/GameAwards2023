#pragma once
#include "Sprite2D.h"
#include "Model.h"

class TitleDrawerCommon
{
protected:

	// ----- Sprite2D ----- //

	// 静的ロゴスプライト
	static YGame::Sprite2D* spLogoSpr_;

	// 静的影スプライト
	static YGame::Sprite2D* spShadowSpr_;

	// 静的背景スプライト
	static YGame::Sprite2D* spBackSpr_;


	// 静的スタートスプライト
	static YGame::Sprite2D* spStartSpr_;

	// 静的終了スプライト
	static YGame::Sprite2D* spExitSpr_;

	// ----- Model ----- //

	// 静的ビルモデル
	static YGame::Model* spBuildingMod_;

public:

	// 静的初期化
	static void StaticInitialize();

};

class TitleDrawer :
	private TitleDrawerCommon
{
public:

	// 選択
	enum class Selection
	{
		Start, // 開始
		Exit,  // 終了
	};

private:
	// ----- オブジェクト ----- //

	// 核
	std::unique_ptr<YGame::Transform> core_;

	// ロゴ
	std::unique_ptr<YGame::Sprite2DObject> logoObj_;


	// 影
	std::unique_ptr<YGame::Sprite2DObject> shadowObj_;

	// 背景
	std::unique_ptr<YGame::Sprite2DObject> backObj_;


	// スタート
	std::unique_ptr<YGame::Sprite2DObject> startObj_;
	// スタート色
	std::unique_ptr<YGame::Color> startColor_;

	// 終了
	std::unique_ptr<YGame::Sprite2DObject> exitObj_;
	// 終了色
	std::unique_ptr<YGame::Color> exitColor_;

	// ----- アニメーション ----- //

	// 動作中か
	bool isAct_ = false;

	// 選択
	Selection current_ = Selection::Start;

public:

	// 初期化
	void Initalize();

	// リセット
	void Reset();

	// 選択
	void Select(const bool isUp, const bool isUnder);

	// 更新
	void Update();

	// スプライト2D描画
	void DrawSprite2D();

	// モデル描画
	void DrawModel();

public:

	// 現在の選択取得
	Selection GetSelection() { return current_; }

	// 現在の選択設定
	void SetSelection(const Selection& selection) { current_ = selection; }

};


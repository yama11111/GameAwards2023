#pragma once
#include "Sprite2D.h"
#include "Model.h"
#include "Lerp.h"
#include "Power.h"

// 多重定義回避用
namespace YInput { class Keys; }

class TitleDrawerCommon
{

public:

	// 選択
	enum class Selection
	{
		Start, // 開始
		Exit,  // 終了
	};

protected:

	// キー
	static YInput::Keys* sKeys_;


	// 静的ロゴスプライト
	static YGame::Sprite2D* spLogoSpr_;

	// 静的影スプライト
	static YGame::Sprite2D* spShadowSpr_;


	// 静的スタートスプライト
	static YGame::Sprite2D* spStartSpr_;

	// 静的終了スプライト
	static YGame::Sprite2D* spExitSpr_;

public:

	// 静的初期化
	static void StaticInitialize();

};

class TitleDrawer :
	private TitleDrawerCommon
{

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


	YMath::Power selectStartPow_;
	YMath::Ease<float> selectMoveXEas_;

	YMath::Power selectExitPow_;
	YMath::Ease<float> selectScaleEas_;

public:

	// 初期化
	void Initialize();

	// リセット
	void Reset();

	// 選択
	void Select(const bool isUp, const bool isUnder);

	// 更新
	void Update();

	// 描画
	void Draw();

public:

	// 現在の選択取得
	Selection GetSelection() { return current_; }

	// 現在の選択設定
	void SetSelection(const Selection& selection) { current_ = selection; }

};


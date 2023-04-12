#pragma once
#include "Sprite2D.h"

class TitleDrawerCommon
{
protected:
	// 静的ロゴスプライト
	static std::unique_ptr<YGame::Sprite2D> sLogoSpr_;
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

	// ----- アニメーション ----- //

	// 選択番号ポインタ
	int* pStageIdx_ = nullptr;

	// 動作中か
	bool isAct_ = false;
public:
	// 初期化
	void Initalize(int* pStageIdx);
	// リセット
	void Reset();
	// 更新
	void Update();
	// 描画
	void Draw();
};


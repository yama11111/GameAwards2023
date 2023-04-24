#pragma once
#include "Model.h"
#include "Lerp.h"
#include "Power.h"

class GridDrawerCommon
{

protected:

	// モデルポインタ
	static YGame::Model* spGridMod_;

	// ビュープロジェクションポインタ
	static YGame::ViewProjection* spVP_;

public:

	/// <summary>
	/// 静的初期化
	/// </summary>
	static void StaticInitialize(YGame::ViewProjection* pVP);

public:

	virtual ~GridDrawerCommon() = default;

};

class GridDrawer : private GridDrawerCommon
{

private:

	// ----- オブジェクト ----- //
	
	// グリッド
	std::list<std::unique_ptr<YGame::ModelObject>> grids_;

	// 色
	std::unique_ptr<YGame::Color> color_;

	// ----- アニメーション ----- //
	
	// アルファ値変動するか
	bool isActAlpha_ = false;

	// アルファ値スイッチャー
	bool isSwitchAlpha_ = false;

	// アルファ値パワー
	YMath::Power alphaPow_;
		
	// アルファ値イージング
	YMath::Ease<float> alphaEas_;

public:

	// 初期化
	void Initialize(const YMath::Vector3& leftTop, const YMath::Vector3& num, const float scaleSize);

	// リセット
	void Reset();

	// 更新
	void Update();

	// 描画
	void Draw();

public:

	// アルファ値アニメーション開始
	void ActAlphaAnimation();

private:

	// アルファ値アニメーション更新
	void UpdateAlphaAnimation();

};


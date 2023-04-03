#pragma once
#include "Vector2.h"
#include "FilterDrawer.h"

class Filter
{
public:
	Filter();
	~Filter();

	void Inilialize();
	void Update();
	void Draw();
	void Reset();

	// フィルター
	YGame::Transform filter_;
	// フィルター描画クラス
	FilterDrawer filterDra_;
private:

	//// フィルター
	//YGame::Transform filter_;
	//// フィルター描画クラス
	//FilterDrawer filterDra_;

	/*YMath::Vector2 filterPos = { 0,0 };
	YMath::Vector2 filterSize = { 128,64 };*/
};


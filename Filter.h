#pragma once
#include "Vector2.h"
#include "FilterDrawer.h"

class Filter
{
private:
	// フィルター
	YGame::Transform filter_;
	// フィルター描画クラス
	FilterDrawer filterDra_;

	//今動いてるかどうか
	//bool nowMove = false;

public:
	//インクリメント
	Filter();

	//デクリメント
	~Filter();

	//初期化
	void Initialize();
	void Initialize(YMath::Vector3 pos_, YMath::Vector3 rot_, YMath::Vector3 scale_);

	//更新
	void Update();

	//描画(ほかのPostとPreの間に描画する)
	void Draw();

	//リセット
	void Reset();

	//動いてるかどうかフラグに代入
	//void SetNowMove(bool flag) { nowMove = flag; };

	//フラグ反転
	//void ChengeNowMove() {nowMove = !nowMove;};

	//動いてるかどうかのフラグを入手
	//bool GetNowMove() { return nowMove; };

	YGame::Transform GetTransform() { return filter_; };
};


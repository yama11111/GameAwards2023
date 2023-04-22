#pragma once
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

	//移動量格納
	YMath::Vector3 movePos = { 0.0f,0.0f,0.0f };

	// フィルター
	YGame::Transform filters[9];

	// フィルター描画クラス
	FilterDrawer filterDras[9];

	bool drawFlag[9];

	//縦横
	const int countX = 3;
	const int countY = 3;

	const int mapCountY = 14;
	const int mapCountX = 40;

	//フィルター用マップ
	int Fmap[14][40];

public:
	//インクリメント
	Filter();

	//デクリメント
	~Filter();

	//初期化
	void Initialize();
	void Initialize(YMath::Vector3 pos_, YMath::Vector3 rot_, YMath::Vector3 scale_);

	void InitializeMap(int i, int j, int chenge);

	//更新
	void Update();

	//描画(ほかのPostとPreの間に描画する)
	void Draw();

	//リセット
	void Reset();

	//Transform獲得
	YGame::Transform GetTransform() { return filter_; };
	YGame::Transform GetTransform(int i) { return filters[i]; };

	//移動量獲得
	YMath::Vector3 GetMovePos() { return movePos; };

	//移動量セット
	void SetMovePos(YMath::Vector3 pos) { movePos = pos; };

	//posセット
	void SetPos(YMath::Vector3 pos) { filter_.pos_ = pos; };

	//複数フィルターのDrawFlag
	void SetDrawFlag(int i, bool flag) { drawFlag[i] = flag; };
	bool GetDrawFlag(int i) { return drawFlag[i]; };
};


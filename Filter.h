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

	//Transform獲得
	YGame::Transform GetTransform() { return filter_; };

	//移動量獲得
	YMath::Vector3 GetMovePos() { return movePos; };

	//移動量セット
	void SetMovePos(YMath::Vector3 pos) { movePos = pos; };
};


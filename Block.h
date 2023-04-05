#pragma once
#include "Vector2.h"
#include "BlockDrawer.h"

enum kind
{
	None,	//空白
	Normal,	//普通
	ColorB,	//透けるよ
	//ABS,	//可変不可
	Start,	//プレイヤーをスタートに出現のちにNormalに移行
	Gorl,	//ゴール
	Collect, // コレクト
	CheckPoint,	//一応用意
};

class Block {
private:

public:
	// ブロック
	YGame::Transform block_;
	// ブロック描画クラス
	BlockDrawer blockDra_;

	Block();
	~Block();

	int nowKind = None;
	bool sukeF = false;

	void Inilialize();
	void Update(YGame::Transform filter);
	void Draw();
	void Reset();
	void SetKind(int kind) { nowKind = kind; };
	void SetMode();
};
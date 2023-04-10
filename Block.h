#pragma once
#include "Vector2.h"
#include "BlockDrawer.h"

//ブロックの種類
enum Kind
{
	None,	//空白
	Normal,	//普通
	ColorB,	//透ける
	Start,	//プレイヤーをスタートに出現のちにNormalに移行する
	Gorl,	//ゴール
	Collect, // コレクト
	CheckPoint,	//一応用意
};

class Block {
private:
	// ブロック
	YGame::Transform block_;

	// ブロック描画クラス
	BlockDrawer blockDra_;

	//ブロックの種類
	int nowKind = None;

	//フィルターと当たって判定がなくなっているか
	//bool sukeF = false;
	bool ClearFlag = false;

public:

	//インクリメント
	Block();

	//デクリメント
	~Block();

	//初期化
	void Initialize();

	//更新
	void Update(YGame::Transform filter);

	//Pre描画(フィルターの前)
	void PreDraw();

	//Post描画(フィルターの後)
	void PostDraw();

	//リセット
	void Reset();

	//ブロックの種類変更
	void SetKind(int kind) { nowKind = kind; };

	//ClearFlagに代入
	void SetClearFlag(bool flag) { flag = ClearFlag; };

	//ClearFlagを入手
	bool GetClearFlag() { return ClearFlag; };

	//posを入手
	void SetPos(YMath::Vector3 pos) { block_.pos_ = pos; };

	//posに代入
	YMath::Vector3 GetPos() { return block_.pos_; };

	//Transformを入手
	YGame::Transform GetTransform() { return block_; };

	//ブロックを生成後に描画する種類を変える
	void SetMode();
};
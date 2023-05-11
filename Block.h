#pragma once
#include "Vector2.h"
#include "BlockDrawer.h"

//ブロックの種類
enum Kind
{
	None,	//空白
	Normal,	//普通
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

public:

	//インクリメント
	Block();

	//デクリメント
	~Block();

	//初期化
	void Initialize();

	//更新
	void Update();

	//描画
	void Draw();

	//リセット
	void Reset();

	//ブロックの種類変更
	void SetKind(int kind) { nowKind = kind; };

	//現在のブロックの種類の取得
	int GetKind() { return nowKind; };

	//Vector3に代入
	void SetPos(YMath::Vector3 pos) { block_.pos_ = pos; };
	void SetScale(YMath::Vector3 scale) { block_.scale_ = scale; };
	void SetRot(YMath::Vector3 rot) { block_.rota_ = rot; };

	//Vector3を入手
	YMath::Vector3 GetPos() { return block_.pos_; };
	YMath::Vector3 GetScale() { return block_.scale_; };
	YMath::Vector3 GetRot() { return block_.rota_; };

	//Transformを入手
	YGame::Transform GetTransform() { return block_; };
};
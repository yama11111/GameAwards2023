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

	//現在のブロックの種類の取得
	int GetKind() { return nowKind; };

	//ClearFlagに代入
	void SetClearFlag(bool flag) { flag = ClearFlag; };

	//ClearFlagを入手
	bool GetClearFlag() { return ClearFlag; };

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

	//ブロックを生成後に描画する種類を変える
	void SetMode();
};
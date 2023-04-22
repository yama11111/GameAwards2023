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

	//総ブロック数
	BlockDrawer blocksDra_[16];

	//ブロックの種類
	int nowKind = None;

	//フィルターと当たって判定がなくなっているか
	//bool sukeF = false;
	bool ClearFlag = false;

	//戻る時間
	int timer_ = 0;

	//上がる
	bool upFlag = false;

	int upTimer = 0;

	void LoadCSVFile(std::vector<std::vector<int>>& data, const char* fileName, int _height, int _width);

	void LoadCSV(std::string csvPath);

	std::vector<std::vector<int>> r_data;
public:

	//インクリメント
	Block();

	//デクリメント
	~Block();

	//初期化
	void Initialize();

	//更新
	void Update(YGame::Transform filter);

	//描画
	void Draw();

	//リセット
	void Reset();

	//ブロックの種類変更
	void SetKind(int kind) { nowKind = kind; };

	//現在のブロックの種類の取得
	int GetKind() { return nowKind; };

	//ClearFlagに代入
	void SetClearFlag(bool flag) { ClearFlag = flag; };

	//ClearFlagを入手
	bool GetClearFlag() { return ClearFlag; };
	bool GetUpFlag() { return upFlag; };
	void SetUpFlag(bool flag) { upFlag = flag; };

	//Vector3に代入
	void SetPos(YMath::Vector3 pos) { block_.pos_ = pos; };
	void SetScale(YMath::Vector3 scale) { block_.scale_ = scale; };
	void SetRot(YMath::Vector3 rot) { block_.rota_ = rot; };

	//全ブロックの位置代入
	void SetBlocksPos(YMath::Vector3 pos);

	//復活する時間
	void SetTimer(int time) { timer_ = time; };
	void SetUpTimer(int time) { upTimer = time; };

	//タイマー現象
	void CountDown() { timer_--; };

	//移動
	void MovePosYUp(int block);
	void MovePosYDown();
	void MovePos(int block);

	//Vector3を入手
	YMath::Vector3 GetPos() { return block_.pos_; };
	YMath::Vector3 GetScale() { return block_.scale_; };
	YMath::Vector3 GetRot() { return block_.rota_; };

	//Transformを入手
	YGame::Transform GetTransform() { return block_; };

	//ブロックを生成後に描画する種類を変える
	void SetMode();
};
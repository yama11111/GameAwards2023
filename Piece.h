#pragma once
#include "Vector2.h"
#include "Block.h"
#include "BlockDrawer.h"

class Piece
{
private:
	// フィルター
	YGame::Transform piece_;

	// ブロック描画クラス
	BlockDrawer blockDra_;

	//ブロック格納用変数
	std::vector<std::vector<Block>> blocks;

	//XY
	const int blockX = 9;
	const int blockY = 9;

	int map[81] =
	{
		1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,1,0,1,
		1,0,1,0,0,0,0,0,1,
		1,0,0,0,0,1,0,0,1,
		1,0,0,0,0,0,0,0,1,
		1,1,0,0,0,0,1,1,1,
		1,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,
	};



public:
	//インクリメント
	Piece();

	//デクリメント
	~Piece();

	//初期化
	void Initialize();

	//更新
	void Update();

	//描画
	void Draw();

	//Vector3に代入
	void SetPos(YMath::Vector3 pos) { piece_.pos_ = pos; };
	void SetScale(YMath::Vector3 scale) { piece_.scale_ = scale; };
	void SetRot(YMath::Vector3 rot) { piece_.rota_ = rot; };

	void CreateBlock();
};


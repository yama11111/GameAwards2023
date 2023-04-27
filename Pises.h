#pragma once
#include "Vector2.h"
#include "Block.h"
#include "BlockDrawer.h"

class Pises
{
private:
	// フィルター
	YGame::Transform pises_;

	// ブロック描画クラス
	BlockDrawer blockDra_;

	//ブロック格納用変数
	std::vector<std::unique_ptr<Block>> blocks;

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
	Pises();

	//デクリメント
	~Pises();

	//初期化
	void Initialize();
	void Initialize(YMath::Vector3 pos, YMath::Vector3 rot, YMath::Vector3 scale);

	//更新
	void Update();

	//描画
	void Draw();
	void DrawBlock();
	void DrawPiese();

	//これをfor文で呼び出してもらってmap分繰り返す
	void CreateBlock(int mode, YGame::Transform pises, int number);
};


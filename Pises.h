#pragma once
#include "Vector2.h"
#include "BlockDrawer.h"
#include "Block.h"

class Pises
{
private:
	// フィルター
	YGame::Transform pises_;

	//ブロック格納用変数
	std::unique_ptr<Block> blocks;

	//XY
	const int blockX = 9;
	const int blockY = 9;

public:
	//インクリメント
	Pises();

	//デクリメント
	~Pises();

	//初期化
	void Initialize();

	//更新
	void Update();

	//描画(ほかのPostとPreの間に描画する)
	void Draw();
};


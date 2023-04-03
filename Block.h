#pragma once
#include "Vector2.h"
#include "BlockDrawer.h"

class Block{
private:
	
public:
	// ブロック
	YGame::Transform block_;
	// ブロック描画クラス
	BlockDrawer blockDra_;

	Block();
	~Block();

	void Inilialize();
	void Update();
	void Draw();
	void Reset();
};
#pragma once
#include "Vector2.h"
#include "BlockDrawer.h"

class Block{
private:
	
public:
	// �u���b�N
	YGame::Transform block_;
	// �u���b�N�`��N���X
	BlockDrawer blockDra_;

	Block();
	~Block();

	void Inilialize();
	void Update();
	void Draw();
	void Reset();
};
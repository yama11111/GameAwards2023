#include "Block.h"

Block::Block()
{
	block_.Initialize({ {}, {}, {5.0f,5.0f,5.0f} });
	blockDra_.Initialize(&block_.m_, IDrawer::Mode::Red);
}

Block::~Block()
{
}

void Block::Inilialize()
{
	block_.Initialize({ {}, {}, {5.0f,5.0f,5.0f} });
	blockDra_.Initialize(&block_.m_, IDrawer::Mode::Red);
}

void Block::Update()
{

	// ÉuÉçÉbÉN
	block_.UpdateMatrix();
	blockDra_.Update();
}

void Block::Draw()
{

}

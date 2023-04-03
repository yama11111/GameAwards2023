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

	//block_.pos_.x_ += 0.1f;

	// ÉuÉçÉbÉN
	block_.UpdateMatrix();
	blockDra_.Update();
}

void Block::Draw()
{
	blockDra_.PostDraw();
}

void Block::Reset()
{
	block_.Initialize({ {}, {}, {5.0f,5.0f,5.0f} });
	blockDra_.Initialize(&block_.m_, IDrawer::Mode::Red);
}

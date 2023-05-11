#include "Block.h"

Block::Block()
{
	block_.Initialize({ {}, {}, {1.0f,1.0f,1.0f} });
	blockDra_.Initialize(&block_, IMode::Type::Normal);

	nowKind = Normal;
}

Block::~Block()
{
}

void Block::Initialize()
{
	block_.Initialize({ {}, {}, {1.0f,1.0f,1.0f} });
	blockDra_.Initialize(&block_, IMode::Type::Normal);

	nowKind = Normal;
}

void Block::Update()
{

	// ブロック
	block_.UpdateMatrix();
	blockDra_.Update();
}

void Block::Draw()
{
	//描画しないモードでないなら
	if (nowKind != None)
	{
		blockDra_.Draw();
	}
}

void Block::Reset()
{
}
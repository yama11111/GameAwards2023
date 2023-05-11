#include "Piece.h"

Piece::Piece()
{
	//transformèâä˙âª
	piece_.Initialize({ {(5.0f),(10.0f),0.0f}, {}, {4.5f,4.5f,0.5f} });
	blockDra_.Initialize(&piece_, IMode::Type::Normal);

	CreateBlock();
}

Piece::~Piece()
{
}

void Piece::Initialize()
{
	//transformèâä˙âª
	piece_.Initialize({ {(5.0f),(10.0f),0.0f}, {}, {4.5f,4.5f,0.5f} });
	blockDra_.Initialize(&piece_, IMode::Type::Normal);

	CreateBlock();
}

void Piece::Update()
{
	for (auto y = 0; y < blocks.size(); y++)
	{
		for (auto x = 0; x < blocks[0].size(); x++)
		{
			blocks[y][x].Update();
		}
	}
}

void Piece::Draw()
{
	for (auto y = 0; y < blocks.size(); y++)
	{
		for (auto x = 0; x < blocks[0].size(); x++)
		{
			blocks[y][x].Draw();
		}
	}
}

void Piece::CreateBlock()
{
	for (int y = 0; y < blockY; y++)
	{
		blocks.emplace_back(std::vector<Block>{});

		for (int x = 0; x < blockX; x++)
		{
			//blocks[y].emplace_back(Block{});
			blocks[y][x].Initialize();
		}
	}

}

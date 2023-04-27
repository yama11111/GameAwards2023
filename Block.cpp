#include "Block.h"
using namespace std;


//インクリメント
Block::Block()
{
	block_.Initialize({ {}, {}, {1.0f,1.0f,1.0f} });
	blockDra_.Initialize(&block_, IMode::Type::Normal);
}

//デクリメント
Block::~Block()
{
}

//初期化
void Block::Initialize()
{
	block_.Initialize({ {}, {}, {1.0f,1.0f,1.0f} });
	blockDra_.Initialize(&block_, IMode::Type::Normal);
}

//更新
void Block::Update(YGame::Transform filter)
{
	/*if (ClearFlag)
	{
		timer_--;
	}*/

	if (timer_ < 1)
	{
		ClearFlag = false;
	}

	// ブロック
	block_.UpdateMatrix();
	blockDra_.Update();
}

//描画
void Block::Draw()
{
	if (nowKind != None)
	{
		//右の条件消すとブロック消えるよ
		if (ClearFlag == false || nowKind != ColorB)
		{
			blockDra_.Draw();
		}
	}
}

//リセット
void Block::Reset()
{
	block_.Initialize({ {}, {}, {1.0f,1.0f,1.0f} });
	blockDra_.Initialize(&block_, IMode::Type::Normal);
}

//全ブロックの位置代入
void Block::SetBlocksPos(YMath::Vector3 pos)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			blocksDra_[i + j];
		}
	}
}

void Block::MovePos(int block)
{
	float spd = 0.1f * block;

	block_.pos_.y_ += spd * 2;
	block_.scale_.y_ += spd ;

}

void Block::MovePosYUp(int block)
{
	float size = block + 0.55;

	if (block_.scale_.y_ >= block)
	{
		upFlag = false;
		return;
	}

	float spd = 0.1f;

	block_.pos_.y_ += spd * 2;
	block_.scale_.y_ += spd;

	// ブロック
	block_.UpdateMatrix();
	blockDra_.Update();
}

void Block::MovePosYDown()
{
	if (upTimer > 0)
	{
		upTimer--;
		return;
	}

	if (block_.scale_.y_ < 0.55f)
	{
		return;
	}

	float spd = 0.1f;

	block_.pos_.y_ -= spd * 2;
	block_.scale_.y_ -= spd;

	// ブロック
	block_.UpdateMatrix();
	blockDra_.Update();
}

//ブロックを生成後に描画する種類を変える
void Block::SetMode()
{
	//色付きブロック
	if (nowKind == ColorB)
	{
		blockDra_.Initialize(&block_, IMode::Type::Movable);
		return;
	}

	////何も描画しない
	//if (nowKind == None)
	//{
	//	blockDra_.Initialize(&block_, IDrawer::Mode::None);
	//	return;
	//}

	//普通のブロック
	if (nowKind == Normal)
	{
		blockDra_.Initialize(&block_, IMode::Type::Normal);
		return;
	}
}
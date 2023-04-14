#include "Block.h"

//インクリメント
Block::Block()
{
	block_.Initialize({ {}, {}, {1.0f,1.0f,1.0f} });
	blockDra_.Initialize(&block_, IDrawer::Mode::Normal);
}

//デクリメント
Block::~Block()
{
}

//初期化
void Block::Initialize()
{
	block_.Initialize({ {}, {}, {1.0f,1.0f,1.0f} });
	blockDra_.Initialize(&block_, IDrawer::Mode::Normal);
}

//更新
void Block::Update(YGame::Transform filter)
{
	if (ClearFlag)
	{
		timer_--;
	}

	if (timer_ < 1)
	{
		ClearFlag = false;
	}

	// ブロック
	block_.UpdateMatrix();
	blockDra_.Update();
}

//Pre描画(フィルターの前)
void Block::PreDraw()
{
	if (nowKind != None)
	{
		if (ClearFlag == false)
		{
			blockDra_.PreDraw();
		}
	}
}

//Post描画(フィルターの後)
void Block::PostDraw()
{
	if (nowKind != None)
	{
		if (ClearFlag == false)
		{
			blockDra_.PostDraw();
		}
	}
}

//リセット
void Block::Reset()
{
	block_.Initialize({ {}, {}, {1.0f,1.0f,1.0f} });
	blockDra_.Initialize(&block_, IDrawer::Mode::Normal);
}

//ブロックを生成後に描画する種類を変える
void Block::SetMode()
{
	//色付きブロック
	if (nowKind == ColorB)
	{
		blockDra_.Initialize(&block_, IDrawer::Mode::Red);
		return;
	}

	//何も描画しない
	if (nowKind == None)
	{
		blockDra_.Initialize(&block_, IDrawer::Mode::None);
		return;
	}

	//普通のブロック
	if (nowKind == Normal)
	{
		blockDra_.Initialize(&block_, IDrawer::Mode::Normal);
		return;
	}
}
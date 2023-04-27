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
void Block::Update()
{
	// ブロック
	block_.UpdateMatrix();
	blockDra_.Update();
}

//描画
void Block::Draw()
{
	//描画しないモードでないなら
	if (nowKind != None)
	{
		blockDra_.Draw();
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
	block_.pos_ = pos;
}

//ブロックを生成後に描画する種類を変える
void Block::SetMode()
{
	////何も描画しない
	//if (nowKind == None)
	//{
	//	blockDra_.Initialize(&block_, IDrawer::Mode::None);
	//	return;
	//}

	////普通のブロック
	//if (nowKind == Normal)
	//{
	//	blockDra_.Initialize(&block_, IMode::Type::Normal);
	//	return;
	//}
}
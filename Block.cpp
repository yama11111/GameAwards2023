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

	rotCount = 0;
	rotRight = false;
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

//右回転
void Block::RotRight(int number)
{
	//if (rotRight == false)
	{
		//数
		int countX = 9;
		int countY = 9;

		int Check = countX / 2 + 1;

		//縦横
		int x = number;
		int y = number;

		//位置を計算で
		y = number / countY;
		x = number - (y * countX);

		//移動ブロック数

		//左にあるブロック用　右はーをつける
		int moveX = (countX - 1) - ((x + 1) * 2);

		//上にあるブロック用　下はーをつける
		int moveY = (countY - 1) - ((y + 1) * 2);

		//左
		if (x < Check)
		{
			//左上
			if (y < Check)
			{
				block_.pos_.x_ += cos(3.14f / 180 * 20);
				block_.pos_.y_ += sin(3.14f / 180 * 20);
				return;
			}
			////左下
			//else if (y > Check - 1)
			//{
			//	block_.pos_.y_ += moveY * 1.0f;
			//}
		}
		////右
		//else if (x > Check - 1)
		//{
		//	//右上
		//	if (y < Check)
		//	{
		//		block_.pos_.y_ += -moveY * 1.0f;
		//	}
		//	//右下
		//	else if (y > Check - 1)
		//	{
		//		block_.pos_.x_ += -moveX * 1.0f;
		//	}
		//}
		
		{
			block_.pos_.x_ = 1000;
			block_.pos_.y_ = 1000;
		}
	}

	//rotCount++;

	/*if (rotCount > 20)
	{
		rotRight = true;
	}*/



	/*float angle -= spd.x / (float)dis * MyMath::PIx2;
#pragma endregion
	if (angle <= -1) angle += 1;

	float angle_ = angle * MyMath::PIx2;

	pos.x = cos(angle_) * dis;
	pos.y = sin(angle_) * dis;

	block_.pos_.x_;
	block_.pos_.y_;*/
}

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
	ClearFlag = false;

	//プレイヤーの上下左右
	float b_top = block_.pos_.y_ - block_.scale_.y_;
	float b_bottom = block_.pos_.y_ + block_.scale_.y_;
	float b_right = block_.pos_.x_ + block_.scale_.x_;
	float b_left = block_.pos_.x_ - block_.scale_.x_;

	//フィルターの上下左右
	float f_top = filter.pos_.y_ - (filter.scale_.y_ * 2);
	float f_bottom = filter.pos_.y_ + (filter.scale_.y_ * 2);
	float f_right = filter.pos_.x_ + (filter.scale_.x_ * 2);
	float f_left = filter.pos_.x_ - (filter.scale_.x_ * 2);

	//SetsukeFlag(false);

	if (nowKind == ColorB)
	{
		//フィルターに当たっているか
		if (b_left < f_right ||
			b_right > f_left ||
			b_top  < f_bottom ||
			b_bottom > f_top)
		{
			//完全にフィルター内にいるか
			if (b_right < f_right &&
				b_left > f_left &&
				b_bottom  < f_bottom &&
				b_top > f_top)
			{
				ClearFlag = true;
			}
			else
			{
				//どこの辺がプレイヤーに当たっているか
				//右上
				//if (b_right > f_right &&
				//	b_left < f_right &&
				//	b_bottom > f_top &&
				//	b_top < f_top)
				//{
				//	block_.scale_.y_ = block_.pos_.x_ - f_right;

				//	block_.scale_.y_ = f_top - block_.pos_.y_;
				//}
				////右下
				//else if (
				//	b_right > f_right &&
				//	b_left < f_right &&
				//	b_bottom > f_bottom &&
				//	b_top < f_bottom)
				//{
				//	block_.scale_.y_ = block_.pos_.x_ - f_right;

				//	block_.scale_.x_ = block_.pos_.y_ - f_bottom;
				//}
				////左上
				//else if (
				//	b_right > f_left &&
				//	b_left < f_left &&
				//	b_bottom > f_top &&
				//	b_top < f_top)
				//{
				//	block_.scale_.x_ = f_left - block_.pos_.x_;

				//	block_.scale_.y_ = f_top - block_.pos_.y_;
				//}
				////左下
				//else if (
				//	b_right > f_left &&
				//	b_left < f_left &&
				//	b_bottom > f_bottom &&
				//	b_top < f_bottom)
				//{
				//	block_.scale_.x_ = f_left - block_.pos_.x_;

				//	block_.scale_.x_ = block_.pos_.y_ - f_bottom;
				//}
				////右
				//else 
				if (b_left < f_right)
				{
					//block_.scale_.x_ = block_.pos_.x_ - f_right;
				//	sukeF = true;

				}
				//左
				else if (b_right > f_left)
				{
					//block_.scale_.x_ = f_left - block_.pos_.x_;
				//	sukeF = true;
				}
				//上
				else if (b_bottom > f_top)
				{
					///あってる
					//sukeF = true;
					//block_.scale_.y_ = f_top - block_.pos_.y_;
				}

				else if (b_top < f_bottom)
				{
					//できた
					//block_.scale_.y_ = block_.pos_.y_ - f_bottom;
					//sukeF = true;
				}
			}
		}
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
		blockDra_.PreDraw();
	}
}

//Post描画(フィルターの後)
void Block::PostDraw()
{
	if (nowKind != None)
	{
		blockDra_.PostDraw();
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
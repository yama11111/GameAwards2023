#include "Block.h"

Block::Block()
{
	block_.Initialize({ {}, {}, {1.0f,1.0f,1.0f} });
	blockDra_.Initialize(&block_, IDrawer::Mode::Normal);
}

Block::~Block()
{
}

void Block::Inilialize()
{
	block_.Initialize({ {}, {}, {1.0f,1.0f,1.0f} });
	blockDra_.Initialize(&block_, IDrawer::Mode::Normal);
}

void Block::Update(YGame::Transform filter)
{
	sukeF = false;

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
			sukeF = true;

			//完全にフィルター内にいるか
			if (b_right < f_right &&
				b_left > f_left &&
				b_bottom  < f_bottom &&
				b_top > f_top)
			{

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
				if (b_right > f_right)
				{
					//block_.scale_.x_ = block_.pos_.x_ - f_right;
					sukeF = false;

				}
				//左
				else if (b_right > f_left)
				{
					//block_.scale_.x_ = f_left - block_.pos_.x_;
					sukeF = false;
				}
				//上
				else if (b_bottom > f_top)
				{
					//あってる
					sukeF = false;
					//block_.scale_.y_ = f_top - block_.pos_.y_;
				}

				else if (b_bottom > f_bottom)
				{
					//できた
					//block_.scale_.y_ = block_.pos_.y_ - f_bottom;
					sukeF = false;
				}
			}
		}
	}

	// ブロック
	block_.UpdateMatrix();
	blockDra_.Update();
}

void Block::Draw()
{
	blockDra_.PostDraw();
}

void Block::Reset()
{
	block_.Initialize({ {}, {}, {1.0f,1.0f,1.0f} });
	blockDra_.Initialize(&block_, IDrawer::Mode::Normal);
}

void Block::SetMode()
{
	if (nowKind == ColorB)
	{
		blockDra_.Initialize(&block_, IDrawer::Mode::Red);
	}

	if (nowKind == None)
	{
		blockDra_.Initialize(&block_, IDrawer::Mode::None);
	}

	if (nowKind == Normal)
	{
		blockDra_.Initialize(&block_, IDrawer::Mode::Normal);
	}
}
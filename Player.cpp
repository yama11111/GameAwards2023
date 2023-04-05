#include "Player.h"
#include "MathUtillity.h"

#pragma region 名前空間宣言
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;
#pragma endregion 

//YMath::Vector3 BoxCollision(Vector3 posP, Vector2 sizePRL, Vector2 sizePUD, Vector3 posF, Vector2 sizeF, Vector2 DS, Vector2 AW)
//{
//	YMath::Vector3 nowPosP = posP;
//	YMath::Vector3 nowPosF = posF;
//
//	//プレイヤーの上下左右
//	float p_top = nowPosP.y_ - sizePUD.x_;
//	float p_bottom = nowPosP.y_ + sizePUD.y_;
//	float p_right = nowPosP.x_ + sizePRL.x_;
//	float p_left = nowPosP.x_ - sizePRL.y_;
//
//	//フィルターの上下左右
//	float f_top = nowPosF.y_ - sizeF.y_;
//	float f_bottom = nowPosF.y_ + sizeF.y_;
//	float f_right = nowPosF.x_ + sizeF.x_;
//	float f_left = nowPosF.x_ - sizeF.x_;
//
//	//フィルターに当たっているか
//	if (p_left < f_right &&
//		p_right > f_left &&
//		p_top  < f_bottom &&
//		p_bottom > f_top)
//	{
//		while (p_left < f_right &&
//			p_right > f_left &&
//			p_top  < f_bottom &&
//			p_bottom > f_top)
//		{
//			nowPosP.x_ -= DS.x_;
//			nowPosP.y_ -= DS.y_;
//
//			nowPosP.x_ += AW.x_;
//			nowPosP.y_ += AW.y_;
//
//			//プレイヤーの上下左右
//			p_top = nowPosP.y_ - sizePUD.x_;
//			p_bottom = nowPosP.y_ + sizePUD.y_;
//			p_right = nowPosP.x_ + sizePRL.x_;
//			p_left = nowPosP.x_ - sizePRL.y_;
//		}
//	}
//
//	return nowPosP;
//}
//
//YMath::Vector3 BoxCollision(Vector3 posP, Vector2 sizePRL, Vector2 sizePUD, Vector3 posF, Vector2 sizeLR, Vector2 sizeUD, Vector2 DS, Vector2 AW)
//{
//	YMath::Vector3 nowPosP = posP;
//	YMath::Vector3 nowPosF = posF;
//
//	YMath::Vector2 Ds = DS;
//	YMath::Vector2 Aw = AW;
//
//	Ds.x_ *= 0.1f;
//	Ds.y_ *= 0.1f;
//	Aw.x_ *= 0.1f;
//	Aw.y_ *= 0.1f;
//
//	//プレイヤーの上下左右
//		//プレイヤーの上下左右
//	float p_top = nowPosP.y_ - sizePUD.x_;
//	float p_bottom = nowPosP.y_ + sizePUD.y_;
//	float p_right = nowPosP.x_ + sizePRL.x_;
//	float p_left = nowPosP.x_ - sizePRL.y_;
//
//	//フィルターの上下左右
//	float f_top = nowPosF.y_ - sizeUD.x_;
//	float f_bottom = nowPosF.y_ + sizeUD.y_;
//	float f_right = nowPosF.x_ + sizeLR.y_;
//	float f_left = nowPosF.x_ - sizeLR.x_;
//
//	//フィルターに当たっているか
//	if (p_left < f_right &&
//		p_right > f_left &&
//		p_top  < f_bottom &&
//		p_bottom > f_top)
//	{
//		while (p_left < f_right &&
//			p_right > f_left &&
//			p_top  < f_bottom &&
//			p_bottom > f_top)
//		{
//			nowPosP.x_ -= Ds.x_;
//			nowPosP.y_ -= Ds.y_;
//			nowPosP.x_ += Aw.x_;
//			nowPosP.y_ += Aw.y_;
//
//			//プレイヤーの上下左右
//			p_top = nowPosP.y_ - sizePUD.x_;
//			p_bottom = nowPosP.y_ + sizePUD.y_;
//			p_right = nowPosP.x_ + sizePRL.x_;
//			p_left = nowPosP.x_ - sizePRL.y_;
//		}
//	}
//
//	return nowPosP;
//}
//

Player::Player()
{
	player_.Initialize({ {}, {}, {0.5f,0.5f,0.5f} });
	direction_ = { +1.0f,0.0f,0.0f };
	playerDra_.Initialize(&player_, &direction_, IDrawer::Mode::Red);

	player_.scale_.x_ = 4.0f;
	player_.scale_.y_ = 8.0f;

	//位置
	playerPos.x_ = 300;
	playerPos.y_ = 400;

	//サイズ
	playerSize.x_ = 21;
	playerSize.y_ = 32;

	//確認用
	playerCheckPos.x_ = 0;
	playerCheckPos.y_ = 0;

	//
	playerCheckSize.x_ = player_.scale_.x_;
	playerCheckSize.y_ = player_.scale_.y_;

	//確認用
	playerCheckSizeRL.x_ = player_.scale_.x_;
	playerCheckSizeRL.y_ = player_.scale_.y_;

	//確認用
	playerCheckSizeUD.x_ = player_.scale_.x_;
	playerCheckSizeUD.y_ = player_.scale_.y_;

	//入力している値を渡す
	DS.x_ = false;
	DS.y_ = false;

	//入力している値を渡す
	AW.x_ = false;
	AW.y_ = false;

	//プレイヤーがすり抜けるか
	SetsukeFlag(false);

	//フィルターの角に当たっているかどうか
	SetkadoFlag(false);

	Jump = 0;
	JumpPower = 0;

	JumpFlag = false;
}

Player::~Player()
{

}

void Player::Inilialize()
{
	player_.Initialize({ {}, {}, {0.5f,0.5f,0.5f} });
	direction_ = { +1.0f,0.0f,0.0f };
	playerDra_.Initialize(&player_, &direction_, IDrawer::Mode::Red);

	//位置
	playerPos.x_ = 300;
	playerPos.y_ = 400;

	//サイズ
	playerSize.x_ = 21;
	playerSize.y_ = 32;

	//確認用
	playerCheckPos.x_ = 0;
	playerCheckPos.y_ = 0;

	//確認用
	playerCheckSize.x_ = player_.scale_.x_;
	playerCheckSize.y_ = player_.scale_.y_;

	//確認用
	playerCheckSizeRL.x_ = player_.scale_.x_;
	playerCheckSizeRL.y_ = player_.scale_.y_;

	//確認用
	playerCheckSizeUD.x_ = player_.scale_.x_;
	playerCheckSizeUD.y_ = player_.scale_.y_;

	//入力している値を渡す
	DS.x_ = false;
	DS.y_ = false;

	//入力している値を渡す
	AW.x_ = false;
	AW.y_ = false;

	//プレイヤーがすり抜けるか
	SetsukeFlag(false);

	//フィルターの角に当たっているかどうか
	SetkadoFlag(false);

	Jump = 0;
	JumpPower = 0;

	JumpFlag = false;
}

void Player::Update(Transform filterPos, Vector2 filterSizeLR, Vector2 filterSizeUD)
{
	DS.x_ = 0;
	DS.y_ = 0;

	AW.x_ = 0;
	AW.y_ = 0;

	// 更新処理
	float moveSpd = 3.0f;

	//playerPos.y += 1;

	playerCheckPos.x_ = player_.pos_.x_;
	playerCheckPos.y_ = player_.pos_.y_;

	//確認用
	playerCheckSize.x_ = player_.scale_.x_ * 2;
	playerCheckSize.y_ = player_.scale_.y_ * 2;

	//確認用
	playerCheckSizeRL.x_ = player_.scale_.x_;
	playerCheckSizeRL.y_ = player_.scale_.y_;

	//確認用
	playerCheckSizeUD.x_ = player_.scale_.x_;
	playerCheckSizeUD.y_ = player_.scale_.y_;

	SetkadoFlag(false);

	//プレイヤーの上下左右
	float p_top = playerCheckPos.y_ - playerCheckSize.y_;
	float p_bottom = playerCheckPos.y_ + playerCheckSize.y_;
	float p_right = playerCheckPos.x_ + playerCheckSize.x_;
	float p_left = playerCheckPos.x_ - playerCheckSize.x_;

	//フィルターの上下左右
	float f_top = filterPos.pos_.y_ - filterSizeUD.y_;
	float f_bottom = filterPos.pos_.y_ + filterSizeUD.y_;
	float f_right = filterPos.pos_.x_ + filterSizeLR.x_;
	float f_left = filterPos.pos_.x_ - filterSizeLR.x_;

	SetsukeFlag(false);

	//フィルターに当たっているか
	if (p_left < f_right ||
		p_right > f_left ||
		p_top  < f_bottom ||
		p_bottom > f_top)
	{
		//完全にフィルター内にいるか
		if (p_right < f_right &&
			p_left > f_left &&
			p_bottom  < f_bottom &&
			p_top > f_top)
		{
			SetsukeFlag(true);
		}
		else
		{
			//どこの辺がプレイヤーに当たっているか
			//右上
			if (p_right > f_right &&
				p_left < f_right &&
				p_bottom > f_top &&
				p_top < f_top)
			{
				playerCheckSizeRL.y_ = playerPos.x_ - f_right;

				playerCheckSizeUD.y_ = f_top - playerPos.y_;

				SetkadoFlag(true);
			}
			//右下
			else if (
				p_right > f_right &&
				p_left < f_right &&
				p_bottom > f_bottom &&
				p_top < f_bottom)
			{
				playerCheckSizeRL.y_ = playerPos.x_ - f_right;

				playerCheckSizeUD.x_ = playerPos.y_ - f_bottom;

				SetkadoFlag(true);
			}
			//左上
			else if (
				p_right > f_left &&
				p_left < f_left &&
				p_bottom > f_top &&
				p_top < f_top)
			{
				playerCheckSizeRL.x_ = f_left - playerPos.x_;

				playerCheckSizeUD.y_ = f_top - playerPos.y_;

				SetkadoFlag(true);
			}
			//左下
			else if (
				p_right > f_left &&
				p_left < f_left &&
				p_bottom > f_bottom &&
				p_top < f_bottom)
			{
				playerCheckSizeRL.x_ = f_left - playerPos.x_;

				playerCheckSizeUD.x_ = playerPos.y_ - f_bottom;

				SetkadoFlag(true);
			}
			//右
			else if (
				p_right > f_right &&
				p_left < f_right)
			{
				playerCheckSizeRL.y_ = playerPos.x_ - f_right;

			}
			//左
			else if (p_right > f_left &&
				p_left < f_left)
			{
				playerCheckSizeRL.x_ = f_left - playerPos.x_;
			}
			//上
			else if (p_bottom > f_top &&
				p_top < f_top)
			{
				//あってる
				playerCheckSizeUD.y_ = f_top - playerPos.y_;
			}

			else if (p_bottom > f_bottom &&
				p_top < f_bottom)
			{
				//できた
				playerCheckSizeUD.x_ = playerPos.y_ - f_bottom;
			}

		}
	}

	//if (chengeF)
	//{
	//	if (Keys::IsDown(DIK_D))
	//	{
	//		playerPos.x_ += moveSpd;

	//		DS.x_ = CheckHitKey(KEY_INPUT_D);
	//		DS.y_ = 0;

	//		AW.x_ = 0;
	//		AW.y_ = 0;

	//		if (!sukeF)
	//		{
	//			if (kadoF)
	//			{
	//				Vector2 size = { playerSize.x_,playerSize.x_ };

	//				for (int i = 0; i < boxcount; i++)
	//				{
	//					playerPos = BoxCollision(
	//						playerPos,
	//						size,
	//						playerCheckSizeUD,
	//						Box[i],
	//						BoxSize,
	//						DS,
	//						AW);
	//				}

	//				size.x_ = playerSize.y_;
	//				size.y_ = playerSize.y_;

	//				for (int i = 0; i < boxcount; i++)
	//				{
	//					playerPos = BoxCollision(
	//						playerPos,
	//						playerCheckSizeRL,
	//						size,
	//						Box[i],
	//						BoxSize,
	//						DS,
	//						AW);
	//				}
	//			}
	//			else
	//			{
	//				for (int i = 0; i < boxcount; i++)
	//				{
	//					playerPos = BoxCollision(
	//						playerPos,
	//						playerCheckSizeRL,
	//						playerCheckSizeUD,
	//						Box[i],
	//						BoxSize,
	//						DS,
	//						AW);
	//				}
	//			}
	//		}
	//	}

	//	if (CheckHitKey(KEY_INPUT_A))
	//	{
	//		playerPos.x_ -= moveSpd;

	//		DS.x_ = 0;
	//		DS.y_ = 0;

	//		AW.x_ = CheckHitKey(KEY_INPUT_A);
	//		AW.y_ = 0;

	//		if (!sukeF)
	//		{
	//			if (kadoF)
	//			{
	//				Vector2 size = { playerSize.x_,playerSize.x_ };

	//				for (int i = 0; i < boxcount; i++)
	//				{
	//					playerPos = BoxCollision(
	//						playerPos,
	//						size,
	//						playerCheckSizeUD,
	//						Box[i],
	//						BoxSize,
	//						DS,
	//						AW);
	//				}

	//				size.x_ = playerSize.y_;
	//				size.y_ = playerSize.y_;

	//				for (int i = 0; i < boxcount; i++)
	//				{
	//					playerPos = BoxCollision(
	//						playerPos,
	//						playerCheckSizeRL,
	//						size,
	//						Box[i],
	//						BoxSize,
	//						DS,
	//						AW);
	//				}
	//			}
	//			else
	//			{
	//				for (int i = 0; i < boxcount; i++)
	//				{
	//					playerPos = BoxCollision(
	//						playerPos,
	//						playerCheckSizeRL,
	//						playerCheckSizeUD,
	//						Box[i],
	//						BoxSize,
	//						DS,
	//						AW);
	//				}
	//			}
	//		}
	//	}

	//	if (CheckHitKey(KEY_INPUT_S))
	//	{
	//		playerPos.y_ += moveSpd;

	//		DS.x_ = 0;
	//		DS.y_ = CheckHitKey(KEY_INPUT_S);
	//		//DS.y = 1;

	//		AW.x_ = 0;
	//		AW.y_ = 0;

	//		if (!sukeF)
	//		{
	//			if (kadoF)
	//			{
	//				Vector2 size = { playerSize.x_,playerSize.x_ };

	//				for (int i = 0; i < boxcount; i++)
	//				{
	//					playerPos = BoxCollision(
	//						playerPos,
	//						size,
	//						playerCheckSizeUD,
	//						Box[i],
	//						BoxSize,
	//						DS,
	//						AW);
	//				}

	//				size.x_ = playerSize.y_;
	//				size.y_ = playerSize.y_;

	//				for (int i = 0; i < boxcount; i++)
	//				{
	//					playerPos = BoxCollision(
	//						playerPos,
	//						playerCheckSizeRL,
	//						size,
	//						Box[i],
	//						BoxSize,
	//						DS,
	//						AW);
	//				}
	//			}
	//			else
	//			{
	//				for (int i = 0; i < boxcount; i++)
	//				{
	//					playerPos = BoxCollision(
	//						playerPos,
	//						playerCheckSizeRL,
	//						playerCheckSizeUD,
	//						Box[i],
	//						BoxSize,
	//						DS,
	//						AW);
	//				}
	//			}
	//		}
	//	}

	//	if (CheckHitKey(KEY_INPUT_W))
	//	{
	//		playerPos.y_ -= moveSpd;

	//		DS.x_ = 0;
	//		DS.y_ = 0;

	//		AW.x_ = 0;
	//		AW.y_ = CheckHitKey(KEY_INPUT_W);

	//		if (!sukeF)
	//		{
	//			if (kadoF)	//GetkadoFlag() == true
	//			{
	//				Vector2 size = { playerSize.x_,playerSize.x_ };

	//				for (int i = 0; i < boxcount; i++)
	//				{
	//					playerPos = BoxCollision(
	//						playerPos,
	//						size,
	//						playerCheckSizeUD,
	//						Box[i],
	//						BoxSize,
	//						DS,
	//						AW);
	//				}

	//				size.x_ = playerSize.y_;
	//				size.y_ = playerSize.y_;

	//				for (int i = 0; i < boxcount; i++)
	//				{
	//					playerPos = BoxCollision(
	//						playerPos,
	//						playerCheckSizeRL,
	//						size,
	//						Box[i],
	//						BoxSize,
	//						DS,
	//						AW);
	//				}
	//			}
	//			else
	//			{
	//				for (int i = 0; i < boxcount; i++)
	//				{
	//					playerPos = BoxCollision(
	//						playerPos,
	//						playerCheckSizeRL,
	//						playerCheckSizeUD,
	//						Box[i],
	//						BoxSize,
	//						DS,
	//						AW);
	//				}
	//			}
	//		}
	//	}
	//}

	player_.UpdateMatrix();
	playerDra_.Update();
}

void Player::Draw()
{
	playerDra_.PreDraw();
}

void Player::Reset()
{
	player_.Initialize({ {}, {}, {1.0f,1.0f,1.0f} });
	direction_ = { +1.0f,0.0f,0.0f };
	playerDra_.Reset(IDrawer::Mode::Red);

	//位置
	playerPos.x_ = 300;
	playerPos.y_ = 400;

	//サイズ
	playerSize.x_ = 21;
	playerSize.y_ = 32;

	//確認用
	playerCheckPos.x_ = 0;
	playerCheckPos.y_ = 0;

	//確認用
	playerCheckSize.x_ = player_.scale_.x_;
	playerCheckSize.y_ = player_.scale_.y_;

	//確認用
	playerCheckSizeRL.x_ = player_.scale_.x_;
	playerCheckSizeRL.y_ = player_.scale_.y_;

	//確認用
	playerCheckSizeUD.x_ = player_.scale_.x_;
	playerCheckSizeUD.y_ = player_.scale_.y_;

	//入力している値を渡す
	DS.x_ = false;
	DS.y_ = false;

	//入力している値を渡す
	AW.x_ = false;
	AW.y_ = false;

	//プレイヤーがすり抜けるか
	SetsukeFlag(false);

	//フィルターの角に当たっているかどうか
	SetkadoFlag(false);

	Jump = 0;
	JumpPower = 0;

	JumpFlag = false;

	Gravity = 0;
	GravityPower = 0;
}
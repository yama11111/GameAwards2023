#include "Player.h"
#include "MathUtillity.h"
#include "Keys.h"
#include "imgui.h"

#pragma region 名前空間宣言
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;
#pragma endregion 

Player::Player()
{
	player_.Initialize({ {}, {}, {0.5f,0.5f,1.0f} });
	direction_ = { +1.0f,0.0f,0.0f };
	playerDra_.Initialize(&player_, &direction_, IDrawer::Mode::Red);
	filterDra_.Initialize(&player_);

	player_.scale_.x_ = 4.0f;
	player_.scale_.y_ = 8.0f;

	//プレイヤーがすり抜けるか
	SetClearFlag(false);

	//フィルターの角に当たっているかどうか
	SetCornerFlag(false);

	Jump = 0;
	JumpPower = 0;

	JumpFlag = false;
}

Player::~Player()
{

}

void Player::Initialize()
{
	player_.Initialize({ {}, {}, {0.5f,0.5f,1.0f} });
	direction_ = { +1.0f,0.0f,0.0f };
	playerDra_.Initialize(&player_, &direction_, IDrawer::Mode::Red);
	filterDra_.Initialize(&player_);

	//プレイヤーがすり抜けるか
	SetClearFlag(false);

	//フィルターの角に当たっているかどうか
	SetCornerFlag(false);

	Jump = 0;
	JumpPower = 0;

	JumpFlag = false;
}

void Player::Initialize(YMath::Vector3 pos_, YMath::Vector3 rot_, YMath::Vector3 scale_)
{
	// フィルター
	player_.Initialize({ pos_, rot_, scale_ });
	direction_ = { +1.0f,0.0f,0.0f };
	playerDra_.Initialize(&player_, &direction_, IDrawer::Mode::Red);
	filterDra_.Initialize(&player_);

	//プレイヤーがすり抜けるか
	SetClearFlag(false);

	//フィルターの角に当たっているかどうか
	SetCornerFlag(false);

	Jump = 0;
	JumpPower = 0;

	JumpFlag = false;
}


//Pre描画(フィルターの前)
void Player::PreDraw()
{
	//playerDra_.PreDraw();
	//filterDra_.Draw();
}

//Post描画(フィルターの後)
void Player::PostDraw()
{
	//playerDra_.PostDraw();
	filterDra_.Draw();
}

void Player::Update()
{
	//更新
	player_.UpdateMatrix();
	playerDra_.Update();

	filterDra_.Update();
}

void Player::Update(Transform filterPos)
{
	YMath::Vector2 playerPos = { 0,0 };
	YMath::Vector2 playerSize = { 16,32 };

	YMath::Vector2 playerCheckPos = { 0,0 };
	YMath::Vector2 playerCheckSize = { 16,64 };

	YMath::Vector2 playerCheckSizeRL = { 16,64 };
	YMath::Vector2 playerCheckSizeUD = { 16,64 };

	//キーが押されているかどうか
	YMath::Vector2 DS;
	YMath::Vector2 AW;

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

	SetCornerFlag(false);

	//プレイヤーの上下左右
	float p_top = playerCheckPos.y_ - playerCheckSize.y_;
	float p_bottom = playerCheckPos.y_ + playerCheckSize.y_;
	float p_right = playerCheckPos.x_ + playerCheckSize.x_;
	float p_left = playerCheckPos.x_ - playerCheckSize.x_;

	//フィルターの上下左右
	float f_top = filterPos.pos_.y_ - filterPos.scale_.y_;
	float f_bottom = filterPos.pos_.y_ + filterPos.scale_.y_;
	float f_right = filterPos.pos_.x_ + filterPos.scale_.x_;
	float f_left = filterPos.pos_.x_ - filterPos.scale_.x_;

	//すり抜けフラグかつ今操作しているかどうか
	//SetClearFlag(false);

	//移動量を足す
	//player_.pos_ += movePos;

	//フィルターに当たっているか
	if (p_left < f_right ||
		p_right > f_left ||
		p_top  < f_bottom ||
		p_bottom > f_top)
	{
		//SetClearFlag(true);

		//完全にフィルター内にいるか
		if (p_right < f_right &&
			p_left > f_left &&
			p_bottom  < f_bottom &&
			p_top > f_top)
		{
			//SetClearFlag(true);
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

				SetCornerFlag(true);
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

				SetCornerFlag(true);
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

				SetCornerFlag(true);
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

				SetCornerFlag(true);
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

	//後で消す
	{
		/*if (chengeF)
		{
			if (Keys::IsDown(DIK_D))
			{
				playerPos.x_ += moveSpd;

				DS.x_ = CheckHitKey(KEY_INPUT_D);
				DS.y_ = 0;

				AW.x_ = 0;
				AW.y_ = 0;

				if (!sukeF)
				{
					if (kadoF)
					{
						Vector2 size = { playerSize.x_,playerSize.x_ };

						for (int i = 0; i < boxcount; i++)
						{
							playerPos = BoxCollision(
								playerPos,
								size,
								playerCheckSizeUD,
								Box[i],
								BoxSize,
								DS,
								AW);
						}

						size.x_ = playerSize.y_;
						size.y_ = playerSize.y_;

						for (int i = 0; i < boxcount; i++)
						{
							playerPos = BoxCollision(
								playerPos,
								playerCheckSizeRL,
								size,
								Box[i],
								BoxSize,
								DS,
								AW);
						}
					}
					else
					{
						for (int i = 0; i < boxcount; i++)
						{
							playerPos = BoxCollision(
								playerPos,
								playerCheckSizeRL,
								playerCheckSizeUD,
								Box[i],
								BoxSize,
								DS,
								AW);
						}
					}
				}
			}

			if (CheckHitKey(KEY_INPUT_A))
			{
				playerPos.x_ -= moveSpd;

				DS.x_ = 0;
				DS.y_ = 0;

				AW.x_ = CheckHitKey(KEY_INPUT_A);
				AW.y_ = 0;

				if (!sukeF)
				{
					if (kadoF)
					{
						Vector2 size = { playerSize.x_,playerSize.x_ };

						for (int i = 0; i < boxcount; i++)
						{
							playerPos = BoxCollision(
								playerPos,
								size,
								playerCheckSizeUD,
								Box[i],
								BoxSize,
								DS,
								AW);
						}

						size.x_ = playerSize.y_;
						size.y_ = playerSize.y_;

						for (int i = 0; i < boxcount; i++)
						{
							playerPos = BoxCollision(
								playerPos,
								playerCheckSizeRL,
								size,
								Box[i],
								BoxSize,
								DS,
								AW);
						}
					}
					else
					{
						for (int i = 0; i < boxcount; i++)
						{
							playerPos = BoxCollision(
								playerPos,
								playerCheckSizeRL,
								playerCheckSizeUD,
								Box[i],
								BoxSize,
								DS,
								AW);
						}
					}
				}
			}*/



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

		/*ImGui::Begin("Player");
		ImGui::SliderFloat("pos", &player_.pos_.x_, -500, 500);
		ImGui::SliderFloat("pos", &player_.pos_.y_, -500, 500);
		ImGui::SliderFloat("scale", &player_.scale_.x_, 0, 10);
		ImGui::SliderFloat("scale", &player_.scale_.y_, 0, 10);
		ImGui::End();*/

	}

	/*if (GetClearFlag())
	{

	}*/

	ImGui::Begin("Player");
	ImGui::Checkbox("J", &JumpFlag);
	ImGui::SliderFloat("JP", &JumpPower, 0, 10);
	ImGui::SliderFloat("G", &Gravity, 0, 10);
	ImGui::SliderFloat("GP", &GravityPower, 0, 10);
	ImGui::SliderFloat("X", &player_.pos_.x_, 0, 10);
	ImGui::SliderFloat("Y", &player_.pos_.y_, 0, 10);
	ImGui::End();


	//更新
	player_.UpdateMatrix();
	playerDra_.Update();

	filterDra_.Update();
}


void Player::Reset()
{
	player_.Initialize({ {0.0f,0.0f,0.0f}, {}, {0.5f,0.5f,0.5f} });
	direction_ = { +1.0f,0.0f,0.0f };
	playerDra_.Reset(IDrawer::Mode::Red);
	filterDra_.Reset();

	//位置
	player_.pos_.x_ = startPos.x_;
	player_.pos_.y_ = startPos.y_;

	//プレイヤーがすり抜けるか
	SetClearFlag(false);

	//フィルターの角に当たっているかどうか
	SetCornerFlag(false);

	Jump = 0;
	JumpPower = 0;

	JumpFlag = false;

	Gravity = 0;
	GravityPower = 0;
}

void Player::JumpReset()
{
	Jump = 1.0f;
	JumpPower = 0;

	JumpFlag = true;

	Gravity = 0;
	GravityPower = 0;
}

//重力、浮力の加算
void Player::AddGravity()
{
	//フラグがonなら
	if (JumpFlag)
	{
		//加算する力が残っているなら
		if (Jump > 0)
		{
			//重力分加算
			JumpPower += Gravity;

			//ジャンプ力減算
			Jump -= JumpPower;

			//座標から引く
			player_.pos_.y_ += Jump;
		}

		//重力
		if (Gravity < 0.2f)
		{
			GravityPower += 0.02f;
			Gravity += GravityPower;
		}
	}

	//ジャンプ力がなくなったら
	/*if (Jump < 0)
	{
		JumpFlag = false;
	}*/

	//////if (!JumpFlag)
//	{
		//重力かける
		player_.pos_.y_ -= Gravity;
//	}
}

void Player::PlayerMove(YMath::Vector3 pos)
{
	//移動
	player_.pos_ += pos;

	//更新処理
	player_.UpdateMatrix();
	playerDra_.Update();

	filterDra_.Update();
}

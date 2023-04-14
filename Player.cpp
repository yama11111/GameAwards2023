#include "Player.h"
#include "MathUtillity.h"
#include "Keys.h"
#include "imgui.h"

#pragma region ���O��Ԑ錾
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

	//�v���C���[�����蔲���邩
	SetClearFlag(false);

	//�t�B���^�[�̊p�ɓ������Ă��邩�ǂ���
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

	//�v���C���[�����蔲���邩
	SetClearFlag(false);

	//�t�B���^�[�̊p�ɓ������Ă��邩�ǂ���
	SetCornerFlag(false);

	Jump = 0;
	JumpPower = 0;

	JumpFlag = false;
}

void Player::Initialize(YMath::Vector3 pos_, YMath::Vector3 rot_, YMath::Vector3 scale_)
{
	// �t�B���^�[
	player_.Initialize({ pos_, rot_, scale_ });
	direction_ = { +1.0f,0.0f,0.0f };
	playerDra_.Initialize(&player_, &direction_, IDrawer::Mode::Red);
	filterDra_.Initialize(&player_);

	//�v���C���[�����蔲���邩
	SetClearFlag(false);

	//�t�B���^�[�̊p�ɓ������Ă��邩�ǂ���
	SetCornerFlag(false);

	Jump = 0;
	JumpPower = 0;

	JumpFlag = false;
}


//Pre�`��(�t�B���^�[�̑O)
void Player::PreDraw()
{
	//playerDra_.PreDraw();
	//filterDra_.Draw();
}

//Post�`��(�t�B���^�[�̌�)
void Player::PostDraw()
{
	//playerDra_.PostDraw();
	filterDra_.Draw();
}

void Player::Update()
{
	//�X�V
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

	//�L�[��������Ă��邩�ǂ���
	YMath::Vector2 DS;
	YMath::Vector2 AW;

	DS.x_ = 0;
	DS.y_ = 0;

	AW.x_ = 0;
	AW.y_ = 0;

	// �X�V����
	float moveSpd = 3.0f;

	//playerPos.y += 1;

	playerCheckPos.x_ = player_.pos_.x_;
	playerCheckPos.y_ = player_.pos_.y_;

	//�m�F�p
	playerCheckSize.x_ = player_.scale_.x_ * 2;
	playerCheckSize.y_ = player_.scale_.y_ * 2;

	//�m�F�p
	playerCheckSizeRL.x_ = player_.scale_.x_;
	playerCheckSizeRL.y_ = player_.scale_.y_;

	//�m�F�p
	playerCheckSizeUD.x_ = player_.scale_.x_;
	playerCheckSizeUD.y_ = player_.scale_.y_;

	SetCornerFlag(false);

	//�v���C���[�̏㉺���E
	float p_top = playerCheckPos.y_ - playerCheckSize.y_;
	float p_bottom = playerCheckPos.y_ + playerCheckSize.y_;
	float p_right = playerCheckPos.x_ + playerCheckSize.x_;
	float p_left = playerCheckPos.x_ - playerCheckSize.x_;

	//�t�B���^�[�̏㉺���E
	float f_top = filterPos.pos_.y_ - filterPos.scale_.y_;
	float f_bottom = filterPos.pos_.y_ + filterPos.scale_.y_;
	float f_right = filterPos.pos_.x_ + filterPos.scale_.x_;
	float f_left = filterPos.pos_.x_ - filterPos.scale_.x_;

	//���蔲���t���O�������삵�Ă��邩�ǂ���
	//SetClearFlag(false);

	//�ړ��ʂ𑫂�
	//player_.pos_ += movePos;

	//�t�B���^�[�ɓ������Ă��邩
	if (p_left < f_right ||
		p_right > f_left ||
		p_top  < f_bottom ||
		p_bottom > f_top)
	{
		//SetClearFlag(true);

		//���S�Ƀt�B���^�[���ɂ��邩
		if (p_right < f_right &&
			p_left > f_left &&
			p_bottom  < f_bottom &&
			p_top > f_top)
		{
			//SetClearFlag(true);
		}
		else
		{
			//�ǂ��̕ӂ��v���C���[�ɓ������Ă��邩
			//�E��
			if (p_right > f_right &&
				p_left < f_right &&
				p_bottom > f_top &&
				p_top < f_top)
			{
				playerCheckSizeRL.y_ = playerPos.x_ - f_right;

				playerCheckSizeUD.y_ = f_top - playerPos.y_;

				SetCornerFlag(true);
			}
			//�E��
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
			//����
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
			//����
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
			//�E
			else if (
				p_right > f_right &&
				p_left < f_right)
			{
				playerCheckSizeRL.y_ = playerPos.x_ - f_right;

			}
			//��
			else if (p_right > f_left &&
				p_left < f_left)
			{
				playerCheckSizeRL.x_ = f_left - playerPos.x_;
			}
			//��
			else if (p_bottom > f_top &&
				p_top < f_top)
			{
				//�����Ă�
				playerCheckSizeUD.y_ = f_top - playerPos.y_;
			}

			else if (p_bottom > f_bottom &&
				p_top < f_bottom)
			{
				//�ł���
				playerCheckSizeUD.x_ = playerPos.y_ - f_bottom;
			}

		}
	}

	//��ŏ���
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


	//�X�V
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

	//�ʒu
	player_.pos_.x_ = startPos.x_;
	player_.pos_.y_ = startPos.y_;

	//�v���C���[�����蔲���邩
	SetClearFlag(false);

	//�t�B���^�[�̊p�ɓ������Ă��邩�ǂ���
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

//�d�́A���͂̉��Z
void Player::AddGravity()
{
	//�t���O��on�Ȃ�
	if (JumpFlag)
	{
		//���Z����͂��c���Ă���Ȃ�
		if (Jump > 0)
		{
			//�d�͕����Z
			JumpPower += Gravity;

			//�W�����v�͌��Z
			Jump -= JumpPower;

			//���W�������
			player_.pos_.y_ += Jump;
		}

		//�d��
		if (Gravity < 0.2f)
		{
			GravityPower += 0.02f;
			Gravity += GravityPower;
		}
	}

	//�W�����v�͂��Ȃ��Ȃ�����
	/*if (Jump < 0)
	{
		JumpFlag = false;
	}*/

	//////if (!JumpFlag)
//	{
		//�d�͂�����
		player_.pos_.y_ -= Gravity;
//	}
}

void Player::PlayerMove(YMath::Vector3 pos)
{
	//�ړ�
	player_.pos_ += pos;

	//�X�V����
	player_.UpdateMatrix();
	playerDra_.Update();

	filterDra_.Update();
}

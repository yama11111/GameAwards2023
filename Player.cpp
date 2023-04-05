#include "Player.h"
#include "MathUtillity.h"

#pragma region ���O��Ԑ錾
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
//	//�v���C���[�̏㉺���E
//	float p_top = nowPosP.y_ - sizePUD.x_;
//	float p_bottom = nowPosP.y_ + sizePUD.y_;
//	float p_right = nowPosP.x_ + sizePRL.x_;
//	float p_left = nowPosP.x_ - sizePRL.y_;
//
//	//�t�B���^�[�̏㉺���E
//	float f_top = nowPosF.y_ - sizeF.y_;
//	float f_bottom = nowPosF.y_ + sizeF.y_;
//	float f_right = nowPosF.x_ + sizeF.x_;
//	float f_left = nowPosF.x_ - sizeF.x_;
//
//	//�t�B���^�[�ɓ������Ă��邩
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
//			//�v���C���[�̏㉺���E
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
//	//�v���C���[�̏㉺���E
//		//�v���C���[�̏㉺���E
//	float p_top = nowPosP.y_ - sizePUD.x_;
//	float p_bottom = nowPosP.y_ + sizePUD.y_;
//	float p_right = nowPosP.x_ + sizePRL.x_;
//	float p_left = nowPosP.x_ - sizePRL.y_;
//
//	//�t�B���^�[�̏㉺���E
//	float f_top = nowPosF.y_ - sizeUD.x_;
//	float f_bottom = nowPosF.y_ + sizeUD.y_;
//	float f_right = nowPosF.x_ + sizeLR.y_;
//	float f_left = nowPosF.x_ - sizeLR.x_;
//
//	//�t�B���^�[�ɓ������Ă��邩
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
//			//�v���C���[�̏㉺���E
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

	//�ʒu
	playerPos.x_ = 300;
	playerPos.y_ = 400;

	//�T�C�Y
	playerSize.x_ = 21;
	playerSize.y_ = 32;

	//�m�F�p
	playerCheckPos.x_ = 0;
	playerCheckPos.y_ = 0;

	//
	playerCheckSize.x_ = player_.scale_.x_;
	playerCheckSize.y_ = player_.scale_.y_;

	//�m�F�p
	playerCheckSizeRL.x_ = player_.scale_.x_;
	playerCheckSizeRL.y_ = player_.scale_.y_;

	//�m�F�p
	playerCheckSizeUD.x_ = player_.scale_.x_;
	playerCheckSizeUD.y_ = player_.scale_.y_;

	//���͂��Ă���l��n��
	DS.x_ = false;
	DS.y_ = false;

	//���͂��Ă���l��n��
	AW.x_ = false;
	AW.y_ = false;

	//�v���C���[�����蔲���邩
	SetsukeFlag(false);

	//�t�B���^�[�̊p�ɓ������Ă��邩�ǂ���
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

	//�ʒu
	playerPos.x_ = 300;
	playerPos.y_ = 400;

	//�T�C�Y
	playerSize.x_ = 21;
	playerSize.y_ = 32;

	//�m�F�p
	playerCheckPos.x_ = 0;
	playerCheckPos.y_ = 0;

	//�m�F�p
	playerCheckSize.x_ = player_.scale_.x_;
	playerCheckSize.y_ = player_.scale_.y_;

	//�m�F�p
	playerCheckSizeRL.x_ = player_.scale_.x_;
	playerCheckSizeRL.y_ = player_.scale_.y_;

	//�m�F�p
	playerCheckSizeUD.x_ = player_.scale_.x_;
	playerCheckSizeUD.y_ = player_.scale_.y_;

	//���͂��Ă���l��n��
	DS.x_ = false;
	DS.y_ = false;

	//���͂��Ă���l��n��
	AW.x_ = false;
	AW.y_ = false;

	//�v���C���[�����蔲���邩
	SetsukeFlag(false);

	//�t�B���^�[�̊p�ɓ������Ă��邩�ǂ���
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

	SetkadoFlag(false);

	//�v���C���[�̏㉺���E
	float p_top = playerCheckPos.y_ - playerCheckSize.y_;
	float p_bottom = playerCheckPos.y_ + playerCheckSize.y_;
	float p_right = playerCheckPos.x_ + playerCheckSize.x_;
	float p_left = playerCheckPos.x_ - playerCheckSize.x_;

	//�t�B���^�[�̏㉺���E
	float f_top = filterPos.pos_.y_ - filterSizeUD.y_;
	float f_bottom = filterPos.pos_.y_ + filterSizeUD.y_;
	float f_right = filterPos.pos_.x_ + filterSizeLR.x_;
	float f_left = filterPos.pos_.x_ - filterSizeLR.x_;

	SetsukeFlag(false);

	//�t�B���^�[�ɓ������Ă��邩
	if (p_left < f_right ||
		p_right > f_left ||
		p_top  < f_bottom ||
		p_bottom > f_top)
	{
		//���S�Ƀt�B���^�[���ɂ��邩
		if (p_right < f_right &&
			p_left > f_left &&
			p_bottom  < f_bottom &&
			p_top > f_top)
		{
			SetsukeFlag(true);
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

				SetkadoFlag(true);
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

				SetkadoFlag(true);
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

				SetkadoFlag(true);
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

				SetkadoFlag(true);
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

	//�ʒu
	playerPos.x_ = 300;
	playerPos.y_ = 400;

	//�T�C�Y
	playerSize.x_ = 21;
	playerSize.y_ = 32;

	//�m�F�p
	playerCheckPos.x_ = 0;
	playerCheckPos.y_ = 0;

	//�m�F�p
	playerCheckSize.x_ = player_.scale_.x_;
	playerCheckSize.y_ = player_.scale_.y_;

	//�m�F�p
	playerCheckSizeRL.x_ = player_.scale_.x_;
	playerCheckSizeRL.y_ = player_.scale_.y_;

	//�m�F�p
	playerCheckSizeUD.x_ = player_.scale_.x_;
	playerCheckSizeUD.y_ = player_.scale_.y_;

	//���͂��Ă���l��n��
	DS.x_ = false;
	DS.y_ = false;

	//���͂��Ă���l��n��
	AW.x_ = false;
	AW.y_ = false;

	//�v���C���[�����蔲���邩
	SetsukeFlag(false);

	//�t�B���^�[�̊p�ɓ������Ă��邩�ǂ���
	SetkadoFlag(false);

	Jump = 0;
	JumpPower = 0;

	JumpFlag = false;

	Gravity = 0;
	GravityPower = 0;
}
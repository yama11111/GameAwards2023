#include "Player.h"

Player::Player()
{
	player_.Initialize({ {}, {}, {5.0f,5.0f,5.0f} });
	direction_ = { +1.0f,0.0f,0.0f };
	playerDra_.Initialize(&player_.m_, &direction_, IDrawer::Mode::Red);

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

	//�m�F�p
	playerCheckSize.x_ = 16;
	playerCheckSize.y_ = 64;

	//�m�F�p
	playerCheckSizeRL.x_ = 16;
	playerCheckSizeRL.y_ = 64;

	//�m�F�p
	playerCheckSizeUD.x_ = 16;
	playerCheckSizeUD.y_ = 64;

	//���͂��Ă���l��n��
	DS.x_ = false;
	DS.y_ = false;
	//���͂��Ă���l��n��
	AW.x_ = false;
	AW.y_ = false;

	//�v���C���[���t�B���^�[��
	chengeF = true;

	//�v���C���[�����蔲���邩
	sukeF = false;

	//�t�B���^�[�̊p�ɓ������Ă��邩�ǂ���
	kadoF = false;
}

Player::~Player()
{

}

void Player::Inilialize()
{
	player_.Initialize({ {}, {}, {5.0f,5.0f,5.0f} });
	direction_ = { +1.0f,0.0f,0.0f };
	playerDra_.Initialize(&player_.m_, &direction_, IDrawer::Mode::Red);


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
	playerCheckSize.x_ = 16;
	playerCheckSize.y_ = 64;

	//�m�F�p
	playerCheckSizeRL.x_ = 16;
	playerCheckSizeRL.y_ = 64;

	//�m�F�p
	playerCheckSizeUD.x_ = 16;
	playerCheckSizeUD.y_ = 64;

	//���͂��Ă���l��n��
	DS.x_ = false;
	DS.y_ = false;
	//���͂��Ă���l��n��
	AW.x_ = false;
	AW.y_ = false;

	//�v���C���[���t�B���^�[��
	chengeF = true;

	//�v���C���[�����蔲���邩
	sukeF = false;

	//�t�B���^�[�̊p�ɓ������Ă��邩�ǂ���
	kadoF = false;
}

void Player::Update()
{
	DS.x_ = 0;
	DS.y_ = 0;

	AW.x_ = 0;
	AW.y_ = 0;

	// �X�V����
	float moveSpd = 3.0f;

	//playerPos.y += 1;

	playerCheckPos = playerPos;
	playerCheckSize = playerSize;

	playerCheckSizeRL.x_ = playerSize.x_;
	playerCheckSizeRL.y_ = playerSize.x_;

	playerCheckSizeUD.x_ = playerSize.y_;
	playerCheckSizeUD.y_ = playerSize.y_;

	kadoF = false;

	//if (CheckHitKey(KEY_INPUT_SPACE) &&
	//	//oldkeys[KEY_INPUT_SPACE] == false &&
	//	sukeF == false)
	//{
	//	chengeF = !chengeF;

	//	/*CF = !CF;

	//	circlePos = playerPos;

	//	CSize = 0;*/
	//}

	///*if (CSize < WIN_WIDTH * 2)
	//	CSize += 30;*/

	//if (CheckHitKey(KEY_INPUT_R)
	//	//&& oldkeys[KEY_INPUT_R] == false
	//	)
	//{
	//	playerPos.x_ = 300;
	//	playerPos.y_ = 400;
	//}

	//�v���C���[�̏㉺���E
	float p_top = playerCheckPos.y_ - playerCheckSize.y_;
	float p_bottom = playerCheckPos.y_ + playerCheckSize.y_;
	float p_right = playerCheckPos.x_ + playerCheckSize.x_;
	float p_left = playerCheckPos.x_ - playerCheckSize.x_;

	sukeF = false;

	////�v���C���[�̏㉺���E
	//float p_top = playerCheckPos.y_ - playerCheckSize.y_;
	//float p_bottom = playerCheckPos.y_ + playerCheckSize.y_;
	//float p_right = playerCheckPos.x_ + playerCheckSize.x_;
	//float p_left = playerCheckPos.x_ - playerCheckSize.x_;

	////�t�B���^�[�̏㉺���E
	//float f_top = filterPos.y - filterSize.y;
	//float f_bottom = filterPos.y + filterSize.y;
	//float f_right = filterPos.x + filterSize.x;
	//float f_left = filterPos.x - filterSize.x;

	//sukeF = false;

	////�t�B���^�[�ɓ������Ă��邩
	//if (p_left < f_right &&
	//	p_right > f_left &&
	//	p_top  < f_bottom &&
	//	p_bottom > f_top)
	//{
	//	DrawFormatString(100, 200, 0xffffff, "hit");

	//	//���S�Ƀt�B���^�[���ɂ��邩
	//	if (p_right < f_right &&
	//		p_left > f_left &&
	//		p_bottom  < f_bottom &&
	//		p_top > f_top)
	//	{
	//		DrawFormatString(100, 220, 0xffffff, "Phit");

	//		sukeF = true;
	//	}
	//	else
	//	{
	//		//�ǂ��̕ӂ��v���C���[�ɓ������Ă��邩

	//		//�E��
	//		if (p_right > f_right &&
	//			p_left < f_right &&
	//			p_bottom > f_top &&
	//			p_top < f_top)
	//		{
	//			playerCheckSizeRL.y = playerPos.x - (filterPos.x + (filterSize.x));
	//			DrawFormatString(100, 240, 0xffffff, "right");

	//			playerCheckSizeUD.y = (filterPos.y - (filterSize.y)) - playerPos.y;
	//			DrawFormatString(100, 280, 0xffffff, "up");

	//			kadoF = true;
	//		}
	//		//�E��
	//		else if (
	//			p_right > f_right &&
	//			p_left < f_right &&
	//			p_bottom > f_bottom &&
	//			p_top < f_bottom)
	//		{
	//			playerCheckSizeRL.y = playerPos.x - (filterPos.x + (filterSize.x));
	//			DrawFormatString(100, 240, 0xffffff, "right");

	//			playerCheckSizeUD.x = playerPos.y - (filterPos.y + (filterSize.y));
	//			DrawFormatString(100, 300, 0xffffff, "down");

	//			kadoF = true;
	//		}
	//		//����
	//		else if (
	//			p_right > f_left &&
	//			p_left < f_left &&
	//			p_bottom > f_top &&
	//			p_top < f_top)
	//		{
	//			playerCheckSizeRL.x = (filterPos.x - (filterSize.x)) - playerPos.x;
	//			DrawFormatString(100, 260, 0xffffff, "left");

	//			playerCheckSizeUD.y = (filterPos.y - (filterSize.y)) - playerPos.y;
	//			DrawFormatString(100, 280, 0xffffff, "up");

	//			kadoF = true;
	//		}
	//		//����
	//		else if (
	//			p_right > f_left &&
	//			p_left < f_left &&
	//			p_bottom > f_bottom &&
	//			p_top < f_bottom)
	//		{
	//			playerCheckSizeRL.x = (filterPos.x - (filterSize.x)) - playerPos.x;
	//			DrawFormatString(100, 260, 0xffffff, "left");

	//			playerCheckSizeUD.x = playerPos.y - (filterPos.y + (filterSize.y));
	//			DrawFormatString(100, 300, 0xffffff, "down");

	//			kadoF = true;
	//		}
	//		//�E
	//		else if (
	//			p_right > f_right &&
	//			p_left < f_right)
	//		{
	//			playerCheckSizeRL.y = playerPos.x - (filterPos.x + (filterSize.x));
	//			DrawFormatString(100, 240, 0xffffff, "right");

	//		}
	//		//��
	//		else if (p_right > f_left &&
	//			p_left < f_left)
	//		{

	//			playerCheckSizeRL.x = (filterPos.x - (filterSize.x)) - playerPos.x;
	//			DrawFormatString(100, 260, 0xffffff, "left");
	//		}
	//		//��
	//		else if (p_bottom > f_top &&
	//			p_top < f_top)
	//		{
	//			//�����Ă�
	//			playerCheckSizeUD.y = (filterPos.y - (filterSize.y / 2)) - playerPos.y - playerSize.y;
	//			DrawFormatString(100, 280, 0xffffff, "up");
	//		}
	//		//��
	//		else if (p_bottom > f_bottom &&
	//			p_top < f_bottom)
	//		{
	//			//�ł���
	//			playerCheckSizeUD.x = playerPos.y - playerSize.y - (filterPos.y + (filterSize.y / 2));

	//			DrawFormatString(100, 300, 0xffffff, "down");
	//		}

	//	}
	//}

	//if (chengeF)
	//{
	//	if (CheckHitKey(KEY_INPUT_D))
	//	{
	//		playerPos.x += moveSpd;

	//		DS.x = CheckHitKey(KEY_INPUT_D);
	//		DS.y = 0;

	//		AW.x = 0;
	//		AW.y = 0;

	//		if (!sukeF)
	//		{
	//			if (kadoF)
	//			{
	//				Vector2 size = { playerSize.x,playerSize.x };

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

	//				size.x = playerSize.y;
	//				size.y = playerSize.y;

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
	//		playerPos.x -= moveSpd;

	//		DS.x = 0;
	//		DS.y = 0;

	//		AW.x = CheckHitKey(KEY_INPUT_A);
	//		AW.y = 0;

	//		if (!sukeF)
	//		{
	//			if (kadoF)
	//			{
	//				Vector2 size = { playerSize.x,playerSize.x };

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

	//				size.x = playerSize.y;
	//				size.y = playerSize.y;

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
	//		playerPos.y += moveSpd;

	//		DS.x = 0;
	//		DS.y = CheckHitKey(KEY_INPUT_S);
	//		//DS.y = 1;

	//		AW.x = 0;
	//		AW.y = 0;

	//		if (!sukeF)
	//		{
	//			if (kadoF)
	//			{
	//				Vector2 size = { playerSize.x,playerSize.x };

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

	//				size.x = playerSize.y;
	//				size.y = playerSize.y;

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
	//		playerPos.y -= moveSpd;

	//		DS.x = 0;
	//		DS.y = 0;

	//		AW.x = 0;
	//		AW.y = CheckHitKey(KEY_INPUT_W);

	//		if (!sukeF)
	//		{
	//			if (kadoF)
	//			{
	//				Vector2 size = { playerSize.x,playerSize.x };

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

	//				size.x = playerSize.y;
	//				size.y = playerSize.y;

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
	//else
	//{
	//	filterPos.x += (CheckHitKey(KEY_INPUT_D) - CheckHitKey(KEY_INPUT_A)) * moveSpd;
	//	filterPos.y += (CheckHitKey(KEY_INPUT_S) - CheckHitKey(KEY_INPUT_W)) * moveSpd;
	//}


	player_.UpdateMatrix();
	playerDra_.Update();
}

void Player::Draw()
{

}

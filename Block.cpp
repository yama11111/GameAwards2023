#include "Block.h"

//�C���N�������g
Block::Block()
{
	block_.Initialize({ {}, {}, {1.0f,1.0f,1.0f} });
	blockDra_.Initialize(&block_, IDrawer::Mode::Normal);
}

//�f�N�������g
Block::~Block()
{
}

//������
void Block::Initialize()
{
	block_.Initialize({ {}, {}, {1.0f,1.0f,1.0f} });
	blockDra_.Initialize(&block_, IDrawer::Mode::Normal);
}

//�X�V
void Block::Update(YGame::Transform filter)
{
	ClearFlag = false;

	//�v���C���[�̏㉺���E
	float b_top = block_.pos_.y_ - block_.scale_.y_;
	float b_bottom = block_.pos_.y_ + block_.scale_.y_;
	float b_right = block_.pos_.x_ + block_.scale_.x_;
	float b_left = block_.pos_.x_ - block_.scale_.x_;

	//�t�B���^�[�̏㉺���E
	float f_top = filter.pos_.y_ - (filter.scale_.y_ * 2);
	float f_bottom = filter.pos_.y_ + (filter.scale_.y_ * 2);
	float f_right = filter.pos_.x_ + (filter.scale_.x_ * 2);
	float f_left = filter.pos_.x_ - (filter.scale_.x_ * 2);

	//SetsukeFlag(false);

	if (nowKind == ColorB)
	{
		//�t�B���^�[�ɓ������Ă��邩
		if (b_left < f_right ||
			b_right > f_left ||
			b_top  < f_bottom ||
			b_bottom > f_top)
		{
			//���S�Ƀt�B���^�[���ɂ��邩
			if (b_right < f_right &&
				b_left > f_left &&
				b_bottom  < f_bottom &&
				b_top > f_top)
			{
				ClearFlag = true;
			}
			else
			{
				//�ǂ��̕ӂ��v���C���[�ɓ������Ă��邩
				//�E��
				//if (b_right > f_right &&
				//	b_left < f_right &&
				//	b_bottom > f_top &&
				//	b_top < f_top)
				//{
				//	block_.scale_.y_ = block_.pos_.x_ - f_right;

				//	block_.scale_.y_ = f_top - block_.pos_.y_;
				//}
				////�E��
				//else if (
				//	b_right > f_right &&
				//	b_left < f_right &&
				//	b_bottom > f_bottom &&
				//	b_top < f_bottom)
				//{
				//	block_.scale_.y_ = block_.pos_.x_ - f_right;

				//	block_.scale_.x_ = block_.pos_.y_ - f_bottom;
				//}
				////����
				//else if (
				//	b_right > f_left &&
				//	b_left < f_left &&
				//	b_bottom > f_top &&
				//	b_top < f_top)
				//{
				//	block_.scale_.x_ = f_left - block_.pos_.x_;

				//	block_.scale_.y_ = f_top - block_.pos_.y_;
				//}
				////����
				//else if (
				//	b_right > f_left &&
				//	b_left < f_left &&
				//	b_bottom > f_bottom &&
				//	b_top < f_bottom)
				//{
				//	block_.scale_.x_ = f_left - block_.pos_.x_;

				//	block_.scale_.x_ = block_.pos_.y_ - f_bottom;
				//}
				////�E
				//else 
				if (b_left < f_right)
				{
					//block_.scale_.x_ = block_.pos_.x_ - f_right;
				//	sukeF = true;

				}
				//��
				else if (b_right > f_left)
				{
					//block_.scale_.x_ = f_left - block_.pos_.x_;
				//	sukeF = true;
				}
				//��
				else if (b_bottom > f_top)
				{
					///�����Ă�
					//sukeF = true;
					//block_.scale_.y_ = f_top - block_.pos_.y_;
				}

				else if (b_top < f_bottom)
				{
					//�ł���
					//block_.scale_.y_ = block_.pos_.y_ - f_bottom;
					//sukeF = true;
				}
			}
		}
	}

	// �u���b�N
	block_.UpdateMatrix();
	blockDra_.Update();
}

//Pre�`��(�t�B���^�[�̑O)
void Block::PreDraw()
{
	if (nowKind != None)
	{
		blockDra_.PreDraw();
	}
}

//Post�`��(�t�B���^�[�̌�)
void Block::PostDraw()
{
	if (nowKind != None)
	{
		blockDra_.PostDraw();
	}
}

//���Z�b�g
void Block::Reset()
{
	block_.Initialize({ {}, {}, {1.0f,1.0f,1.0f} });
	blockDra_.Initialize(&block_, IDrawer::Mode::Normal);
}

//�u���b�N�𐶐���ɕ`�悷���ނ�ς���
void Block::SetMode()
{
	//�F�t���u���b�N
	if (nowKind == ColorB)
	{
		blockDra_.Initialize(&block_, IDrawer::Mode::Red);
		return;
	}

	//�����`�悵�Ȃ�
	if (nowKind == None)
	{
		blockDra_.Initialize(&block_, IDrawer::Mode::None);
		return;
	}

	//���ʂ̃u���b�N
	if (nowKind == Normal)
	{
		blockDra_.Initialize(&block_, IDrawer::Mode::Normal);
		return;
	}
}
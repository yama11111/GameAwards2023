#include "Block.h"
using namespace std;


//�C���N�������g
Block::Block()
{
	block_.Initialize({ {}, {}, {1.0f,1.0f,1.0f} });
	blockDra_.Initialize(&block_, IMode::Type::Normal);
}

//�f�N�������g
Block::~Block()
{
}

//������
void Block::Initialize()
{
	block_.Initialize({ {}, {}, {1.0f,1.0f,1.0f} });
	blockDra_.Initialize(&block_, IMode::Type::Normal);

	rotCount = 0;
	rotRight = false;
}

//�X�V
void Block::Update()
{


	// �u���b�N
	block_.UpdateMatrix();
	blockDra_.Update();
}

//�`��
void Block::Draw()
{
	//�`�悵�Ȃ����[�h�łȂ��Ȃ�
	if (nowKind != None)
	{
		blockDra_.Draw();
	}
}

//���Z�b�g
void Block::Reset()
{
	block_.Initialize({ {}, {}, {1.0f,1.0f,1.0f} });
	blockDra_.Initialize(&block_, IMode::Type::Normal);
}

//�S�u���b�N�̈ʒu���
void Block::SetBlocksPos(YMath::Vector3 pos)
{
	block_.pos_ = pos;
}

//�u���b�N�𐶐���ɕ`�悷���ނ�ς���
void Block::SetMode()
{
	////�����`�悵�Ȃ�
	//if (nowKind == None)
	//{
	//	blockDra_.Initialize(&block_, IDrawer::Mode::None);
	//	return;
	//}

	////���ʂ̃u���b�N
	//if (nowKind == Normal)
	//{
	//	blockDra_.Initialize(&block_, IMode::Type::Normal);
	//	return;
	//}
}

//�E��]
void Block::RotRight(int number)
{
	//if (rotRight == false)
	{
		//��
		int countX = 9;
		int countY = 9;

		int Check = countX / 2 + 1;

		//�c��
		int x = number;
		int y = number;

		//�ʒu���v�Z��
		y = number / countY;
		x = number - (y * countX);

		//�ړ��u���b�N��

		//���ɂ���u���b�N�p�@�E�́[������
		int moveX = (countX - 1) - ((x + 1) * 2);

		//��ɂ���u���b�N�p�@���́[������
		int moveY = (countY - 1) - ((y + 1) * 2);

		//��
		if (x < Check)
		{
			//����
			if (y < Check)
			{
				block_.pos_.x_ += cos(3.14f / 180 * 20);
				block_.pos_.y_ += sin(3.14f / 180 * 20);
				return;
			}
			////����
			//else if (y > Check - 1)
			//{
			//	block_.pos_.y_ += moveY * 1.0f;
			//}
		}
		////�E
		//else if (x > Check - 1)
		//{
		//	//�E��
		//	if (y < Check)
		//	{
		//		block_.pos_.y_ += -moveY * 1.0f;
		//	}
		//	//�E��
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

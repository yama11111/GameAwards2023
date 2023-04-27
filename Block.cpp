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
}

//�X�V
void Block::Update(YGame::Transform filter)
{
	/*if (ClearFlag)
	{
		timer_--;
	}*/

	if (timer_ < 1)
	{
		ClearFlag = false;
	}

	// �u���b�N
	block_.UpdateMatrix();
	blockDra_.Update();
}

//�`��
void Block::Draw()
{
	if (nowKind != None)
	{
		//�E�̏��������ƃu���b�N�������
		if (ClearFlag == false || nowKind != ColorB)
		{
			blockDra_.Draw();
		}
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
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			blocksDra_[i + j];
		}
	}
}

void Block::MovePos(int block)
{
	float spd = 0.1f * block;

	block_.pos_.y_ += spd * 2;
	block_.scale_.y_ += spd ;

}

void Block::MovePosYUp(int block)
{
	float size = block + 0.55;

	if (block_.scale_.y_ >= block)
	{
		upFlag = false;
		return;
	}

	float spd = 0.1f;

	block_.pos_.y_ += spd * 2;
	block_.scale_.y_ += spd;

	// �u���b�N
	block_.UpdateMatrix();
	blockDra_.Update();
}

void Block::MovePosYDown()
{
	if (upTimer > 0)
	{
		upTimer--;
		return;
	}

	if (block_.scale_.y_ < 0.55f)
	{
		return;
	}

	float spd = 0.1f;

	block_.pos_.y_ -= spd * 2;
	block_.scale_.y_ -= spd;

	// �u���b�N
	block_.UpdateMatrix();
	blockDra_.Update();
}

//�u���b�N�𐶐���ɕ`�悷���ނ�ς���
void Block::SetMode()
{
	//�F�t���u���b�N
	if (nowKind == ColorB)
	{
		blockDra_.Initialize(&block_, IMode::Type::Movable);
		return;
	}

	////�����`�悵�Ȃ�
	//if (nowKind == None)
	//{
	//	blockDra_.Initialize(&block_, IDrawer::Mode::None);
	//	return;
	//}

	//���ʂ̃u���b�N
	if (nowKind == Normal)
	{
		blockDra_.Initialize(&block_, IMode::Type::Normal);
		return;
	}
}
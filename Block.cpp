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
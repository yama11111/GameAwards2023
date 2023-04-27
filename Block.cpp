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
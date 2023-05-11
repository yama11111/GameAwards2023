#pragma once
#include "Vector2.h"
#include "Block.h"
#include "BlockDrawer.h"

class Piece
{
private:
	// �t�B���^�[
	YGame::Transform piece_;

	// �u���b�N�`��N���X
	BlockDrawer blockDra_;

	//�u���b�N�i�[�p�ϐ�
	std::vector<std::vector<Block>> blocks;

	//XY
	const int blockX = 9;
	const int blockY = 9;

	int map[81] =
	{
		1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,1,0,1,
		1,0,1,0,0,0,0,0,1,
		1,0,0,0,0,1,0,0,1,
		1,0,0,0,0,0,0,0,1,
		1,1,0,0,0,0,1,1,1,
		1,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,
	};



public:
	//�C���N�������g
	Piece();

	//�f�N�������g
	~Piece();

	//������
	void Initialize();

	//�X�V
	void Update();

	//�`��
	void Draw();

	//Vector3�ɑ��
	void SetPos(YMath::Vector3 pos) { piece_.pos_ = pos; };
	void SetScale(YMath::Vector3 scale) { piece_.scale_ = scale; };
	void SetRot(YMath::Vector3 rot) { piece_.rota_ = rot; };

	void CreateBlock();
};


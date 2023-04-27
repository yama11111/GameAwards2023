#pragma once
#include "Vector2.h"
#include "Block.h"
#include "BlockDrawer.h"

class Pises
{
private:
	// �t�B���^�[
	YGame::Transform pises_;

	// �u���b�N�`��N���X
	BlockDrawer blockDra_;

	//�u���b�N�i�[�p�ϐ�
	std::vector<std::unique_ptr<Block>> blocks;

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
	Pises();

	//�f�N�������g
	~Pises();

	//������
	void Initialize();
	void Initialize(YMath::Vector3 pos, YMath::Vector3 rot, YMath::Vector3 scale);

	//�X�V
	void Update();

	//�`��
	void Draw();
	void DrawBlock();
	void DrawPiese();

	//�����for���ŌĂяo���Ă������map���J��Ԃ�
	void CreateBlock(int mode, YGame::Transform pises, int number);
};


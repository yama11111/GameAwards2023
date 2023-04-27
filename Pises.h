#pragma once
#include "Vector2.h"
#include "BlockDrawer.h"
#include "Block.h"

class Pises
{
private:
	// �t�B���^�[
	YGame::Transform pises_;

	//�u���b�N�i�[�p�ϐ�
	std::vector<std::unique_ptr<Block>> block;

public:
	//�C���N�������g
	Pises();

	//�f�N�������g
	~Pises();

	//������
	void Initialize();

	//�X�V
	void Update();

	//�`��(�ق���Post��Pre�̊Ԃɕ`�悷��)
	void Draw();
};


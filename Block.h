#pragma once
#include "Vector2.h"
#include "BlockDrawer.h"

enum kind
{
	None,	//��
	Normal,	//����
	ColorB,	//�������
	//ABS,	//�ϕs��
	Start,	//�v���C���[���X�^�[�g�ɏo���̂���Normal�Ɉڍs
	Gorl,	//�S�[��
	Collect, // �R���N�g
	CheckPoint,	//�ꉞ�p��
};

class Block {
private:

public:
	// �u���b�N
	YGame::Transform block_;
	// �u���b�N�`��N���X
	BlockDrawer blockDra_;

	Block();
	~Block();

	int nowKind = None;
	bool sukeF = false;

	void Inilialize();
	void Update(YGame::Transform filter);
	void Draw();
	void Reset();
	void SetKind(int kind) { nowKind = kind; };
	void SetMode();
};
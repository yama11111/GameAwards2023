#pragma once
#include "Vector2.h"
#include "BlockDrawer.h"

//�u���b�N�̎��
enum Kind
{
	None,	//��
	Normal,	//����
	ColorB,	//������
	Start,	//�v���C���[���X�^�[�g�ɏo���̂���Normal�Ɉڍs����
	Gorl,	//�S�[��
	Collect, // �R���N�g
	CheckPoint,	//�ꉞ�p��
};

class Block {
private:
	// �u���b�N
	YGame::Transform block_;

	// �u���b�N�`��N���X
	BlockDrawer blockDra_;

	//�u���b�N�̎��
	int nowKind = None;

	//�t�B���^�[�Ɠ������Ĕ��肪�Ȃ��Ȃ��Ă��邩
	//bool sukeF = false;
	bool ClearFlag = false;

public:

	//�C���N�������g
	Block();

	//�f�N�������g
	~Block();

	//������
	void Initialize();

	//�X�V
	void Update(YGame::Transform filter);

	//Pre�`��(�t�B���^�[�̑O)
	void PreDraw();

	//Post�`��(�t�B���^�[�̌�)
	void PostDraw();

	//���Z�b�g
	void Reset();

	//�u���b�N�̎�ޕύX
	void SetKind(int kind) { nowKind = kind; };

	//ClearFlag�ɑ��
	void SetClearFlag(bool flag) { flag = ClearFlag; };

	//ClearFlag�����
	bool GetClearFlag() { return ClearFlag; };

	//pos�����
	void SetPos(YMath::Vector3 pos) { block_.pos_ = pos; };

	//pos�ɑ��
	YMath::Vector3 GetPos() { return block_.pos_; };

	//Transform�����
	YGame::Transform GetTransform() { return block_; };

	//�u���b�N�𐶐���ɕ`�悷���ނ�ς���
	void SetMode();
};
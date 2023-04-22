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

	//���u���b�N��
	BlockDrawer blocksDra_[16];

	//�u���b�N�̎��
	int nowKind = None;

	//�t�B���^�[�Ɠ������Ĕ��肪�Ȃ��Ȃ��Ă��邩
	//bool sukeF = false;
	bool ClearFlag = false;

	//�߂鎞��
	int timer_ = 0;

	//�オ��
	bool upFlag = false;

	int upTimer = 0;

	void LoadCSVFile(std::vector<std::vector<int>>& data, const char* fileName, int _height, int _width);

	void LoadCSV(std::string csvPath);

	std::vector<std::vector<int>> r_data;
public:

	//�C���N�������g
	Block();

	//�f�N�������g
	~Block();

	//������
	void Initialize();

	//�X�V
	void Update(YGame::Transform filter);

	//�`��
	void Draw();

	//���Z�b�g
	void Reset();

	//�u���b�N�̎�ޕύX
	void SetKind(int kind) { nowKind = kind; };

	//���݂̃u���b�N�̎�ނ̎擾
	int GetKind() { return nowKind; };

	//ClearFlag�ɑ��
	void SetClearFlag(bool flag) { ClearFlag = flag; };

	//ClearFlag�����
	bool GetClearFlag() { return ClearFlag; };
	bool GetUpFlag() { return upFlag; };
	void SetUpFlag(bool flag) { upFlag = flag; };

	//Vector3�ɑ��
	void SetPos(YMath::Vector3 pos) { block_.pos_ = pos; };
	void SetScale(YMath::Vector3 scale) { block_.scale_ = scale; };
	void SetRot(YMath::Vector3 rot) { block_.rota_ = rot; };

	//�S�u���b�N�̈ʒu���
	void SetBlocksPos(YMath::Vector3 pos);

	//�������鎞��
	void SetTimer(int time) { timer_ = time; };
	void SetUpTimer(int time) { upTimer = time; };

	//�^�C�}�[����
	void CountDown() { timer_--; };

	//�ړ�
	void MovePosYUp(int block);
	void MovePosYDown();
	void MovePos(int block);

	//Vector3�����
	YMath::Vector3 GetPos() { return block_.pos_; };
	YMath::Vector3 GetScale() { return block_.scale_; };
	YMath::Vector3 GetRot() { return block_.rota_; };

	//Transform�����
	YGame::Transform GetTransform() { return block_; };

	//�u���b�N�𐶐���ɕ`�悷���ނ�ς���
	void SetMode();
};
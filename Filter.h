#pragma once
#include "Vector2.h"
#include "FilterDrawer.h"

class Filter
{
private:
	// �t�B���^�[
	YGame::Transform filter_;
	// �t�B���^�[�`��N���X
	FilterDrawer filterDra_;

	//�������Ă邩�ǂ���
	//bool nowMove = false;

public:
	//�C���N�������g
	Filter();

	//�f�N�������g
	~Filter();

	//������
	void Initialize();
	void Initialize(YMath::Vector3 pos_, YMath::Vector3 rot_, YMath::Vector3 scale_);

	//�X�V
	void Update();

	//�`��(�ق���Post��Pre�̊Ԃɕ`�悷��)
	void Draw();

	//���Z�b�g
	void Reset();

	//�����Ă邩�ǂ����t���O�ɑ��
	//void SetNowMove(bool flag) { nowMove = flag; };

	//�t���O���]
	//void ChengeNowMove() {nowMove = !nowMove;};

	//�����Ă邩�ǂ����̃t���O�����
	//bool GetNowMove() { return nowMove; };

	YGame::Transform GetTransform() { return filter_; };
};


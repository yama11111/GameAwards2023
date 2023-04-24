#pragma once
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

	//�ړ��ʊi�[
	YMath::Vector3 movePos = { 0.0f,0.0f,0.0f };

	// �t�B���^�[
	YGame::Transform filters[9];

	// �t�B���^�[�`��N���X
	FilterDrawer filterDras[9];

	//�`�悷��t���O
	bool drawFlag[9];

	//�u���b�N���o���邩�ǂ���
	bool blockFlag[9];

	bool allBlockFlag;

	//�c��
	const int countX = 3;
	const int countY = 3;

	const int mapCountY = 14;
	const int mapCountX = 40;

	//�t�B���^�[�p�}�b�v
	int Fmap[14][40];

	//�t�B���^�[�ƃv���C���[�̋���
	float FilterToPlayer = 2.0f;

	float scales = 0.5f;
public:
	//�C���N�������g
	Filter();

	//�f�N�������g
	~Filter();

	//������
	void Initialize();
	void Initialize(YMath::Vector3 pos_, YMath::Vector3 rot_, YMath::Vector3 scale_);

	void InitializeMap(int i, int j, int chenge);

	//�X�V
	void Update();

	//�`��(�ق���Post��Pre�̊Ԃɕ`�悷��)
	void Draw();

	//���Z�b�g
	void Reset();

	//Transform�l��
	YGame::Transform GetTransform() { return filter_; };
	YGame::Transform GetTransform(int i) { return filters[i]; };

	//�ړ��ʊl��
	YMath::Vector3 GetMovePos() { return movePos; };

	//�ړ��ʃZ�b�g
	void SetMovePos(YMath::Vector3 pos) { movePos = pos; };

	//pos�Z�b�g
	void SetPos(YMath::Vector3 pos) { filter_.pos_ = pos; };

	//�����t�B���^�[��DrawFlag
	void SetDrawFlag(int i, bool flag) { drawFlag[i] = flag; };
	bool GetDrawFlag(int i) { return drawFlag[i]; };

	//�X�̃u���b�N�̃t���O
	bool GetBlockFlag(int i) { return blockFlag[i]; };
	void SetBlockFlag(int i, bool flag) { blockFlag[i] = flag; };

	//�u���b�N��ǉ����邩�ǂ���
	bool GetBlockFlag() { return allBlockFlag; };
	void SetBlockFlag(bool flag) { allBlockFlag = flag; };

	//�����Ă���ύX
	void DirectionSet(int direction);

	void SetDirection(YGame::Transform player, int direction);
};


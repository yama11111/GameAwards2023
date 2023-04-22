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

	bool drawFlag[9];

	//�c��
	const int countX = 3;
	const int countY = 3;

	const int mapCountY = 14;
	const int mapCountX = 40;

	//�t�B���^�[�p�}�b�v
	int Fmap[14][40];

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
};


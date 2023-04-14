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

	//Transform�l��
	YGame::Transform GetTransform() { return filter_; };

	//�ړ��ʊl��
	YMath::Vector3 GetMovePos() { return movePos; };

	//�ړ��ʃZ�b�g
	void SetMovePos(YMath::Vector3 pos) { movePos = pos; };
};


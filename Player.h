#pragma once
#include "Keys.h"
#include "PlayerDrawer.h"

class Player
{
private:

	// �v���C���[
	YGame::Transform player_;

	// ����
	YMath::Vector3 direction_;

	// �v���C���[�`��N���X
	PlayerDrawer playerDra_;

	//�X�^�[�g����Pos�i�[
	YMath::Vector3 startPos = { 0.0f,0.0f,0.0f };

	//�v���C���[�����蔲���邩
	bool ClearFlag = false;

	//�t�B���^�[�̊p�ɓ������Ă��邩�ǂ���
	bool CornerFlag = false;

public:

	//�C���N�������g
	Player();

	//�f�N�������g
	~Player();

	//������
	void Initialize();
	void Initialize(YMath::Vector3 pos_, YMath::Vector3 rot_, YMath::Vector3 scale_);

	//�X�V
	void Update(YGame::Transform filterPos, YMath::Vector2 filterSizeLR, YMath::Vector2 filterSizeUD);
	void Update(YGame::Transform filterPos);

	//Pre�`��(�t�B���^�[�̑O)
	void PreDraw();

	//Post�`��(�t�B���^�[�̌�)
	void PostDraw();

	//���Z�b�g
	void Reset();

	//GetFlag�֐�
	bool GetClearFlag() { return ClearFlag; };
	bool GetCornerFlag() { return CornerFlag; };

	//SetFlag�֐�
	void SetClearFlag(bool flag) { ClearFlag = flag; };
	void SetCornerFlag(bool flag) { CornerFlag = flag; };

	//CengeFlag�֌W
	void ChengeClearFlag() { ClearFlag = !ClearFlag; };
	void ChengeCornerFlag() { CornerFlag = !ClearFlag; };

	//direction�֌W
	void SetDirection(YMath::Vector3 direction) { direction_ = direction; };
	YMath::Vector3 GetDirection() { return direction_; };

	//�W�����v�֌W
	bool JumpFlag = false;
	float JumpPower = 0;
	float Jump = 0;

	//�d�͊֌W
	float Gravity = 0;
	float GravityPower = 0;
};
#pragma once
#include "PlayerDrawer.h"
#include "FilterDrawer.h"

class Player
{
private:

	// �v���C���[
	YGame::Transform player_;

	// ����
	YMath::Vector3 direction_;

	// �v���C���[�`��N���X
	PlayerDrawer playerDra_;
	FilterDrawer filterDra_;

	//�X�^�[�g����Pos�i�[
	YMath::Vector3 startPos = { 0.0f,0.0f,0.0f };

	//�ړ��ʊi�[
	YMath::Vector3 movePos = { 0.0f,0.0f,0.0f };

	//���삵�Ă邩�ǂ���
	bool PlayFlag = true;

	//�v���C���[�����蔲���邩
	bool ClearFlag = false;

	//�t�B���^�[�̊p�ɓ������Ă��邩�ǂ���
	bool CornerFlag = false;

	//�W�����v�֌W
	bool JumpFlag = false;
	float JumpPower = 0;
	float Jump = 0;

	//�d�͊֌W
	float Gravity = 0;
	float GravityPower = 0;
public:

	//�C���N�������g
	Player();

	//�f�N�������g
	~Player();

	//������
	void Initialize();
	void Initialize(YMath::Vector3 pos_, YMath::Vector3 rot_, YMath::Vector3 scale_);

	//�X�V
	//void Update(YGame::Transform filterPos, YMath::Vector2 filterSizeLR, YMath::Vector2 filterSizeUD);
	void Update(YGame::Transform filterPos);
	void Update();

	//Pre�`��(�t�B���^�[�̑O)
	void PreDraw();

	//Post�`��(�t�B���^�[�̌�)
	void PostDraw();

	//���Z�b�g
	void Reset();

	//�d�͊֌W�̃��Z�b�g
	void JumpReset();

	//�d�́A�W�����v�̗͂����Z
	void AddGravity();

	// ���n
	void Landing() { playerDra_.LandingAnimation(); }

	//GetFlag�֐�
	bool GetClearFlag() { return ClearFlag; };
	bool GetCornerFlag() { return CornerFlag; };
	bool GetJumpFlag() { return JumpFlag; };
	bool GetPlayFlag() { return PlayFlag; };

	//SetFlag�֐�
	void SetClearFlag(bool flag) { ClearFlag = flag; };
	void SetCornerFlag(bool flag) { CornerFlag = flag; };
	void SetJumpFlag(bool flag) { JumpFlag = flag; };
	void SetPlayFlag(bool flag) { PlayFlag = flag; };

	//CengeFlag�֌W
	void ChengeClearFlag() { ClearFlag = !ClearFlag; };
	void ChengeCornerFlag() { CornerFlag = !CornerFlag; };
	void ChengeJumpFlag() { JumpFlag = !JumpFlag; };
	void ChengePlayFlag() { PlayFlag = !PlayFlag; };

	//Vector3�ɑ��
	void SetPos(YMath::Vector3 pos) { player_.pos_ = pos; };
	void SetScale(YMath::Vector3 scale) { player_.scale_ = scale; };
	void SetRot(YMath::Vector3 rot) { player_.rota_ = rot; };
	void SetStartPos(YMath::Vector3 pos) { startPos = pos; };
	void SetMovePos(YMath::Vector3 pos) { movePos = pos; };
	void SetJumpPower(float power) { JumpPower = power; };
	void SetJump(float power) { Jump = power; };
	void SetGravityPower(float power) { GravityPower = power; };
	void SetGravity(float power) { Gravity = power; };

	//Vector3�����
	YMath::Vector3 GetPos() { return player_.pos_; };
	YMath::Vector3 GetScale() { return player_.scale_; };
	YMath::Vector3 GetRot() { return player_.rota_; };
	YMath::Vector3 GetStartPos() { return startPos; };
	YMath::Vector3 GetMovePos() { return movePos; };
	float GetGravity() { return Gravity; };

	//�����Ɉړ�
	void PlayerMove(YMath::Vector3 pos);

	//Transform�����
	YGame::Transform GetTransform() { return player_; };

	//direction�֌W
	void SetDirection(YMath::Vector3 direction) { direction_ = direction; };
	YMath::Vector3 GetDirection() { return direction_; };
};
#pragma once
#include "Keys.h"
#include "PlayerDrawer.h"

class Player
{
private:
	YMath::Vector2 playerPos = { 0,0 };
	YMath::Vector2 playerSize = { 16,32 };

	YMath::Vector2 playerCheckPos = { 0,0 };
	YMath::Vector2 playerCheckSize = { 16,64 };

	YMath::Vector2 playerCheckSizeRL = { 16,64 };
	YMath::Vector2 playerCheckSizeUD = { 16,64 };

	//�L�[��������Ă��邩�ǂ���
	YMath::Vector2 DS;
	YMath::Vector2 AW;

	//�v���C���[�����蔲���邩
	bool sukeF = false;
	//passFlag

	//�t�B���^�[�̊p�ɓ������Ă��邩�ǂ���
	bool kadoF = false;
	//corner
public:

	// �v���C���[
	YGame::Transform player_;
	// ����
	YMath::Vector3 direction_;
	// �v���C���[�`��N���X
	PlayerDrawer playerDra_;

	Player();
	~Player();

	void Inilialize();
	void Update(YGame::Transform filterPos, YMath::Vector2 filterSizeLR, YMath::Vector2 filterSizeUD);
	void Draw();
	void Reset();

	//�ʒu
	YMath::Vector2 GetPos() { return playerPos; };
	void SetPos(YMath::Vector2 nowpos) { playerPos = nowpos; };

	//�ŏ��̑傫��
	YMath::Vector2 GetSize() { return playerSize; };
	void SetSize(YMath::Vector2 nowsize) { playerPos = nowsize; };

	//���̑傫��
	YMath::Vector2 GetNowSizeX() { return playerCheckSizeRL; };
	YMath::Vector2 GetNowSizeY() { return playerCheckSizeUD; };

	bool GetsukeFlag() { return sukeF; };
	bool GetkadoFlag() { return kadoF; };

	void SetsukeFlag(bool flag) { sukeF = flag; };
	void SetkadoFlag(bool flag) { kadoF = flag; };

	bool JumpFlag = false;
	float JumpPower = 0;
	float Jump = 0;

	float Gravity = 0;
	float GravityPower = 0;
};
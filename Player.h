#pragma once
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
	
public:

	//�C���N�������g
	Player();

	//�f�N�������g
	~Player();

	//������
	void Initialize();

	//�X�V
	void Update();

	// �`��
	void Draw();

	//���Z�b�g
	void Reset();

	// ���n
	void Landing() { playerDra_.LandingAnimation(); }

	//Vector3�ɑ��
	void SetPos(YMath::Vector3 pos) { player_.pos_ = pos; };
	void SetScale(YMath::Vector3 scale) { player_.scale_ = scale; };
	void SetRot(YMath::Vector3 rot) { player_.rota_ = rot; };

	//Vector3�����
	YMath::Vector3 GetPos() { return player_.pos_; };
	YMath::Vector3 GetScale() { return player_.scale_; };
	YMath::Vector3 GetRot() { return player_.rota_; };

	//Transform�����
	YGame::Transform GetTransform() { return player_; };

	//direction�֌W
	void SetDirection(YMath::Vector3 direction) { direction_ = direction; };
	YMath::Vector3 GetDirection() { return direction_; };
};
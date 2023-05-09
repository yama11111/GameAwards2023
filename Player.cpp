#include "Player.h"
#include "MathUtillity.h"
#include "Keys.h"
#include "imgui.h"

#pragma region ���O��Ԑ錾
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;
#pragma endregion 

Player::Player()
{
	player_.Initialize({ {}, {}, {0.5f,0.5f,1.0f} });
	direction_ = { +1.0f,0.0f,0.0f };
	playerDra_.Initialize(&player_, &direction_);

	player_.scale_.x_ = 4.0f;
	player_.scale_.y_ = 8.0f;

	//�v���C���[�����蔲���邩
	SetClearFlag(false);

	//�t�B���^�[�̊p�ɓ������Ă��邩�ǂ���
	SetCornerFlag(false);

	Jump = 0;
	JumpPower = 0;

	JumpFlag = false;
}

Player::~Player()
{

}

void Player::Initialize()
{
	player_.Initialize({ {}, {}, {0.5f,0.5f,1.0f} });
	direction_ = { +1.0f,0.0f,0.0f };
	playerDra_.Initialize(&player_, &direction_);

	//�v���C���[�����蔲���邩
	SetClearFlag(false);

	//�t�B���^�[�̊p�ɓ������Ă��邩�ǂ���
	SetCornerFlag(false);

	Jump = 0;
	JumpPower = 0;

	JumpFlag = false;
}

void Player::Initialize(YMath::Vector3 pos_, YMath::Vector3 rot_, YMath::Vector3 scale_)
{
	// �t�B���^�[
	player_.Initialize({ pos_, rot_, scale_ });
	direction_ = { +1.0f,0.0f,0.0f };
	playerDra_.Initialize(&player_, &direction_);

	//�v���C���[�����蔲���邩
	SetClearFlag(false);

	//�t�B���^�[�̊p�ɓ������Ă��邩�ǂ���
	SetCornerFlag(false);

	Jump = 0;
	JumpPower = 0;

	JumpFlag = false;
}

void Player::Draw()
{
	playerDra_.Draw();
}

void Player::Update()
{

	ImGui::Begin("Player");
	ImGui::Checkbox("J", &JumpFlag);
	ImGui::SliderFloat("J", &Jump, 0, 10);
	ImGui::SliderFloat("G", &Gravity, 0, 10);
	ImGui::SliderFloat("GP", &GravityPower, 0, 10);
	ImGui::SliderFloat("X", &player_.pos_.x_, 0, 10);
	ImGui::SliderFloat("Y", &player_.pos_.y_, 0, 10);
	ImGui::End();

	//�X�V
	player_.UpdateMatrix();
	playerDra_.Update();
}


void Player::Reset()
{
	player_.Initialize({ {0.0f,0.0f,0.0f}, {}, {0.49f,0.9f,1.0f} });
	direction_ = { +1.0f,0.0f,0.0f };
	playerDra_.Reset();

	//�ʒu
	player_.pos_.x_ = startPos.x_;
	player_.pos_.y_ = startPos.y_;

	//�v���C���[�����蔲���邩
	SetClearFlag(false);

	//�t�B���^�[�̊p�ɓ������Ă��邩�ǂ���
	SetCornerFlag(false);

	Jump = 0;
	JumpPower = 0;

	JumpFlag = false;

	Gravity = 0;
	GravityPower = 0;
}

void Player::JumpReset()
{
	Jump = 1.2f;
	JumpPower = 0;

	JumpFlag = true;

	Gravity = 0;
	GravityPower = 0;

	playerDra_.JumpAnimation();
}

//�d�́A���͂̉��Z
void Player::AddGravity()
{
	//�t���O��on�Ȃ�
	if (JumpFlag)
	{
		//���Z����͂��c���Ă���Ȃ�
		if (Jump > 0)
		{
			//�d�͕����Z
			JumpPower += Gravity;

			//�W�����v�͌��Z
			Jump -= JumpPower;

			//���W�������
			player_.pos_.y_ += Jump;
		}

		//�d��
		if (Gravity < 0.2f)
		{
			GravityPower += 0.01f;
			Gravity += GravityPower;
		}
	}

	//�d�͂�����
	player_.pos_.y_ -= Gravity;
}

void Player::PlayerMove(YMath::Vector3 pos)
{
	//�ړ�
	player_.pos_ += pos;

	//�X�V����
	player_.UpdateMatrix();
	playerDra_.Update();
}

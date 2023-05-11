#include "Player.h"

Player::Player()
{
	player_.Initialize({ {}, {}, {0.5f,0.5f,1.0f} });
	direction_ = { +1.0f,0.0f,0.0f };
	playerDra_.Initialize(&player_, &direction_);

	player_.scale_.x_ = 4.0f;
	player_.scale_.y_ = 8.0f;
}

Player::~Player()
{
}

void Player::Initialize()
{
	player_.Initialize({ {}, {}, {0.5f,0.5f,1.0f} });
	direction_ = { +1.0f,0.0f,0.0f };
	playerDra_.Initialize(&player_, &direction_);

	player_.scale_.x_ = 4.0f;
	player_.scale_.y_ = 8.0f;
}

void Player::Update()
{
	
	//çXêV
	player_.UpdateMatrix();
	playerDra_.Update();
}

void Player::Draw()
{
	playerDra_.Draw();
}


void Player::Reset()
{
	player_.Initialize({ {0.0f,0.0f,0.0f}, {}, {0.49f,0.9f,1.0f} });
	direction_ = { +1.0f,0.0f,0.0f };
	playerDra_.Reset();
}

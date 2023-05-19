#include "TestPlayer.h"

TestPlayer::TestPlayer(void)
{
    YukiMapchipCollider::Initialize();
    bd_.Initialize(&transform_, IMode::Type::Normal);
}

void TestPlayer::Update(void)
{
    YukiMapchipCollider::UpdatePos();
    bd_.Update();

    Move();
}

void TestPlayer::Draw(void)
{
    bd_.Draw();
}

void TestPlayer::Move(void)
{
    velocity_.x_ = keys_->IsDown(DIK_A) - keys_->IsDown(DIK_D) * speed_;
    Jump();

    velocity_.y_ -= gravity_;
}

void TestPlayer::Jump(void)
{
    // 静的に値を保持
    static float jumpValue{};

    // ジャンプ入力
    if (keys_->IsDown(DIK_SPACE))
        jumpValue = jumpPower_; // 跳躍量に跳躍力を代入

    // 跳躍量は常に減少する
    jumpValue -= jumpFall_;
    jumpValue = (std::max)(jumpValue, 0.f); // 跳躍量は決して0を下回らない

    // 平常時は0が入り続けるので、変わらない。
    velocity_.y_ += jumpValue;
}

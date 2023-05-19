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
    // �ÓI�ɒl��ێ�
    static float jumpValue{};

    // �W�����v����
    if (keys_->IsDown(DIK_SPACE))
        jumpValue = jumpPower_; // �����ʂɒ����͂���

    // �����ʂ͏�Ɍ�������
    jumpValue -= jumpFall_;
    jumpValue = (std::max)(jumpValue, 0.f); // �����ʂ͌�����0�������Ȃ�

    // ���펞��0�����葱����̂ŁA�ς��Ȃ��B
    velocity_.y_ += jumpValue;
}

#include "TestPlayer.h"
#include <imgui.h>

void TestPlayer::Initialize(void)
{
    YukiMapchipCollider::Initialize();
    bd_.Initialize(&transform_, BlockDrawerCommon::Type::eWhite);
    radius_.x_ = 1.f;
    radius_.y_ = 1.f;
}

void TestPlayer::Update(void)
{
    YukiMapchipCollider::UpdatePos();
    bd_.Update();

    Move();

    DrawDebug();
}

void TestPlayer::Draw(void)
{
    bd_.Draw();
}

void TestPlayer::DrawDebug(void)
{
    ImGui::Begin("testPlayer");
    ImGui::Text("transform: %f,%f,%f", transform_.pos_.x_, transform_.pos_.y_, transform_.pos_.z_);
    ImGui::Text("velocity: %f,%f,%f", velocity_.x_, velocity_.y_, velocity_.z_);
    ImGui::Spacing();
    ImGui::Text("point[TL]: %f,%f", point_.TopLeft_.x_, point_.TopLeft_.y_);
    ImGui::Text("point[TR]: %f,%f", point_.TopRight_.x_, point_.TopRight_.y_);
    ImGui::Text("point[BL]: %f,%f", point_.BottomLeft_.x_, point_.BottomLeft_.y_);
    ImGui::Text("point[BR]: %f,%f", point_.BottomRight_.x_, point_.BottomRight_.y_);
    ImGui::End();
}

void TestPlayer::Move(void)
{
    velocity_.x_ = (keys_->IsDown(DIK_D) - keys_->IsDown(DIK_A)) * speed_;
    velocity_.x_ += (keys_->IsTrigger(DIK_P) - keys_->IsTrigger(DIK_O)) * speed_;
    Jump();

    velocity_.y_ -= gravity_;

    // �����I�[���x
    velocity_.y_ = (std::max)(velocity_.y_, -1.75f);

    velocity_.Normalized();
}

void TestPlayer::Jump(void)
{
    // �ÓI�ɒl��ێ�
    static float jumpValue{};

    // �W�����v����
    if (keys_->IsTrigger(DIK_SPACE))
        jumpValue = jumpPower_; // �����ʂɒ����͂���

    // �΂�
    if (isSpring_) {
        isSpring_ = false;
        jumpValue = springPower_;
    }

    // �����ʂ͏�Ɍ�������
    jumpValue -= jumpFall_;
    jumpValue = (std::max)(jumpValue, 0.f); // �����ʂ͌�����0�������Ȃ�

    // ���펞��0�����葱����̂ŁA�ς��Ȃ��B
    velocity_.y_ += jumpValue;
}

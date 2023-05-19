#include "YukiMapchipCollider.h"

YukiMapchipCollider::YukiMapchipCollider(void)
{
    Initialize();
}

void YukiMapchipCollider::Initialize(void)
{
    transform_.Initialize(Transform::Status{});
}

void YukiMapchipCollider::UpdatePos(void)
{
    transform_.pos_ += velocity_;
    transform_.UpdateMatrix();

    // 左上
    point_.TopLeft_.x_ = transform_.pos_.x_ - radius_.x_;
    point_.TopLeft_.y_ = transform_.pos_.y_ + radius_.y_;
    // 右上
    point_.TopRight_.x_ = transform_.pos_.x_ + radius_.x_;
    point_.TopRight_.y_ = transform_.pos_.y_ + radius_.y_;
    // 左下
    point_.BottomLeft_.x_ = transform_.pos_.x_ - radius_.x_;
    point_.BottomLeft_.y_ = transform_.pos_.y_ - radius_.y_;

    // 右下
    point_.BottomRight_.x_ = transform_.pos_.x_ + radius_.x_;
    point_.BottomRight_.y_ = transform_.pos_.y_ - radius_.y_;
}

#include "YukiMapchipCollider.h"

YukiMapchipCollider::YukiMapchipCollider(void)
{
    transform_.Initialize(Transform::Status{});
}

void YukiMapchipCollider::Update(void)
{
    // ç∂è„
    point_.TopLeft_.x_ = transform_.pos_.x_ - radius_.x_;
    point_.TopLeft_.y_ = transform_.pos_.y_ + radius_.y_;
    // âEè„
    point_.TopRight_.x_ = transform_.pos_.x_ + radius_.x_;
    point_.TopRight_.y_ = transform_.pos_.y_ + radius_.y_;
    // ç∂â∫
    point_.BottomLeft_.x_ = transform_.pos_.x_ - radius_.x_;
    point_.BottomLeft_.y_ = transform_.pos_.y_ - radius_.y_;
    // âEâ∫
    point_.BottomRight_.x_ = transform_.pos_.x_ + radius_.x_;
    point_.BottomRight_.y_ = transform_.pos_.y_ - radius_.y_;
}

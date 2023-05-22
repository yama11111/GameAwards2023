#include "YukiMapchipCollider.h"
#include <cmath>

YukiMapchipCollider::YukiMapchipCollider(void)
{
    Initialize();
}

void YukiMapchipCollider::Initialize(void)
{
    transform_.Initialize();
}

void YukiMapchipCollider::UpdatePos(void)
{
    // �ۂߌ덷���� - transform.pos
    transform_.pos_ = { roundToDecimal(transform_.pos_.x_, decimalPlace_),roundToDecimal(transform_.pos_.y_,  decimalPlace_),roundToDecimal(transform_.pos_.z_,  decimalPlace_) };
    // �ۂߌ덷���� - velocity
     velocity_ = { roundToDecimal(velocity_.x_, decimalPlace_),roundToDecimal(velocity_.y_, decimalPlace_), roundToDecimal(velocity_.z_, decimalPlace_) };

    // ���Z
    transform_.pos_ += velocity_;
    transform_.UpdateMatrix();

    isOldGrounded_ = isGrounded_;

    UpdatePoint();
}

void YukiMapchipCollider::UpdatePoint(void)
{
    // ����̍��W�Z�o�Ɗۂߌ덷����
    point_.TopLeft_.x_ = transform_.pos_.x_ - radius_.x_;
    point_.TopLeft_.y_ = transform_.pos_.y_ + radius_.y_;
    point_.TopLeft_.x_ = roundToDecimal(point_.TopLeft_.x_, decimalPlace_);
    point_.TopLeft_.y_ = roundToDecimal(point_.TopLeft_.y_, decimalPlace_);
    // �E��̍��W�Z�o�Ɗۂߌ덷����
    point_.TopRight_.x_ = transform_.pos_.x_ + radius_.x_;
    point_.TopRight_.y_ = transform_.pos_.y_ + radius_.y_;
    point_.TopRight_.x_ = roundToDecimal(point_.TopRight_.x_, decimalPlace_);
    point_.TopRight_.y_ = roundToDecimal(point_.TopRight_.y_, decimalPlace_);
    // �����̍��W�Z�o�Ɗۂߌ덷����
    point_.BottomLeft_.x_ = transform_.pos_.x_ - radius_.x_;
    point_.BottomLeft_.y_ = transform_.pos_.y_ - radius_.y_;
    point_.BottomLeft_.x_ = roundToDecimal(point_.BottomLeft_.x_, decimalPlace_);
    point_.BottomLeft_.y_ = roundToDecimal(point_.BottomLeft_.y_, decimalPlace_);
    // �E���̍��W�Z�o�Ɗۂߌ덷����
    point_.BottomRight_.x_ = transform_.pos_.x_ + radius_.x_;
    point_.BottomRight_.y_ = transform_.pos_.y_ - radius_.y_;
    point_.BottomRight_.x_ = roundToDecimal(point_.BottomRight_.x_, decimalPlace_);
    point_.BottomRight_.y_ = roundToDecimal(point_.BottomRight_.y_, decimalPlace_);
}

float YukiMapchipCollider::roundToDecimal(float value, int decimalPlaces)
{
    float multiplier = (float)std::pow(10.0f, decimalPlaces);
    float roundedValue = (int)std::round(value * multiplier) / multiplier;
    return roundedValue;
}

#include "YukiMapchipCollider.h"
#include <cmath>

YukiMapchipCollider::YukiMapchipCollider(void)
{
    Initialize();
}

void YukiMapchipCollider::Initialize(void)
{
    trfm_.Initialize();
}

void YukiMapchipCollider::UpdatePos(void)
{
    // 丸め誤差処理 - transform.pos
    trfm_.pos_ = { roundToDecimal(trfm_.pos_.x_, decimalPlace_),roundToDecimal(trfm_.pos_.y_,  decimalPlace_),roundToDecimal(trfm_.pos_.z_,  decimalPlace_) };
    // 丸め誤差処理 - velocity
    velocity_ = { roundToDecimal(velocity_.x_, decimalPlace_),roundToDecimal(velocity_.y_, decimalPlace_), roundToDecimal(velocity_.z_, decimalPlace_) };

    // 加算
    trfm_.pos_ += velocity_;
    trfm_.UpdateMatrix();

    if (isTeleport_)
    {
        isTeleport_ = false;
        isGrounded_ = false;
        trfm_.pos_ = { roundToDecimal(teleportedPos_.x_, decimalPlace_),roundToDecimal(teleportedPos_.y_,  decimalPlace_),roundToDecimal(teleportedPos_.z_,  decimalPlace_) };
        idxSign_ = teleportedIdxSign_;
    }
    isOldGrounded_ = isGrounded_;

    UpdatePoint();
}

void YukiMapchipCollider::UpdatePoint(void)
{
    // 左上の座標算出と丸め誤差処理
    point_.TopLeft_.x_ = trfm_.pos_.x_ - radius_.x_;
    point_.TopLeft_.y_ = trfm_.pos_.y_ + radius_.y_;
    point_.TopLeft_.x_ = roundToDecimal(point_.TopLeft_.x_, decimalPlace_);
    point_.TopLeft_.y_ = roundToDecimal(point_.TopLeft_.y_, decimalPlace_);
    // 右上の座標算出と丸め誤差処理
    point_.TopRight_.x_ = trfm_.pos_.x_ + radius_.x_;
    point_.TopRight_.y_ = trfm_.pos_.y_ + radius_.y_;
    point_.TopRight_.x_ = roundToDecimal(point_.TopRight_.x_, decimalPlace_);
    point_.TopRight_.y_ = roundToDecimal(point_.TopRight_.y_, decimalPlace_);
    // 左下の座標算出と丸め誤差処理
    point_.BottomLeft_.x_ = trfm_.pos_.x_ - radius_.x_;
    point_.BottomLeft_.y_ = trfm_.pos_.y_ - radius_.y_;
    point_.BottomLeft_.x_ = roundToDecimal(point_.BottomLeft_.x_, decimalPlace_);
    point_.BottomLeft_.y_ = roundToDecimal(point_.BottomLeft_.y_, decimalPlace_);
    // 右下の座標算出と丸め誤差処理
    point_.BottomRight_.x_ = trfm_.pos_.x_ + radius_.x_;
    point_.BottomRight_.y_ = trfm_.pos_.y_ - radius_.y_;
    point_.BottomRight_.x_ = roundToDecimal(point_.BottomRight_.x_, decimalPlace_);
    point_.BottomRight_.y_ = roundToDecimal(point_.BottomRight_.y_, decimalPlace_);
}

float YukiMapchipCollider::roundToDecimal(float value, int decimalPlaces)
{
    float multiplier = (float)std::pow(10.0f, decimalPlaces);
    float roundedValue = (int)std::round(value * multiplier) / multiplier;
    return roundedValue;
}

#include "IBlock.h"
#include "Vector3.h"

IBlock::IBlock(const YMath::Vector2& pos, const YMath::Vector2& offset, const YMath::Vector2& radius) :
    type_(Type::NONE), pos_(pos), offset_(offset), radius_(radius), rotate_(0)
{
    transform_.Initialize({ YMath::Vector3{pos.x_,pos.y_,0},YMath::Vector3{0,0,(float)rotate_},YMath::Vector3{radius.x_,radius.y_, 1} });
    bDrawer_.Initialize(&transform_, IMode::Type::Normal);
}

void IBlock::Update(void)
{
    transform_.pos_ = { pos_.x_,pos_.y_,0 };
    transform_.rota_ = { 0,0,(float)rotate_ };
    //transform_.scale_ = { radius_.x_,radius_.y_,1 };
    transform_.scale_ = { radius_.x_/2,radius_.y_/2,1 };

    transform_.UpdateMatrix();
    bDrawer_.Update();
}

void IBlock::Draw(void)
{
    bDrawer_.Draw();
}

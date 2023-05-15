#include "WoodenBlock.h"

WoodenBlock::WoodenBlock(const YMath::Vector2& pos, const YMath::Vector2& offset, const YMath::Vector2& radius) :
    IBlock(pos, offset, radius)
{
    SetType(Type::WOODEN);
}

void WoodenBlock::Update(void)
{
    IBlock::Update();
}

void WoodenBlock::Draw(void)
{
    IBlock::Draw();
}

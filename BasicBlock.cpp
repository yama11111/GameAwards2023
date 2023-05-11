#include "BasicBlock.h"

BasicBlock::BasicBlock(const YMath::Vector2& pos, const YMath::Vector2& offset, const YMath::Vector2& radius) :
    IBlock(pos, offset, radius)
{
    SetType(Type::BASIC);
}

void BasicBlock::Update(void)
{
    IBlock::Update();
}

void BasicBlock::Draw(void)
{
    IBlock::Draw();
}

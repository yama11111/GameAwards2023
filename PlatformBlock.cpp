#include "PlatformBlock.h"

PlatformBlock::PlatformBlock(const YMath::Vector2& pos, const YMath::Vector2& offset, const YMath::Vector2& radius) :
    IBlock(pos, offset, radius)
{
    SetType(Type::PLATFORM);
}

void PlatformBlock::Update(void)
{
    IBlock::Update();
}

void PlatformBlock::Draw(void)
{
    IBlock::Draw();
}

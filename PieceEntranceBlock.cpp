#include "PieceEntranceBlock.h"

PieceEntranceBlock::PieceEntranceBlock(const YMath::Vector2& pos, const YMath::Vector2& offset, const YMath::Vector2& radius) :
    IBlock(pos, offset, radius)
{
    SetType(Type::PIECEENTRANCE);
}

void PieceEntranceBlock::Update(void)
{
    IBlock::Update();
}

void PieceEntranceBlock::Draw(void)
{
    if (GetEntranceOpen() == false)
        IBlock::Draw();
}

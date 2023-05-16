#include "PieceEntranceBlock.h"

PieceEntranceBlock::PieceEntranceBlock(const YMath::Vector2& pos, const YMath::Vector2& offset, bool tab, const YMath::Vector2& radius) :
    IBlock(pos, offset, radius)
{
    SetType(Type::PIECEENTRANCE);
    tab ?
        IBlock::GetBlockDrawerRef().Reset(IMode::Type::Junction1) :
        IBlock::GetBlockDrawerRef().Reset(IMode::Type::Junction2);
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

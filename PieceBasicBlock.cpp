#include "PieceBasicBlock.h"

PieceBasicBlock::PieceBasicBlock(const YMath::Vector2& pos, const YMath::Vector2& offset, const YMath::Vector2& radius) :
    IBlock(pos,offset,radius)
{
    SetType(Type::PIECEBASIC);
}

void PieceBasicBlock::Update(void)
{
    IBlock::Update();
}

void PieceBasicBlock::Draw(void)
{
    IBlock::Draw();
}

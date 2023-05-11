#pragma once
#include "IBlock.h"
class PieceEntranceBlock :
    public IBlock
{
public:
    // ä÷êî
    PieceEntranceBlock(const YMath::Vector2& pos, const YMath::Vector2& offset, const YMath::Vector2& radius = { 1,1 });
    ~PieceEntranceBlock(void) {};

    void Update(void) override;
    void Draw(void) override;
};


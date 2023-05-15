#pragma once
#include "IBlock.h"
class WoodenBlock :
    public IBlock
{
public:
    // ä÷êî
    WoodenBlock(const YMath::Vector2& pos, const YMath::Vector2& offset, const YMath::Vector2& radius = { 1,1 });
    ~WoodenBlock(void) {};

    void Update(void) override;
    void Draw(void) override;
};


#pragma once
#include "IBlock.h"
class BasicBlock :
    public IBlock
{
public:
    // ä÷êî
    BasicBlock(const YMath::Vector2& pos, const YMath::Vector2& offset, const YMath::Vector2& radius = { 1,1 });
    ~BasicBlock(void) {};

    void Update(void) override;
    void Draw(void) override;
};


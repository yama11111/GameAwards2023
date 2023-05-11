#pragma once
#include "IBlock.h"
class SpringBlock :
    public IBlock
{
public:
    // ä÷êî
    SpringBlock(const YMath::Vector2& pos, const YMath::Vector2& offset, const YMath::Vector2& radius = { 1,1 });
    ~SpringBlock(void) {};

    void Update(void) override;
    void Draw(void) override;
};


#pragma once
#include "IBlock.h"
class PlatformBlock :
    public IBlock
{
public:
    // ä÷êî
    PlatformBlock(const YMath::Vector2& pos, const YMath::Vector2& offset, const YMath::Vector2& radius = { 1,1 });
    ~PlatformBlock(void) {};

    void Update(void) override;
    void Draw(void) override;
};


#pragma once
#include "IBlock.h"
#include "GoalDrawer.h"

class GoalBlock :
    public IBlock
{
    // ä÷êî
    GoalBlock(const YMath::Vector2& pos, const YMath::Vector2& offset, const YMath::Vector2& radius = { 1,1 });
    ~GoalBlock(void) {};

    void Update(void) override;
    void Draw(void) override;

private:
    // ïœêî
    GoalDrawer goalDrawer_{};
};


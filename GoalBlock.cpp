#include "GoalBlock.h"

GoalBlock::GoalBlock(const YMath::Vector2& pos, const YMath::Vector2& offset, const YMath::Vector2& radius) :
    IBlock(pos, offset, radius)
{
    SetType(Type::GOAL);
}

void GoalBlock::Update(void)
{
    IBlock::Update();
}

void GoalBlock::Draw(void)
{
    IBlock::Draw();
}

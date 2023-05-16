#include "GoalBlock.h"

GoalBlock::GoalBlock(const YMath::Vector2& pos, const YMath::Vector2& offset, const YMath::Vector2& radius) :
    IBlock(pos, offset, radius)
{
    SetType(Type::GOAL);
    goalDrawer_.Initialize(IBlock::GetTransformPtr());
}

void GoalBlock::Update(void)
{
    YGame::Transform t{};
    t.pos_ = { IBlock::GetPos().x_,IBlock::GetPos().y_,0 };
    t.rota_ = { 0,0,(float)IBlock::GetRotate() };
    t.scale_ = { GetRadius().x_ / 2, GetRadius().y_ / 2,1};
    IBlock::SetTransform(t);

    IBlock::UseTransformUpdate();
    goalDrawer_.Update();
}

void GoalBlock::Draw(void)
{
    goalDrawer_.Draw();
}

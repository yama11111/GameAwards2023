#include "Stage.h"

using namespace YInput;

void Stage::Update(void)
{
    for (size_t i = 0; i < signVector_.size(); i++)
    {
        signVector_[i]->Update();
    }
}

void Stage::Draw(void)
{
    for (size_t i = 0; i < signVector_.size(); i++)
    {
        signVector_[i]->Draw();
    }
}

void Stage::MouseCol4Warp(void)
{
    for (size_t i = 0; i < signVector_.size(); i++)
    {
        signVector_[i]->mCollider_.CollisionMousePointer() &&
            Mouse::GetInstance()->IsTrigger(MouseClick::DIM_LEFT) ?
            isHoldSignVector_[i] = true :
            isHoldSignVector_[i] = false;

        if (isHoldSignVector_[i]) {

        }
    }
}

void Stage::RegisterSign(Sign* ptr)
{
    signVector_.emplace_back(ptr);
}

void Stage::CallPPC(YukiMapchipCollider* ptr)
{
    signVector_[ptr->idxSign_]->PPC(ptr);
}

const Stage::Vector3& Stage::GetTopLeftPos(size_t idx)
{
    return signVector_[idx]->topLeftPos_;
}

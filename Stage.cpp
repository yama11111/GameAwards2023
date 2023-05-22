#include "Stage.h"

void Stage::Update(void)
{
    for (YukiMapchipCollider* entity : colliderPtrList_)
    {
        signVector_[entity->idxSign_].Update();
        entity->Update();
        signVector_[entity->idxSign_].PPC(entity);
    }
}

void Stage::Draw(void)
{
    for (size_t i = 0; i < signVector_.size(); i++)
    {
        signVector_[i].Draw();
    }
}

void Stage::RegisterSign(Sign* ptr)
{
    //signVector_.emplace_back(ptr);
}

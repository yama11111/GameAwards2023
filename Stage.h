#pragma once
#include "YukiMapchipCollider.h"
#include "Sign.h"
#include <list>

class Stage
{
protected:
    using Sign = maruyama::Sign;

public:
    // ŠÖ”
    Stage(void) {};

    void Update(void);
    void Draw(void);

    void RegisterSign(Sign* ptr);
    void RegisterEntity(YukiMapchipCollider* ptr);

    // •Ï”
    std::vector<std::unique_ptr<Sign>> signVector_;
    std::list<YukiMapchipCollider*> colliderPtrList_;
};


#pragma once
#include "YukiMapchipCollider.h"
#include "Sign.h"
#include <list>

class Stage
{
protected:
    using Sign = maruyama::Sign;

public:
    // �֐�
    Stage(void) {};

    void Update(void);
    void Draw(void);

    void RegisterSign(Sign* ptr);

    // �ϐ�
    std::vector<Sign> signVector_;
    std::list<YukiMapchipCollider*> colliderPtrList_;
};


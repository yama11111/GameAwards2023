#pragma once
#include "Sign.h"
#include <list>

class Stage
{
protected:
    using Sign = maruyama::Sign;

public:
    // �֐�
    Stage(void) {};

    // �ϐ�
    std::list<Sign> list_;
};


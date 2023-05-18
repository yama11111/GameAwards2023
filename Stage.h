#pragma once
#include "Sign.h"
#include <list>

class Stage
{
protected:
    using Sign = maruyama::Sign;

public:
    // ŠÖ”
    Stage(void) {};

    // •Ï”
    std::list<Sign> list_;
};


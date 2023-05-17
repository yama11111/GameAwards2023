#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Transform.h"

class IBlock
{
protected:
    // íËã`
    using Vector2 = YMath::Vector2;
    using Vector3 = YMath::Vector3;
    using Vector4 = YMath::Vector4;
    using Transform = YGame::Transform;

    enum class Type
    {
        NONE,
        BASIC,
    };

public:
    // ä÷êî
    IBlock(void) = default;
    virtual ~IBlock(void) = default;

    virtual void Update(void) {}
    virtual void Draw(void) {}

    // ïœêî
    Vector3 pos_{};
    Vector3 radius_{};
    Type type_{};
};


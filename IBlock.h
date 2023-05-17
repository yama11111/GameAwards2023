#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Transform.h"

class IBlock
{
protected:
    // 定義
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
    // 関数
    IBlock(void) = default;
    virtual ~IBlock(void) = default;

    virtual void Update(void) {}
    virtual void Draw(void) {}

    // 変数
    Vector3 pos_{};
    Vector3 radius_{};
    Type type_{};
};


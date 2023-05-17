#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Transform.h"
class YukiMapchipCollider
{
protected:
    // 定義
    using Vector2 = YMath::Vector2;
    using Vector3 = YMath::Vector3;
    using Vector4 = YMath::Vector4;
    using Transform = YGame::Transform;

public:
    struct Point
    {
        Vector2 TopLeft_{};
        Vector2 TopRight_{};
        Vector2 BottomLeft_{};
        Vector2 BottomRight_{};
    };

public:
    // 関数
    YukiMapchipCollider(void);
    virtual ~YukiMapchipCollider(void) = default;

    void UpdatePos(void);

    // 変数
    Transform transform_{};
    Vector3 radius_{};
    Vector3 velocity_{};

    Point point_{};
};


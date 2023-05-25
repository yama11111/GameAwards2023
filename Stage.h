#pragma once
#include "YukiMapchipCollider.h"
#include "Sign.h"
#include <list>
#include "Mouse.h"

class Stage
{
protected:
    // 定義
    using Vector2 = YMath::Vector2;
    using Vector3 = YMath::Vector3;
    using Vector4 = YMath::Vector4;
    using Transform = YGame::Transform;
    using Sign = maruyama::Sign;

public:
    // 関数
    Stage(void) {};

    void Update(void);
    void Draw(void);

    void MouseCol4Warp(void);
    void RegisterSign(Sign* ptr);
    void CallPPC(YukiMapchipCollider* ptr);

    const Vector3& GetTopLeftPos(size_t idx);

    // 変数
    std::vector<std::unique_ptr<Sign>> signVector_;
    std::vector<bool> isHoldSignVector_;
};


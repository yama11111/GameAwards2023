#pragma once
#include "YukiMapchipCollider.h"
#include "Sign.h"
#include <list>

class Stage
{
protected:
    // íËã`
    using Vector2 = YMath::Vector2;
    using Vector3 = YMath::Vector3;
    using Vector4 = YMath::Vector4;
    using Transform = YGame::Transform;
    using Sign = maruyama::Sign;

public:
    // ä÷êî
    Stage(void) {};

    void Update(void);
    void Draw(void);

    void RegisterSign(Sign* ptr);
    void CallPPC(YukiMapchipCollider* ptr);

    const Vector3& GetTopLeftPos(size_t idx);

    // ïœêî
    std::vector<std::unique_ptr<Sign>> signVector_;
};


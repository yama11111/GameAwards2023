#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Transform.h"
class YukiMapchipCollider
{
protected:
    // íËã`
    using Vector2 = YMath::Vector2;
    using Vector3 = YMath::Vector3;
    using Vector4 = YMath::Vector4;
    using Transform = YGame::Transform;


public:
    static constexpr int decimalPlace_{ 3 };
    static constexpr float gravity_{ 0.15f };

    enum class EntityType
    {
        PLAYER,
        WOODENBOX,
        LASOR,
    };

    struct Point
    {
        Vector2 TopLeft_{};
        Vector2 TopRight_{};
        Vector2 BottomLeft_{};
        Vector2 BottomRight_{};
    };

public:
    // ä÷êî
    YukiMapchipCollider(void);
    virtual ~YukiMapchipCollider(void) = default;

    void Initialize(void);
    virtual void Update(void) = 0;
    void UpdatePos(void);
    void UpdatePoint(void);

protected:
    float roundToDecimal(float value, int decimalPlaces);

public:
    // ïœêî
    Transform trfm_{};
    Vector3 radius_{};
    Vector3 velocity_{};

    Point point_{};

    EntityType entityType_{};

    size_t idxSign_{};

    bool isSpring_{};
    bool isGrounded_{};
    bool isOldGrounded_{};

    bool isTeleport_{};
    Vector3 teleportedPos_{};
    size_t teleportedIdxSign_{};
    Vector2 teleportedVec_{};
};


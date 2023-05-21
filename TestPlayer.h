#pragma once
#include "YukiMapchipCollider.h"
#include "BlockDrawer.h"
#include "Keys.h"

class TestPlayer :
    public YukiMapchipCollider
{
public:
    static constexpr float gravity_{ 0.2f };
    static constexpr float jumpPower_{ 7.f };
    static constexpr float jumpFall_{ 0.2f };
    static constexpr float speed_{ 0.4f };

    TestPlayer(void) = default;

    void Initialize(void);
    void Update(void);
    void Draw(void);

    void DrawDebug(void);

    BlockDrawer bd_{};
    YInput::Keys* keys_{ YInput::Keys::GetInstance() };

private:
    void Move(void);
    void Jump(void);
};


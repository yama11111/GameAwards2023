#pragma once
#include "YukiMapchipCollider.h"
#include "BlockDrawer.h"
#include "Keys.h"

class TestPlayer :
    public YukiMapchipCollider
{
public:
    static constexpr float gravity_{ 3.5f };
    static constexpr float jumpPower_{ 7.f };
    static constexpr float jumpFall_{ 0.2f };
    static constexpr float speed_{ 5.0f };

    TestPlayer(void);

    void Update(void);
    void Draw(void);

    BlockDrawer bd_{};
    YInput::Keys* keys_{ YInput::Keys::GetInstance() };

private:
    void Move(void);
    void Jump(void);
};


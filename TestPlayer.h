#pragma once
#include "YukiMapchipCollider.h"
#include "BlockDrawer.h"
#include "Keys.h"

class TestPlayer :
    public YukiMapchipCollider
{
public:
    static constexpr float jumpPower_{ 0.8f };
    static constexpr float jumpFall_{ 0.15f };
    static constexpr float speed_{ 0.4f };

    TestPlayer(void) = default;

    void Initialize(void);
    void Update(void);
    void Draw(void);

    void DrawDebug(void);

    BlockDrawer bd_{};
    YInput::Keys* keys_{ YInput::Keys::GetInstance() };

    size_t idxSign_{};
private:
    void Move(void);
    void Jump(void);
};


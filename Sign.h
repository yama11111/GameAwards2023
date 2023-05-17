#pragma once
#include <vector>
#include <memory>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Transform.h"

#include "YukiMapchipCollider.h"

class Sign
{
protected:
    // 定義
    using Vector2 = YMath::Vector2;
    using Vector3 = YMath::Vector3;
    using Vector4 = YMath::Vector4;
    using Transform = YGame::Transform;

    static constexpr float pushOut_{ 0.2f };
    static constexpr float blockRadius_{ 16.f };

    enum class BlockType
    {
        NONE,
        BASIC,
    };

public:
    // 関数
    Sign(const Vector2& mapchipSize);

    void Update(void);
    void Draw(void);

    // パーフェクトピクセルコリジョン
    void PPC(YukiMapchipCollider* ptr);
    const Vector2& CalcVelStuck(const Vector2& pointPos); // 移動入力なしの押し出し値計算関数 ※Moveの前に使う =>今使ってない
    const Vector2& CalcVelMove(const Vector2& pointPos, const Vector2& vel); // 移動入力ありの押し出し値計算関数 ※Stuckの後に使う

    // 変数
    //std::vector<std::vector<std::unique_ptr<IBlock>>> mapchip2_{};
    std::vector<std::vector<int>> mapchip_{};
    
    // 基点（左上）座標
    Vector3 topLeftPos_{}; // zは常に0
};


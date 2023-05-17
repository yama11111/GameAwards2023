#pragma once
#include "IBlock.h"
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

public:
    // 関数
    Sign(const Vector2& mapchipSize);

    void Update(void);
    void Draw(void);

    // パーフェクトピクセルコリジョン
    void PPC(YukiMapchipCollider* ptr);

    // 変数
    std::vector<std::vector<std::unique_ptr<IBlock>>> mapchip_{};
};


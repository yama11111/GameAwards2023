#pragma once
#include "YukiMapchipCollider.h"
#include "Sign.h"
#include <list>
#include "Mouse.h"

class Stage
{
protected:
    // ��`
    using Vector2 = YMath::Vector2;
    using Vector3 = YMath::Vector3;
    using Vector4 = YMath::Vector4;
    using Transform = YGame::Transform;
    using Sign = maruyama::Sign;

public:
    // �֐�
    Stage(void) {};

    void Update(void);
    void Draw(void);

    void DrawDebug(void);

    void MouseCol4Warp(void);
    void RegisterSign(Sign* ptr);
    void CallPPC(YukiMapchipCollider* ptr);

    const Vector3& GetTopLeftPos(size_t idx);

    // �ϐ�
    std::vector<std::unique_ptr<Sign>> signVector_;
    std::vector<bool> isHoldSignVector_;

    bool isReset_{};

    // MouseCol4Warp�p
    // WARP
    size_t mc4w_IdxWarpInfo_start_{};
    size_t mc4w_idxWarpInfo_end_{};
    bool mc4w_isConnectingWarp_{};
    // Sign
    // �I�t�Z�b�g
    Vector2 mc4w_offset_{};
    size_t mc4w_idxSign_start_{};
    size_t mc4w_idxSign_end_{};
    bool mc4w_isHoldOther_{};

    bool mc4w_isConnectCheck_{};
};


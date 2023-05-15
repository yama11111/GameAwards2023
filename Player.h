#pragma once
#include "Vector2.h"
#include "Stage.h"
#include "Keys.h"
#include "Transform.h"
#include "PlayerDrawer.h"
#include "Vector3.h"

class Player
{
public:
    // 定数
    static constexpr uint32_t defaultWidth_{ 4 };
    static constexpr uint32_t defaultHeight_{ 8 };
    static constexpr float moveSpeed_{ 3.f };       // 移動速度
    static constexpr float jumpPower_{ 7.f };       // ジャンプ力
    static constexpr float fallValue_{ 0.2f };      // ジャンプ力の減衰
    static constexpr float gravity_{ 3.5f };        // 重力
    static constexpr float springPower_{ 8.f };    // バネで跳ねる時の跳躍力

    // 関数
    Player(Stage* stagePtr);
    void Update(void);
    void Draw(void);

    void DrawDebug(void);

private:
    void Move(void);
    void Jump(YMath::Vector2& vel);
    void Spring(YMath::Vector2& vel, int rot);

    void Collision(YMath::Vector2& vel);
    bool CheckHit(float pos, float radius, float vel, float blockpos, float blockradius);
    bool CheckHit(float pos, float radius, float vel, float blockpos, float blockradius, float& surplus);

    // 変数
    YMath::Vector2 pos_{};
    YMath::Vector2 radius_{};
    YMath::Vector2 offsetForPieceCenter_{};

    bool isJump_{ true };
    bool isSpring_{};
    // 持ち運び
    bool isCarryWoodenBox_{};

    Stage* stagePtr_;

    //ばねに触れた時の角度を入れる変数
    int nowSpringRot = 0;
    //代入変数
    YMath::Vector2 nowVel = { 0, 0 };

    YGame::Transform transform_;
    //PlayerDrawer pDrawer_;
    BlockDrawer pBDrawer_;
    YMath::Vector3 direction_{ 1,0,0 }; 

    YInput::Keys* keysPtr_{};
public:
    // setter・getter
    inline void SetPos(const YMath::Vector2& pos) { pos_ = pos; };
    inline void SetRadius(const YMath::Vector2& radius) { radius_ = radius; };
    inline void SetOffset(const YMath::Vector2& offset) { offsetForPieceCenter_ = offset; }

    inline const YMath::Vector2& GetPos(void) { return pos_; }
    inline const YMath::Vector2& GetRadius(void) { return radius_; }
    inline YMath::Vector2* GetPosPtr(void) { return &pos_; }
    inline const YMath::Vector2& GetOffset(void) { return offsetForPieceCenter_; }
};


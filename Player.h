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
    // �萔
    static constexpr uint32_t defaultWidth_{ 4 };
    static constexpr uint32_t defaultHeight_{ 8 };
    static constexpr float moveSpeed_{ 3.f };       // �ړ����x
    static constexpr float jumpPower_{ 7.f };       // �W�����v��
    static constexpr float fallValue_{ 0.2f };      // �W�����v�͂̌���
    static constexpr float gravity_{ 3.5f };        // �d��
    static constexpr float springPower_{ 12.f };    // �o�l�Œ��˂鎞�̒�����

    // �֐�
    Player(Stage* stagePtr);
    void Update(void);
    void Draw(void);
    
    void DrawDebug(void);

private:
    void Move(void);
    void Jump(YMath::Vector2& vel,bool spring);

    void Collision(YMath::Vector2& vel);
    bool CheckHit(float pos, float radius, float vel, float blockpos, float blockradius);
    bool CheckHit(float pos, float radius, float vel, float blockpos, float blockradius, float& surplus);

    // �ϐ�
    YMath::Vector2 pos_{};
    YMath::Vector2 radius_{};
    YMath::Vector2 offsetForPieceCenter_{};

    bool isJump_{ true };

    Stage* stagePtr_;

    YGame::Transform transform_;
    //PlayerDrawer pDrawer_;
    BlockDrawer pBDrawer_;
    YMath::Vector3 direction_{ 1,0,0 }; 

    YInput::Keys* keysPtr_{};
public:
    // setter�Egetter
    inline void SetPos(const YMath::Vector2& pos) { pos_ = pos; };
    inline void SetRadius(const YMath::Vector2& radius) { radius_ = radius; };
    inline void SetOffset(const YMath::Vector2& offset) { offsetForPieceCenter_ = offset; }

    inline const YMath::Vector2& GetPos(void) { return pos_; }
    inline const YMath::Vector2& GetRadius(void) { return radius_; }
    inline YMath::Vector2* GetPosPtr(void) { return &pos_; }
    inline const YMath::Vector2& GetOffset(void) { return offsetForPieceCenter_; }
};


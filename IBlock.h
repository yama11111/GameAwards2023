#pragma once
#include "Vector2.h"
#include "Transform.h"
#include "BlockDrawer.h"

class IBlock
{
public:
    enum class Type
    {
        NONE,
        PIECEBASIC,
        PIECEENTRANCE,
        BASIC,
        PLATFORM,
        SPRING,
        WOODEN,
        GOAL,
    };

    static constexpr float radiusBase_{ 16.f };

    // 関数
    IBlock(const YMath::Vector2& pos, const YMath::Vector2& offset, const YMath::Vector2& radius = { radiusBase_,radiusBase_ });
    virtual ~IBlock(void) = default;

    virtual void Update(void);
    virtual void Draw(void);

private:
    // 変数
    Type type_;

    YMath::Vector2 pos_;
    YMath::Vector2 radius_;
    YMath::Vector2 offset_;

    int rotate_;

    // 当たり判定の有無
    bool isEntranceOpen_{};
    // このブロックを通過したかどうか
    bool isPlayerEnterInside_{ false };

    YGame::Transform transform_;
    BlockDrawer bDrawer_;

public:
    // setter・getter
    inline void SetEntranceOpen(bool inPiece) { isEntranceOpen_ = inPiece; }
    inline bool GetEntranceOpen(void) { return isEntranceOpen_; }

    inline void SetPlayerEnterInside(bool enterinside) { isPlayerEnterInside_ = enterinside; }
    inline bool GetPlayerEnterInside(void) { return isPlayerEnterInside_; }

    inline void SetType(const Type& type) { type_ = type; }
    inline void SetPos(const YMath::Vector2& pos) { pos_ = pos; }
    inline void SetOffset(const YMath::Vector2& offset) { offset_ = offset; }
    inline void SetRadius(const YMath::Vector2& radius) { radius_ = radius; }
    inline void SetRotate(int rotate) { rotate_ = rotate; }

    inline const Type& GetType(void) { return type_; }
    inline const YMath::Vector2& GetPos(void) { return pos_; }
    inline const YMath::Vector2& GetOffset(void) { return offset_; }
    inline const YMath::Vector2& GetRadius(void) { return radius_; }
    inline int GetRotate(void) { return rotate_; }
    inline BlockDrawer& GetBlockDrawerRef(void) { return bDrawer_; }
};


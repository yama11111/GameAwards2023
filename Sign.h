#pragma once
#include <map>
#include <vector>
#include <memory>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Transform.h"
#include "BlockDrawer.h"

#include "YukiMapchipCollider.h"

namespace maruyama {
    class Sign
    {
    protected:
        // 定義
        using Vector2 = YMath::Vector2;
        using Vector3 = YMath::Vector3;
        using Vector4 = YMath::Vector4;
        using Transform = YGame::Transform;

        static constexpr float blockRadius_{ 2.f }; // ブロックの半径

        static constexpr float pushOut_{ 0.2f }; // 定期的押し出し時の移動量
        static constexpr float springPower_{ 5.f }; // バネブロックのジャンプ力
        static constexpr float springFall_{ 0.5f }; // バネブロック時の落下速度

        enum class BlockType // ブロックの種類
        {
            NONE,
            BASIC,

            SPRING,

            WARP1,
            WARP2,
        };

        enum class Direction
        {
            TOP,
            RIGHT,
            LEFT,
            BOTTOM,
        };

        struct Vec2Int_t
        {
            size_t x_{};
            size_t y_{};
        };

        struct WarpIdx_t
        {
            // 自分が接続済みか - 可変
            bool isConnected_{};
            // 自分側の出現位置 - 不変
            Direction dirMe_{};

            // 相手の"ブロック"の配列要素数（看板に帰属） - 不変
            Vec2Int_t mapchipElemPartner_{};
            // 相手の"看板"の配列要素数（stageに帰属） - 不変
            size_t IdxSign_{};
            // 相手側の出現位置 - 不変
            Direction dirPartner_{};
        };

        struct Info_t
        {
            Vector3* topLeftPosPtr_{};
            // 計算量抑制オフセット
            Vector2 offset_{};
            Transform transform_{};
            BlockDrawer bd_{};

        public:
            Info_t(Vector3* basePosPtr, const Vector2& offset) : topLeftPosPtr_(basePosPtr), offset_(offset)
            {
                Transform::Status status{ *basePosPtr + Vector3{offset.x_,offset.y_,0},{0,0,0},{1,1,1} };
                transform_.Initialize(status);
            }

            void Initialize(int bt) {
                bd_.Initialize(&transform_, static_cast<IMode::Type>(bt));
            }

            void Update(void) {
                transform_.pos_ = *topLeftPosPtr_ + Vector3{ offset_.x_,offset_.y_,0 };
                transform_.UpdateMatrix();
                bd_.Update();
            }

            void Draw(void) {
                bd_.Draw();
            }
        };

    public:
        // 関数
        Sign(void) = default;

        void Initialize(const Vector2& mapchipSize);
        void Update(void);
        void Draw(void);

        // パーフェクトピクセルコリジョン
        void PPC(YukiMapchipCollider* ptr);
        const Vector2& CalcVelStuck(const Vector2& pointPos); // 移動入力なしの押し出し値計算関数 ※Moveの前に使う =>今使ってない
        const Vector2& CalcVelMove(const Vector2& pointPos, const Vector2& vel); // 移動入力ありの押し出し値計算関数 ※Stuckの後に使う

        // 変数
        //std::vector<std::vector<std::unique_ptr<IBlock>>> mapchip2_{};
        std::vector<std::vector<int>> mapchip_{};
        std::list<std::unique_ptr<Info_t>> BDrawerList_{};
        std::map<WarpIdx_t, Vec2Int_t> warpInfos_{};

        // 基点（左上）座標
        Vector3 topLeftPos_{}; // zは常に0
    };
}


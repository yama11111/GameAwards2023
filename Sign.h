#pragma once
#include <map>
#include "Keys.h"
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

        static constexpr float blockRadius_{ 1.f }; // ブロックの半径

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

        // 方向のenum
        enum class Direction
        {
            TOP,
            RIGHT,
            LEFT,
            BOTTOM,
        };

        // ワープブロックの情報体
        struct WarpIdx_t
        {
        public:
            WarpIdx_t(Direction dirSelf,const std::pair<size_t,size_t>& mces) : dirSelf_(dirSelf),mapchipElemSelf_(mces) {}

            // 自分が接続済みか - 可変
            bool isConnected_{};
            // 自分の"ブロック"の配列要素数（看板に帰属） - 不変
            std::pair<size_t, size_t> mapchipElemSelf_{};
            // 自分側の出現方向 - 不変
            Direction dirSelf_{};

            // 相手の"ブロック"の配列要素数（看板に帰属） - 不変
            std::pair<size_t,size_t> mapchipElemPartner_{};
            // 相手の"看板"の配列要素数（stageに帰属） - 不変
            size_t IdxSign_{};
            // 相手側の出現方向 - 不変
            Direction dirPartner_{};
        };

        // ブロック全般用情報
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

            void Initialize(int bt) { // int 0 = 空気判定だが、enum とずれるので対応　差分　-1
                bd_.Initialize(&transform_, static_cast<BlockDrawerCommon::Type>(bt - 1));
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

        void DrawDebug(void);

        // パーフェクトピクセルコリジョン
        void PPC(YukiMapchipCollider* ptr);
        // 空気ブロックを他ブロックに置換できる。それ以外は例外スロー
        void ReWriteBlock(size_t X,size_t Y,BlockType bt);
        void ReWriteBlock2Warp(size_t X,size_t Y,BlockType bt, Direction dirSelf);

        inline Vector3 GetCenterPos(void);
    private:
        // (現在地 + vel) - 基準点 で距離算出 ※プレイヤーは看板の基準点より必ず右にいる想定
        // 距離 / ブロックの直径 でマップチップ配列の要素数では何番目に相当する位置か算出 ->CalcElem()で処理
        inline int CalcElemX(float pointX) { return static_cast<int>((pointX - topLeftPos_.x_) / (blockRadius_ * 2)); }
        inline int CalcElemY(float pointY) { return static_cast<int>((pointY - topLeftPos_.y_) / (blockRadius_ * 2) * -1); }
        inline int CalcMovedElemX(float pointX, float velX) { return static_cast<int>(std::fabs(pointX + velX - topLeftPos_.x_) / (blockRadius_ * 2)); }
        inline int CalcMovedElemY(float pointY, float velY) { return static_cast<int>(std::fabs(pointY + velY - topLeftPos_.y_) / (blockRadius_ * 2)); }
        float roundToDecimal(float value, int decimalPlaces); // 丸め誤差を修正する関数
        bool SlowlyFillingSpaceX(YukiMapchipCollider* ptr, float& pointX, const Vector2& approach, int mElemX, int elemY);
        bool SlowlyFillingSpaceY(YukiMapchipCollider* ptr, float& pointY, const Vector2& approach, int elemX, int mElemY/*, bool gravity*/);
    public:
        // 変数
        //std::vector<std::vector<std::unique_ptr<IBlock>>> mapchip2_{};
        std::vector<std::vector<int>> mapchip_{};
        std::list<std::unique_ptr<Info_t>> BDrawerList_{};
        std::vector<WarpIdx_t> warpInfos_{};

        // 基点（左上）座標
        Vector3 topLeftPos_{}; // zは常に0

        YInput::Keys* keys_{ YInput::Keys::GetInstance() };
    };
}


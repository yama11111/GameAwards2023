#pragma once
#include "IBlock.h"
#include <list>
#include <vector>
#include <memory>
#include "Keys.h"

class Piece
{
public:
    // 定義
    enum class Dir
    {
        TOP,
        RIGHT,
        LEFT,
        BOTTOM,
    };

    enum class State
    {
        ROOT, // 初期状態で固定
        IMMUTABLE, // tab相互接続後プレイヤーの通過により変更不可状態
        MOVABLE, // 変更可能状態
    };

    // for文の肥大化抑制のため、PieceEntranceBlockの情報を持つ構造体（≒ヘルパー）
    struct Tab_t
    {
        // 凹凸どちらなのか
        bool isTab_{ true }; // デフォルトは凸

        // PieceEntranceBlockの中心点
        YMath::Vector2 pos_{};
        
        // 該当PieceEntranceBlockはPieceから見てどの面に存在しているのか
        Dir dir_{};

        // 該当PieceEntranceBlockはBlockVectorの何番目なのか
        size_t indexBlockVector_{};

        // 該当PieceEntranceBlockは接続してるかどうか
        bool isConnected_{ false };

        // 該当PieceEntranceBlockは接続する側なのかされる側なのか
        bool isConnectExecuter_{ false };

        // ピースを再操作時、接続されていたら自分以外に相手もconnectedをfalseにしないといけないので情報保存
        size_t indexOtherPiece_{};
        size_t indexOthertab_{};
    };

    // 関数
    Piece(const YMath::Vector2& pos, const YMath::Vector2& radiusBlockCount);

    void Update(void);
    void Draw(void);

    void DrawDebug(void);

    // 新規生成するときの初期値はどうでもいい。offsetとradiusは正確な値が必要
    void RegisterBlock(IBlock* ptr,const YMath::Vector2& offset, const YMath::Vector2& radius);
    void RegisterTab(bool isTab, int indexBlockVector); // PieceEntranceBlockの追加関数

    // 諸事情により特別に公開。使うな。
    void UpdateTabs(void); // 全ブロック移動時tabs_情報更新関数
    void UpdateTabsPos(void); // 上記関数のposのみ版。最適化はもう間に合わないからあと回し
private:
    void MovePiecePos(void);

    void ChangeTabsDir(int changeValue); // tabs_回転時情報更新用関数
    void RotateBlocks(int rotateValue); // 全ブロック回転時更新関数

    void WriteBlockPos(void);

    // 変数
    std::vector<std::unique_ptr<IBlock>> blockVector_;

    // 中心点
    YMath::Vector2 pos_;
    // 中心点を1ブロックとして、何ブロック分伸ばすか
    YMath::Vector2 radiusBlockCount_;

    int rotate_;

    std::vector<Tab_t> tabs_;

    // 動かせるかどうか
    State state_{ State::MOVABLE };
    // はめたかどうか = 固定
    bool isFixity_{ false };

    // 操作しているか
    bool isOperator_{};

    YInput::Keys* keysPtr_{};

public:
    // setter・getter
    inline void SetPos(const YMath::Vector2& pos) { pos_ = pos; }
    inline void SetRadius(const YMath::Vector2& radius) { radiusBlockCount_ = radius; }
    inline void SetRotate(int rotate) { rotate = rotate; }
    inline void SetOperator(bool isOperator) { isOperator_ = isOperator; }
    inline void SetState(State state) { state_ = state; }
    inline void SetFixity(bool fixity) { isFixity_ = fixity; }

    inline const YMath::Vector2& GetPos(void) { return pos_; }
    inline const YMath::Vector2& GetRadius(void) { return radiusBlockCount_; }
    inline int GetRotate(void) { return rotate_; }
    inline const std::vector<std::unique_ptr<IBlock>>* GetBlocksPtr(void) { return &blockVector_; }
    inline const std::vector<Tab_t>& GetTabs(void) { return tabs_; }
    inline std::vector<Tab_t>& GetTabsRef(void) { return tabs_; }
    inline bool GetOperator(void) { return isOperator_; }
    inline State GetState(void) { return state_; }
    inline bool GetFixity(void) { return isFixity_; }
};


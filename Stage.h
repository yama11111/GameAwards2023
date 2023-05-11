#pragma once
#include "Piece.h"
#include "Keys.h"

class Stage
{
public:
    // 定義
    static constexpr float detectRadius_{ 32.f };

    // 関数
    Stage(void) : keysPtr_(YInput::Keys::GetInstance()) {}

    void Update(void);
    void Draw(void);

    void AddPiece(Piece* ptr);
private:
    // 選択したPieceを操作
    void OperatePiece(int index);
    // 操作しているPieceをはめ込む（座標を確定し、操作権を放棄する）
    void ConfirmOperatorPiecePos(const YMath::Vector2& pos);

    void MiningOperatorPieceTabs(void); // isOperatorがtrueになってるPieceを探しtabをコピーする関数 ※該当Pieceは単一である前提
    void ExplorateNearTabs(YMath::Vector2& recordPos); // 該当Pieceに付属するtabの座標から一定範囲内にある他pieceのtab座標を検索し、条件が合致する場合に該当Pieceの中心座標を、付属tabと他tabが重なる位置に自動調整する関数
    void SelectPieceForOperatorDebug(void);

    void InternalUpdatePieces(int index); // for文を減らすためMiningOperatorPieceTabs内で実行するUpdate関数

    // 変数
    std::vector<std::unique_ptr<Piece>> pieceVector_;
    size_t indexOperatorPiece_{};
    size_t indexNoOperatorPiece_{};
    size_t indexInPieceMineTab_{};
    size_t indexInPieceOtherTab_{};

    std::vector<Piece::Tab_t> operatorTabs_;

    bool permissionTabsAccess_{ false };
    bool isPossibleInPiece_{ false };

    bool isReset_{ false };

    YInput::Keys* keysPtr_{};
public:
    //setter・getter
    std::vector<std::unique_ptr<Piece>>* GetPieceVectorPtr(void) { return &pieceVector_; }
};


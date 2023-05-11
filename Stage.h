#pragma once
#include "Piece.h"
#include "Keys.h"

class Stage
{
public:
    // ��`
    static constexpr float detectRadius_{ 32.f };

    // �֐�
    Stage(void) : keysPtr_(YInput::Keys::GetInstance()) {}

    void Update(void);
    void Draw(void);

    void AddPiece(Piece* ptr);
private:
    // �I������Piece�𑀍�
    void OperatePiece(int index);
    // ���삵�Ă���Piece���͂ߍ��ށi���W���m�肵�A���쌠���������j
    void ConfirmOperatorPiecePos(const YMath::Vector2& pos);

    void MiningOperatorPieceTabs(void); // isOperator��true�ɂȂ��Ă�Piece��T��tab���R�s�[����֐� ���Y��Piece�͒P��ł���O��
    void ExplorateNearTabs(YMath::Vector2& recordPos); // �Y��Piece�ɕt������tab�̍��W������͈͓��ɂ��鑼piece��tab���W���������A���������v����ꍇ�ɊY��Piece�̒��S���W���A�t��tab�Ƒ�tab���d�Ȃ�ʒu�Ɏ�����������֐�
    void SelectPieceForOperatorDebug(void);

    void InternalUpdatePieces(int index); // for�������炷����MiningOperatorPieceTabs���Ŏ��s����Update�֐�

    // �ϐ�
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
    //setter�Egetter
    std::vector<std::unique_ptr<Piece>>* GetPieceVectorPtr(void) { return &pieceVector_; }
};


#pragma once
#include "IBlock.h"
#include <list>
#include <vector>
#include <memory>
#include "Keys.h"

class Piece
{
public:
    // ��`
    enum class Dir
    {
        TOP,
        RIGHT,
        LEFT,
        BOTTOM,
    };

    enum class State
    {
        ROOT, // ������ԂŌŒ�
        IMMUTABLE, // tab���ݐڑ���v���C���[�̒ʉ߂ɂ��ύX�s���
        MOVABLE, // �ύX�\���
    };

    // for���̔�剻�}���̂��߁APieceEntranceBlock�̏������\���́i���w���p�[�j
    struct Tab_t
    {
        // ���ʂǂ���Ȃ̂�
        bool isTab_{ true }; // �f�t�H���g�͓�

        // PieceEntranceBlock�̒��S�_
        YMath::Vector2 pos_{};
        
        // �Y��PieceEntranceBlock��Piece���猩�Ăǂ̖ʂɑ��݂��Ă���̂�
        Dir dir_{};

        // �Y��PieceEntranceBlock��BlockVector�̉��ԖڂȂ̂�
        size_t indexBlockVector_{};

        // �Y��PieceEntranceBlock�͐ڑ����Ă邩�ǂ���
        bool isConnected_{ false };

        // �Y��PieceEntranceBlock�͐ڑ����鑤�Ȃ̂�����鑤�Ȃ̂�
        bool isConnectExecuter_{ false };

        // �s�[�X���đ��쎞�A�ڑ�����Ă����玩���ȊO�ɑ����connected��false�ɂ��Ȃ��Ƃ����Ȃ��̂ŏ��ۑ�
        size_t indexOtherPiece_{};
        size_t indexOthertab_{};
    };

    // �֐�
    Piece(const YMath::Vector2& pos, const YMath::Vector2& radiusBlockCount);

    void Update(void);
    void Draw(void);

    void DrawDebug(void);

    // �V�K��������Ƃ��̏����l�͂ǂ��ł������Boffset��radius�͐��m�Ȓl���K�v
    void RegisterBlock(IBlock* ptr,const YMath::Vector2& offset, const YMath::Vector2& radius);
    void RegisterTab(bool isTab, int indexBlockVector); // PieceEntranceBlock�̒ǉ��֐�

    // ������ɂ����ʂɌ��J�B�g���ȁB
    void UpdateTabs(void); // �S�u���b�N�ړ���tabs_���X�V�֐�
    void UpdateTabsPos(void); // ��L�֐���pos�̂ݔŁB�œK���͂����Ԃɍ���Ȃ����炠�Ɖ�
private:
    void MovePiecePos(void);

    void ChangeTabsDir(int changeValue); // tabs_��]�����X�V�p�֐�
    void RotateBlocks(int rotateValue); // �S�u���b�N��]���X�V�֐�

    void WriteBlockPos(void);

    // �ϐ�
    std::vector<std::unique_ptr<IBlock>> blockVector_;

    // ���S�_
    YMath::Vector2 pos_;
    // ���S�_��1�u���b�N�Ƃ��āA���u���b�N���L�΂���
    YMath::Vector2 radiusBlockCount_;

    int rotate_;

    std::vector<Tab_t> tabs_;

    // �������邩�ǂ���
    State state_{ State::MOVABLE };
    // �͂߂����ǂ��� = �Œ�
    bool isFixity_{ false };

    // ���삵�Ă��邩
    bool isOperator_{};

    YInput::Keys* keysPtr_{};

public:
    // setter�Egetter
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


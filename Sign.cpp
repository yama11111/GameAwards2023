#include "Sign.h"
#include <algorithm>
#include <cmath>

using namespace maruyama;

void Sign::Initialize(const Vector2& mapchipSize)
{
    //for (int y{}; y < (int)mapchipSize.y_; y++) {
//    mapchip2_.emplace_back(std::vector<std::unique_ptr<IBlock>>{});
//    for (int x{}; x < (int)mapchipSize.y_; x++) {
//        mapchip2_.emplace_back(new IBlock{});
//    }
//}

    for (int y{}; y < (int)mapchipSize.y_; y++) {
        // �Ƃ�܋�`�ɂ���
        mapchip_.emplace_back(std::vector<int>{});
        for (int x{}; x < (int)mapchipSize.x_; x++) {
            if (y == 0 || y == (int)(mapchipSize.y_ - 1)) {
                mapchip_[y].emplace_back(1);
                BDrawerList_.emplace_back(new Info_t{ &topLeftPos_,Vector2{ x * blockRadius_ * 2 + blockRadius_, -y * blockRadius_ * 2 - blockRadius_ } });
                BDrawerList_.back()->Initialize(1);
            }
            else if (x == 0 || x == (int)(mapchipSize.x_ - 1)) {
                mapchip_[y].emplace_back(1);
                BDrawerList_.emplace_back(new Info_t{ &topLeftPos_,Vector2{ x * blockRadius_ * 2 + blockRadius_, -y * blockRadius_ * 2 - blockRadius_ } });
                BDrawerList_.back()->Initialize(1);
            }
            else {
                mapchip_[y].emplace_back(0);
            }
        }
    }
}

void Sign::Update(void)
{
    for (auto& bd : BDrawerList_) {
        bd->Update();
    }
}

void Sign::Draw(void)
{
    for (auto& bd : BDrawerList_) {
        bd->Draw();
    }
}

void Sign::PPC(YukiMapchipCollider* ptr)
{
    bool isStuck{ false };
    // �l��ÓI�ێ� [�΂ˊ֘A]
    static bool isSpring{};
    static float springValue{};

    Vector2 TL{}, TR{}, BL{}, BR{};
    Vector2 vec2Vel{ ptr->velocity_.x_,ptr->velocity_.y_ };

    // point�̍��W���}�b�v�`�b�v�P�ʂɕϊ�
    size_t elemX{}, elemY{};
    //<<<<<<<<<<<<<<<<<<<<<< ���� >>>>>>>>>>>>>>>>>>>>>>>>>>//
    elemX = (int)(ptr->point_.TopLeft_.x_ / blockRadius_ * 2);
    elemY = (int)(ptr->point_.TopLeft_.y_ / blockRadius_ * 2);
    if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::BASIC) // �ʏ�u���b�N
    {
        isStuck = true;
    }

    //<<<<<<<<<<<<<<<<<<<<<< �E�� >>>>>>>>>>>>>>>>>>>>>>>>>>//
    elemX = (int)(ptr->point_.TopRight_.x_ / blockRadius_ * 2);
    elemY = (int)(ptr->point_.TopRight_.y_ / blockRadius_ * 2);
    if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::BASIC) // �ʏ�u���b�N
    {
        isStuck = true;
    }

    //<<<<<<<<<<<<<<<<<<<<<< ���� >>>>>>>>>>>>>>>>>>>>>>>>>>//
    elemX = (int)(ptr->point_.BottomLeft_.x_ / blockRadius_ * 2);
    elemY = (int)(ptr->point_.BottomLeft_.y_ / blockRadius_ * 2);
    if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::BASIC) // �ʏ�u���b�N
    {
        isStuck = true;
    }
    else if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::SPRING) // �΂˃u���b�N
    {
        isSpring = true;
        springValue = springPower_; // �l��ݒ肳�ꂽ�l�ɕύX
    }

    //<<<<<<<<<<<<<<<<<<<<<< �E�� >>>>>>>>>>>>>>>>>>>>>>>>>>//
    elemX = (int)(ptr->point_.BottomRight_.x_ / blockRadius_ * 2);
    elemY = (int)(ptr->point_.BottomRight_.y_ / blockRadius_ * 2);
    if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::BASIC) // �ʏ�u���b�N
    {
        isStuck = true;
    }
    else if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::SPRING) // �΂˃u���b�N
    {
        isSpring = true;
        springValue = springPower_; // �l��ݒ肳�ꂽ�l�ɕύX
    }

    //// CalcVelStuck�p
    //{
    //    Vector2 TL{}, TR{}, BL{}, BR{};

    //    // ���ݒn�i�߂荞��ł�ꍇ�j�̈ړ��l���Z�o
    //    Vector2 vec2Vel{ ptr->velocity_.x_,ptr->velocity_.y_ };
    //    TL = CalcVelStuck(ptr->point_.TopLeft_); // ����
    //    TR = CalcVelStuck(ptr->point_.TopRight_); // �E��
    //    BL = CalcVelStuck(ptr->point_.BottomLeft_); // ����
    //    BR = CalcVelStuck(ptr->point_.BottomRight_); // �E��
    //}

    // ��ʓI�ȃu���b�N
    if (isStuck) {
        TL = CalcVelMove(ptr->point_.TopLeft_, vec2Vel); // ����
        TR = CalcVelMove(ptr->point_.TopRight_, vec2Vel); // �E��
        BL = CalcVelMove(ptr->point_.BottomLeft_, vec2Vel); // ����
        BR = CalcVelMove(ptr->point_.BottomRight_, vec2Vel); // �E��

        // �Z�o���ꂽ�l�̒��ōŏ��l���ړ��ʂƂ��ēK�p
        ptr->velocity_.x_ = (std::min)({ TL.x_,TR.x_,BL.x_,BR.x_ });
        ptr->velocity_.y_ = (std::min)({ TL.y_,TR.y_,BL.y_,BR.y_ });
        //// �Z�o���ꂽ�l�̒��ōő�l���ړ��ʂƂ��ēK�p
        //ptr->velocity_.x_ = (std::max)({ TL.x_,TR.x_,BL.x_,BR.x_ });
        //ptr->velocity_.y_ = (std::max)({ TL.y_,TR.y_,BL.y_,BR.y_ });
    }
    // �΂�
    if (isSpring && ptr->entityType_ == YukiMapchipCollider::EntityType::PLAYER) { // �t���O��true && �Ώۂ�Player�ł��邱��
        // �ǂ񂾂����˂邩
        springValue -= springFall_; // �����͂͏��X�Ɍ�������

        // �����͂�����0�ɂȂ��Ă���ꍇ�̓t���OOFF
        if (springValue < 0.f) isSpring = false;
        // �����͂͌�����0�����ɂ͂Ȃ�Ȃ�
        springValue = (std::max)(springValue, 0.f);

        // �ړ��ʂƂ��đ��
        ptr->velocity_.y_ += springValue;
    }

    // <summary>
    //## ���̍\���̏ꍇ�A�R���C�_�[���p�������q�N���X������Update()�֐��́A
    //## �K�����L�̂悤�ɍŏ��̍s�ȊO�ł̍��W�X�V���s���Ă͂Ȃ�Ȃ��B
    //## �ŏ��̍s: UpdatePos();
    //## ����ȍ~: velocity�v�Z;
    // </summary>
    ptr->UpdatePos();
}

const Sign::Vector2& Sign::CalcVelStuck(const Vector2& pointPos)
{
    // velocity ���Ax|y �ǂ����0�O�� //

    size_t elemX{}, elemY{}; // point�̍��W���}�b�v�`�b�v�P�ʂɕϊ�
    elemX = (int)(pointPos.x_ / blockRadius_ * 2);
    elemY = (int)(pointPos.y_ / blockRadius_ * 2);

    Vector2 result{};
    if (mapchip_[elemY][elemX] != 0) // [����]�@�u���b�N������ꍇ
    {
        // �E�����ɉ����o��
        //result.x_ += pushOut_;
        //result.y_ += 
    }

    return result;
}

const Sign::Vector2& Sign::CalcVelMove(const Vector2& pointPos, const Vector2& vel)
{
    // velocity < blockRadius ���O�� //
    // [�ړ���]�@�u���b�N������ꍇ ���O�� //

    size_t elemX{}, elemY{}; // point�̍��W(point + vel)���}�b�v�`�b�v�P�ʂɕϊ�
    elemX = (int)(pointPos.x_ + vel.x_ / blockRadius_ * 2);
    elemY = (int)(pointPos.y_ + vel.y_ / blockRadius_ * 2);

    Vector2 result{};

    Vector2 lenUntilBlock{};
    lenUntilBlock.x_ = std::fabs(pointPos.x_ - topLeftPos_.x_ + elemX * blockRadius_ * 2); // ���ォ��E�����ɃJ�E���g����̂� topLeft + offsetX
    lenUntilBlock.y_ = std::fabs(pointPos.y_ - topLeftPos_.y_ - elemY * blockRadius_ * 2); // ���ォ�牺�����ɃJ�E���g����̂� topLeft - offsetY

    vel.x_ > 0 ?
        result.x_ = lenUntilBlock.x_ :
        result.x_ = -lenUntilBlock.x_;
    vel.y_ > 0 ?
        result.y_ = lenUntilBlock.y_ :
        result.y_ = -lenUntilBlock.y_;

    // �߂荞��ł��Ă��ړ����͂����Ȃ��ꍇ�����o���Ȃ� ���o�O�����ɘa
    if (vel.x_ == 0.f) result.x_ = 0.f;
    if (vel.y_ == 0.f) result.y_ = 0.f;

    return result;
}

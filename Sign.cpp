#include "Sign.h"
#include <algorithm>
#include <cmath>

Sign::Sign(const Vector2& mapchipSize)
{
    //for (int y{}; y < (int)mapchipSize.y_; y++) {
    //    mapchip2_.emplace_back(std::vector<std::unique_ptr<IBlock>>{});
    //    for (int x{}; x < (int)mapchipSize.y_; x++) {
    //        mapchip2_.emplace_back(new IBlock{});
    //    }
    //}

    for (int y{}; y < (int)mapchipSize.y_; y++) {
        mapchip_.emplace_back(std::vector<int>{});
        for (int x{}; x < (int)mapchipSize.y_; x++) {
            mapchip_.emplace_back(int{ 0 });
        }
    }
}

void Sign::Update(void)
{
}

void Sign::Draw(void)
{
    for (size_t y{}; y < (int)mapchip_.size(); y++) {
        for (size_t x{}; x < (int)mapchip_[0].size(); x++) {
            switch (static_cast<BlockType>(mapchip_[y][x]))
            {
            case BlockType::NONE:
                break;
            case BlockType::BASIC:
                break;

            default:
                break;
            }
        }
    }
}

void Sign::PPC(YukiMapchipCollider* ptr)
{
    Vector2 TL{}, TR{}, BL{}, BR{};
    Vector2 vec2Vel{ ptr->velocity_.x_,ptr->velocity_.y_ };

    size_t elemX{}, elemY{}; // point�̍��W���}�b�v�`�b�v�P�ʂɕϊ�
    // ����
    elemX = (int)(ptr->point_.TopLeft_.x_ / blockRadius_ * 2);
    elemY = (int)(ptr->point_.TopLeft_.y_ / blockRadius_ * 2);
    if (mapchip_[elemY][elemX] != 0) TL = CalcVelMove(ptr->point_.TopLeft_, vec2Vel); // ����
    // �E��
    elemX = (int)(ptr->point_.TopRight_.x_ / blockRadius_ * 2);
    elemY = (int)(ptr->point_.TopRight_.y_ / blockRadius_ * 2);
    if (mapchip_[elemY][elemX] != 0) TR = CalcVelMove(ptr->point_.TopRight_, vec2Vel); // �E��
    // ����
    elemX = (int)(ptr->point_.BottomLeft_.x_ / blockRadius_ * 2);
    elemY = (int)(ptr->point_.BottomLeft_.y_ / blockRadius_ * 2);
    if (mapchip_[elemY][elemX] != 0) BL = CalcVelMove(ptr->point_.BottomLeft_, vec2Vel); // ����
    // �E��
    elemX = (int)(ptr->point_.BottomRight_.x_ / blockRadius_ * 2);
    elemY = (int)(ptr->point_.BottomRight_.y_ / blockRadius_ * 2);
    if (mapchip_[elemY][elemX] != 0) BR = CalcVelMove(ptr->point_.BottomRight_, vec2Vel); // �E��

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

    //// �Z�o���ꂽ�l�̒��ōŏ��l���ړ��ʂƂ��ēK�p
    //ptr->velocity_.x_ = (std::min)({ TL.x_,TR.x_,BL.x_,BR.x_ });
    //ptr->velocity_.y_ = (std::min)({ TL.y_,TR.y_,BL.y_,BR.y_ });

    // �Z�o���ꂽ�l�̒��ōő�l���ړ��ʂƂ��ēK�p
    ptr->velocity_.x_ = (std::max)({ TL.x_,TR.x_,BL.x_,BR.x_ });
    ptr->velocity_.y_ = (std::max)({ TL.y_,TR.y_,BL.y_,BR.y_ });

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

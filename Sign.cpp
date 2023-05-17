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

    size_t elemX{}, elemY{}; // pointの座標をマップチップ単位に変換
    // 左上
    elemX = (int)(ptr->point_.TopLeft_.x_ / blockRadius_ * 2);
    elemY = (int)(ptr->point_.TopLeft_.y_ / blockRadius_ * 2);
    if (mapchip_[elemY][elemX] != 0) TL = CalcVelMove(ptr->point_.TopLeft_, vec2Vel); // 左上
    // 右上
    elemX = (int)(ptr->point_.TopRight_.x_ / blockRadius_ * 2);
    elemY = (int)(ptr->point_.TopRight_.y_ / blockRadius_ * 2);
    if (mapchip_[elemY][elemX] != 0) TR = CalcVelMove(ptr->point_.TopRight_, vec2Vel); // 右上
    // 左下
    elemX = (int)(ptr->point_.BottomLeft_.x_ / blockRadius_ * 2);
    elemY = (int)(ptr->point_.BottomLeft_.y_ / blockRadius_ * 2);
    if (mapchip_[elemY][elemX] != 0) BL = CalcVelMove(ptr->point_.BottomLeft_, vec2Vel); // 左下
    // 右下
    elemX = (int)(ptr->point_.BottomRight_.x_ / blockRadius_ * 2);
    elemY = (int)(ptr->point_.BottomRight_.y_ / blockRadius_ * 2);
    if (mapchip_[elemY][elemX] != 0) BR = CalcVelMove(ptr->point_.BottomRight_, vec2Vel); // 右下

    //// CalcVelStuck用
    //{
    //    Vector2 TL{}, TR{}, BL{}, BR{};

    //    // 現在地（めり込んでる場合）の移動値を算出
    //    Vector2 vec2Vel{ ptr->velocity_.x_,ptr->velocity_.y_ };
    //    TL = CalcVelStuck(ptr->point_.TopLeft_); // 左上
    //    TR = CalcVelStuck(ptr->point_.TopRight_); // 右上
    //    BL = CalcVelStuck(ptr->point_.BottomLeft_); // 左下
    //    BR = CalcVelStuck(ptr->point_.BottomRight_); // 右下
    //}

    //// 算出された値の中で最小値を移動量として適用
    //ptr->velocity_.x_ = (std::min)({ TL.x_,TR.x_,BL.x_,BR.x_ });
    //ptr->velocity_.y_ = (std::min)({ TL.y_,TR.y_,BL.y_,BR.y_ });

    // 算出された値の中で最大値を移動量として適用
    ptr->velocity_.x_ = (std::max)({ TL.x_,TR.x_,BL.x_,BR.x_ });
    ptr->velocity_.y_ = (std::max)({ TL.y_,TR.y_,BL.y_,BR.y_ });

    // <summary>
    //## この構造の場合、コライダーを継承した子クラスたちのUpdate()関数は、
    //## 必ず下記のように最初の行以外での座標更新を行ってはならない。
    //## 最初の行: UpdatePos();
    //## それ以降: velocity計算;
    // </summary>
    ptr->UpdatePos();
}

const Sign::Vector2& Sign::CalcVelStuck(const Vector2& pointPos)
{
    // velocity が、x|y どちらも0前提 //

    size_t elemX{}, elemY{}; // pointの座標をマップチップ単位に変換
    elemX = (int)(pointPos.x_ / blockRadius_ * 2);
    elemY = (int)(pointPos.y_ / blockRadius_ * 2);

    Vector2 result{};
    if (mapchip_[elemY][elemX] != 0) // [現在]　ブロックがある場合
    {
        // 右方向に押し出し
        //result.x_ += pushOut_;
        //result.y_ += 
    }

    return result;
}

const Sign::Vector2& Sign::CalcVelMove(const Vector2& pointPos, const Vector2& vel)
{
    // velocity < blockRadius が前提 //
    // [移動後]　ブロックがある場合 が前提 //

    size_t elemX{}, elemY{}; // pointの座標(point + vel)をマップチップ単位に変換
    elemX = (int)(pointPos.x_ + vel.x_ / blockRadius_ * 2);
    elemY = (int)(pointPos.y_ + vel.y_ / blockRadius_ * 2);

    Vector2 result{};

    Vector2 lenUntilBlock{};
    lenUntilBlock.x_ = std::fabs(pointPos.x_ - topLeftPos_.x_ + elemX * blockRadius_ * 2); // 左上から右方向にカウントするので topLeft + offsetX
    lenUntilBlock.y_ = std::fabs(pointPos.y_ - topLeftPos_.y_ - elemY * blockRadius_ * 2); // 左上から下方向にカウントするので topLeft - offsetY

    vel.x_ > 0 ?
        result.x_ = lenUntilBlock.x_ :
        result.x_ = -lenUntilBlock.x_;
    vel.y_ > 0 ?
        result.y_ = lenUntilBlock.y_ :
        result.y_ = -lenUntilBlock.y_;

    // めり込んでいても移動入力をしない場合押し出さない ※バグ挙動緩和
    if (vel.x_ == 0.f) result.x_ = 0.f;
    if (vel.y_ == 0.f) result.y_ = 0.f;

    return result;
}

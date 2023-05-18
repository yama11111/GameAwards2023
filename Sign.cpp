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
        // とりま矩形にする
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
    // 値を静的保持 [ばね関連]
    static bool isSpring{};
    static float springValue{};

    Vector2 TL{}, TR{}, BL{}, BR{};
    Vector2 vec2Vel{ ptr->velocity_.x_,ptr->velocity_.y_ };

    // pointの座標をマップチップ単位に変換
    size_t elemX{}, elemY{};
    //<<<<<<<<<<<<<<<<<<<<<< 左上 >>>>>>>>>>>>>>>>>>>>>>>>>>//
    elemX = (int)(ptr->point_.TopLeft_.x_ / blockRadius_ * 2);
    elemY = (int)(ptr->point_.TopLeft_.y_ / blockRadius_ * 2);
    if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::BASIC) // 通常ブロック
    {
        isStuck = true;
    }

    //<<<<<<<<<<<<<<<<<<<<<< 右上 >>>>>>>>>>>>>>>>>>>>>>>>>>//
    elemX = (int)(ptr->point_.TopRight_.x_ / blockRadius_ * 2);
    elemY = (int)(ptr->point_.TopRight_.y_ / blockRadius_ * 2);
    if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::BASIC) // 通常ブロック
    {
        isStuck = true;
    }

    //<<<<<<<<<<<<<<<<<<<<<< 左下 >>>>>>>>>>>>>>>>>>>>>>>>>>//
    elemX = (int)(ptr->point_.BottomLeft_.x_ / blockRadius_ * 2);
    elemY = (int)(ptr->point_.BottomLeft_.y_ / blockRadius_ * 2);
    if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::BASIC) // 通常ブロック
    {
        isStuck = true;
    }
    else if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::SPRING) // ばねブロック
    {
        isSpring = true;
        springValue = springPower_; // 値を設定された値に変更
    }

    //<<<<<<<<<<<<<<<<<<<<<< 右下 >>>>>>>>>>>>>>>>>>>>>>>>>>//
    elemX = (int)(ptr->point_.BottomRight_.x_ / blockRadius_ * 2);
    elemY = (int)(ptr->point_.BottomRight_.y_ / blockRadius_ * 2);
    if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::BASIC) // 通常ブロック
    {
        isStuck = true;
    }
    else if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::SPRING) // ばねブロック
    {
        isSpring = true;
        springValue = springPower_; // 値を設定された値に変更
    }

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

    // 一般的なブロック
    if (isStuck) {
        TL = CalcVelMove(ptr->point_.TopLeft_, vec2Vel); // 左上
        TR = CalcVelMove(ptr->point_.TopRight_, vec2Vel); // 右上
        BL = CalcVelMove(ptr->point_.BottomLeft_, vec2Vel); // 左下
        BR = CalcVelMove(ptr->point_.BottomRight_, vec2Vel); // 右下

        // 算出された値の中で最小値を移動量として適用
        ptr->velocity_.x_ = (std::min)({ TL.x_,TR.x_,BL.x_,BR.x_ });
        ptr->velocity_.y_ = (std::min)({ TL.y_,TR.y_,BL.y_,BR.y_ });
        //// 算出された値の中で最大値を移動量として適用
        //ptr->velocity_.x_ = (std::max)({ TL.x_,TR.x_,BL.x_,BR.x_ });
        //ptr->velocity_.y_ = (std::max)({ TL.y_,TR.y_,BL.y_,BR.y_ });
    }
    // ばね
    if (isSpring && ptr->entityType_ == YukiMapchipCollider::EntityType::PLAYER) { // フラグがtrue && 対象がPlayerであること
        // どんだけ跳ねるか
        springValue -= springFall_; // 跳躍力は徐々に減衰する

        // 跳躍力が既に0になっている場合はフラグOFF
        if (springValue < 0.f) isSpring = false;
        // 跳躍力は決して0未満にはならない
        springValue = (std::max)(springValue, 0.f);

        // 移動量として代入
        ptr->velocity_.y_ += springValue;
    }

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

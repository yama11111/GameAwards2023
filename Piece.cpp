#include "Piece.h"
#include <cmath>
#include "PieceBasicBlock.h"
#include "PieceEntranceBlock.h"
#include "MathUtillity.h"
#include <imgui.h>

Piece::Piece(const YMath::Vector2& pos, const YMath::Vector2& radiusBlockCount) :
    pos_(pos), radiusBlockCount_(radiusBlockCount), rotate_(0), keysPtr_(YInput::Keys::GetInstance())
{
    float offset{ IBlock::radiusBase_ };

    // 上辺
    // 0 ~ radiusBlockCount * 2 まで
    for (size_t t = 0; t < radiusBlockCount.x_ * 2 + 1; t++)
    {
        blockVector_.emplace_back(new PieceBasicBlock{ 
            YMath::Vector2{(pos.x_ - radiusBlockCount.x_ * IBlock::radiusBase_ * 2) + t * IBlock::radiusBase_ * 2, pos.y_ + radiusBlockCount.y_ * IBlock::radiusBase_ * 2 + offset}, 
            YMath::Vector2{ -radiusBlockCount.x_ * IBlock::radiusBase_ * 2 + t * IBlock::radiusBase_ * 2, +radiusBlockCount.y_ * IBlock::radiusBase_ * 2 + offset}, 
            YMath::Vector2{IBlock::radiusBase_,1} });
    }
    // 底辺
    // radiusBlockCount * 2 + 1 ~ radiusBlockCount * 4 まで
    for (size_t b = 0; b < radiusBlockCount.x_ * 2 + 1; b++)
    {
        blockVector_.emplace_back(new PieceBasicBlock{ 
            YMath::Vector2{(pos.x_ - radiusBlockCount.x_ * IBlock::radiusBase_ * 2) + b * IBlock::radiusBase_ * 2, pos.y_ - radiusBlockCount.y_ * IBlock::radiusBase_ * 2 - offset}, 
            YMath::Vector2{ -radiusBlockCount.x_ * IBlock::radiusBase_ * 2 + b * IBlock::radiusBase_ * 2, -radiusBlockCount.y_ * IBlock::radiusBase_ * 2 - offset }, 
            YMath::Vector2{IBlock::radiusBase_,1} });
    }
    // 左辺
    // radiusBlockCount * 4 + 1 ~ radiusBlockCount * 6 まで
    for (size_t l = 0; l < radiusBlockCount.y_ * 2 + 1; l++)
    {
        blockVector_.emplace_back(new PieceBasicBlock{ 
            YMath::Vector2{ pos.x_ - radiusBlockCount.x_ * IBlock::radiusBase_ * 2 - offset, (pos.y_ + radiusBlockCount.y_ * IBlock::radiusBase_ * 2) - l * IBlock::radiusBase_ * 2}, 
            YMath::Vector2{ -radiusBlockCount.x_ * IBlock::radiusBase_ * 2 - offset, +radiusBlockCount.y_ * IBlock::radiusBase_ * 2 - l * IBlock::radiusBase_ * 2}, 
            YMath::Vector2{1,IBlock::radiusBase_} });
    }
    // 右辺
    for (size_t r = 0; r < radiusBlockCount.y_ * 2 + 1; r++)
    {
        blockVector_.emplace_back(new PieceBasicBlock{ 
            YMath::Vector2{ pos.x_ + radiusBlockCount.x_ * IBlock::radiusBase_ * 2 + offset, (pos.y_ + radiusBlockCount.y_ * IBlock::radiusBase_ * 2) - r * IBlock::radiusBase_ * 2}, 
            YMath::Vector2{ +radiusBlockCount.x_ * IBlock::radiusBase_ * 2 + offset,  +radiusBlockCount.y_ * IBlock::radiusBase_ * 2 - r * IBlock::radiusBase_ * 2}, 
            YMath::Vector2{1,IBlock::radiusBase_} });
    }
}

void Piece::Update(void)
{
    //for (auto& block : blockVector_) {
    //    block->Update();
    //}

    for (size_t i = 0; i < blockVector_.size(); i++)
    {
        blockVector_[i]->Update();
    }

    if (isOperator_)
    {
        MovePiecePos();

        UpdateTabs();
        WriteBlockPos();
    }
}

void Piece::Draw(void)
{
    //for (auto& block : blockVector_) {
    //    block->Draw();
    //}

    for (size_t i = 0; i < blockVector_.size(); i++)
    {
        blockVector_[i]->Draw();
    }

    int color{ 0xff0000 };
    if (isFixity_) color = 0x00ff00; // 緑
    if (tabs_[0].isConnected_) color = 0xff00ff; // 紫
    if (state_ == State::IMMUTABLE) color = 0x00ffff; // 水

    //// pieceの範囲表示
    //DrawBox(
    //    static_cast<int>(pos_.x - radiusBlockCount_.x * IBlock::radiusBase_), static_cast<int>(pos_.y - radiusBlockCount_.y * IBlock::radiusBase_),
    //    static_cast<int>(pos_.x + radiusBlockCount_.x * IBlock::radiusBase_), static_cast<int>(pos_.y + radiusBlockCount_.y * IBlock::radiusBase_),
    //    color, false
    //);

    //// 中心点
    //DrawCircle(static_cast<int>(pos_.x), static_cast<int>(pos_.y), 4, color, false, 1);

    //if (isOperator_)
    //    for (size_t i = 0; i < tabs_.size(); i++)
    //    {
    //        DrawFormatString(500 + i * 20, 0, 0xffffff, "tabs_dir[%d]", static_cast<int>(tabs_[i].dir_));
    //    }
}

void Piece::RegisterBlock(IBlock* ptr, const YMath::Vector2& offset, const YMath::Vector2& radius)
{
    ptr->SetPos(pos_ + offset);
    ptr->SetOffset(offset);
    ptr->SetRadius(radius);

    blockVector_.emplace_back(ptr);
}

void Piece::RegisterTab(bool isTab, int indexBlockVector)
{
    Tab_t tab;
    tab.isTab_ = isTab;
    tab.pos_ = blockVector_[indexBlockVector]->GetPos();
    tab.indexBlockVector_ = indexBlockVector;
    if (0<= indexBlockVector && indexBlockVector <= (int)radiusBlockCount_.x_ * 2) tab.dir_ = Dir::TOP;
    else if ((int)radiusBlockCount_.x_ * 2 + 1 <= indexBlockVector && indexBlockVector <= (int)radiusBlockCount_.x_ * 4 + 1) tab.dir_ = Dir::BOTTOM;
    else if ((int)radiusBlockCount_.x_ * 4 + 2 <= indexBlockVector && indexBlockVector <= (int)radiusBlockCount_.x_ * 4 + 2 + radiusBlockCount_.y_ * 2) tab.dir_ = Dir::LEFT;
    else if ((int)radiusBlockCount_.x_ * 4 + 3 + radiusBlockCount_.y_ * 2 <= indexBlockVector && indexBlockVector <= (int)radiusBlockCount_.x_ * 4 + 3 + radiusBlockCount_.y_ * 4) tab.dir_ = Dir::RIGHT;

    tabs_.emplace_back(tab);

    blockVector_[indexBlockVector] = std::make_unique<PieceEntranceBlock>(blockVector_[indexBlockVector]->GetPos(), blockVector_[indexBlockVector]->GetOffset(), blockVector_[indexBlockVector]->GetRadius());
}

void Piece::MovePiecePos(void)
{
        if (keysPtr_->IsDown(DIK_UP)) {
            // Pieceの中心点座標の移動
            pos_.y_ += 5;
        }
        if (keysPtr_->IsDown(DIK_DOWN)) {
            pos_.y_ -= 5;
        }
        if (keysPtr_->IsDown(DIK_LEFT)) {
            pos_.x_ -= 5;
        }
        if (keysPtr_->IsDown(DIK_RIGHT)) {
            pos_.x_ += 5;
        }
}

void Piece::ChangeTabsDir(int changeValue)
{
    std::vector<Tab_t> copy = tabs_;

    // changeValueの値は 90/-90 のみの想定
    if (changeValue > 0) {
        for (size_t i = 0; i < tabs_.size(); i++)
        {
            if (copy[i].dir_ == Dir::TOP) tabs_[i].dir_ = Dir::RIGHT;
            if (copy[i].dir_ == Dir::RIGHT) tabs_[i].dir_ = Dir::BOTTOM;
            if (copy[i].dir_ == Dir::BOTTOM) tabs_[i].dir_ = Dir::LEFT;
            if (copy[i].dir_ == Dir::LEFT) tabs_[i].dir_ = Dir::TOP;
        }
    }
    else {
        for (size_t i = 0; i < tabs_.size(); i++)
        {
            if (copy[i].dir_ == Dir::TOP) tabs_[i].dir_ = Dir::LEFT;
            if (copy[i].dir_ == Dir::RIGHT) tabs_[i].dir_ = Dir::TOP;
            if (copy[i].dir_ == Dir::BOTTOM) tabs_[i].dir_ = Dir::RIGHT;
            if (copy[i].dir_ == Dir::LEFT) tabs_[i].dir_ = Dir::BOTTOM;
        }
    }

}

void Piece::RotateBlocks(int rotateValue)
{
    // rotateValueは 90/-90 のみの想定。また度数法とする。

    YMath::Vector2 radiusCopy{ radiusBlockCount_ };

    if (rotateValue > 0) {
        for (size_t i = 0; i < blockVector_.size(); i++)
        {
            // rotate変更。
            int rotate{ blockVector_[i]->GetRotate() };

            rotate + rotateValue >= 450 ?
                blockVector_[i]->SetRotate(90) :
                blockVector_[i]->SetRotate(rotate + 90);


            // 座標変換
            YMath::Vector2 bpos{ blockVector_[i]->GetPos() };
            YMath::Vector2 diffPos{ bpos.x_ - pos_.x_,bpos.y_ - pos_.y_ };
            float rad{ YMath::ConvertFromDegreeToRadian((float)rotateValue) };

            YMath::Vector2 result{};
            result.x_ = diffPos.x_ * std::cosf(rad) - diffPos.y_ * std::sinf(rad) + pos_.x_;
            result.y_ = diffPos.x_ * std::sinf(rad) + diffPos.y_ * std::cosf(rad) + pos_.y_;

            blockVector_[i]->SetPos(result);

            // 半径変更
            //if (blockVector_[i]->GetType() == IBlock::Type::PIECEBASIC ||
            //    blockVector_[i]->GetType() == IBlock::Type::PIECEENTRANCE) {
            //    Vector2 bradius{ blockVector_[i]->GetRadius() };

            //    bradius.x > bradius.y ?
            //        blockVector_[i]->SetRadius(Vector2{ 1, IBlock::radiusBase_ }) :
            //        blockVector_[i]->SetRadius(Vector2{ IBlock::radiusBase_, 1 });
            //}
            YMath::Vector2 bradius{ blockVector_[i]->GetRadius() };

            blockVector_[i]->SetRadius({ bradius.y_,bradius.x_ });

            // offset
            blockVector_[i]->SetOffset(YMath::Vector2{ result - pos_ });
        }
    }
    else {
        for (size_t i = 0; i < blockVector_.size(); i++)
        {
            // rotate変更。
            int rotate{ blockVector_[i]->GetRotate() };

            rotate + rotateValue <= -90 ?
                blockVector_[i]->SetRotate(270) :
                blockVector_[i]->SetRotate(rotate - 90);


            // 座標変換
            YMath::Vector2 bpos{ blockVector_[i]->GetPos() };
            YMath::Vector2 diffPos{ bpos.x_ - pos_.x_,bpos.y_ - pos_.y_ };
            float rad{ YMath::ConvertFromDegreeToRadian((float)rotateValue) };

            YMath::Vector2 result{};
            result.x_ = diffPos.x_ * std::cosf(rad) - diffPos.y_ * std::sinf(rad) + pos_.x_;
            result.y_ = diffPos.x_ * std::sinf(rad) + diffPos.y_ * std::cosf(rad) + pos_.y_;

            blockVector_[i]->SetPos(result);


            //if (blockVector_[i]->GetType() == IBlock::Type::PIECEBASIC ||
            //    blockVector_[i]->GetType() == IBlock::Type::PIECEENTRANCE) {
            //    Vector2 bradius{ blockVector_[i]->GetRadius() };

            //    // 半径変更
            //    bradius.x > bradius.y ?
            //        blockVector_[i]->SetRadius(Vector2{ 1, IBlock::radiusBase_ }) :
            //        blockVector_[i]->SetRadius(Vector2{ IBlock::radiusBase_, 1 });
            //}
            YMath::Vector2 bradius{ blockVector_[i]->GetRadius() };
            blockVector_[i]->SetRadius({ bradius.y_,bradius.x_ });

            // offset
            blockVector_[i]->SetOffset(YMath::Vector2{ result - pos_ });
        }
    }

    radiusBlockCount_ = { radiusCopy.y_,radiusCopy.x_ };
}

void Piece::UpdateTabs(void)
{
    if (keysPtr_->IsTrigger(DIK_J)) {
        rotate_ - 90 < 0 ? // 押したことによって 0 >> -90になるかどうか
            rotate_ = 270 :
            rotate_ -= 90;

        ChangeTabsDir(-90);
        RotateBlocks(-90);
    }
    if (keysPtr_->IsTrigger(DIK_K)) {
        rotate_ + 90 > 270 ? // 押したことによって 360 >> 450になるかどうか
            rotate_ = 90 :
            rotate_ += 90;

        ChangeTabsDir(90);
        RotateBlocks(90);
    }

    for (size_t i = 0; i < tabs_.size(); i++)
    {
        // tabsに記録しているPieceEntranceBlockの座標を更新
        tabs_[i].pos_ = blockVector_[tabs_[i].indexBlockVector_]->GetPos();
        // この関数が通っているということはisOperatorがtrue = Pieceは固定されていないためisConnectedは全てfalse
        tabs_[i].isConnected_ = false;
        // 同上の理由で固定されていないので、blockの判定透過はoff
        blockVector_[tabs_[i].indexBlockVector_]->SetEntranceOpen(false);
    }
}

void Piece::UpdateTabsPos(void)
{
    for (size_t i = 0; i < tabs_.size(); i++) {
        // tabsに記録しているPieceEntranceBlockの座標を更新
        tabs_[i].pos_ = blockVector_[tabs_[i].indexBlockVector_]->GetPos();
    }
}

void Piece::WriteBlockPos(void)
{
    float offset{ IBlock::radiusBase_ };

    for (size_t i = 0; i < blockVector_.size(); i++)
    {
        blockVector_[i]->SetPos(pos_ + blockVector_[i]->GetOffset());
    }
}

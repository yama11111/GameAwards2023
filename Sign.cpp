#include "Sign.h"
#include <algorithm>
#include <cmath>
#include <imgui.h>
#include "Stage.h"

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
            mapchip_[y].emplace_back(0);
        }
    }

    mCollider_.SetBox2DCenter({ GetCenterPos().x_,GetCenterPos().y_ });
    mCollider_.SetBox2DRadSize({ (mapchipSize.x_ / 2 - 2) * blockRadius_ * 2,(mapchipSize.y_ / 2 - 1) * blockRadius_ * 2 });
}

void Sign::Update(void)
{
    for (auto& bd : BDrawerList_) {
        bd->Update();
    }

    if (keys_->IsTrigger(DIK_U)) {
        topLeftPos_.x_ -= 2;
    }

    DrawDebug();
}

void Sign::Draw(void)
{
    for (auto& bd : BDrawerList_) {
        bd->Draw();
    }
}

void maruyama::Sign::DrawDebug(void)
{

    ImGui::Begin("SignMapchip");
    for (size_t y = 0; y < mapchip_.size(); y++)
    {
        for (size_t x = 0; x < mapchip_[0].size(); x++)
        {
            ImGui::Text("elem[%d][%d]", y, x);
            ImGui::Text("bt: %d", mapchip_[y][x]);
        }
    }
    ImGui::End();

    ImGui::Begin("SignBDList");
    for (auto& bd : BDrawerList_) {
        ImGui::Text("bdTrans: %f,%f.,%f", bd->transform_.pos_.x_, bd->transform_.pos_.y_, bd->transform_.pos_.z_);
    }
    ImGui::End();

    ImGui::Begin("mcollider");
    ImGui::Text("c (%f,%f), r (%f,%f)", mCollider_.GetBox2DCenter().x_, mCollider_.GetBox2DCenter().y_, mCollider_.GetBox2DRadSize().x_, mCollider_.GetBox2DRadSize().y_);
    ImGui::End();

    ImGui::Begin("warpcollider");
    for (size_t i = 0; i < warpInfos_.size(); i++)
    {
        ImGui::Text("c (%f,%f),r (%f,%f)", warpInfos_[i].mCollider_.GetBox2DCenter().x_, warpInfos_[i].mCollider_.GetBox2DCenter().y_, warpInfos_[i].mCollider_.GetBox2DRadSize().x_, warpInfos_[i].mCollider_.GetBox2DRadSize().y_);
        ImGui::Text(warpInfos_[i].mCollider_.CollisionMousePointer() ? "warpCol : true" : "warpCol : false");
        ImGui::Text(warpInfos_[i].isConnected_ ? "isConnected : true" : "isConnected : false");
    }
    ImGui::End();
}

void Sign::PPC(YukiMapchipCollider* ptr)
{
    // �ړ��ʂ͐�������
    bool velSignX = ptr->velocity_.x_ > 0 ? true : false;
    bool velSignY = ptr->velocity_.y_ > 0 ? true : false;

    // �ڋߒl
    //Vector2 approach = { ptr->velocity_.x_ / 100.f, ptr->velocity_.y_ / 100.f };

    Vector2 approach{};
    if (ptr->velocity_.x_)
        velSignX ? approach.x_ = 0.01f : approach.x_ = -0.01f;
    if (ptr->velocity_.y_)
        velSignY ? approach.y_ = 0.01f : approach.y_ = -0.01f;

    approach.x_ = roundToDecimal(approach.x_, 4);
    approach.y_ = roundToDecimal(approach.y_, 4);
    //if (velSignX == false) approach.x_ = -approach.x_;
    //if (velSignY == false) approach.y_ = -approach.y_;
    Vector3 velCopy = ptr->velocity_;
    ptr->velocity_ = { 0,0,0 };

    // ����
    // ���ړ���̍��W�Ń}�b�v�`�b�v�z��̈ʒu
    int elemX = CalcElemX(ptr->point_.TopLeft_.x_);
    int elemY = CalcElemY(ptr->point_.TopLeft_.y_);
    int mElemX = CalcMovedElemX(ptr->point_.TopLeft_.x_, velCopy.x_);
    int mElemY = CalcMovedElemY(ptr->point_.TopLeft_.y_, velCopy.y_);
    // �����l�߂��s�������ǂ���
    bool isExeTLX = false;
    bool isExeTLY = false;
    // �������ړ��オ�u���b�N�Ȃ珙�X�Ƀu���b�N�Ƃ̋������l�߂�
    isExeTLX = SlowlyFillingSpaceX(ptr, ptr->point_.TopLeft_.x_, approach, mElemX, elemY);
    isExeTLY = SlowlyFillingSpaceY(ptr, ptr->point_.TopLeft_.y_, approach, elemX, mElemY/*,false*/);

    // �E��
    // ���ړ���̍��W�Ń}�b�v�`�b�v�z��̈ʒu
    elemX = CalcElemX(ptr->point_.TopRight_.x_);
    elemY = CalcElemY(ptr->point_.TopRight_.y_);
    mElemX = CalcMovedElemX(ptr->point_.TopRight_.x_, velCopy.x_);
    mElemY = CalcMovedElemY(ptr->point_.TopRight_.y_, velCopy.y_);
    // �����l�߂��s�������ǂ���
    bool isExeTRX = false;
    bool isExeTRY = false;
    // �������ړ��オ�u���b�N�Ȃ珙�X�Ƀu���b�N�Ƃ̋������l�߂�
    isExeTRX = SlowlyFillingSpaceX(ptr, ptr->point_.TopRight_.x_, approach, mElemX, elemY);
    isExeTRY = SlowlyFillingSpaceY(ptr, ptr->point_.TopRight_.y_, approach, elemX, mElemY/*, false*/);

    //// �ړ��ʂ͏d�͂ɂ����݂̂̂�
    //bool gravityOnly{};
    //if (velCopy.y_ == -YukiMapchipCollider::gravity_)
    //    gravityOnly = true;

    // ����
    // ���ړ���̍��W�Ń}�b�v�`�b�v�z��̈ʒu
    elemX = CalcElemX(ptr->point_.BottomLeft_.x_);
    elemY = CalcElemY(ptr->point_.BottomLeft_.y_);
    mElemX = CalcMovedElemX(ptr->point_.BottomLeft_.x_, velCopy.x_);
    mElemY = CalcMovedElemY(ptr->point_.BottomLeft_.y_, velCopy.y_);
    // �����l�߂��s�������ǂ���
    bool isExeBLX = false;
    bool isExeBLY = false;
    // �������ړ��オ�u���b�N�Ȃ珙�X�Ƀu���b�N�Ƃ̋������l�߂�
    isExeBLX = SlowlyFillingSpaceX(ptr, ptr->point_.BottomLeft_.x_, approach, mElemX, elemY);
    isExeBLY = SlowlyFillingSpaceY(ptr, ptr->point_.BottomLeft_.y_, approach, elemX, mElemY/*, gravityOnly*/);

    // �E��
    // ���ړ���̍��W�Ń}�b�v�`�b�v�z��̈ʒu
    elemX = CalcElemX(ptr->point_.BottomRight_.x_);
    elemY = CalcElemY(ptr->point_.BottomRight_.y_);
    mElemX = CalcMovedElemX(ptr->point_.BottomRight_.x_, velCopy.x_);
    mElemY = CalcMovedElemY(ptr->point_.BottomRight_.y_, velCopy.y_);
    // �����l�߂��s�������ǂ���
    bool isExeBRX = false;
    bool isExeBRY = false;
    // �������ړ��オ�u���b�N�Ȃ珙�X�Ƀu���b�N�Ƃ̋������l�߂�
    isExeBRX = SlowlyFillingSpaceX(ptr, ptr->point_.BottomRight_.x_, approach, mElemX, elemY);
    isExeBRY = SlowlyFillingSpaceY(ptr, ptr->point_.BottomRight_.y_, approach, elemX, mElemY/*, gravityOnly*/);

    if (!isExeTLX && !isExeTRX && !isExeBLX && !isExeBRX) ptr->velocity_.x_ = velCopy.x_;
    if (!isExeTLY && !isExeTRY && !isExeBLY && !isExeBRY) ptr->velocity_.y_ = velCopy.y_;
}

void maruyama::Sign::ReWriteBlock(size_t X, size_t Y, BlockType bt)
{
    // �Ή��O�̃u���b�N�u���̓X�L�b�v
    if (bt == BlockType::WARP1 || bt == BlockType::WARP2) return;

    // ���Wmapchip��int(blockType)��������
    mapchip_[Y][X] = static_cast<int>(bt);

    int x{ (int)X }, y{ (int)Y };
    // �u���b�N�̊Ǘ����X�g�ւ̒ǉ�
    BDrawerList_.emplace_back(new Info_t{ &topLeftPos_,Vector2{x * blockRadius_ * 2 + blockRadius_,-y * blockRadius_ * 2 - blockRadius_ } });
    // ���Y�u���b�N�̏�����
    BDrawerList_.back()->Initialize(static_cast<int>(bt));
}

void maruyama::Sign::ReWriteBlock2Warp(size_t X, size_t Y, BlockType bt, Direction dirSelf)
{
    //<< WARP�n�u���b�N���肪�O�� >>//

    // �Ή��O�̃u���b�N�u���̓X�L�b�v
    if (bt != BlockType::WARP1 && bt != BlockType::WARP2) return;

    // ���Wmapchip��int(blockType)��������
    mapchip_[Y][X] = static_cast<int>(bt);

    int x{ (int)X }, y{ (int)Y };
    // �u���b�N�̊Ǘ����X�g�ւ̒ǉ�
    BDrawerList_.emplace_back(new Info_t{ &topLeftPos_,Vector2{x * blockRadius_ * 2 + blockRadius_,-y * blockRadius_ * 2 - blockRadius_ } });
    // ���Y�u���b�N�̏�����
    BDrawerList_.back()->InitializeWarp(static_cast<int>(bt), dirSelf);

    // ���[�v�u���b�N�̏����p���X�g�ɒǉ����ă}�b�s���O�Ǘ����L�[�͑Ώۂ̔z��v�f��
    WarpIdx_t tempWarpIdx{ dirSelf,{X,Y} };
    tempWarpIdx.mCollider_.SetBox2DCenter({ topLeftPos_.x_ + x * blockRadius_ * 2 + blockRadius_,topLeftPos_.y_ - y * blockRadius_ * 2 - blockRadius_ });
    tempWarpIdx.mCollider_.SetBox2DRadSize({ warpColRad_,warpColRad_ });
    tempWarpIdx.jdPtr_ = BDrawerList_.back().get();
    warpInfos_.emplace_back(tempWarpIdx);
}

inline Sign::Vector3 maruyama::Sign::GetCenterPos(void)
{
    float x = (mapchip_[0].size() / 2) * blockRadius_ * 2;
    float y = (mapchip_.size() / 2) * blockRadius_ * 2;

    // true�Ŋ
    if (mapchip_[0].size() % 2) x += blockRadius_;
    if (mapchip_.size() % 2) y += blockRadius_;

    return Vector3(topLeftPos_.x_ + x, topLeftPos_.y_ - y, topLeftPos_.z_);
}

float maruyama::Sign::roundToDecimal(float value, int decimalPlaces)
{
    float multiplier = (float)std::pow(10.0f, decimalPlaces);
    float roundedValue = (int)std::round(value * multiplier) / multiplier;
    return roundedValue;
}

bool maruyama::Sign::SlowlyFillingSpaceX(YukiMapchipCollider* ptr, float& pointX, const Vector2& approach, int mElemX, int elemY)
{
    bool isExecuted = false;
    if (mElemX <= -1 || mElemX >= mapchip_[0].size()) return isExecuted;
    if (elemY <= -1 || elemY >= mapchip_.size()) return isExecuted;

    if (static_cast<BlockType>(mapchip_[elemY][mElemX]) == BlockType::BASIC) {
        while (1)
        {
            // ���ړ���̍��W�Ń}�b�v�`�b�v�z��̈ʒu
            int checkElemX = CalcMovedElemX(pointX, approach.x_);
            isExecuted = true;
            if (checkElemX == mElemX) break;

            ptr->trfm_.pos_.x_ += approach.x_;
            ptr->UpdatePos();
            ptr->UpdatePoint();
        }
    }
    else if (static_cast<BlockType>(mapchip_[elemY][mElemX]) == BlockType::SPRING) {
        while (1)
        {
            // ���ړ���̍��W�Ń}�b�v�`�b�v�z��̈ʒu
            int checkElemX = CalcMovedElemX(pointX, approach.x_);
            isExecuted = true;
            if (checkElemX == mElemX) break;

            ptr->trfm_.pos_.x_ += approach.x_;
            ptr->UpdatePos();
            ptr->UpdatePoint();
        }
    }
    else if (static_cast<BlockType>(mapchip_[elemY][mElemX]) == BlockType::WARP1) {
        size_t idxWarpInfos_{};
        for (size_t i = 0; i < warpInfos_.size(); i++)
        {
            if (mElemX == warpInfos_[i].mapchipElemSelf_.first && elemY == warpInfos_[i].mapchipElemSelf_.second) {
                idxWarpInfos_ = i;
                break;
            }
        }
        if (warpInfos_[idxWarpInfos_].isConnected_ == false)
        {
            while (1)
            {
                // ���ړ���̍��W�Ń}�b�v�`�b�v�z��̈ʒu
                int checkElemX = CalcMovedElemX(pointX, approach.x_);
                isExecuted = true;
                if (checkElemX == mElemX) break;

                ptr->trfm_.pos_.x_ += approach.x_;
                ptr->UpdatePos();
                ptr->UpdatePoint();
            }
        }
        else {
            if (warpInfos_[idxWarpInfos_].dirPartner_ != Direction::RIGHT && warpInfos_[idxWarpInfos_].dirPartner_ != Direction::LEFT) return isExecuted;

            if (warpInfos_[idxWarpInfos_].isConnected_) {
                //while (1)
                //{
                //    isExecuted = true;
                //    // ���n�t���Otrue
                //    ptr->isGrounded_ = true;
                //    // �Y��point��y�����W���A���[�v�u���b�N�̉E�ӂ������͍��ӂɐG�ꂽ��
                //    if (pointX <= topLeftPos_.x_ - (mElemX * blockRadius_ * 2) && warpInfos_[idxWarpInfos_].dirSelf_ == Direction::RIGHT) break;
                //    if (pointX >= topLeftPos_.x_ - ((mElemX + 1) * blockRadius_ * 2) && warpInfos_[idxWarpInfos_].dirSelf_ == Direction::LEFT) break;

                //    ptr->trfm_.pos_.x_ += approach.x_;
                //    ptr->UpdatePos();
                //    ptr->UpdatePoint();
                //}
                ptr->isTeleport_ = true;
                Vector3 TLP = warpInfos_[idxWarpInfos_].partnerPtr_->topLeftPos_;
                float offset{};
                warpInfos_[idxWarpInfos_].dirPartner_ == Direction::RIGHT ?
                    offset = +teleportDistance_ :
                    offset = -teleportDistance_;
                ptr->teleportedPos_ = {
                    TLP.x_ + warpInfos_[idxWarpInfos_].mapchipElemPartner_.first * blockRadius_ * 2 + offset,
                    TLP.y_ - warpInfos_[idxWarpInfos_].mapchipElemPartner_.second * blockRadius_ * 2 + 0.2f,
                    0 };
                ptr->teleportedVec_ = { offset,0.2f };
                ptr->teleportedIdxSign_ = warpInfos_[idxWarpInfos_].IdxPartnerSign_;
                // �������̃��[�v�u���b�N���v���C���[���ʉ߁i�g�p�j��������true
                warpInfos_[idxWarpInfos_].isUsed_ = true;
                // ���葤�̃��[�v�u���b�N���ʉ߁i�g�p�j��������true
                warpInfos_[idxWarpInfos_].partnerPtr_->warpInfos_[warpInfos_[idxWarpInfos_].IdxPartnerWarp_].isUsed_ = true;
            }
        }
    }
    else if (static_cast<BlockType>(mapchip_[elemY][mElemX]) == BlockType::WARP2) {
        size_t idxWarpInfos_{};
        for (size_t i = 0; i < warpInfos_.size(); i++)
        {
            if (mElemX == warpInfos_[i].mapchipElemSelf_.first && elemY == warpInfos_[i].mapchipElemSelf_.second) {
                idxWarpInfos_ = i;
                break;
            }
        }
        if (warpInfos_[idxWarpInfos_].isConnected_ == false)
        {
            while (1)
            {
                // ���ړ���̍��W�Ń}�b�v�`�b�v�z��̈ʒu
                int checkElemX = CalcMovedElemX(pointX, approach.x_);
                isExecuted = true;
                if (checkElemX == mElemX) break;

                ptr->trfm_.pos_.x_ += approach.x_;
                ptr->UpdatePos();
                ptr->UpdatePoint();
            }
        }
    }
    //if (!approach.x_)isExecuted = false;
    return isExecuted;
}

bool maruyama::Sign::SlowlyFillingSpaceY(YukiMapchipCollider* ptr, float& pointY, const Vector2& approach, int elemX, int mElemY/*, bool gravity*/)
{
    bool isExecuted = false;
    if (elemX <= -1 || elemX >= mapchip_[0].size()) return isExecuted;
    if (mElemY <= -1 || mElemY >= mapchip_.size()) return isExecuted;

    if (static_cast<BlockType>(mapchip_[mElemY][elemX]) == BlockType::BASIC) {
        while (1)
        {
            //ptr->velocity_.y_ = 0;
            // ���ړ���̍��W�Ń}�b�v�`�b�v�z��̈ʒu
            int checkElemY = CalcMovedElemY(pointY, approach.y_);
            //if(checkElemY )
            isExecuted = true;
            // ���n�t���Otrue
            ptr->isGrounded_ = true;
            if (checkElemY == mElemY) break;

            ptr->trfm_.pos_.y_ += approach.y_;
            ptr->UpdatePos();
            ptr->UpdatePoint();
        }
    }
    else if (static_cast<BlockType>(mapchip_[mElemY][elemX]) == BlockType::SPRING) {
        if (approach.y_ > 0)
            while (1)
            {
                // ���ړ���̍��W�Ń}�b�v�`�b�v�z��̈ʒu
                int checkElemY = CalcMovedElemY(pointY, approach.y_);
                //if(checkElemY )
                isExecuted = true;
                if (checkElemY == mElemY) break;

                ptr->trfm_.pos_.y_ += approach.y_;
                ptr->UpdatePos();
                ptr->UpdatePoint();
            }
        else {
            while (1)
            {
                isExecuted = true;
                // ���n�t���Otrue
                ptr->isGrounded_ = true;
                // ��_����Ђ�
                if (pointY <= topLeftPos_.y_ - (mElemY * blockRadius_ * 2)) break;

                ptr->trfm_.pos_.y_ += approach.y_;
                ptr->UpdatePos();
                ptr->UpdatePoint();
            }
            ptr->isSpring_ = true;
        }
    }
    else if (static_cast<BlockType>(mapchip_[mElemY][elemX]) == BlockType::WARP1) {
        size_t idxWarpInfos_{};
        for (size_t i = 0; i < warpInfos_.size(); i++)
        {
            if (elemX == warpInfos_[i].mapchipElemSelf_.first && mElemY == warpInfos_[i].mapchipElemSelf_.second) {
                idxWarpInfos_ = i;
                break;
            }
        }
        if (warpInfos_[idxWarpInfos_].isConnected_ == false)
        {
            while (1)
            {
                // ���ړ���̍��W�Ń}�b�v�`�b�v�z��̈ʒu
                int checkElemY = CalcMovedElemY(pointY, approach.y_);
                //if(checkElemY )
                isExecuted = true;
                if (checkElemY == mElemY) break;

                ptr->trfm_.pos_.y_ += approach.y_;
                ptr->UpdatePos();
                ptr->UpdatePoint();
            }
        }
    }
    else if (static_cast<BlockType>(mapchip_[mElemY][elemX]) == BlockType::WARP2) {
        size_t idxWarpInfos_{};
        for (size_t i = 0; i < warpInfos_.size(); i++)
        {
            if (elemX == warpInfos_[i].mapchipElemSelf_.first && mElemY == warpInfos_[i].mapchipElemSelf_.second) {
                idxWarpInfos_ = i;
                break;
            }
        }
        if (warpInfos_[idxWarpInfos_].isConnected_ == false)
        {
            while (1)
            {
                // ���ړ���̍��W�Ń}�b�v�`�b�v�z��̈ʒu
                int checkElemY = CalcMovedElemY(pointY, approach.y_);
                //if(checkElemY )
                isExecuted = true;
                if (checkElemY == mElemY) break;

                ptr->trfm_.pos_.y_ += approach.y_;
                ptr->UpdatePos();
                ptr->UpdatePoint();
            }
        }
        else {
            if (warpInfos_[idxWarpInfos_].dirPartner_ != Direction::TOP && warpInfos_[idxWarpInfos_].dirPartner_ != Direction::BOTTOM) return isExecuted;

            if (warpInfos_[idxWarpInfos_].isConnected_) {
                while (1)
                {
                    isExecuted = true;
                    // ���n�t���Otrue
                    ptr->isGrounded_ = true;
                    // �Y��point��y�����W���A���[�v�u���b�N�̏�ӂ������͒�ӂɐG�ꂽ��
                    if (pointY <= topLeftPos_.y_ - (mElemY * blockRadius_ * 2) && warpInfos_[idxWarpInfos_].dirSelf_ == Direction::TOP) break;
                    if (pointY >= topLeftPos_.y_ - ((mElemY + 1) * blockRadius_ * 2) && warpInfos_[idxWarpInfos_].dirSelf_ == Direction::BOTTOM) break;

                    ptr->trfm_.pos_.y_ += approach.y_;
                    ptr->UpdatePos();
                    ptr->UpdatePoint();
                }
                ptr->isTeleport_ = true;
                Vector3 TLP = warpInfos_[idxWarpInfos_].partnerPtr_->topLeftPos_;
                float offset{};
                warpInfos_[idxWarpInfos_].dirPartner_ == Direction::TOP ?
                    offset = +teleportDistance_ :
                    offset = -teleportDistance_;
                if (warpInfos_[idxWarpInfos_].dirPartner_ == Direction::TOP) {
                    ptr->teleportedPos_ = {
                    TLP.x_ + warpInfos_[idxWarpInfos_].mapchipElemPartner_.first * blockRadius_ * 2 - offset,
                    TLP.y_ - warpInfos_[idxWarpInfos_].mapchipElemPartner_.second * blockRadius_ * 2 + offset,
                    0 };
                    ptr->teleportedVec_ = { -offset,offset };
                }
                else
                {
                    ptr->teleportedPos_ = {
                        TLP.x_ + warpInfos_[idxWarpInfos_].mapchipElemPartner_.first * blockRadius_ * 2,
                        TLP.y_ - warpInfos_[idxWarpInfos_].mapchipElemPartner_.second * blockRadius_ * 2 + offset,
                        0 };
                    ptr->teleportedVec_ = { 0,offset };
                }
                ptr->teleportedIdxSign_ = warpInfos_[idxWarpInfos_].IdxPartnerSign_;
                // �������̃��[�v�u���b�N���v���C���[���ʉ߁i�g�p�j��������true
                warpInfos_[idxWarpInfos_].isUsed_ = true;
                // ���葤�̃��[�v�u���b�N���ʉ߁i�g�p�j��������true
                warpInfos_[idxWarpInfos_].partnerPtr_->warpInfos_[warpInfos_[idxWarpInfos_].IdxPartnerWarp_].isUsed_ = true;
            }
        }
    }
    else {
        ptr->isGrounded_ = false;
    }
    // �֐����s���A�d�ׂ͂̈����Ɏ��s���ꂽ�ꍇ�͊֐����s�͂Ȃ��������̂Ƃ���
    //if (gravity) isExecuted = false;
    return isExecuted;
}


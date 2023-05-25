#include "Stage.h"
#include <imgui.h>

using namespace YInput;

void Stage::Update(void)
{
    for (size_t i = 0; i < signVector_.size(); i++)
    {
        signVector_[i]->Update();
    }

    MouseCol4Warp();

    DrawDebug();
}

void Stage::Draw(void)
{
    for (size_t i = 0; i < signVector_.size(); i++)
    {
        signVector_[i]->Draw();
    }
}

void Stage::DrawDebug(void)
{
    ImGui::Begin("Stage");
    ImGui::Text("Cursor:%f,%f,%f", MouseColliderCommon::StaticGetMouseWorldPos().x_, MouseColliderCommon::StaticGetMouseWorldPos().y_, MouseColliderCommon::StaticGetMouseWorldPos().z_);
    for (size_t i = 0; i < isHoldSignVector_.size(); i++)
    {
        ImGui::Text(isHoldSignVector_[i] ? "isHold : true" : "isHold : false");
    }
    ImGui::End();
}

void Stage::MouseCol4Warp(void)
{
    bool isHoldOther{};

    for (size_t i = 0; i < signVector_.size(); i++)
    {
        // オフセット
        static Vector2 offset{};

        // 看板とマウスが重なっているとき && 左クリックを押したとき && 他の看板を掴んでいないとき
        if (signVector_[i]->mCollider_.CollisionMousePointer() &&
            Mouse::GetInstance()->IsTrigger(MouseClick::DIM_LEFT) &&
            isHoldOther == false ) {

            // 看板をつかんでいるかをtrue
            isHoldSignVector_[i] = true;
            isHoldOther = true;

            // 看板を掴んでいるカーソル
            offset.x_ = MouseColliderCommon::StaticGetMouseWorldPos().x_ - signVector_[i]->topLeftPos_.x_;
            offset.y_ = MouseColliderCommon::StaticGetMouseWorldPos().y_ - signVector_[i]->topLeftPos_.y_;
        }

        if (isHoldSignVector_[i]) {
            signVector_[i]->topLeftPos_.x_ = MouseColliderCommon::StaticGetMouseWorldPos().x_ + offset.x_;
            signVector_[i]->topLeftPos_.y_ = MouseColliderCommon::StaticGetMouseWorldPos().y_ + offset.y_;
        }

        // 看板とマウスが重なっているとき && 左クリックを離したとき
        if (signVector_[i]->mCollider_.CollisionMousePointer() &&
            Mouse::GetInstance()->IsRelease(MouseClick::DIM_LEFT)) {
            // 看板をつかんでいるかをfalse
            isHoldSignVector_[i] = false;
            isHoldOther = false;
            offset = { 0,0 };
        }
    }
}

void Stage::RegisterSign(Sign* ptr)
{
    signVector_.emplace_back(ptr);
    isHoldSignVector_.emplace_back(false);
}

void Stage::CallPPC(YukiMapchipCollider* ptr)
{
    signVector_[ptr->idxSign_]->PPC(ptr);
}

const Stage::Vector3& Stage::GetTopLeftPos(size_t idx)
{
    return signVector_[idx]->topLeftPos_;
}

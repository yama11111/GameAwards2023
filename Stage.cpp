#include "Stage.h"
#include <imgui.h>

using namespace YInput;

void Stage::Update(void)
{
    MouseCol4Warp();

    for (size_t i = 0; i < signVector_.size(); i++)
    {
        signVector_[i]->Update();
    }

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
    // WARP
    size_t idxWarpInfo_start{};
    size_t idxWarpInfo_end{};
    bool isConnectingWarp{};
    // Sign
    size_t idxSign_start{};
    size_t idxSign_end{};
    bool isHoldOther{};

    bool isConnectCheck{};

    for (size_t i = 0; i < signVector_.size(); i++)
    {
        for (size_t j = 0; j < signVector_[i]->warpInfos_.size(); j++)
        {
            if (signVector_[i]->warpInfos_[j].mCollider_.CollisionMousePointer() &&
                Mouse::GetInstance()->IsTrigger(MouseClick::DIM_LEFT) &&
                isConnectingWarp == false) {
                // ワープ軌道を引き伸ばし
                isConnectingWarp = true;
                idxWarpInfo_start = j;
                idxSign_start = i;
            }
        }

        if (Mouse::GetInstance()->IsDown(MouseClick::DIM_LEFT)) {
            if (isConnectingWarp) {
                // 始点から現在点まで線を引く
            }
        }
        else { // 左クリックを離した瞬間
            // 看板とカーソルが重なっている && その看板が該当のものではない場合
            if (signVector_[i]->mCollider_.CollisionMousePointer() && i != idxSign_start) {
                for (size_t j = 0; j < signVector_[i]->warpInfos_.size(); j++)
                {
                    // 看板内のワープブロックとカーソルが重なっている
                    if (signVector_[i]->warpInfos_[j].mCollider_.CollisionMousePointer()) {
                        idxSign_end = i;
                        idxWarpInfo_end = j;
                        isConnectCheck = true;
                    }
                }
            }
            isConnectingWarp = false;
        }

        // オフセット
        static Vector2 offset{};

        // 看板とマウスが重なっているとき && 左クリックを押したとき && 他の看板を掴んでいないとき
        if (signVector_[i]->mCollider_.CollisionMousePointer() &&
            Mouse::GetInstance()->IsTrigger(MouseClick::DIM_LEFT) &&
            isHoldOther == false && isConnectingWarp == false &&
            isConnectCheck == false) {

            // 看板をつかんでいるかをtrue
            isHoldSignVector_[i] = true;
            isHoldOther = true;

            // 看板を掴んでいるカーソル
            offset.x_ = MouseColliderCommon::StaticGetMouseWorldPos().x_ - signVector_[i]->topLeftPos_.x_;
            offset.y_ = MouseColliderCommon::StaticGetMouseWorldPos().y_ - signVector_[i]->topLeftPos_.y_;
        }

        if (Mouse::GetInstance()->IsDown(MouseClick::DIM_LEFT)) {
            if (isHoldSignVector_[i]) {
                signVector_[i]->topLeftPos_.x_ = MouseColliderCommon::StaticGetMouseWorldPos().x_ - offset.x_;
                signVector_[i]->topLeftPos_.y_ = MouseColliderCommon::StaticGetMouseWorldPos().y_ - offset.y_;
                signVector_[i]->mCollider_.SetBox2DCenter({ signVector_[i]->GetCenterPos().x_,signVector_[i]->GetCenterPos().y_ });
            }
        }
        else {
            // 看板をつかんでいるかをfalse
            isHoldSignVector_[i] = false;
            isHoldOther = false;
            offset = { 0,0 };
        }

        //// 看板とマウスが重なっているとき && 左クリックを離したとき
        //if (signVector_[i]->mCollider_.CollisionMousePointer() &&
        //    Mouse::GetInstance()->IsRelease(MouseClick::DIM_LEFT)) {
        //    // 看板をつかんでいるかをfalse
        //    isHoldSignVector_[i] = false;
        //    isHoldOther = false;
        //    offset = { 0,0 };
        //}
    }

    // warpの接続合図がtrueのとき
    if (isConnectCheck) {
        // 始点と終点の向きが一致しているとき 上 + 下 / 左 + 右
        if (static_cast<int>(signVector_[idxSign_start]->warpInfos_[idxWarpInfo_start].dirSelf_) +
            static_cast<int>(signVector_[idxSign_end]->warpInfos_[idxWarpInfo_end].dirSelf_) == 3) {
            // 接続フラグを変更
            signVector_[idxSign_start]->warpInfos_[idxWarpInfo_start].isConnected_ = true;

            // 始点のwarpInfoに終点側の情報を入力
            // <相手の看板のidx保存>
            // <相手の出現方向保存>
            // <相手のワープブロックの要素数{X,Y}保存>
            // <相手のptr保存>
            signVector_[idxSign_start]->warpInfos_[idxWarpInfo_start].IdxPartnerSign_ = idxSign_end;
            signVector_[idxSign_start]->warpInfos_[idxWarpInfo_start].dirPartner_ = signVector_[idxSign_end]->warpInfos_[idxWarpInfo_end].dirSelf_;
            signVector_[idxSign_start]->warpInfos_[idxWarpInfo_start].mapchipElemPartner_ =
            { signVector_[idxSign_end]->warpInfos_[idxWarpInfo_end].mapchipElemSelf_.first,signVector_[idxSign_end]->warpInfos_[idxWarpInfo_end].mapchipElemSelf_.second };
            signVector_[idxSign_start]->warpInfos_[idxWarpInfo_start].partnerPtr_ = signVector_[idxSign_end].get();

            // 終点のwarpInfoに始点の情報を入力
            signVector_[idxSign_end]->warpInfos_[idxWarpInfo_end].IdxPartnerSign_ = idxSign_start;
            signVector_[idxSign_end]->warpInfos_[idxWarpInfo_end].dirPartner_ = signVector_[idxSign_start]->warpInfos_[idxWarpInfo_start].dirSelf_;
            signVector_[idxSign_end]->warpInfos_[idxWarpInfo_end].mapchipElemPartner_ = 
            { signVector_[idxSign_start]->warpInfos_[idxWarpInfo_start].mapchipElemSelf_.first,signVector_[idxSign_start]->warpInfos_[idxWarpInfo_start].mapchipElemSelf_.second };
            signVector_[idxSign_end]->warpInfos_[idxWarpInfo_end].partnerPtr_ = signVector_[idxSign_start].get();
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

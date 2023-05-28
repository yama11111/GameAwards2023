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
    static size_t idxWarpInfo_start{};
    static size_t idxWarpInfo_end{};
    static bool isConnectingWarp{};
    // Sign
    // オフセット
    static Vector2 offset{};
    static size_t idxSign_start{};
    static size_t idxSign_end{};
    static bool isHoldOther{};

    static bool isConnectCheck{};

    ImGui::Begin("mouseCol4");

    // 左クリックを押した瞬間
    if (Mouse::GetInstance()->IsTrigger(MouseClick::DIM_LEFT)) {
        ImGui::Text("isTriggerLeft : true");
        // ----- ワープブロック ----- //

        // コライダー全検索
        for (size_t i = 0; i < signVector_.size(); i++)
        {
            for (size_t j = 0; j < signVector_[i]->warpInfos_.size(); j++)
            {
                //<< ワープブロック接続処理 >>//
                // ワープブロックのマウスコライダーがtrue && 他のワープブロックの接続処理中でないなら
                if (signVector_[i]->warpInfos_[j].mCollider_.CollisionMousePointer() &&
                    isConnectingWarp == false) {
                    // ワープ軌道を引き伸ばし
                    isConnectingWarp = true;
                    idxWarpInfo_start = j;
                    idxSign_start = i;
                }
            }
        }

        // ----- 看板移動 ----- //
        // ワープブロックの接続処理中でないなら
        if (isConnectingWarp == false && isConnectCheck == false) {
            // 看板コライダー全検索
            for (size_t i = 0; i < signVector_.size(); i++)
            {
                // 看板とマウスが重なっているとき && 他の看板を掴んでいないとき
                if (signVector_[i]->mCollider_.CollisionMousePointer() && isHoldOther == false) {
                    // 看板をつかんでいるかをtrue
                    isHoldSignVector_[i] = true;
                    isHoldOther = true;

                    // 看板を掴んでいるカーソル
                    offset.x_ = MouseColliderCommon::StaticGetMouseWorldPos().x_ - signVector_[i]->topLeftPos_.x_;
                    offset.y_ = MouseColliderCommon::StaticGetMouseWorldPos().y_ - signVector_[i]->topLeftPos_.y_;
                }
            }
        }
    }
    else {
        ImGui::Text("isTriggerLeft : false");
    }

    // 左クリックを押している間
    if (Mouse::GetInstance()->IsDown(MouseClick::DIM_LEFT)) {
        ImGui::Text("isDownLeft : true");
        // ----- ワープブロック ----- //
        if (isConnectingWarp) {
            // 始点から現在点まで線を引く
        }

        // ----- 看板移動 ----- //
        if (isHoldOther) {
            for (size_t i = 0; i < signVector_.size(); i++)
            {
                if (isHoldSignVector_[i]) {
                    signVector_[i]->topLeftPos_.x_ = MouseColliderCommon::StaticGetMouseWorldPos().x_ - offset.x_;
                    signVector_[i]->topLeftPos_.y_ = MouseColliderCommon::StaticGetMouseWorldPos().y_ - offset.y_;
                    signVector_[i]->mCollider_.SetBox2DCenter({ signVector_[i]->GetCenterPos().x_,signVector_[i]->GetCenterPos().y_ });
                }
            }
        }
    }
    else { // 押さなくなった時
        ImGui::Text("isDownLeft : false");
        // ----- ワープブロック ----- //
        // コライダー全検索
        if (isConnectingWarp) {
            for (size_t i = 0; i < signVector_.size(); i++)
            {
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
            }
            isConnectingWarp = false;
        }

        // ----- 看板移動 ----- //
        if (isHoldOther) {
            for (size_t i = 0; i < signVector_.size(); i++)
            {
                // 看板をつかんでいるかをfalse
                isHoldSignVector_[i] = false;
                isHoldOther = false;
                offset = { 0,0 };
            }
        }
    }

    //for (size_t i = 0; i < signVector_.size(); i++)
    //{
        //for (size_t j = 0; j < signVector_[i]->warpInfos_.size(); j++)
        //{
        //    if (signVector_[i]->warpInfos_[j].mCollider_.CollisionMousePointer() &&
        //        Mouse::GetInstance()->IsTrigger(MouseClick::DIM_LEFT) &&
        //        isConnectingWarp == false) {
        //        // ワープ軌道を引き伸ばし
        //        isConnectingWarp = true;
        //        idxWarpInfo_start = j;
        //        idxSign_start = i;
        //    }
        //}

        //if (Mouse::GetInstance()->IsDown(MouseClick::DIM_LEFT)) {
        //    if (isConnectingWarp) {
        //        // 始点から現在点まで線を引く
        //    }
        //}
        //else { // 左クリックを離した瞬間
        //    // 看板とカーソルが重なっている && その看板が該当のものではない場合
        //    if (signVector_[i]->mCollider_.CollisionMousePointer() && i != idxSign_start) {
        //        for (size_t j = 0; j < signVector_[i]->warpInfos_.size(); j++)
        //        {
        //            // 看板内のワープブロックとカーソルが重なっている
        //            if (signVector_[i]->warpInfos_[j].mCollider_.CollisionMousePointer()) {
        //                idxSign_end = i;
        //                idxWarpInfo_end = j;
        //                isConnectCheck = true;
        //            }
        //        }
        //    }
        //    isConnectingWarp = false;
        //}

        // オフセット
        //static Vector2 offset{};

        // 看板とマウスが重なっているとき && 左クリックを押したとき && 他の看板を掴んでいないとき
        //if (signVector_[i]->mCollider_.CollisionMousePointer() &&
            //Mouse::GetInstance()->IsTrigger(MouseClick::DIM_LEFT) &&
            //isHoldOther == false && isConnectingWarp == false &&
            //isConnectCheck == false) {

            //// 看板をつかんでいるかをtrue
            //isHoldSignVector_[i] = true;
            //isHoldOther = true;

            //// 看板を掴んでいるカーソル
            //offset.x_ = MouseColliderCommon::StaticGetMouseWorldPos().x_ - signVector_[i]->topLeftPos_.x_;
            //offset.y_ = MouseColliderCommon::StaticGetMouseWorldPos().y_ - signVector_[i]->topLeftPos_.y_;
        //}

    //if (Mouse::GetInstance()->IsDown(MouseClick::DIM_LEFT)) {
    //    //if (isHoldSignVector_[i]) {
    //    //    signVector_[i]->topLeftPos_.x_ = MouseColliderCommon::StaticGetMouseWorldPos().x_ - offset.x_;
    //    //    signVector_[i]->topLeftPos_.y_ = MouseColliderCommon::StaticGetMouseWorldPos().y_ - offset.y_;
    //    //    signVector_[i]->mCollider_.SetBox2DCenter({ signVector_[i]->GetCenterPos().x_,signVector_[i]->GetCenterPos().y_ });
    //    //}
    //}
    //else {
    //    //// 看板をつかんでいるかをfalse
    //    //isHoldSignVector_[i] = false;
    //    //isHoldOther = false;
    //    //offset = { 0,0 };
    //}

    //// 看板とマウスが重なっているとき && 左クリックを離したとき
    //if (signVector_[i]->mCollider_.CollisionMousePointer() &&
    //    Mouse::GetInstance()->IsRelease(MouseClick::DIM_LEFT)) {
    //    // 看板をつかんでいるかをfalse
    //    isHoldSignVector_[i] = false;
    //    isHoldOther = false;
    //    offset = { 0,0 };
    //}
//}

    // warpの接続合図がtrueのとき
    if (isConnectCheck) {
        // 始点と終点の向きが一致しているとき 上 + 下 / 左 + 右
        if (static_cast<int>(signVector_[idxSign_start]->warpInfos_[idxWarpInfo_start].dirSelf_) +
            static_cast<int>(signVector_[idxSign_end]->warpInfos_[idxWarpInfo_end].dirSelf_) == 3) {

            // 始点側の接続フラグを変更
            signVector_[idxSign_start]->warpInfos_[idxWarpInfo_start].isConnected_ = true;
            // 始点のwarpInfoに終点側の情報を入力
            // <相手の看板のidx保存>
            // <相手の出現方向保存>
            // <相手のワープブロックの要素数{X,Y}保存>
            // <相手のptr保存>
            // <相手のjd_のptrを使ってアニメーション開始>
            // いけるかなこれ

            signVector_[idxSign_start]->warpInfos_[idxWarpInfo_start].IdxPartnerSign_ = idxSign_end;
            signVector_[idxSign_start]->warpInfos_[idxWarpInfo_start].dirPartner_ = signVector_[idxSign_end]->warpInfos_[idxWarpInfo_end].dirSelf_;
            signVector_[idxSign_start]->warpInfos_[idxWarpInfo_start].mapchipElemPartner_ =
            { signVector_[idxSign_end]->warpInfos_[idxWarpInfo_end].mapchipElemSelf_.first,signVector_[idxSign_end]->warpInfos_[idxWarpInfo_end].mapchipElemSelf_.second };
            signVector_[idxSign_start]->warpInfos_[idxWarpInfo_start].partnerPtr_ = signVector_[idxSign_end].get();
            signVector_[idxSign_start]->warpInfos_[idxWarpInfo_start].jdPtr_->jd_.AnimateConnection(&signVector_[idxSign_end]->warpInfos_[idxWarpInfo_end].jdPtr_->jd_);

            // 終点側の接続フラグを変更
            signVector_[idxSign_end]->warpInfos_[idxWarpInfo_end].isConnected_ = true;
            // 終点のwarpInfoに始点の情報を入力
            signVector_[idxSign_end]->warpInfos_[idxWarpInfo_end].IdxPartnerSign_ = idxSign_start;
            signVector_[idxSign_end]->warpInfos_[idxWarpInfo_end].dirPartner_ = signVector_[idxSign_start]->warpInfos_[idxWarpInfo_start].dirSelf_;
            signVector_[idxSign_end]->warpInfos_[idxWarpInfo_end].mapchipElemPartner_ =
            { signVector_[idxSign_start]->warpInfos_[idxWarpInfo_start].mapchipElemSelf_.first,signVector_[idxSign_start]->warpInfos_[idxWarpInfo_start].mapchipElemSelf_.second };
            signVector_[idxSign_end]->warpInfos_[idxWarpInfo_end].partnerPtr_ = signVector_[idxSign_start].get();
            signVector_[idxSign_end]->warpInfos_[idxWarpInfo_end].jdPtr_->jd_.AnimateConnection(&signVector_[idxSign_start]->warpInfos_[idxWarpInfo_start].jdPtr_->jd_);

            //idxSign_start = 0;
            //idxSign_end = 0;
            //idxWarpInfo_start = 0;
            //idxWarpInfo_end = 0;
        }
        isConnectCheck = false;
    }
    ImGui::Text("idxSign_S : %d", idxSign_start);
    ImGui::Text("idxSign_E : %d", idxSign_end);
    ImGui::Text("idxWarp_S : %d", idxWarpInfo_start);
    ImGui::Text("idxWarp_E : %d", idxWarpInfo_end);
    ImGui::Text("S:signVec[%d]->warp[%d].isConnected : %d", idxSign_start, idxWarpInfo_start, signVector_[idxSign_start]->warpInfos_[idxWarpInfo_start].isConnected_);
    ImGui::Text("E:signVec[%d]->warp[%d].isConnected : %d", idxSign_end, idxWarpInfo_end, signVector_[idxSign_end]->warpInfos_[idxWarpInfo_end].isConnected_);

    ImGui::End();
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

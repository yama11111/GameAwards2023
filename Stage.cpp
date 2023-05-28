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
                    mc4w_isConnectingWarp_ == false) {
                    // ワープ軌道を引き伸ばし
                    mc4w_isConnectingWarp_ = true;
                    mc4w_IdxWarpInfo_start_ = j;
                    mc4w_idxSign_start_ = i;
                }
            }
        }

        // ----- 看板移動 ----- //
        // ワープブロックの接続処理中でないなら
        if (mc4w_isConnectingWarp_ == false && mc4w_isConnectCheck_ == false) {
            // 看板コライダー全検索
            for (size_t i = 0; i < signVector_.size(); i++)
            {
                // 看板とマウスが重なっているとき && 他の看板を掴んでいないとき
                if (signVector_[i]->mCollider_.CollisionMousePointer() && mc4w_isHoldOther_ == false) {
                    // 看板をつかんでいるかをtrue
                    isHoldSignVector_[i] = true;
                    mc4w_isHoldOther_ = true;

                    // 看板を掴んでいるカーソル
                    mc4w_offset_.x_ = MouseColliderCommon::StaticGetMouseWorldPos().x_ - signVector_[i]->topLeftPos_.x_;
                    mc4w_offset_.y_ = MouseColliderCommon::StaticGetMouseWorldPos().y_ - signVector_[i]->topLeftPos_.y_;
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
        if (mc4w_isConnectingWarp_) {
            // 始点から現在点まで線を引く
        }

        // ----- 看板移動 ----- //
        if (mc4w_isHoldOther_) {
            for (size_t i = 0; i < signVector_.size(); i++)
            {
                if (isHoldSignVector_[i]) {
                    signVector_[i]->topLeftPos_.x_ = MouseColliderCommon::StaticGetMouseWorldPos().x_ - mc4w_offset_.x_;
                    signVector_[i]->topLeftPos_.y_ = MouseColliderCommon::StaticGetMouseWorldPos().y_ - mc4w_offset_.y_;
                    signVector_[i]->mCollider_.SetBox2DCenter({ signVector_[i]->GetCenterPos().x_,signVector_[i]->GetCenterPos().y_ });
                }
            }
        }
    }
    else { // 押さなくなった時
        ImGui::Text("isDownLeft : false");
        // ----- ワープブロック ----- //
        // コライダー全検索
        if (mc4w_isConnectingWarp_) {
            for (size_t i = 0; i < signVector_.size(); i++)
            {
                // 看板とカーソルが重なっている && その看板が該当のものではない場合
                if (signVector_[i]->mCollider_.CollisionMousePointer() && i != mc4w_idxSign_start_) {
                    for (size_t j = 0; j < signVector_[i]->warpInfos_.size(); j++)
                    {
                        // 看板内のワープブロックとカーソルが重なっている
                        if (signVector_[i]->warpInfos_[j].mCollider_.CollisionMousePointer()) {
                            mc4w_idxSign_end_ = i;
                            mc4w_idxWarpInfo_end_ = j;
                            mc4w_isConnectCheck_ = true;
                        }
                    }
                }
            }
            mc4w_isConnectingWarp_ = false;
        }

        // ----- 看板移動 ----- //
        if (mc4w_isHoldOther_) {
            for (size_t i = 0; i < signVector_.size(); i++)
            {
                // これが動かした看板に該当するなら
                if (isHoldSignVector_[i]) {
                    // 看板のワープブロック全てのマウスコライダーの判定を動かした後の座標に
                    for (size_t j = 0; j < signVector_[i]->warpInfos_.size(); j++)
                    {
                        Vector2 movedCenter =
                        {
                            signVector_[i]->topLeftPos_.x_ + signVector_[i]->warpInfos_[j].mapchipElemSelf_.first * Sign::blockRadius_ * 2 + Sign::blockRadius_,
                            signVector_[i]->topLeftPos_.y_ - signVector_[i]->warpInfos_[j].mapchipElemSelf_.second * Sign::blockRadius_ * 2 - Sign::blockRadius_
                        };
                        signVector_[i]->warpInfos_[j].mCollider_.SetBox2DCenter(movedCenter);
                    }
                }
                // 看板をつかんでいるかをfalse
                isHoldSignVector_[i] = false;
                mc4w_isHoldOther_ = false;
                mc4w_offset_ = { 0,0 };
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
    if (mc4w_isConnectCheck_) {
        // 始点と終点の向きが一致しているとき 上 + 下 / 左 + 右
        if (static_cast<int>(signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].dirSelf_) +
            static_cast<int>(signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].dirSelf_) == 3) {

            if (signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].isUsed_ || signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].isUsed_) {
                isReset_ = true;
                ImGui::End();
                return;
            }

            // 始点側の接続フラグを変更
            signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].isConnected_ = true;
            // 始点のwarpInfoに終点側の情報を入力
            // <相手の看板のidx保存>
            // <相手の出現方向保存>
            // <相手のワープブロックの要素数{X,Y}保存>
            // <相手のptr保存>
            // <相手のjd_のptrを使ってアニメーション開始>
            // いけるかなこれ

            signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].IdxPartnerSign_ = mc4w_idxSign_end_;
            signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].dirPartner_ = signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].dirSelf_;
            signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].mapchipElemPartner_ =
            { signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].mapchipElemSelf_.first,signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].mapchipElemSelf_.second };
            signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].partnerPtr_ = signVector_[mc4w_idxSign_end_].get();
            signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].jdPtr_->jd_.AnimateConnection(&signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].jdPtr_->jd_);

            // 終点側の接続フラグを変更
            signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].isConnected_ = true;
            // 終点のwarpInfoに始点の情報を入力
            signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].IdxPartnerSign_ = mc4w_idxSign_start_;
            signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].dirPartner_ = signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].dirSelf_;
            signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].mapchipElemPartner_ =
            { signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].mapchipElemSelf_.first,signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].mapchipElemSelf_.second };
            signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].partnerPtr_ = signVector_[mc4w_idxSign_start_].get();
            signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].jdPtr_->jd_.AnimateConnection(&signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].jdPtr_->jd_);

            //idxSign_start = 0;
            //idxSign_end = 0;
            //idxWarpInfo_start = 0;
            //idxWarpInfo_end = 0;
        }
        mc4w_isConnectCheck_ = false;
    }
    ImGui::Text("idxSign_S : %d", mc4w_idxSign_start_);
    ImGui::Text("idxSign_E : %d", mc4w_idxSign_end_);
    ImGui::Text("idxWarp_S : %d", mc4w_IdxWarpInfo_start_);
    ImGui::Text("idxWarp_E : %d", mc4w_idxWarpInfo_end_);
    ImGui::Text("S:signVec[%d]->warp[%d].isConnected : %d", mc4w_idxSign_start_, mc4w_IdxWarpInfo_start_, signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].isConnected_);
    ImGui::Text("E:signVec[%d]->warp[%d].isConnected : %d", mc4w_idxSign_end_, mc4w_idxWarpInfo_end_, signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].isConnected_);

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

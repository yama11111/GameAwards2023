#include "Stage.h"
#include <imgui.h>
#include "MathUtillity.h"

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
    //ImGui::Begin("Stage");
    //ImGui::Text("Cursor:%f,%f,%f", MouseColliderCommon::StaticGetMouseWorldPos().x_, MouseColliderCommon::StaticGetMouseWorldPos().y_, MouseColliderCommon::StaticGetMouseWorldPos().z_);
    //for (size_t i = 0; i < isHoldSignVector_.size(); i++)
    //{
    //    ImGui::Text(isHoldSignVector_[i] ? "isHold : true" : "isHold : false");
    //}
    //ImGui::End();
}

void Stage::MouseCol4Warp(void)
{
    //ImGui::Begin("mouseCol4");
    //ImGui::Text("mpos : (%f,%f)", MouseColliderCommon::StaticGetMouseWorldPos().x_, MouseColliderCommon::StaticGetMouseWorldPos().y_);
    //ImGui::End();

    // 左クリックを押した瞬間
    if (Mouse::GetInstance()->IsTrigger(MouseClick::DIM_LEFT)) {
        //ImGui::Text("isTriggerLeft : true");
        // ----- ワープブロック ----- //

        // コライダー全検索
        for (size_t i = 0; i < signVector_.size(); i++)
        {
            for (size_t j = 0; j < signVector_[i]->warpInfos_.size(); j++)
            {
                //<< ワープブロック接続処理 >>//
                // ワープブロックのマウスコライダーがtrue && 他のワープブロックの接続処理中でないなら
                if (signVector_[i]->warpInfos_[j].mCollider_.CollisionMousePointer() &&
                    mc4w_isConnectingWarp_ == false && signVector_[i]->warpInfos_[j].isConnected_ == false) {
                    // ワープ軌道を引き伸ばし
                    mc4w_IdxWarpInfo_oldstart_ = mc4w_IdxWarpInfo_start_;
                    mc4w_idxSign_oldstart_ = mc4w_idxSign_start_;
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
    //else {
    //    //ImGui::Text("isTriggerLeft : false");
    //}

    // 左クリックを押している間
    if (Mouse::GetInstance()->IsDown(MouseClick::DIM_LEFT)) {
        //ImGui::Text("isDownLeft : true");
        // ----- ワープブロック ----- //
        if (mc4w_isConnectingWarp_) {
            // 始点から現在点まで線を引く
            // 選択したワープブロックからマウスに線を伸ばすか？の関数（true)
            signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].jdPtr_->jd_.AnimateSelectConnect(true);
        }

        // ----- 看板移動 ----- //
        if (mc4w_isHoldOther_) {
            for (size_t i = 0; i < signVector_.size(); i++)
            {
                if (isHoldSignVector_[i]) {
                    // 左右（-+）
                    signVector_[i]->topLeftPos_.x_ = (std::max)(MouseColliderCommon::StaticGetMouseWorldPos().x_ - mc4w_offset_.x_, movablePointMin_.x_);
                    if (MouseColliderCommon::StaticGetMouseWorldPos().x_ - mc4w_offset_.x_ + signVector_[i]->mapchip_[0].size() * Sign::blockRadius_ * 2 > movablePointMax_.x_) {
                        signVector_[i]->topLeftPos_.x_ = movablePointMax_.x_ - signVector_[i]->mapchip_[0].size() * Sign::blockRadius_ * 2;
                    }
                    // 上下（+-)
                    signVector_[i]->topLeftPos_.y_ = (std::min)(MouseColliderCommon::StaticGetMouseWorldPos().y_ - mc4w_offset_.y_, movablePointMax_.y_);
                    if (MouseColliderCommon::StaticGetMouseWorldPos().y_ - mc4w_offset_.y_ - signVector_[i]->mapchip_.size() * Sign::blockRadius_ * 2 < movablePointMin_.y_) {
                        signVector_[i]->topLeftPos_.y_ = movablePointMin_.y_ + signVector_[i]->mapchip_.size() * Sign::blockRadius_ * 2;
                    }
                    //signVector_[i]->topLeftPos_.y_ = (std::max)(MouseColliderCommon::StaticGetMouseWorldPos().y_ - mc4w_offset_.y_,movablePointMin_.y_);


                    //signVector_[i]->topLeftPos_.x_ = YMath::Clamp(MouseColliderCommon::StaticGetMouseWorldPos().x_ - mc4w_offset_.x_,movablePointMin_.x_,movablePointMax_.x_);
                    //signVector_[i]->topLeftPos_.y_ = YMath::Clamp(MouseColliderCommon::StaticGetMouseWorldPos().y_ - mc4w_offset_.y_,movablePointMin_.y_,movablePointMax_.y_);
                    signVector_[i]->mCollider_.SetBox2DCenter({ signVector_[i]->GetCenterPos().x_,signVector_[i]->GetCenterPos().y_ });

                    // 動かした看板内のワープブロックに接続済みのものがあるかどうか全検索
                    for (size_t j = 0; j < signVector_[i]->warpInfos_.size(); j++)
                    {
                        // それが接続済みなら
                        if (signVector_[i]->warpInfos_[j].isConnected_) {
                            // ワープブロックが右壁にあるなら（ワープブロックから見た出現方向がLEFTなので）
                            if (signVector_[i]->warpInfos_[j].dirSelf_ == Sign::Direction::LEFT) {
                                // 相手（左壁）のx座標が自分（右壁）のx座標より小さい時
                                if (signVector_[i]->topLeftPos_.x_ + signVector_[i]->warpInfos_[j].mapchipElemSelf_.first * Sign::blockRadius_ * 2 > signVector_[i]->warpInfos_[j].partnerPtr_->topLeftPos_.x_ + signVector_[i]->warpInfos_[j].mapchipElemPartner_.first * Sign::blockRadius_ * 2) {
                                    // そのワープブロックは利用不可能になる
                                    signVector_[i]->warpInfos_[j].isAvailable_ = false;
                                    signVector_[i]->warpInfos_[j].jdPtr_->jd_.AnimatePass(signVector_[i]->warpInfos_[j].isAvailable_);
                                    // そいつの相方のワープブロックも利用不可
                                    signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].isAvailable_ = false;
                                    signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].jdPtr_->jd_.AnimatePass(signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].isAvailable_);
                                }
                                else {
                                    // そのワープブロックは利用不可能になる
                                    signVector_[i]->warpInfos_[j].isAvailable_ = true;
                                    signVector_[i]->warpInfos_[j].jdPtr_->jd_.AnimatePass(signVector_[i]->warpInfos_[j].isAvailable_);
                                    // そいつの相方のワープブロックも利用不可
                                    signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].isAvailable_ = true;
                                    signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].jdPtr_->jd_.AnimatePass(signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].isAvailable_);
                                }
                            }
                            // ワープブロックが左壁にあるなら（ワープブロックから見た出現方向がRIGHTなので）
                            if (signVector_[i]->warpInfos_[j].dirSelf_ == Sign::Direction::RIGHT) {
                                // 相手（左壁）のx座標が自分（右壁）のx座標より大きい時
                                if (signVector_[i]->topLeftPos_.x_ + signVector_[i]->warpInfos_[j].mapchipElemSelf_.first * Sign::blockRadius_ * 2 < signVector_[i]->warpInfos_[j].partnerPtr_->topLeftPos_.x_ + signVector_[i]->warpInfos_[j].mapchipElemPartner_.first * Sign::blockRadius_ * 2) {
                                    // そのワープブロックは利用不可能になる
                                    signVector_[i]->warpInfos_[j].isAvailable_ = false;
                                    signVector_[i]->warpInfos_[j].jdPtr_->jd_.AnimatePass(signVector_[i]->warpInfos_[j].isAvailable_);
                                    // そいつの相方のワープブロックも利用不可
                                    signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].isAvailable_ = false;
                                    signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].jdPtr_->jd_.AnimatePass(signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].isAvailable_);
                                }
                                else {
                                    // そのワープブロックは利用可能になる
                                    signVector_[i]->warpInfos_[j].isAvailable_ = true;
                                    signVector_[i]->warpInfos_[j].jdPtr_->jd_.AnimatePass(signVector_[i]->warpInfos_[j].isAvailable_);
                                    // そいつの相方のワープブロックも利用可
                                    signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].isAvailable_ = true;
                                    signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].jdPtr_->jd_.AnimatePass(signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].isAvailable_);
                                }
                            }

                            // ワープブロックが底壁にあるなら（ワープブロックから見た出現方向がTOPなので）
                            if (signVector_[i]->warpInfos_[j].dirSelf_ == Sign::Direction::TOP) {
                                // 相手（上壁）のy座標が自分（底壁）のy座標より小さい時
                                if (signVector_[i]->topLeftPos_.y_ - signVector_[i]->warpInfos_[j].mapchipElemSelf_.second * Sign::blockRadius_ * 2 < signVector_[i]->warpInfos_[j].partnerPtr_->topLeftPos_.y_ + signVector_[i]->warpInfos_[j].mapchipElemPartner_.second * Sign::blockRadius_ * 2) {
                                    // そのワープブロックは利用不可能になる
                                    signVector_[i]->warpInfos_[j].isAvailable_ = false;
                                    signVector_[i]->warpInfos_[j].jdPtr_->jd_.AnimatePass(signVector_[i]->warpInfos_[j].isAvailable_);
                                    // そいつの相方のワープブロックも利用不可
                                    signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].isAvailable_ = false;
                                    signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].jdPtr_->jd_.AnimatePass(signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].isAvailable_);
                                }
                                else {
                                    // そのワープブロックは利用不可能になる
                                    signVector_[i]->warpInfos_[j].isAvailable_ = true;
                                    signVector_[i]->warpInfos_[j].jdPtr_->jd_.AnimatePass(signVector_[i]->warpInfos_[j].isAvailable_);
                                    // そいつの相方のワープブロックも利用不可
                                    signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].isAvailable_ = true;
                                    signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].jdPtr_->jd_.AnimatePass(signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].isAvailable_);
                                }
                            }
                            // ワープブロックが上壁にあるなら（ワープブロックから見た出現方向がBOTTOMなので）
                            if (signVector_[i]->warpInfos_[j].dirSelf_ == Sign::Direction::BOTTOM) {
                                // 相手（底壁）のy座標が自分（上壁）のy座標より大きい時
                                if (signVector_[i]->topLeftPos_.y_ + signVector_[i]->warpInfos_[j].mapchipElemSelf_.second * Sign::blockRadius_ * 2 > signVector_[i]->warpInfos_[j].partnerPtr_->topLeftPos_.y_ + signVector_[i]->warpInfos_[j].mapchipElemPartner_.second * Sign::blockRadius_ * 2) {
                                    // そのワープブロックは利用不可能になる
                                    signVector_[i]->warpInfos_[j].isAvailable_ = false;
                                    signVector_[i]->warpInfos_[j].jdPtr_->jd_.AnimatePass(signVector_[i]->warpInfos_[j].isAvailable_);
                                    // そいつの相方のワープブロックも利用不可
                                    signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].isAvailable_ = false;
                                    signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].jdPtr_->jd_.AnimatePass(signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].isAvailable_);
                                }
                                else {
                                    // そのワープブロックは利用可能になる
                                    signVector_[i]->warpInfos_[j].isAvailable_ = true;
                                    signVector_[i]->warpInfos_[j].jdPtr_->jd_.AnimatePass(signVector_[i]->warpInfos_[j].isAvailable_);
                                    // そいつの相方のワープブロックも利用可
                                    signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].isAvailable_ = true;
                                    signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].jdPtr_->jd_.AnimatePass(signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].isAvailable_);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else { // 押さなくなった時
        //ImGui::Text("isDownLeft : false");
        // ----- ワープブロック ----- //
        // 選択したワープブロックからマウスに線を伸ばすか？の関数（false)
        signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].jdPtr_->jd_.AnimateSelectConnect(false);
        // コライダー全検索
        if (mc4w_isConnectingWarp_) {
            for (size_t i = 0; i < signVector_.size(); i++)
            {
                // 看板とカーソルが重なっている && その看板が該当のものではない場合
                if (signVector_[i]->mCollider_.CollisionMousePointer() && i != mc4w_idxSign_start_) {
                    for (size_t j = 0; j < signVector_[i]->warpInfos_.size(); j++)
                    {
                        // 看板内のワープブロックとカーソルが重なっている && 繋げ先が繋がってない
                        if (signVector_[i]->warpInfos_[j].mCollider_.CollisionMousePointer() && signVector_[i]->warpInfos_[j].isConnected_ == false) {
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

    // warpの接続合図がtrueのとき
    if (mc4w_isConnectCheck_) {
        // 始点と終点の向きが一致しているとき 上 + 下 / 左 + 右
        if (static_cast<int>(signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].dirSelf_) +
            static_cast<int>(signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].dirSelf_) == 3) {

            //if (signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].isUsed_ || signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].isUsed_) {
            //    isReset_ = true;
            //    //ImGui::End();
            //    return;
            //}

            // 自分側のワープブロックが既にisConnectedだった場合（isConnected == true && isUsed == false)
            //if (signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].isConnected_) {
            //    //// 相手側のワープブロックに保存された情報は初期化する
            //    //// 終点側の接続フラグを変更
            //    //signVector_[mc4w_idxSign_oldstart_]->warpInfos_[mc4w_IdxWarpInfo_oldstart_].isConnected_ = false;
            //    //signVector_[mc4w_idxSign_oldstart_]->warpInfos_[mc4w_IdxWarpInfo_oldstart_].isAvailable_ = false;
            //    //// 終点のwarpInfoに始点の情報を入力
            //    //signVector_[mc4w_idxSign_oldstart_]->warpInfos_[mc4w_IdxWarpInfo_oldstart_].IdxPartnerSign_ = 0;
            //    //signVector_[mc4w_idxSign_oldstart_]->warpInfos_[mc4w_IdxWarpInfo_oldstart_].IdxPartnerWarp_ = 0;
            //    //signVector_[mc4w_idxSign_oldstart_]->warpInfos_[mc4w_IdxWarpInfo_oldstart_].dirPartner_ = Sign::Direction::TOP;
            //    //signVector_[mc4w_idxSign_oldstart_]->warpInfos_[mc4w_IdxWarpInfo_oldstart_].mapchipElemPartner_ = { 0,0 };
            //    //signVector_[mc4w_idxSign_oldstart_]->warpInfos_[mc4w_IdxWarpInfo_oldstart_].partnerPtr_ = nullptr;
            //    //signVector_[mc4w_idxSign_oldstart_]->warpInfos_[mc4w_IdxWarpInfo_oldstart_].jdPtr_->jd_.Reset();
            //}

            // 始点側の接続フラグを変更
            signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].isConnected_ = true;
            signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].isAvailable_ = true;
            // 始点のwarpInfoに終点側の情報を入力
            // <相手の看板のidx保存>
            // <相手のワープブロックのidx保存>
            // <相手の出現方向保存>
            // <相手のワープブロックの要素数{X,Y}保存>
            // <相手のptr保存>
            // <相手のjd_のptrを使ってアニメーション開始>
            // いけるかなこれ
            signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].IdxPartnerSign_ = mc4w_idxSign_end_;
            signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].IdxPartnerWarp_ = mc4w_idxWarpInfo_end_;
            signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].dirPartner_ = signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].dirSelf_;
            signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].mapchipElemPartner_ =
            { signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].mapchipElemSelf_.first,signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].mapchipElemSelf_.second };
            signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].partnerPtr_ = signVector_[mc4w_idxSign_end_].get();
            signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].jdPtr_->jd_.AnimateConnection(&signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].jdPtr_->jd_);

            // 終点側の接続フラグを変更
            signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].isConnected_ = true;
            signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].isAvailable_ = true;
            // 終点のwarpInfoに始点の情報を入力
            signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].IdxPartnerSign_ = mc4w_idxSign_start_;
            signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].IdxPartnerWarp_ = mc4w_IdxWarpInfo_start_;
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
    //ImGui::Text("idxSign_S : %d", mc4w_idxSign_start_);
    //ImGui::Text("idxSign_E : %d", mc4w_idxSign_end_);
    //ImGui::Text("idxWarp_S : %d", mc4w_IdxWarpInfo_start_);
    //ImGui::Text("idxWarp_E : %d", mc4w_idxWarpInfo_end_);
    //ImGui::Text("S:signVec[%d]->warp[%d].isConnected : %d", mc4w_idxSign_start_, mc4w_IdxWarpInfo_start_, signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].isConnected_);
    //ImGui::Text("E:signVec[%d]->warp[%d].isConnected : %d", mc4w_idxSign_end_, mc4w_idxWarpInfo_end_, signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].isConnected_);

    //ImGui::End();
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

void Stage::SetMovableSignRenge(const Vector2& pointMin, const Vector2& pointMax)
{
    movablePointMin_ = pointMin;
    movablePointMax_ = pointMax;
}

const Stage::Vector3& Stage::GetTopLeftPos(size_t idx)
{
    return signVector_[idx]->topLeftPos_;
}

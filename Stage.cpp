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

    // ���N���b�N���������u��
    if (Mouse::GetInstance()->IsTrigger(MouseClick::DIM_LEFT)) {
        ImGui::Text("isTriggerLeft : true");
        // ----- ���[�v�u���b�N ----- //

        // �R���C�_�[�S����
        for (size_t i = 0; i < signVector_.size(); i++)
        {
            for (size_t j = 0; j < signVector_[i]->warpInfos_.size(); j++)
            {
                //<< ���[�v�u���b�N�ڑ����� >>//
                // ���[�v�u���b�N�̃}�E�X�R���C�_�[��true && ���̃��[�v�u���b�N�̐ڑ��������łȂ��Ȃ�
                if (signVector_[i]->warpInfos_[j].mCollider_.CollisionMousePointer() &&
                    mc4w_isConnectingWarp_ == false) {
                    // ���[�v�O���������L�΂�
                    mc4w_isConnectingWarp_ = true;
                    mc4w_IdxWarpInfo_start_ = j;
                    mc4w_idxSign_start_ = i;
                }
            }
        }

        // ----- �Ŕړ� ----- //
        // ���[�v�u���b�N�̐ڑ��������łȂ��Ȃ�
        if (mc4w_isConnectingWarp_ == false && mc4w_isConnectCheck_ == false) {
            // �ŔR���C�_�[�S����
            for (size_t i = 0; i < signVector_.size(); i++)
            {
                // �Ŕƃ}�E�X���d�Ȃ��Ă���Ƃ� && ���̊Ŕ�͂�ł��Ȃ��Ƃ�
                if (signVector_[i]->mCollider_.CollisionMousePointer() && mc4w_isHoldOther_ == false) {
                    // �Ŕ�����ł��邩��true
                    isHoldSignVector_[i] = true;
                    mc4w_isHoldOther_ = true;

                    // �Ŕ�͂�ł���J�[�\��
                    mc4w_offset_.x_ = MouseColliderCommon::StaticGetMouseWorldPos().x_ - signVector_[i]->topLeftPos_.x_;
                    mc4w_offset_.y_ = MouseColliderCommon::StaticGetMouseWorldPos().y_ - signVector_[i]->topLeftPos_.y_;
                }
            }
        }
    }
    else {
        ImGui::Text("isTriggerLeft : false");
    }

    // ���N���b�N�������Ă����
    if (Mouse::GetInstance()->IsDown(MouseClick::DIM_LEFT)) {
        ImGui::Text("isDownLeft : true");
        // ----- ���[�v�u���b�N ----- //
        if (mc4w_isConnectingWarp_) {
            // �n�_���猻�ݓ_�܂Ő�������
        }

        // ----- �Ŕړ� ----- //
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
    else { // �����Ȃ��Ȃ�����
        ImGui::Text("isDownLeft : false");
        // ----- ���[�v�u���b�N ----- //
        // �R���C�_�[�S����
        if (mc4w_isConnectingWarp_) {
            for (size_t i = 0; i < signVector_.size(); i++)
            {
                // �ŔƃJ�[�\�����d�Ȃ��Ă��� && ���̊Ŕ��Y���̂��̂ł͂Ȃ��ꍇ
                if (signVector_[i]->mCollider_.CollisionMousePointer() && i != mc4w_idxSign_start_) {
                    for (size_t j = 0; j < signVector_[i]->warpInfos_.size(); j++)
                    {
                        // �Ŕ��̃��[�v�u���b�N�ƃJ�[�\�����d�Ȃ��Ă���
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

        // ----- �Ŕړ� ----- //
        if (mc4w_isHoldOther_) {
            for (size_t i = 0; i < signVector_.size(); i++)
            {
                // ���ꂪ���������ŔɊY������Ȃ�
                if (isHoldSignVector_[i]) {
                    // �Ŕ̃��[�v�u���b�N�S�Ẵ}�E�X�R���C�_�[�̔���𓮂�������̍��W��
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
                // �Ŕ�����ł��邩��false
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
        //        // ���[�v�O���������L�΂�
        //        isConnectingWarp = true;
        //        idxWarpInfo_start = j;
        //        idxSign_start = i;
        //    }
        //}

        //if (Mouse::GetInstance()->IsDown(MouseClick::DIM_LEFT)) {
        //    if (isConnectingWarp) {
        //        // �n�_���猻�ݓ_�܂Ő�������
        //    }
        //}
        //else { // ���N���b�N�𗣂����u��
        //    // �ŔƃJ�[�\�����d�Ȃ��Ă��� && ���̊Ŕ��Y���̂��̂ł͂Ȃ��ꍇ
        //    if (signVector_[i]->mCollider_.CollisionMousePointer() && i != idxSign_start) {
        //        for (size_t j = 0; j < signVector_[i]->warpInfos_.size(); j++)
        //        {
        //            // �Ŕ��̃��[�v�u���b�N�ƃJ�[�\�����d�Ȃ��Ă���
        //            if (signVector_[i]->warpInfos_[j].mCollider_.CollisionMousePointer()) {
        //                idxSign_end = i;
        //                idxWarpInfo_end = j;
        //                isConnectCheck = true;
        //            }
        //        }
        //    }
        //    isConnectingWarp = false;
        //}

        // �I�t�Z�b�g
        //static Vector2 offset{};

        // �Ŕƃ}�E�X���d�Ȃ��Ă���Ƃ� && ���N���b�N���������Ƃ� && ���̊Ŕ�͂�ł��Ȃ��Ƃ�
        //if (signVector_[i]->mCollider_.CollisionMousePointer() &&
            //Mouse::GetInstance()->IsTrigger(MouseClick::DIM_LEFT) &&
            //isHoldOther == false && isConnectingWarp == false &&
            //isConnectCheck == false) {

            //// �Ŕ�����ł��邩��true
            //isHoldSignVector_[i] = true;
            //isHoldOther = true;

            //// �Ŕ�͂�ł���J�[�\��
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
    //    //// �Ŕ�����ł��邩��false
    //    //isHoldSignVector_[i] = false;
    //    //isHoldOther = false;
    //    //offset = { 0,0 };
    //}

    //// �Ŕƃ}�E�X���d�Ȃ��Ă���Ƃ� && ���N���b�N�𗣂����Ƃ�
    //if (signVector_[i]->mCollider_.CollisionMousePointer() &&
    //    Mouse::GetInstance()->IsRelease(MouseClick::DIM_LEFT)) {
    //    // �Ŕ�����ł��邩��false
    //    isHoldSignVector_[i] = false;
    //    isHoldOther = false;
    //    offset = { 0,0 };
    //}
//}

    // warp�̐ڑ����}��true�̂Ƃ�
    if (mc4w_isConnectCheck_) {
        // �n�_�ƏI�_�̌�������v���Ă���Ƃ� �� + �� / �� + �E
        if (static_cast<int>(signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].dirSelf_) +
            static_cast<int>(signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].dirSelf_) == 3) {

            if (signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].isUsed_ || signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].isUsed_) {
                isReset_ = true;
                ImGui::End();
                return;
            }

            // �n�_���̐ڑ��t���O��ύX
            signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].isConnected_ = true;
            // �n�_��warpInfo�ɏI�_���̏������
            // <����̊Ŕ�idx�ۑ�>
            // <����̏o�������ۑ�>
            // <����̃��[�v�u���b�N�̗v�f��{X,Y}�ۑ�>
            // <�����ptr�ۑ�>
            // <�����jd_��ptr���g���ăA�j���[�V�����J�n>
            // �����邩�Ȃ���

            signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].IdxPartnerSign_ = mc4w_idxSign_end_;
            signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].dirPartner_ = signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].dirSelf_;
            signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].mapchipElemPartner_ =
            { signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].mapchipElemSelf_.first,signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].mapchipElemSelf_.second };
            signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].partnerPtr_ = signVector_[mc4w_idxSign_end_].get();
            signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].jdPtr_->jd_.AnimateConnection(&signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].jdPtr_->jd_);

            // �I�_���̐ڑ��t���O��ύX
            signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].isConnected_ = true;
            // �I�_��warpInfo�Ɏn�_�̏������
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

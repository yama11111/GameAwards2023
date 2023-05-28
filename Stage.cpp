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
    // �I�t�Z�b�g
    static Vector2 offset{};
    static size_t idxSign_start{};
    static size_t idxSign_end{};
    static bool isHoldOther{};

    static bool isConnectCheck{};

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
                    isConnectingWarp == false) {
                    // ���[�v�O���������L�΂�
                    isConnectingWarp = true;
                    idxWarpInfo_start = j;
                    idxSign_start = i;
                }
            }
        }

        // ----- �Ŕړ� ----- //
        // ���[�v�u���b�N�̐ڑ��������łȂ��Ȃ�
        if (isConnectingWarp == false && isConnectCheck == false) {
            // �ŔR���C�_�[�S����
            for (size_t i = 0; i < signVector_.size(); i++)
            {
                // �Ŕƃ}�E�X���d�Ȃ��Ă���Ƃ� && ���̊Ŕ�͂�ł��Ȃ��Ƃ�
                if (signVector_[i]->mCollider_.CollisionMousePointer() && isHoldOther == false) {
                    // �Ŕ�����ł��邩��true
                    isHoldSignVector_[i] = true;
                    isHoldOther = true;

                    // �Ŕ�͂�ł���J�[�\��
                    offset.x_ = MouseColliderCommon::StaticGetMouseWorldPos().x_ - signVector_[i]->topLeftPos_.x_;
                    offset.y_ = MouseColliderCommon::StaticGetMouseWorldPos().y_ - signVector_[i]->topLeftPos_.y_;
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
        if (isConnectingWarp) {
            // �n�_���猻�ݓ_�܂Ő�������
        }

        // ----- �Ŕړ� ----- //
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
    else { // �����Ȃ��Ȃ�����
        ImGui::Text("isDownLeft : false");
        // ----- ���[�v�u���b�N ----- //
        // �R���C�_�[�S����
        if (isConnectingWarp) {
            for (size_t i = 0; i < signVector_.size(); i++)
            {
                // �ŔƃJ�[�\�����d�Ȃ��Ă��� && ���̊Ŕ��Y���̂��̂ł͂Ȃ��ꍇ
                if (signVector_[i]->mCollider_.CollisionMousePointer() && i != idxSign_start) {
                    for (size_t j = 0; j < signVector_[i]->warpInfos_.size(); j++)
                    {
                        // �Ŕ��̃��[�v�u���b�N�ƃJ�[�\�����d�Ȃ��Ă���
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

        // ----- �Ŕړ� ----- //
        if (isHoldOther) {
            for (size_t i = 0; i < signVector_.size(); i++)
            {
                // �Ŕ�����ł��邩��false
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
    if (isConnectCheck) {
        // �n�_�ƏI�_�̌�������v���Ă���Ƃ� �� + �� / �� + �E
        if (static_cast<int>(signVector_[idxSign_start]->warpInfos_[idxWarpInfo_start].dirSelf_) +
            static_cast<int>(signVector_[idxSign_end]->warpInfos_[idxWarpInfo_end].dirSelf_) == 3) {

            // �n�_���̐ڑ��t���O��ύX
            signVector_[idxSign_start]->warpInfos_[idxWarpInfo_start].isConnected_ = true;
            // �n�_��warpInfo�ɏI�_���̏������
            // <����̊Ŕ�idx�ۑ�>
            // <����̏o�������ۑ�>
            // <����̃��[�v�u���b�N�̗v�f��{X,Y}�ۑ�>
            // <�����ptr�ۑ�>
            // <�����jd_��ptr���g���ăA�j���[�V�����J�n>
            // �����邩�Ȃ���

            signVector_[idxSign_start]->warpInfos_[idxWarpInfo_start].IdxPartnerSign_ = idxSign_end;
            signVector_[idxSign_start]->warpInfos_[idxWarpInfo_start].dirPartner_ = signVector_[idxSign_end]->warpInfos_[idxWarpInfo_end].dirSelf_;
            signVector_[idxSign_start]->warpInfos_[idxWarpInfo_start].mapchipElemPartner_ =
            { signVector_[idxSign_end]->warpInfos_[idxWarpInfo_end].mapchipElemSelf_.first,signVector_[idxSign_end]->warpInfos_[idxWarpInfo_end].mapchipElemSelf_.second };
            signVector_[idxSign_start]->warpInfos_[idxWarpInfo_start].partnerPtr_ = signVector_[idxSign_end].get();
            signVector_[idxSign_start]->warpInfos_[idxWarpInfo_start].jdPtr_->jd_.AnimateConnection(&signVector_[idxSign_end]->warpInfos_[idxWarpInfo_end].jdPtr_->jd_);

            // �I�_���̐ڑ��t���O��ύX
            signVector_[idxSign_end]->warpInfos_[idxWarpInfo_end].isConnected_ = true;
            // �I�_��warpInfo�Ɏn�_�̏������
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

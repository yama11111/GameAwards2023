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

    // ���N���b�N���������u��
    if (Mouse::GetInstance()->IsTrigger(MouseClick::DIM_LEFT)) {
        //ImGui::Text("isTriggerLeft : true");
        // ----- ���[�v�u���b�N ----- //

        // �R���C�_�[�S����
        for (size_t i = 0; i < signVector_.size(); i++)
        {
            for (size_t j = 0; j < signVector_[i]->warpInfos_.size(); j++)
            {
                //<< ���[�v�u���b�N�ڑ����� >>//
                // ���[�v�u���b�N�̃}�E�X�R���C�_�[��true && ���̃��[�v�u���b�N�̐ڑ��������łȂ��Ȃ�
                if (signVector_[i]->warpInfos_[j].mCollider_.CollisionMousePointer() &&
                    mc4w_isConnectingWarp_ == false && signVector_[i]->warpInfos_[j].isConnected_ == false) {
                    // ���[�v�O���������L�΂�
                    mc4w_IdxWarpInfo_oldstart_ = mc4w_IdxWarpInfo_start_;
                    mc4w_idxSign_oldstart_ = mc4w_idxSign_start_;
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
    //else {
    //    //ImGui::Text("isTriggerLeft : false");
    //}

    // ���N���b�N�������Ă����
    if (Mouse::GetInstance()->IsDown(MouseClick::DIM_LEFT)) {
        //ImGui::Text("isDownLeft : true");
        // ----- ���[�v�u���b�N ----- //
        if (mc4w_isConnectingWarp_) {
            // �n�_���猻�ݓ_�܂Ő�������
            // �I���������[�v�u���b�N����}�E�X�ɐ���L�΂����H�̊֐��itrue)
            signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].jdPtr_->jd_.AnimateSelectConnect(true);
        }

        // ----- �Ŕړ� ----- //
        if (mc4w_isHoldOther_) {
            for (size_t i = 0; i < signVector_.size(); i++)
            {
                if (isHoldSignVector_[i]) {
                    // ���E�i-+�j
                    signVector_[i]->topLeftPos_.x_ = (std::max)(MouseColliderCommon::StaticGetMouseWorldPos().x_ - mc4w_offset_.x_, movablePointMin_.x_);
                    if (MouseColliderCommon::StaticGetMouseWorldPos().x_ - mc4w_offset_.x_ + signVector_[i]->mapchip_[0].size() * Sign::blockRadius_ * 2 > movablePointMax_.x_) {
                        signVector_[i]->topLeftPos_.x_ = movablePointMax_.x_ - signVector_[i]->mapchip_[0].size() * Sign::blockRadius_ * 2;
                    }
                    // �㉺�i+-)
                    signVector_[i]->topLeftPos_.y_ = (std::min)(MouseColliderCommon::StaticGetMouseWorldPos().y_ - mc4w_offset_.y_, movablePointMax_.y_);
                    if (MouseColliderCommon::StaticGetMouseWorldPos().y_ - mc4w_offset_.y_ - signVector_[i]->mapchip_.size() * Sign::blockRadius_ * 2 < movablePointMin_.y_) {
                        signVector_[i]->topLeftPos_.y_ = movablePointMin_.y_ + signVector_[i]->mapchip_.size() * Sign::blockRadius_ * 2;
                    }
                    //signVector_[i]->topLeftPos_.y_ = (std::max)(MouseColliderCommon::StaticGetMouseWorldPos().y_ - mc4w_offset_.y_,movablePointMin_.y_);


                    //signVector_[i]->topLeftPos_.x_ = YMath::Clamp(MouseColliderCommon::StaticGetMouseWorldPos().x_ - mc4w_offset_.x_,movablePointMin_.x_,movablePointMax_.x_);
                    //signVector_[i]->topLeftPos_.y_ = YMath::Clamp(MouseColliderCommon::StaticGetMouseWorldPos().y_ - mc4w_offset_.y_,movablePointMin_.y_,movablePointMax_.y_);
                    signVector_[i]->mCollider_.SetBox2DCenter({ signVector_[i]->GetCenterPos().x_,signVector_[i]->GetCenterPos().y_ });

                    // ���������Ŕ��̃��[�v�u���b�N�ɐڑ��ς݂̂��̂����邩�ǂ����S����
                    for (size_t j = 0; j < signVector_[i]->warpInfos_.size(); j++)
                    {
                        // ���ꂪ�ڑ��ς݂Ȃ�
                        if (signVector_[i]->warpInfos_[j].isConnected_) {
                            // ���[�v�u���b�N���E�ǂɂ���Ȃ�i���[�v�u���b�N���猩���o��������LEFT�Ȃ̂Łj
                            if (signVector_[i]->warpInfos_[j].dirSelf_ == Sign::Direction::LEFT) {
                                // ����i���ǁj��x���W�������i�E�ǁj��x���W��菬������
                                if (signVector_[i]->topLeftPos_.x_ + signVector_[i]->warpInfos_[j].mapchipElemSelf_.first * Sign::blockRadius_ * 2 > signVector_[i]->warpInfos_[j].partnerPtr_->topLeftPos_.x_ + signVector_[i]->warpInfos_[j].mapchipElemPartner_.first * Sign::blockRadius_ * 2) {
                                    // ���̃��[�v�u���b�N�͗��p�s�\�ɂȂ�
                                    signVector_[i]->warpInfos_[j].isAvailable_ = false;
                                    signVector_[i]->warpInfos_[j].jdPtr_->jd_.AnimatePass(signVector_[i]->warpInfos_[j].isAvailable_);
                                    // �����̑����̃��[�v�u���b�N�����p�s��
                                    signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].isAvailable_ = false;
                                    signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].jdPtr_->jd_.AnimatePass(signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].isAvailable_);
                                }
                                else {
                                    // ���̃��[�v�u���b�N�͗��p�s�\�ɂȂ�
                                    signVector_[i]->warpInfos_[j].isAvailable_ = true;
                                    signVector_[i]->warpInfos_[j].jdPtr_->jd_.AnimatePass(signVector_[i]->warpInfos_[j].isAvailable_);
                                    // �����̑����̃��[�v�u���b�N�����p�s��
                                    signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].isAvailable_ = true;
                                    signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].jdPtr_->jd_.AnimatePass(signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].isAvailable_);
                                }
                            }
                            // ���[�v�u���b�N�����ǂɂ���Ȃ�i���[�v�u���b�N���猩���o��������RIGHT�Ȃ̂Łj
                            if (signVector_[i]->warpInfos_[j].dirSelf_ == Sign::Direction::RIGHT) {
                                // ����i���ǁj��x���W�������i�E�ǁj��x���W���傫����
                                if (signVector_[i]->topLeftPos_.x_ + signVector_[i]->warpInfos_[j].mapchipElemSelf_.first * Sign::blockRadius_ * 2 < signVector_[i]->warpInfos_[j].partnerPtr_->topLeftPos_.x_ + signVector_[i]->warpInfos_[j].mapchipElemPartner_.first * Sign::blockRadius_ * 2) {
                                    // ���̃��[�v�u���b�N�͗��p�s�\�ɂȂ�
                                    signVector_[i]->warpInfos_[j].isAvailable_ = false;
                                    signVector_[i]->warpInfos_[j].jdPtr_->jd_.AnimatePass(signVector_[i]->warpInfos_[j].isAvailable_);
                                    // �����̑����̃��[�v�u���b�N�����p�s��
                                    signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].isAvailable_ = false;
                                    signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].jdPtr_->jd_.AnimatePass(signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].isAvailable_);
                                }
                                else {
                                    // ���̃��[�v�u���b�N�͗��p�\�ɂȂ�
                                    signVector_[i]->warpInfos_[j].isAvailable_ = true;
                                    signVector_[i]->warpInfos_[j].jdPtr_->jd_.AnimatePass(signVector_[i]->warpInfos_[j].isAvailable_);
                                    // �����̑����̃��[�v�u���b�N�����p��
                                    signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].isAvailable_ = true;
                                    signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].jdPtr_->jd_.AnimatePass(signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].isAvailable_);
                                }
                            }

                            // ���[�v�u���b�N����ǂɂ���Ȃ�i���[�v�u���b�N���猩���o��������TOP�Ȃ̂Łj
                            if (signVector_[i]->warpInfos_[j].dirSelf_ == Sign::Direction::TOP) {
                                // ����i��ǁj��y���W�������i��ǁj��y���W��菬������
                                if (signVector_[i]->topLeftPos_.y_ - signVector_[i]->warpInfos_[j].mapchipElemSelf_.second * Sign::blockRadius_ * 2 < signVector_[i]->warpInfos_[j].partnerPtr_->topLeftPos_.y_ + signVector_[i]->warpInfos_[j].mapchipElemPartner_.second * Sign::blockRadius_ * 2) {
                                    // ���̃��[�v�u���b�N�͗��p�s�\�ɂȂ�
                                    signVector_[i]->warpInfos_[j].isAvailable_ = false;
                                    signVector_[i]->warpInfos_[j].jdPtr_->jd_.AnimatePass(signVector_[i]->warpInfos_[j].isAvailable_);
                                    // �����̑����̃��[�v�u���b�N�����p�s��
                                    signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].isAvailable_ = false;
                                    signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].jdPtr_->jd_.AnimatePass(signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].isAvailable_);
                                }
                                else {
                                    // ���̃��[�v�u���b�N�͗��p�s�\�ɂȂ�
                                    signVector_[i]->warpInfos_[j].isAvailable_ = true;
                                    signVector_[i]->warpInfos_[j].jdPtr_->jd_.AnimatePass(signVector_[i]->warpInfos_[j].isAvailable_);
                                    // �����̑����̃��[�v�u���b�N�����p�s��
                                    signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].isAvailable_ = true;
                                    signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].jdPtr_->jd_.AnimatePass(signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].isAvailable_);
                                }
                            }
                            // ���[�v�u���b�N����ǂɂ���Ȃ�i���[�v�u���b�N���猩���o��������BOTTOM�Ȃ̂Łj
                            if (signVector_[i]->warpInfos_[j].dirSelf_ == Sign::Direction::BOTTOM) {
                                // ����i��ǁj��y���W�������i��ǁj��y���W���傫����
                                if (signVector_[i]->topLeftPos_.y_ + signVector_[i]->warpInfos_[j].mapchipElemSelf_.second * Sign::blockRadius_ * 2 > signVector_[i]->warpInfos_[j].partnerPtr_->topLeftPos_.y_ + signVector_[i]->warpInfos_[j].mapchipElemPartner_.second * Sign::blockRadius_ * 2) {
                                    // ���̃��[�v�u���b�N�͗��p�s�\�ɂȂ�
                                    signVector_[i]->warpInfos_[j].isAvailable_ = false;
                                    signVector_[i]->warpInfos_[j].jdPtr_->jd_.AnimatePass(signVector_[i]->warpInfos_[j].isAvailable_);
                                    // �����̑����̃��[�v�u���b�N�����p�s��
                                    signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].isAvailable_ = false;
                                    signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].jdPtr_->jd_.AnimatePass(signVector_[i]->warpInfos_[j].partnerPtr_->warpInfos_[signVector_[i]->warpInfos_[j].IdxPartnerWarp_].isAvailable_);
                                }
                                else {
                                    // ���̃��[�v�u���b�N�͗��p�\�ɂȂ�
                                    signVector_[i]->warpInfos_[j].isAvailable_ = true;
                                    signVector_[i]->warpInfos_[j].jdPtr_->jd_.AnimatePass(signVector_[i]->warpInfos_[j].isAvailable_);
                                    // �����̑����̃��[�v�u���b�N�����p��
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
    else { // �����Ȃ��Ȃ�����
        //ImGui::Text("isDownLeft : false");
        // ----- ���[�v�u���b�N ----- //
        // �I���������[�v�u���b�N����}�E�X�ɐ���L�΂����H�̊֐��ifalse)
        signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].jdPtr_->jd_.AnimateSelectConnect(false);
        // �R���C�_�[�S����
        if (mc4w_isConnectingWarp_) {
            for (size_t i = 0; i < signVector_.size(); i++)
            {
                // �ŔƃJ�[�\�����d�Ȃ��Ă��� && ���̊Ŕ��Y���̂��̂ł͂Ȃ��ꍇ
                if (signVector_[i]->mCollider_.CollisionMousePointer() && i != mc4w_idxSign_start_) {
                    for (size_t j = 0; j < signVector_[i]->warpInfos_.size(); j++)
                    {
                        // �Ŕ��̃��[�v�u���b�N�ƃJ�[�\�����d�Ȃ��Ă��� && �q���悪�q�����ĂȂ�
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

    // warp�̐ڑ����}��true�̂Ƃ�
    if (mc4w_isConnectCheck_) {
        // �n�_�ƏI�_�̌�������v���Ă���Ƃ� �� + �� / �� + �E
        if (static_cast<int>(signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].dirSelf_) +
            static_cast<int>(signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].dirSelf_) == 3) {

            //if (signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].isUsed_ || signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].isUsed_) {
            //    isReset_ = true;
            //    //ImGui::End();
            //    return;
            //}

            // �������̃��[�v�u���b�N������isConnected�������ꍇ�iisConnected == true && isUsed == false)
            //if (signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].isConnected_) {
            //    //// ���葤�̃��[�v�u���b�N�ɕۑ����ꂽ���͏���������
            //    //// �I�_���̐ڑ��t���O��ύX
            //    //signVector_[mc4w_idxSign_oldstart_]->warpInfos_[mc4w_IdxWarpInfo_oldstart_].isConnected_ = false;
            //    //signVector_[mc4w_idxSign_oldstart_]->warpInfos_[mc4w_IdxWarpInfo_oldstart_].isAvailable_ = false;
            //    //// �I�_��warpInfo�Ɏn�_�̏������
            //    //signVector_[mc4w_idxSign_oldstart_]->warpInfos_[mc4w_IdxWarpInfo_oldstart_].IdxPartnerSign_ = 0;
            //    //signVector_[mc4w_idxSign_oldstart_]->warpInfos_[mc4w_IdxWarpInfo_oldstart_].IdxPartnerWarp_ = 0;
            //    //signVector_[mc4w_idxSign_oldstart_]->warpInfos_[mc4w_IdxWarpInfo_oldstart_].dirPartner_ = Sign::Direction::TOP;
            //    //signVector_[mc4w_idxSign_oldstart_]->warpInfos_[mc4w_IdxWarpInfo_oldstart_].mapchipElemPartner_ = { 0,0 };
            //    //signVector_[mc4w_idxSign_oldstart_]->warpInfos_[mc4w_IdxWarpInfo_oldstart_].partnerPtr_ = nullptr;
            //    //signVector_[mc4w_idxSign_oldstart_]->warpInfos_[mc4w_IdxWarpInfo_oldstart_].jdPtr_->jd_.Reset();
            //}

            // �n�_���̐ڑ��t���O��ύX
            signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].isConnected_ = true;
            signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].isAvailable_ = true;
            // �n�_��warpInfo�ɏI�_���̏������
            // <����̊Ŕ�idx�ۑ�>
            // <����̃��[�v�u���b�N��idx�ۑ�>
            // <����̏o�������ۑ�>
            // <����̃��[�v�u���b�N�̗v�f��{X,Y}�ۑ�>
            // <�����ptr�ۑ�>
            // <�����jd_��ptr���g���ăA�j���[�V�����J�n>
            // �����邩�Ȃ���
            signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].IdxPartnerSign_ = mc4w_idxSign_end_;
            signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].IdxPartnerWarp_ = mc4w_idxWarpInfo_end_;
            signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].dirPartner_ = signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].dirSelf_;
            signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].mapchipElemPartner_ =
            { signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].mapchipElemSelf_.first,signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].mapchipElemSelf_.second };
            signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].partnerPtr_ = signVector_[mc4w_idxSign_end_].get();
            signVector_[mc4w_idxSign_start_]->warpInfos_[mc4w_IdxWarpInfo_start_].jdPtr_->jd_.AnimateConnection(&signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].jdPtr_->jd_);

            // �I�_���̐ڑ��t���O��ύX
            signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].isConnected_ = true;
            signVector_[mc4w_idxSign_end_]->warpInfos_[mc4w_idxWarpInfo_end_].isAvailable_ = true;
            // �I�_��warpInfo�Ɏn�_�̏������
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

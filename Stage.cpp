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
        // �I�t�Z�b�g
        static Vector2 offset{};

        // �Ŕƃ}�E�X���d�Ȃ��Ă���Ƃ� && ���N���b�N���������Ƃ� && ���̊Ŕ�͂�ł��Ȃ��Ƃ�
        if (signVector_[i]->mCollider_.CollisionMousePointer() &&
            Mouse::GetInstance()->IsTrigger(MouseClick::DIM_LEFT) &&
            isHoldOther == false ) {

            // �Ŕ�����ł��邩��true
            isHoldSignVector_[i] = true;
            isHoldOther = true;

            // �Ŕ�͂�ł���J�[�\��
            offset.x_ = MouseColliderCommon::StaticGetMouseWorldPos().x_ - signVector_[i]->topLeftPos_.x_;
            offset.y_ = MouseColliderCommon::StaticGetMouseWorldPos().y_ - signVector_[i]->topLeftPos_.y_;
        }

        if (isHoldSignVector_[i]) {
            signVector_[i]->topLeftPos_.x_ = MouseColliderCommon::StaticGetMouseWorldPos().x_ + offset.x_;
            signVector_[i]->topLeftPos_.y_ = MouseColliderCommon::StaticGetMouseWorldPos().y_ + offset.y_;
        }

        // �Ŕƃ}�E�X���d�Ȃ��Ă���Ƃ� && ���N���b�N�𗣂����Ƃ�
        if (signVector_[i]->mCollider_.CollisionMousePointer() &&
            Mouse::GetInstance()->IsRelease(MouseClick::DIM_LEFT)) {
            // �Ŕ�����ł��邩��false
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

#include "Sign.h"
#include <algorithm>
#include <cmath>
#include <imgui.h>

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
            if (y == 0 || y == (int)(mapchipSize.y_ - 1)) {
                mapchip_[y].emplace_back(1);
                BDrawerList_.emplace_back(new Info_t{ &topLeftPos_,Vector2{ x * blockRadius_ * 2 + blockRadius_, -y * blockRadius_ * 2 - blockRadius_ } }); // y���}�C�i�X�Ȃ̂́Ay�̐��������ゾ����B
                BDrawerList_.back()->Initialize(1);
            }
            else if (x == 0 || x == (int)(mapchipSize.x_ - 1)) {
                mapchip_[y].emplace_back(1);
                BDrawerList_.emplace_back(new Info_t{ &topLeftPos_,Vector2{ x * blockRadius_ * 2 + blockRadius_, -y * blockRadius_ * 2 - blockRadius_ } });
                BDrawerList_.back()->Initialize(1);
            }
            else {
                mapchip_[y].emplace_back(0);
            }
        }
    }
}

void Sign::Update(void)
{
    for (auto& bd : BDrawerList_) {
        bd->Update();
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
    int mElemX = CalcMovedElemX(ptr->point_.TopLeft_.x_, velCopy.x_);
    int mElemY = CalcMovedElemY(ptr->point_.TopLeft_.y_, velCopy.y_);
    // �����l�߂��s�������ǂ���
    bool isExeTL = false;
    // �������ړ��オ�u���b�N�Ȃ珙�X�Ƀu���b�N�Ƃ̋������l�߂�
    isExeTL = SlowlyFillingSpaceX(ptr, ptr->point_.TopLeft_.x_, approach, mElemX, mElemY) || SlowlyFillingSpaceY(ptr, ptr->point_.TopLeft_.y_, approach, mElemX, mElemY);

    // �E��
    // ���ړ���̍��W�Ń}�b�v�`�b�v�z��̈ʒu
    mElemX = CalcMovedElemX(ptr->point_.TopRight_.x_, velCopy.x_);
    mElemY = CalcMovedElemY(ptr->point_.TopRight_.y_, velCopy.y_);
    // �����l�߂��s�������ǂ���
    bool isExeTR = false;
    // �������ړ��オ�u���b�N�Ȃ珙�X�Ƀu���b�N�Ƃ̋������l�߂�
    isExeTR = SlowlyFillingSpaceX(ptr, ptr->point_.TopRight_.x_, approach, mElemX, mElemY) || SlowlyFillingSpaceY(ptr, ptr->point_.TopRight_.y_, approach, mElemX, mElemY);

    // ����
    // ���ړ���̍��W�Ń}�b�v�`�b�v�z��̈ʒu
    mElemX = CalcMovedElemX(ptr->point_.BottomLeft_.x_, velCopy.x_);
    mElemY = CalcMovedElemY(ptr->point_.BottomLeft_.y_, velCopy.y_);
    // �����l�߂��s�������ǂ���
    bool isExeBL = false;
    // �������ړ��オ�u���b�N�Ȃ珙�X�Ƀu���b�N�Ƃ̋������l�߂�
    isExeBL = SlowlyFillingSpaceX(ptr, ptr->point_.BottomLeft_.x_, approach, mElemX, mElemY) || SlowlyFillingSpaceY(ptr, ptr->point_.BottomLeft_.y_, approach, mElemX, mElemY);

    // �E��
    // ���ړ���̍��W�Ń}�b�v�`�b�v�z��̈ʒu
    mElemX = CalcMovedElemX(ptr->point_.BottomRight_.x_, velCopy.x_);
    mElemY = CalcMovedElemY(ptr->point_.BottomRight_.y_, velCopy.y_);
    // �����l�߂��s�������ǂ���
    bool isExeBR = false;
    // �������ړ��オ�u���b�N�Ȃ珙�X�Ƀu���b�N�Ƃ̋������l�߂�
    isExeBR = SlowlyFillingSpaceX(ptr, ptr->point_.BottomRight_.x_, approach, mElemX, mElemY) || SlowlyFillingSpaceY(ptr, ptr->point_.BottomRight_.y_, approach, mElemX, mElemY);

    if (!isExeTL && !isExeTR && !isExeBL && !isExeBR) ptr->velocity_ = velCopy;













    ////// �u���b�N�ɂ͂܂��Ă��邩�ǂ���
    ////bool isStuck{ false };
    //// �l��ÓI�ێ� [�΂ˊ֘A]
    //static bool isSpring{};
    //static float springValue{};

    //// ����
    //int elemX = CalcMovedElemX(ptr->point_.TopLeft_.x_, ptr->velocity_.x_);
    //int elemY = CalcMovedElemY(ptr->point_.TopLeft_.y_, ptr->velocity_.y_);
    //// �␳�l�i�[�ϐ�
    //Vector2 TL{};
    //// �ړ���̍��W���}�b�v�`�b�v�ゾ�ƃu���b�N���ǂ���
    //if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::BASIC) {
    //    Vector2 surplus{};
    //    surplus.x_ = std::fabs(topLeftPos_.x_ + (elemX + 1) * blockRadius_ * 2); // ���ォ��E�����ɃJ�E���g����̂� topLeft + offsetX
    //    surplus.y_ = std::fabs(topLeftPos_.y_ - (elemY + 1) * blockRadius_ * 2); // ���ォ�牺�����ɃJ�E���g����̂� topLeft - offsetY

    //    ptr->velocity_.x_ > 0 ?
    //        TL.x_ = -surplus.x_ :
    //        TL.x_ = surplus.x_;
    //    ptr->velocity_.y_ > 0 ?
    //        TL.y_ = -surplus.y_ :
    //        TL.y_ = surplus.y_;
    //}

    //// �E��
    //elemX = CalcMovedElemX(ptr->point_.TopRight_.x_, ptr->velocity_.x_);
    //elemY = CalcMovedElemY(ptr->point_.TopRight_.y_, ptr->velocity_.y_);
    //// �␳�l�i�[�ϐ�
    //Vector2 TR{};
    //// �ړ���̍��W���}�b�v�`�b�v�ゾ�ƃu���b�N���ǂ���
    //if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::BASIC) {
    //    Vector2 surplus{};
    //    surplus.x_ = std::fabs(topLeftPos_.x_ + elemX * blockRadius_ * 2); // ���ォ��E�����ɃJ�E���g����̂� topLeft + offsetX
    //    surplus.y_ = std::fabs(topLeftPos_.y_ - (elemY + 1) * blockRadius_ * 2); // ���ォ�牺�����ɃJ�E���g����̂� topLeft - offsetY

    //    ptr->velocity_.x_ > 0 ?
    //        TR.x_ = -surplus.x_ :
    //        TR.x_ = surplus.x_;
    //    ptr->velocity_.y_ > 0 ?
    //        TR.y_ = -surplus.y_ :
    //        TR.y_ = surplus.y_;
    //}

    //// ����
    //elemX = CalcMovedElemX(ptr->point_.BottomLeft_.x_, ptr->velocity_.x_);
    //elemY = CalcMovedElemY(ptr->point_.BottomLeft_.y_, ptr->velocity_.y_);
    //// �␳�l�i�[�ϐ�
    //Vector2 BL{};
    //// �ړ���̍��W���}�b�v�`�b�v�ゾ�ƃu���b�N���ǂ���
    //if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::BASIC) {
    //    Vector2 surplus{};
    //    surplus.x_ = std::fabs(topLeftPos_.x_ + (elemX + 1) * blockRadius_ * 2); // ���ォ��E�����ɃJ�E���g����̂� topLeft + offsetX
    //    surplus.y_ = std::fabs(topLeftPos_.y_ - elemY * blockRadius_ * 2); // ���ォ�牺�����ɃJ�E���g����̂� topLeft - offsetY

    //    ptr->velocity_.x_ > 0 ?
    //        BL.x_ = -surplus.x_ :
    //        BL.x_ = surplus.x_;
    //    ptr->velocity_.y_ > 0 ?
    //        BL.y_ = -surplus.y_ :
    //        BL.y_ = surplus.y_;
    //}
    //else if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::SPRING) {
    //    isSpring = true;
    //    springValue = springPower_; // �l��ݒ肳�ꂽ�l�ɕύX
    //}

    //// �E��
    //elemX = CalcMovedElemX(ptr->point_.BottomRight_.x_, ptr->velocity_.x_);
    //elemY = CalcMovedElemY(ptr->point_.BottomRight_.y_, ptr->velocity_.y_);
    //// �␳�l�i�[�ϐ�
    //Vector2 BR{};
    //// �ړ���̍��W���}�b�v�`�b�v�ゾ�ƃu���b�N���ǂ���
    //if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::BASIC) {
    //    Vector2 surplus{};
    //    surplus.x_ = std::fabs(topLeftPos_.x_ + elemX * blockRadius_ * 2); // ���ォ��E�����ɃJ�E���g����̂� topLeft + offsetX
    //    surplus.y_ = std::fabs(topLeftPos_.y_ - elemY * blockRadius_ * 2); // ���ォ�牺�����ɃJ�E���g����̂� topLeft - offsetY

    //    ptr->velocity_.x_ > 0 ?
    //        BR.x_ = -surplus.x_ :
    //        BR.x_ = surplus.x_;
    //    ptr->velocity_.y_ > 0 ?
    //        BR.y_ = -surplus.y_ :
    //        BR.y_ = surplus.y_;
    //}
    //else if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::SPRING) {
    //    isSpring = true;
    //    springValue = springPower_; // �l��ݒ肳�ꂽ�l�ɕύX
    //}

    //// ��ʓI�ȃu���b�N�ɑ΂��鉟���߂�����
    //Vector2 totalVel{};
    //// ����
    //CalcTotal(totalVel, TL);
    //CalcTotal(totalVel, TR);
    //CalcTotal(totalVel, BL);
    //CalcTotal(totalVel, BR);
    //if (totalVel.Length())
    //    ptr->velocity_ = { totalVel.x_,totalVel.y_,0 };

    //// �΂˃u���b�N�ɑ΂�����ꋓ��
    //if (isSpring && ptr->entityType_ == YukiMapchipCollider::EntityType::PLAYER) { // �t���O��true && �Ώۂ�Player�ł��邱��
    //    // �ǂ񂾂����˂邩
    //    springValue -= springFall_; // �����͂͏��X�Ɍ�������

    //    // �����͂�����0�ɂȂ��Ă���ꍇ�̓t���OOFF
    //    if (springValue < 0.f) isSpring = false;
    //    // �����͂͌�����0�����ɂ͂Ȃ�Ȃ�
    //    springValue = (std::max)(springValue, 0.f);

    //    // �ړ��ʂƂ��đ��
    //    ptr->velocity_.y_ += springValue;
    //}

    //// velocity�i�[�p�i�Ăяo���񐔗}�� + �ۖڌ덷�����j
    //Vector2 vec2Vel{ roundToDecimal(ptr->velocity_.x_, 6),roundToDecimal(ptr->velocity_.y_, 6) };
    //// point�i�[�p�i�Ăяo���񐔗}�� + �ۖڌ덷�����j
    //YukiMapchipCollider::Point pointCopy{};
    //pointCopy.TopLeft_.x_ = roundToDecimal(ptr->point_.TopLeft_.x_, 6);
    //pointCopy.TopLeft_.y_ = roundToDecimal(ptr->point_.TopLeft_.y_, 6);
    //pointCopy.TopRight_.x_ = roundToDecimal(ptr->point_.TopRight_.x_, 6);
    //pointCopy.TopRight_.y_ = roundToDecimal(ptr->point_.TopRight_.y_, 6);
    //pointCopy.BottomLeft_.x_ = roundToDecimal(ptr->point_.BottomLeft_.x_, 6);
    //pointCopy.BottomLeft_.y_ = roundToDecimal(ptr->point_.BottomLeft_.y_, 6);
    //pointCopy.BottomRight_.x_ = roundToDecimal(ptr->point_.BottomRight_.x_, 6);
    //pointCopy.BottomRight_.y_ = roundToDecimal(ptr->point_.BottomRight_.y_, 6);

    //// point�̍��W���}�b�v�`�b�v�P�ʂɕϊ�
    //int elemX{}, elemY{};
    //if (keys_->IsTrigger(DIK_P)) { // �u���C�N�|�C���g�p
    //    int a{};
    //}
    ////<<<<<<<<<<<<<<<<<<<<<< ���� >>>>>>>>>>>>>>>>>>>>>>>>>>//
    //elemX = pointCopy.TopLeft_.x_ / (int)(blockRadius_ * 2); // �v�f���̌v�Z
    //elemY = -1 * pointCopy.TopLeft_.y_ / (int)(blockRadius_ * 2); // �v�f���͐��A���W�͕��A�Z�o�� ���W / ���a*2 �ŗ�O�X���[����̂� -�����遦y����
    //if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::BASIC) // �ʏ�u���b�N
    //{
    //    isStuck = true;
    //}

    ////<<<<<<<<<<<<<<<<<<<<<< �E�� >>>>>>>>>>>>>>>>>>>>>>>>>>//
    //elemX = pointCopy.TopRight_.x_ / (int)(blockRadius_ * 2);
    //elemY = -1 * pointCopy.TopRight_.y_ / (int)(blockRadius_ * 2); // �v�f���͐��A���W�͕��A�Z�o�� ���W / ���a*2 �ŗ�O�X���[����̂� -�����遦y����
    //if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::BASIC) // �ʏ�u���b�N
    //{
    //    isStuck = true;
    //}

    ////<<<<<<<<<<<<<<<<<<<<<< ���� >>>>>>>>>>>>>>>>>>>>>>>>>>//
    //elemX = pointCopy.BottomLeft_.x_ / (int)(blockRadius_ * 2);
    //elemY = -1 * pointCopy.BottomLeft_.y_ / (int)(blockRadius_ * 2); // �v�f���͐��A���W�͕��A�Z�o�� ���W / ���a*2 �ŗ�O�X���[����̂� -�����遦y����
    //if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::BASIC) // �ʏ�u���b�N
    //{
    //    isStuck = true;
    //}
    //else if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::SPRING) // �΂˃u���b�N
    //{
    //    isSpring = true;
    //    springValue = springPower_; // �l��ݒ肳�ꂽ�l�ɕύX
    //}

    ////<<<<<<<<<<<<<<<<<<<<<< �E�� >>>>>>>>>>>>>>>>>>>>>>>>>>//
    //elemX = pointCopy.BottomRight_.x_ / (int)(blockRadius_ * 2);
    //elemY = -1 * pointCopy.BottomRight_.y_ / (int)(blockRadius_ * 2); // �v�f���͐��A���W�͕��A�Z�o�� ���W / ���a*2 �ŗ�O�X���[����̂� -�����遦y����
    //if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::BASIC) // �ʏ�u���b�N
    //{
    //    isStuck = true;
    //}
    //else if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::SPRING) // �΂˃u���b�N
    //{
    //    isSpring = true;
    //    springValue = springPower_; // �l��ݒ肳�ꂽ�l�ɕύX
    //}

    //// CalcVelStuck�p
    //{
    //    Vector2 TL{}, TR{}, BL{}, BR{};

    //    // ���ݒn�i�߂荞��ł�ꍇ�j�̈ړ��l���Z�o
    //    Vector2 vec2Vel{ ptr->velocity_.x_,ptr->velocity_.y_ };
    //    TL = CalcVelStuck(ptr->point_.TopLeft_); // ����
    //    TR = CalcVelStuck(ptr->point_.TopRight_); // �E��
    //    BL = CalcVelStuck(ptr->point_.BottomLeft_); // ����
    //    BR = CalcVelStuck(ptr->point_.BottomRight_); // �E��
    //}

    //// 4�_�̉����߂��ړ��ʔ�r�p
    //Vector2 TL{}, TR{}, BL{}, BR{};
    //// ��ʓI�ȃu���b�N
    //if (isStuck) {
    //    TL = CalcVelMove(pointCopy.TopLeft_, vec2Vel); // ����
    //    TR = CalcVelMove(pointCopy.TopRight_, vec2Vel); // �E��
    //    BL = CalcVelMove(pointCopy.BottomLeft_, vec2Vel); // ����
    //    BR = CalcVelMove(pointCopy.BottomRight_, vec2Vel); // �E��

    //    // �Z�o���ꂽ�l�̒��ōŏ��l���ړ��ʂƂ��ēK�p
    //    ptr->velocity_.x_ = (std::min)({ TL.x_,TR.x_,BL.x_,BR.x_ });
    //    ptr->velocity_.y_ = (std::min)({ TL.y_,TR.y_,BL.y_,BR.y_ });
    //    //// �Z�o���ꂽ�l�̒��ōő�l���ړ��ʂƂ��ēK�p
    //    //ptr->velocity_.x_ = (std::max)({ TL.x_,TR.x_,BL.x_,BR.x_ });
    //    //ptr->velocity_.y_ = (std::max)({ TL.y_,TR.y_,BL.y_,BR.y_ });
    //}
    //// �΂�
    //if (isSpring && ptr->entityType_ == YukiMapchipCollider::EntityType::PLAYER) { // �t���O��true && �Ώۂ�Player�ł��邱��
    //    // �ǂ񂾂����˂邩
    //    springValue -= springFall_; // �����͂͏��X�Ɍ�������

    //    // �����͂�����0�ɂȂ��Ă���ꍇ�̓t���OOFF
    //    if (springValue < 0.f) isSpring = false;
    //    // �����͂͌�����0�����ɂ͂Ȃ�Ȃ�
    //    springValue = (std::max)(springValue, 0.f);

    //    // �ړ��ʂƂ��đ��
    //    ptr->velocity_.y_ += springValue;
    //}

    // <summary>
    //## ���̍\���̏ꍇ�A�R���C�_�[���p�������q�N���X������Update()�֐��́A
    //## �K�����L�̂悤�ɍŏ��̍s�ȊO�ł̍��W�X�V���s���Ă͂Ȃ�Ȃ��B
    //## �ŏ��̍s: UpdatePos();
    //## ����ȍ~: velocity�v�Z;
    // </summary>
    //ptr->UpdatePos();
}

void maruyama::Sign::ReWriteBlock(size_t X, size_t Y, BlockType bt)
{
    // �Ή��O�̃u���b�N�u���̓X�L�b�v
    if (bt == BlockType::WARP1 || bt == BlockType::WARP2) return;

    // ���Wmapchip��int(blockType)��������
    mapchip_[Y][X] = static_cast<int>(bt);

    int x{ (int)X }, y{ (int)Y };
    // �u���b�N�̊Ǘ����X�g�ւ̒ǉ�
    BDrawerList_.emplace_back(new Info_t{ &topLeftPos_,Vector2{ x * blockRadius_ * 2 + blockRadius_, -y * blockRadius_ * 2 - blockRadius_ } });
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
    BDrawerList_.emplace_back(new Info_t{ &topLeftPos_,Vector2{ x * blockRadius_ * 2 + blockRadius_, -y * blockRadius_ * 2 - blockRadius_ } });
    // ���Y�u���b�N�̏�����
    BDrawerList_.back()->Initialize(static_cast<int>(bt));

    // ���[�v�u���b�N�̏����p���X�g�ɒǉ����ă}�b�s���O�Ǘ����L�[�͑Ώۂ̔z��v�f��
    warpInfos_.emplace_back(WarpIdx_t{ dirSelf,{X,Y} });
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

bool maruyama::Sign::SlowlyFillingSpaceX(YukiMapchipCollider* ptr, float& pointX, const Vector2& approach, int mElemX, int mElemY)
{
    bool isExecuted = false;
    if (mElemX == -1 || mElemX == mapchip_[0].size()) return isExecuted;
    if (mElemY == -1 || mElemY == mapchip_.size()) return isExecuted;

    while (static_cast<BlockType>(mapchip_[mElemY][mElemX]) == BlockType::BASIC)
    {
        // ���ړ���̍��W�Ń}�b�v�`�b�v�z��̈ʒu
        int checkElemX = CalcMovedElemX(pointX, approach.x_);
        isExecuted = true;
        if (checkElemX == mElemX) break;

        ptr->transform_.pos_.x_ += approach.x_;
        ptr->UpdatePos();
        ptr->UpdatePoint();
    }
    return isExecuted;
}

bool maruyama::Sign::SlowlyFillingSpaceY(YukiMapchipCollider* ptr, float& pointY, const Vector2& approach, int mElemX, int mElemY)
{
    bool isExecuted = false;
    if (mElemX <= -1 || mElemX >= mapchip_[0].size()) return isExecuted;
    if (mElemY <= -1 || mElemY >= mapchip_.size()) return isExecuted;

    while (static_cast<BlockType>(mapchip_[mElemY][mElemX]) == BlockType::BASIC)
    {
        // ���ړ���̍��W�Ń}�b�v�`�b�v�z��̈ʒu
        int checkElemY = CalcMovedElemX(pointY, approach.y_);
        isExecuted = true;
        if (checkElemY == mElemY) break;

        ptr->transform_.pos_.y_ += approach.y_;
        ptr->UpdatePos();
        ptr->UpdatePoint();
    }
    return isExecuted;
}


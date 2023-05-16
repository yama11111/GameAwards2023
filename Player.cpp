#include "Player.h"
#include <cmath>
#include <imgui.h>

Player::Player(Stage* stagePtr) :
    stagePtr_(stagePtr), radius_(defaultWidth_, defaultHeight_), keysPtr_(YInput::Keys::GetInstance())
{
    transform_.Initialize({ YMath::Vector3{0,0,0},YMath::Vector3{0,0,0},YMath::Vector3{radius_.x_,radius_.y_, 1} });
    //pDrawer_.Initialize(&transform_, &direction_);
    pBDrawer_.Initialize(&transform_, IMode::Type::Movable);
}

void Player::Update(void)
{
    Move();

    transform_.UpdateMatrix();
    //pDrawer_.Update();
    pBDrawer_.Update();
    //if (pos_.y > 600)pos_.y = 0;
}

void Player::Draw(void)
{
    //pDrawer_.Draw();
    pBDrawer_.Draw();
}

void Player::DrawDebug(void)
{
    ImGui::Begin("Player");
    ImGui::Text("posx: %f,posy: %f,posz:%f", transform_.pos_.x_, transform_.pos_.y_, transform_.pos_.z_);
    ImGui::Text("scax: %f,scay: %f,scaz:%f", transform_.scale_.x_, transform_.scale_.y_, transform_.scale_.z_);
    ImGui::End();
}

void Player::Move(void)
{
    // �ړ���
    YMath::Vector2 vel{};

    // x��
    // ���E���͂̔���ƈړ��ʉ��Z
    vel.x_ += (keysPtr_->IsDown(DIK_D) - keysPtr_->IsDown(DIK_A)) * moveSpeed_;
    //vel.y += (KEY::IsDown(KEY_INPUT_S) - KEY::IsDown(KEY_INPUT_W)) * moveSpeed_;

    static float jumpValue{ 0.f };
    // y��
    // �W�����v����
    Jump(vel, jumpValue);

    // �o�l����
    Spring(vel, nowSpringRot);

    // �d��
    vel.y_ -= gravity_;

    //vel = vel.normalize();

    // �ړ��ʕ␳
    Collision(vel, jumpValue);

    // �␳�ς̈ړ��ʂ�pos�ɉ��Z
    YMath::Vector2 pos{ GetPos() + vel };
    SetPos(pos);

    // transform���X�V
    transform_.pos_ = { pos.x_,pos.y_,0 };

    if (vel.x_ != 0.f) direction_ = { vel.x_, 0, 0 };
}

void Player::Jump(YMath::Vector2& vel, float& jumpValue)
{
    // �g���K�[�ŃW�����v
    if (keysPtr_->IsTrigger(DIK_SPACE) && isJump_ == false) {
        isJump_ = true;
        jumpValue += jumpPower_;
    }

    // vel�ɃW�����v��(y���ړ���)�����Z
    vel.y_ += jumpValue;
    if (jumpValue > 0.f) {
        jumpValue -= fallValue_;
    }
    else if (jumpValue <= 0.f) {
        isJump_ = false;
    }

    // 0�����̒l�ɂȂ�Ȃ��B
    jumpValue = (std::max)(jumpValue, 0.f);
}

void Player::Spring(YMath::Vector2& vel, int rot)
{
    //true����Ȃ���Δ�����
    if (!isSpring_ && nowVel.x_ == 0 && nowVel.y_ == 0)
    {
        nowSpringRot = 0;
        return;
    }

    //�W�����v�h�~
    isJump_ = true;

    //��]�p
    int rot_ = rot;

    if (isSpring_)
    {
        //90�x���Ƃ�
        switch (rot_ / 90)
        {
        case 0:
            nowVel.y_ = springPower_;
            break;
        case 1:
            nowVel.x_ = springPower_ / 2;
            break;
        case 2:
            nowVel.y_ = -springPower_;
            break;
        case 3:
            nowVel.x_ = -springPower_ / 2;
            break;
        }

        isSpring_ = false;
    }
    else
    {
        //90�x���Ƃ�
        switch (rot_ / 90)
        {
        case 0:
            nowVel.y_ -= fallValue_;

            if (nowVel.y_ < 0)
            {
                nowVel.y_ = 0;
            }
            break;
        case 1:
            nowVel.x_ -= fallValue_;

            if (nowVel.x_ < 0)
            {
                nowVel.x_ = 0;
            }
            break;
        case 2:
            nowVel.y_ += fallValue_;

            if (nowVel.y_ > 0)
            {
                nowVel.y_ = 0;
            }
            break;
        case 3:
            nowVel.x_ += fallValue_;

            if (nowVel.x_ > 0)
            {
                nowVel.x_ = 0;
            }
            break;
        }
    }

    vel += nowVel;
}

void Player::Collision(YMath::Vector2& vel, float& jumpValue)
{
    for (size_t i = 0; i < stagePtr_->GetPieceVectorPtr()->size(); i++) {
        // �Y��Piece�����삳��Ă���ꍇ�X�L�b�v
        if (stagePtr_->GetPieceVectorPtr()->at(i)->GetOperator()) continue;
        // �Y��Piece
        if (stagePtr_->GetPieceVectorPtr()->at(i)->GetFixity() == false) continue;

        for (size_t j = 0; j < stagePtr_->GetPieceVectorPtr()->at(i)->GetBlocksPtr()->size(); j++)
        {
            // �|�C���^���m�ۂ���getter�֐��Ăяo���}��
            IBlock* tempBlockPtr{ stagePtr_->GetPieceVectorPtr()->at(i)->GetBlocksPtr()->at(j).get() };

            // X��,Y����3�u���b�N�͈͓��ł͂Ȃ��ꍇ�A�X�L�b�v
            if (std::abs(tempBlockPtr->GetPos().x_ - GetPos().x_) > IBlock::radiusBase_ * 6) continue;
            if (std::abs(tempBlockPtr->GetPos().y_ - GetPos().y_) > IBlock::radiusBase_ * 6) continue;

            // �u���b�N�̎�ނ� PIECEENTRANCEBLOCK �ł���ꍇ
            if (tempBlockPtr->GetType() == IBlock::Type::PIECEENTRANCE) {
                // �v���C���[���u���b�N�̒����ɐG��邩
                if (CheckHit(GetPos().x_, GetRadius().x_, 0, tempBlockPtr->GetPos().x_, 8) &&
                    CheckHit(GetPos().y_, GetRadius().y_, 0, tempBlockPtr->GetPos().y_, 8)) {
                    if (stagePtr_->GetPieceVectorPtr()->at(i)->GetState() == Piece::State::MOVABLE) stagePtr_->GetPieceVectorPtr()->at(i)->SetState(Piece::State::IMMUTABLE);
                }

                if (tempBlockPtr->GetEntranceOpen())
                    continue;
            }

            // �o�l�u���b�N����
            if (tempBlockPtr->GetType() == IBlock::Type::SPRING) {

                int sizex = defaultHeight_ + 1;
                int sizey = 1;

                int sizeX = 0;
                int sizeY = 0;

                //90�x���Ƃ�
                switch (tempBlockPtr->GetRotate() / 90)
                {
                case 0://��

                    sizex = 0;
                    sizeX = defaultHeight_;
                    sizey = defaultHeight_;
                    sizey = sizey * -1;
                    sizeY = 1;

                    break;
                case 1://�E

                    sizex = defaultHeight_;
                    sizeX = 1;
                    sizey = 0;
                    sizeY = defaultHeight_;

                    break;
                case 2://��

                    sizex = 0;
                    sizeX = defaultHeight_;
                    sizey = defaultHeight_;
                    sizeY = 1;

                    break;
                case 3://��

                    sizex = defaultHeight_;
                    sizey = sizey * -1;
                    sizeX = 1;
                    sizey = 0;
                    sizeY = defaultHeight_;

                    break;

                    //DrawFormatString(0, 60, GetColor(100, 100, 100), "true");

                    //if (isJump_ == false) {
                    /*Jump(vel, true);*/
                    //}
                    if (CheckHit(GetPos().x_, GetRadius().x_, 0, tempBlockPtr->GetPos().x_ + sizex, sizeX) &&
                        CheckHit(GetPos().y_, GetRadius().y_, 0, tempBlockPtr->GetPos().y_ + sizey, sizeY)) {

                        nowSpringRot = tempBlockPtr->GetRotate();

                        isSpring_ = true;

                        //jumpValue = 0.f;
                    }
                }
            }

            // ���[�J���ϐ�
            bool isWoodenSetPosLater{}; // ���W�ϊ�����ɍs�����ǂ����̔���l
            YMath::Vector2 woodenBoxPos{}; // ���W�ϊ��𓖂��蔻��̌�ɍs���ۂ̎Q�ƒl
            // �ؔ�
            if (tempBlockPtr->GetType() == IBlock::Type::WOODEN) {
                if (CheckHit(GetPos().x_, GetRadius().x_, 0, tempBlockPtr->GetPos().x_, tempBlockPtr->GetRadius().x_ + 3) &&
                    CheckHit(GetPos().y_, GetRadius().y_, 0, tempBlockPtr->GetPos().y_, tempBlockPtr->GetRadius().y_ - 1)) {
                    if (keysPtr_->IsTrigger(DIK_E)) {
                        isCarryWoodenBox_ ?
                            isCarryWoodenBox_ = false :
                            isCarryWoodenBox_ = true;
                    }

                    if (isCarryWoodenBox_) {
                        // player��x���ɂ����āA�ؔ���荶���ɂ���Ȃ��
                        if (GetPos().x_ < tempBlockPtr->GetPos().x_) {
                            // ����vel�̒l�������ǂ���Ȃ̂�
                            if (vel.x_ > 0.f) tempBlockPtr->SetPos(tempBlockPtr->GetPos() + vel);
                            else {
                                woodenBoxPos = tempBlockPtr->GetPos() + vel;
                                isWoodenSetPosLater = true;
                            }
                        }
                        // �E���ɂ���Ȃ�
                        else {
                            // ����vel�̒l�������ǂ���Ȃ̂�
                            if (vel.x_ < 0.f) tempBlockPtr->SetPos(tempBlockPtr->GetPos() + vel);
                            else {
                                woodenBoxPos = tempBlockPtr->GetPos() + vel;
                                isWoodenSetPosLater = true;
                            }
                        }
                    }
                }
                else {
                    isCarryWoodenBox_ = false;
                }
            }

            // �S�[��
            if (tempBlockPtr->GetType() == IBlock::Type::GOAL) {
                stagePtr_->SetIsGoal(true);
            }

            // �u���b�N�ɂ߂荞�񂾃s�N�Z���l
            float surplus{};

            // y������
            if (CheckHit(GetPos().x_, GetRadius().x_, 0, tempBlockPtr->GetPos().x_, tempBlockPtr->GetRadius().x_)) {
                if (CheckHit(GetPos().y_, GetRadius().y_, vel.y_, tempBlockPtr->GetPos().y_, tempBlockPtr->GetRadius().y_, surplus)) {
                    //�V��ɓ�����������
                    if (GetPos().y_ - GetRadius().y_ + vel.y_ > tempBlockPtr->GetPos().y_ - tempBlockPtr->GetRadius().y_) {
                        //���̒��ŃW�����v�ʂ�0�ɂ���ƓV��ɂԂ������u�ԗ�����
                        jumpValue = 0.f;
                        nowVel = { 0,0 };
                    }
                    vel.y_ < 0 ? vel.y_ -= surplus : vel.y_ += surplus;
                }
            }

            // x������
            if (CheckHit(GetPos().y_, GetRadius().y_, 0, tempBlockPtr->GetPos().y_, tempBlockPtr->GetRadius().y_)) {
                if (CheckHit(GetPos().x_, GetRadius().x_, vel.x_, tempBlockPtr->GetPos().x_, tempBlockPtr->GetRadius().x_, surplus)) {
                    vel.x_ < 0 ? vel.x_ -= surplus : vel.x_ += surplus;
                }
            }

            if (tempBlockPtr->GetType() == IBlock::Type::WOODEN && isWoodenSetPosLater) tempBlockPtr->SetPos(tempBlockPtr->GetPos() + vel);
        }
    }
}

bool Player::CheckHit(float pos, float radius, float vel, float blockpos, float blockradius)
{
    // �l��0�����Ȃ�߂荞��ł�B
    return std::abs(pos - blockpos + vel) - (radius + blockradius) < 0;
}

bool Player::CheckHit(float pos, float radius, float vel, float blockpos, float blockradius, float& surplus)
{
    surplus = std::abs(pos - blockpos + vel) - (radius + blockradius);

    // �l��0�����Ȃ�߂荞��ł�B
    return surplus < 0;
}

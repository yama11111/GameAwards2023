#include "Player.h"
#include <cmath>

Player::Player(Stage* stagePtr) :
    stagePtr_(stagePtr), radius_(defaultWidth_, defaultHeight_), keysPtr_(YInput::Keys::GetInstance())
{
    transform_.Initialize({ YMath::Vector3{0,0,0},YMath::Vector3{0,0,0},YMath::Vector3{1,1, 1} });
    pDrawer_.Initialize(&transform_, &direction_);
}

void Player::Update(void)
{
    Move();

    transform_.UpdateMatrix();
    pDrawer_.Update();
    //if (pos_.y > 600)pos_.y = 0;
}

void Player::Draw(void)
{
    pDrawer_.Draw();
}

void Player::Move(void)
{
    // �ړ���
    YMath::Vector2 vel{};

    // x��
    // ���E���͂̔���ƈړ��ʉ��Z
    vel.x_ += (keysPtr_->IsDown(DIK_D) - keysPtr_->IsDown(DIK_A)) * moveSpeed_;
    //vel.y += (KEY::IsDown(KEY_INPUT_S) - KEY::IsDown(KEY_INPUT_W)) * moveSpeed_;

    // y��
    // �W�����v����
    Jump(vel);
    // �d��
    vel.y_ += gravity_;

    //vel = vel.normalize();

    // �ړ��ʕ␳
    Collision(vel);

    // �␳�ς̈ړ��ʂ�pos�ɉ��Z
    YMath::Vector2 pos{ GetPos() + vel };
    SetPos(pos);

    // transform���X�V
    transform_.pos_ = { pos.x_,pos.y_,0 };

    if (vel.x_ != 0.f) direction_ = { vel.x_, 0, 0 };
}

void Player::Jump(YMath::Vector2& vel)
{
    static float jumpValue{ 0.f };

    // �g���K�[�ŃW�����v
    if (keysPtr_->IsTrigger(DIK_SPACE) && isJump_ == false) {
        isJump_ = true;
        jumpValue += jumpPower_;
    }

    // vel�ɃW�����v��(y���ړ���)�����Z
    vel.y_ -= jumpValue;
    if (jumpValue > 0.f) {
        jumpValue -= fallValue_;
    }
    else if (jumpValue <= 0.f) {
        isJump_ = false;
    }

    // 0�����̒l�ɂȂ�Ȃ��B
    jumpValue = (std::max)(jumpValue, 0.f);
}

void Player::Collision(YMath::Vector2& vel)
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

            if (tempBlockPtr->GetType() == IBlock::Type::SPRING) {

            }

            // �u���b�N�ɂ߂荞�񂾃s�N�Z���l
            float surplus{};

            // y������
            if (CheckHit(GetPos().x_, GetRadius().x_, 0, tempBlockPtr->GetPos().x_, tempBlockPtr->GetRadius().x_)) {
                if (CheckHit(GetPos().y_, GetRadius().y_, vel.y_, tempBlockPtr->GetPos().y_, tempBlockPtr->GetRadius().y_, surplus)) {
                    vel.y_ > 0 ? vel.y_ += surplus : vel.y_ -= surplus;
                }
            }

            // x������
            if (CheckHit(GetPos().y_, GetRadius().y_, 0, tempBlockPtr->GetPos().y_, tempBlockPtr->GetRadius().y_)) {
                if (CheckHit(GetPos().x_, GetRadius().x_, vel.x_, tempBlockPtr->GetPos().x_, tempBlockPtr->GetRadius().x_, surplus)) {
                    vel.x_ > 0 ? vel.x_ += surplus : vel.x_ -= surplus;
                }
            }
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

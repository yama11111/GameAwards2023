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
    // 移動量
    YMath::Vector2 vel{};

    // x軸
    // 左右入力の判定と移動量加算
    vel.x_ += (keysPtr_->IsDown(DIK_D) - keysPtr_->IsDown(DIK_A)) * moveSpeed_;
    //vel.y += (KEY::IsDown(KEY_INPUT_S) - KEY::IsDown(KEY_INPUT_W)) * moveSpeed_;

    // y軸
    // ジャンプ処理
    Jump(vel);
    // 重力
    vel.y_ += gravity_;

    //vel = vel.normalize();

    // 移動量補正
    Collision(vel);

    // 補正済の移動量をposに加算
    YMath::Vector2 pos{ GetPos() + vel };
    SetPos(pos);

    // transformを更新
    transform_.pos_ = { pos.x_,pos.y_,0 };

    if (vel.x_ != 0.f) direction_ = { vel.x_, 0, 0 };
}

void Player::Jump(YMath::Vector2& vel)
{
    static float jumpValue{ 0.f };

    // トリガーでジャンプ
    if (keysPtr_->IsTrigger(DIK_SPACE) && isJump_ == false) {
        isJump_ = true;
        jumpValue += jumpPower_;
    }

    // velにジャンプ量(y軸移動量)を加算
    vel.y_ -= jumpValue;
    if (jumpValue > 0.f) {
        jumpValue -= fallValue_;
    }
    else if (jumpValue <= 0.f) {
        isJump_ = false;
    }

    // 0未満の値にならない。
    jumpValue = (std::max)(jumpValue, 0.f);
}

void Player::Collision(YMath::Vector2& vel)
{
    for (size_t i = 0; i < stagePtr_->GetPieceVectorPtr()->size(); i++) {
        // 該当Pieceが操作されている場合スキップ
        if (stagePtr_->GetPieceVectorPtr()->at(i)->GetOperator()) continue;
        // 該当Piece
        if (stagePtr_->GetPieceVectorPtr()->at(i)->GetFixity() == false) continue;

        for (size_t j = 0; j < stagePtr_->GetPieceVectorPtr()->at(i)->GetBlocksPtr()->size(); j++)
        {
            // ポインタを確保してgetter関数呼び出し抑制
            IBlock* tempBlockPtr{ stagePtr_->GetPieceVectorPtr()->at(i)->GetBlocksPtr()->at(j).get() };

            // X軸,Y軸で3ブロック範囲内ではない場合、スキップ
            if (std::abs(tempBlockPtr->GetPos().x_ - GetPos().x_) > IBlock::radiusBase_ * 6) continue;
            if (std::abs(tempBlockPtr->GetPos().y_ - GetPos().y_) > IBlock::radiusBase_ * 6) continue;

            // ブロックの種類が PIECEENTRANCEBLOCK である場合
            if (tempBlockPtr->GetType() == IBlock::Type::PIECEENTRANCE) {
                // プレイヤーがブロックの中央に触れるか
                if (CheckHit(GetPos().x_, GetRadius().x_, 0, tempBlockPtr->GetPos().x_, 8) &&
                    CheckHit(GetPos().y_, GetRadius().y_, 0, tempBlockPtr->GetPos().y_, 8)) {
                    if (stagePtr_->GetPieceVectorPtr()->at(i)->GetState() == Piece::State::MOVABLE) stagePtr_->GetPieceVectorPtr()->at(i)->SetState(Piece::State::IMMUTABLE);
                }

                if (tempBlockPtr->GetEntranceOpen())
                    continue;
            }

            if (tempBlockPtr->GetType() == IBlock::Type::SPRING) {

            }

            // ブロックにめり込んだピクセル値
            float surplus{};

            // y軸方向
            if (CheckHit(GetPos().x_, GetRadius().x_, 0, tempBlockPtr->GetPos().x_, tempBlockPtr->GetRadius().x_)) {
                if (CheckHit(GetPos().y_, GetRadius().y_, vel.y_, tempBlockPtr->GetPos().y_, tempBlockPtr->GetRadius().y_, surplus)) {
                    vel.y_ > 0 ? vel.y_ += surplus : vel.y_ -= surplus;
                }
            }

            // x軸方向
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
    // 値が0未満ならめり込んでる。
    return std::abs(pos - blockpos + vel) - (radius + blockradius) < 0;
}

bool Player::CheckHit(float pos, float radius, float vel, float blockpos, float blockradius, float& surplus)
{
    surplus = std::abs(pos - blockpos + vel) - (radius + blockradius);

    // 値が0未満ならめり込んでる。
    return surplus < 0;
}

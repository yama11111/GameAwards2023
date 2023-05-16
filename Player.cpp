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
    // 移動量
    YMath::Vector2 vel{};

    // x軸
    // 左右入力の判定と移動量加算
    vel.x_ += (keysPtr_->IsDown(DIK_D) - keysPtr_->IsDown(DIK_A)) * moveSpeed_;
    //vel.y += (KEY::IsDown(KEY_INPUT_S) - KEY::IsDown(KEY_INPUT_W)) * moveSpeed_;

    static float jumpValue{ 0.f };
    // y軸
    // ジャンプ処理
    Jump(vel, jumpValue);

    // バネ処理
    Spring(vel, nowSpringRot);

    // 重力
    vel.y_ -= gravity_;

    //vel = vel.normalize();

    // 移動量補正
    Collision(vel, jumpValue);

    // 補正済の移動量をposに加算
    YMath::Vector2 pos{ GetPos() + vel };
    SetPos(pos);

    // transformを更新
    transform_.pos_ = { pos.x_,pos.y_,0 };

    if (vel.x_ != 0.f) direction_ = { vel.x_, 0, 0 };
}

void Player::Jump(YMath::Vector2& vel, float& jumpValue)
{
    // トリガーでジャンプ
    if (keysPtr_->IsTrigger(DIK_SPACE) && isJump_ == false) {
        isJump_ = true;
        jumpValue += jumpPower_;
    }

    // velにジャンプ量(y軸移動量)を加算
    vel.y_ += jumpValue;
    if (jumpValue > 0.f) {
        jumpValue -= fallValue_;
    }
    else if (jumpValue <= 0.f) {
        isJump_ = false;
    }

    // 0未満の値にならない。
    jumpValue = (std::max)(jumpValue, 0.f);
}

void Player::Spring(YMath::Vector2& vel, int rot)
{
    //trueじゃなければ抜ける
    if (!isSpring_ && nowVel.x_ == 0 && nowVel.y_ == 0)
    {
        nowSpringRot = 0;
        return;
    }

    //ジャンプ防止
    isJump_ = true;

    //回転角
    int rot_ = rot;

    if (isSpring_)
    {
        //90度ごとに
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
        //90度ごとに
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

            // バネブロック処理
            if (tempBlockPtr->GetType() == IBlock::Type::SPRING) {

                int sizex = defaultHeight_ + 1;
                int sizey = 1;

                int sizeX = 0;
                int sizeY = 0;

                //90度ごとに
                switch (tempBlockPtr->GetRotate() / 90)
                {
                case 0://上

                    sizex = 0;
                    sizeX = defaultHeight_;
                    sizey = defaultHeight_;
                    sizey = sizey * -1;
                    sizeY = 1;

                    break;
                case 1://右

                    sizex = defaultHeight_;
                    sizeX = 1;
                    sizey = 0;
                    sizeY = defaultHeight_;

                    break;
                case 2://下

                    sizex = 0;
                    sizeX = defaultHeight_;
                    sizey = defaultHeight_;
                    sizeY = 1;

                    break;
                case 3://左

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

            // ローカル変数
            bool isWoodenSetPosLater{}; // 座標変換を後に行うかどうかの判定値
            YMath::Vector2 woodenBoxPos{}; // 座標変換を当たり判定の後に行う際の参照値
            // 木箱
            if (tempBlockPtr->GetType() == IBlock::Type::WOODEN) {
                if (CheckHit(GetPos().x_, GetRadius().x_, 0, tempBlockPtr->GetPos().x_, tempBlockPtr->GetRadius().x_ + 3) &&
                    CheckHit(GetPos().y_, GetRadius().y_, 0, tempBlockPtr->GetPos().y_, tempBlockPtr->GetRadius().y_ - 1)) {
                    if (keysPtr_->IsTrigger(DIK_E)) {
                        isCarryWoodenBox_ ?
                            isCarryWoodenBox_ = false :
                            isCarryWoodenBox_ = true;
                    }

                    if (isCarryWoodenBox_) {
                        // playerがx軸において、木箱より左側にいるならば
                        if (GetPos().x_ < tempBlockPtr->GetPos().x_) {
                            // かつvelの値が正負どちらなのか
                            if (vel.x_ > 0.f) tempBlockPtr->SetPos(tempBlockPtr->GetPos() + vel);
                            else {
                                woodenBoxPos = tempBlockPtr->GetPos() + vel;
                                isWoodenSetPosLater = true;
                            }
                        }
                        // 右側にいるなら
                        else {
                            // かつvelの値が正負どちらなのか
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

            // ゴール
            if (tempBlockPtr->GetType() == IBlock::Type::GOAL) {
                stagePtr_->SetIsGoal(true);
            }

            // ブロックにめり込んだピクセル値
            float surplus{};

            // y軸方向
            if (CheckHit(GetPos().x_, GetRadius().x_, 0, tempBlockPtr->GetPos().x_, tempBlockPtr->GetRadius().x_)) {
                if (CheckHit(GetPos().y_, GetRadius().y_, vel.y_, tempBlockPtr->GetPos().y_, tempBlockPtr->GetRadius().y_, surplus)) {
                    //天井に当たった処理
                    if (GetPos().y_ - GetRadius().y_ + vel.y_ > tempBlockPtr->GetPos().y_ - tempBlockPtr->GetRadius().y_) {
                        //この中でジャンプ量を0にすると天井にぶつかった瞬間落ちる
                        jumpValue = 0.f;
                        nowVel = { 0,0 };
                    }
                    vel.y_ < 0 ? vel.y_ -= surplus : vel.y_ += surplus;
                }
            }

            // x軸方向
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
    // 値が0未満ならめり込んでる。
    return std::abs(pos - blockpos + vel) - (radius + blockradius) < 0;
}

bool Player::CheckHit(float pos, float radius, float vel, float blockpos, float blockradius, float& surplus)
{
    surplus = std::abs(pos - blockpos + vel) - (radius + blockradius);

    // 値が0未満ならめり込んでる。
    return surplus < 0;
}

#include "PlayScene.h"
#include "SceneExecutive.h"
#include "MathUtillity.h"
#include "CalcTransform.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>
#include "Sign.h"

#include "DrawerHelper.h"
#include "MouseCollider.h"
#include "LevelData.h"

#pragma region 名前空間宣言

using YScene::PlayScene;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;
using Sign = maruyama::Sign;

#pragma endregion 


#pragma region Static関連

#pragma endregion 


#pragma region 読み込み

void PlayScene::Load()
{
    // ----- オーディオ ----- //

    // プレイBGM
    pPlayBGM_ = Audio::Load("BGM/select.wav");

    // ----- 静的初期化 ----- //

    // マウスコライダー静的初期化
    MouseColliderCommon::StaticInitialize();

    // マウスコライダーにビュープロジェクション設定
    MouseColliderCommon::StaticSetViewProjectionPointer(&transferVP_);

    // パーティクル
    ParticleManager::StaticInitialize(&transferVP_);

    // 描画クラス全て
    DrawerHelper::StaticInitialize(&transferVP_, &camera_, &particleMan_);

    // オブジェクト
    IObject::StaticInitialize(&sign_);

    // プレイヤー
    Player::StaticInitialize();

    // ブロック
    Block::StaticInitialize();
}

#pragma endregion


#pragma region 初期化

void PlayScene::Initialize()
{
    // パーティクル初期化
    particleMan_.Initialize();

    // ステージ番号
    size_t stageIdx = static_cast<size_t>(StageConfig::GetInstance()->GetCurrentStageIndex());

    sign_.Initialize({ 20,20 });
    sign_.ReWriteBlock(1, 14, Sign::BlockType::BASIC);
    sign_.ReWriteBlock(2, 14, Sign::BlockType::BASIC);
    sign_.ReWriteBlock(3, 14, Sign::BlockType::BASIC);
    sign_.ReWriteBlock(4, 14, Sign::BlockType::BASIC);
    sign_.ReWriteBlock(5, 14, Sign::BlockType::BASIC);
    sign_.ReWriteBlock(7, 18, Sign::BlockType::BASIC);
    sign_.ReWriteBlock(8, 17, Sign::BlockType::BASIC);
    sign_.ReWriteBlock(9, 16, Sign::BlockType::BASIC);
    sign_.ReWriteBlock(10, 15, Sign::BlockType::BASIC);

    //stage_.RegisterEntity(player_.get());
    //maruyama::Sign* sign1ptr = new maruyama::Sign;
    //sign1ptr->Initialize({ 20,20 });
    //sign1ptr->ReWriteBlock(1, 14, Sign::BlockType::BASIC);
    //sign1ptr->ReWriteBlock(2, 14, Sign::BlockType::BASIC);
    //sign1ptr->ReWriteBlock(3, 14, Sign::BlockType::BASIC);
    //sign1ptr->ReWriteBlock(4, 14, Sign::BlockType::BASIC);
    //sign1ptr->ReWriteBlock(5, 14, Sign::BlockType::BASIC);
    //sign1ptr->ReWriteBlock(7, 18, Sign::BlockType::BASIC);
    //sign1ptr->ReWriteBlock(8, 17, Sign::BlockType::BASIC);
    //sign1ptr->ReWriteBlock(9, 16, Sign::BlockType::BASIC);
    //sign1ptr->ReWriteBlock(10, 15, Sign::BlockType::BASIC);
    //stage_.RegisterSign(sign1ptr);

    // オブジェクト
    {
        // オブジェクトマネージャー初期化
        objMan_.Initialize();

        // インデックス
        size_t index = stageIdx - 1;

        // プレイヤー
        {
            // プレイヤー生成
            player_ = std::make_unique<Player>();

            // プレイヤー初期化
            player_->Initialize(
                LevelData::Player::InitStatuses[index].signIndex_,
                {
                    LevelData::Player::InitStatuses[index].pos_.x_,
                    LevelData::Player::InitStatuses[index].pos_.y_,
                    0.0f
                });

            // 挿入
            objMan_.PushBack(player_.get());
        }

        // ブロック
        {
            for (size_t i = 0; i < LevelData::Block::InitStatuses[index].size(); i++)
            {
                // インスタンス生成
                std::unique_ptr<Block> newBlock = std::make_unique<Block>();

                // 初期化
                newBlock->Initialize(
                    LevelData::Block::InitStatuses[index][i].signIndex_,
                    {
                        LevelData::Block::InitStatuses[index][i].pos_.x_,
                        LevelData::Block::InitStatuses[index][i].pos_.y_,
                        0.0f,
                    });

                // 挿入
                objMan_.PushBack(newBlock.get());

                // 挿入
                blocks_.push_back(std::move(newBlock));
            }
        }

        // ばね
        {
            for (size_t i = 0; i < LevelData::Spring::InitStatuses[index].size(); i++)
            {
                // インスタンス生成
                std::unique_ptr<Spring> newSpring = std::make_unique<Spring>();

                // 初期化
                newSpring->Initialize(
                    LevelData::Spring::InitStatuses[index][i].signIndex_,
                    {
                        LevelData::Spring::InitStatuses[index][i].pos_.x_,
                        LevelData::Spring::InitStatuses[index][i].pos_.y_,
                        0.0f,
                    },
                    LevelData::Spring::InitStatuses[index][i].jumpPowar_);

                // 挿入
                objMan_.PushBack(newSpring.get());

                // 挿入
                springs_.push_back(std::move(newSpring));
            }
        }

        // 足場
        {
            for (size_t i = 0; i < LevelData::Platform::InitStatuses[index].size(); i++)
            {
                // インスタンス生成
                std::unique_ptr<Platform> newPlatform = std::make_unique<Platform>();

                // 初期化
                newPlatform->Initialize(
                    LevelData::Platform::InitStatuses[index][i].signIndex_,
                    {
                        LevelData::Platform::InitStatuses[index][i].pos_.x_,
                        LevelData::Platform::InitStatuses[index][i].pos_.y_,
                        0.0f,
                    },
                    LevelData::Platform::InitStatuses[index][i].length_);

                // 挿入
                objMan_.PushBack(newPlatform.get());

                // 挿入
                platforms_.push_back(std::move(newPlatform));
            }
        }

        // レーザー
        {
            for (size_t i = 0; i < LevelData::Laser::InitStatuses[index].size(); i++)
            {
                // インスタンス生成
                std::unique_ptr<Laser> newLaser = std::make_unique<Laser>();

                // 初期化
                newLaser->Initialize(
                    LevelData::Laser::InitStatuses[index][i].signIndex_,
                    {
                        LevelData::Laser::InitStatuses[index][i].pos_.x_,
                        LevelData::Laser::InitStatuses[index][i].pos_.y_,
                        0.0f,
                    },
                    {
                        LevelData::Laser::InitStatuses[index][i].direction_.x_,
                        LevelData::Laser::InitStatuses[index][i].direction_.y_,
                        0.0f,
                    },
                    LevelData::Laser::InitStatuses[index][i].length_);

                // 挿入
                objMan_.PushBack(newLaser.get());

                // 挿入
                lasers_.push_back(std::move(newLaser));
            }
        }

        // スイッチ
        {
            for (size_t i = 0; i < LevelData::Switch::InitStatuses[index].size(); i++)
            {
                // インスタンス生成
                std::unique_ptr<Switch> newSwitch = std::make_unique<Switch>();

                // 初期化
                newSwitch->Initialize(
                    LevelData::Switch::InitStatuses[index][i].signIndex_,
                    {
                        LevelData::Switch::InitStatuses[index][i].pos_.x_,
                        LevelData::Switch::InitStatuses[index][i].pos_.y_,
                        0.0f,
                    },
                    LevelData::Switch::InitStatuses[index][i].isAct_);

                // 挿入
                objMan_.PushBack(newSwitch.get());

                // 挿入
                switches_.push_back(std::move(newSwitch));
            }
        }

        // 鍵
        {
            for (size_t i = 0; i < LevelData::Key::InitStatuses[index].size(); i++)
            {
                // インスタンス生成
                std::unique_ptr<Key> newKey = std::make_unique<Key>();

                // 初期化
                newKey->Initialize(
                    LevelData::Key::InitStatuses[index][i].signIndex_,
                    {
                        LevelData::Key::InitStatuses[index][i].pos_.x_,
                        LevelData::Key::InitStatuses[index][i].pos_.y_,
                        0.0f,
                    });

                // 挿入
                objMan_.PushBack(newKey.get());

                // 挿入
                keys_.push_back(std::move(newKey));
            }
        }

        // ゴール
        {
            // ゴール生成
            goal_ = std::make_unique<Goal>();

            // ゴール初期化
            goal_->Initialize(
                LevelData::Goal::InitStatuses[index].signIndex_,
                {
                    LevelData::Goal::InitStatuses[index].pos_.x_,
                    LevelData::Goal::InitStatuses[index].pos_.y_,
                    0.0f
                },
                LevelData::Goal::InitStatuses[index].isRock_);

            // 挿入
            objMan_.PushBack(goal_.get());
        }
    }

    // 背景初期化
    background_.Initialize();

    // HUD初期化
    hud_.Initialize();


    // カメラ
    camera_.Initialize({ +10.0f,-20.0f,-80.0f }, {});

    // ビュープロジェクション初期化
    transferVP_.Initialize();

    // ビュープロジェクションにカメラ代入
    transferVP_ = camera_.GetViewProjection();


    // プレイBGM開始
    //pPlayBGM_->Play(true);
}

#pragma endregion


#pragma region 終了処理

void PlayScene::Finalize()
{
    // プレイBGM停止
    pPlayBGM_->Stop();
}

#pragma endregion


#pragma region 更新

void PlayScene::Update()
{
    // マウスコライダー静的更新
    MouseColliderCommon::StaticUpdate();

    // 入力描画静的更新
    InputDrawerCommon::StaticUpdate();

    // カメラ位置更新
    CameraUpdate();

    // HUD更新
    hud_.Update();

    // ポーズ中なら弾く
    if (hud_.IsElderPause()) { return; }

    // ------------ ↓ プレイシーンの処理 ↓ ------------//

    sign_.Update();
    //stage_.Update();

    // ------------ ↑ プレイシーンの処理 ↑ ------------//

    // オブジェクトマネージャー更新
    objMan_.Update();

    // 背景更新
    background_.Update();

    // DrawerHelper更新
    DrawerHelper::StaticUpdate();


    // パーティクル更新
    particleMan_.Update();


    // カメラ更新
    camera_.Update();

    // ビュープロジェクションにカメラ代入
    transferVP_ = camera_.GetViewProjection();

    // ビュープロジェクション
    transferVP_.UpdateMatrix();

    //ゴール判定
    //if ()
    //{
    //	StageConfig::GetInstance()->ClearStage(StageConfig::GetInstance()->GetCurrentStageIndex() - 1);
    //	SceneExecutive::GetInstance()->Change("SELECT", "INFECTION", 5, 10);
    //}

    // リセット
    if (sKeys_->IsTrigger(DIK_R))
    {
        SceneManager::GetInstance()->Change("PLAY");
    }

}
#pragma endregion


#pragma region 描画

void PlayScene::Draw()
{
    // 背景描画
    background_.Draw();

    // ------------ ↓ プレイシーンの描画 ↓ ------------//

    sign_.Draw();
    //stage_.Draw();

    // ------------ ↑ プレイシーンの描画 ↑ ------------//

    // オブジェクト描画
    objMan_.Draw();

    // HUD描画
    hud_.Draw();

    // パーティクル描画
    particleMan_.Draw();
}

void PlayScene::CameraUpdate()
{
    static const float sCameraMoveSpeed = 1.0f;
    static const float sCameraMoveValue = 5.0f;

    if (sMouse_->IsDown(MouseClick::DIM_MIDDLE))
    {
        bool isMoveR = (sMouse_->Pos().x_ - sMouse_->Pos(When::Elder).x_) >= +sCameraMoveValue;
        bool isMoveL = (sMouse_->Pos().x_ - sMouse_->Pos(When::Elder).x_) <= -sCameraMoveValue;
        bool isMoveT = (sMouse_->Pos().y_ - sMouse_->Pos(When::Elder).y_) >= +sCameraMoveValue;
        bool isMoveB = (sMouse_->Pos().y_ - sMouse_->Pos(When::Elder).y_) <= -sCameraMoveValue;

        camera_.pos_.x_ += sCameraMoveSpeed * static_cast<float>(isMoveL - isMoveR);
        camera_.pos_.y_ += sCameraMoveSpeed * static_cast<float>(isMoveT - isMoveB);
    }

    static const float sCameraScrollSpeed = 3.0f;

    if (sMouse_->ScrollValue() > 0.0f) { camera_.pos_.z_ += sCameraScrollSpeed; }
    if (sMouse_->ScrollValue() < 0.0f) { camera_.pos_.z_ -= sCameraScrollSpeed; }
}

#pragma endregion
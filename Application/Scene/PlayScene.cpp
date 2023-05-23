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

#pragma region ���O��Ԑ錾

using YScene::PlayScene;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;
using Sign = maruyama::Sign;

#pragma endregion 


#pragma region Static�֘A

#pragma endregion 


#pragma region �ǂݍ���

void PlayScene::Load()
{
    // ----- �I�[�f�B�I ----- //

    // �v���CBGM
    pPlayBGM_ = Audio::Load("BGM/select.wav");

    // ----- �ÓI������ ----- //

    // �}�E�X�R���C�_�[�ÓI������
    MouseColliderCommon::StaticInitialize();

    // �}�E�X�R���C�_�[�Ƀr���[�v���W�F�N�V�����ݒ�
    MouseColliderCommon::StaticSetViewProjectionPointer(&transferVP_);

    // �p�[�e�B�N��
    ParticleManager::StaticInitialize(&transferVP_);

    // �`��N���X�S��
    DrawerHelper::StaticInitialize(&transferVP_, &camera_, &particleMan_);

    // �I�u�W�F�N�g
    IObject::StaticInitialize(&sign_);

    // �v���C���[
    Player::StaticInitialize();

    // �u���b�N
    Block::StaticInitialize();
}

#pragma endregion


#pragma region ������

void PlayScene::Initialize()
{
    // �p�[�e�B�N��������
    particleMan_.Initialize();

    // �X�e�[�W�ԍ�
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

    // �I�u�W�F�N�g
    {
        // �I�u�W�F�N�g�}�l�[�W���[������
        objMan_.Initialize();

        // �C���f�b�N�X
        size_t index = stageIdx - 1;

        // �v���C���[
        {
            // �v���C���[����
            player_ = std::make_unique<Player>();

            // �v���C���[������
            player_->Initialize(
                LevelData::Player::InitStatuses[index].signIndex_,
                {
                    LevelData::Player::InitStatuses[index].pos_.x_,
                    LevelData::Player::InitStatuses[index].pos_.y_,
                    0.0f
                });

            // �}��
            objMan_.PushBack(player_.get());
        }

        // �u���b�N
        {
            for (size_t i = 0; i < LevelData::Block::InitStatuses[index].size(); i++)
            {
                // �C���X�^���X����
                std::unique_ptr<Block> newBlock = std::make_unique<Block>();

                // ������
                newBlock->Initialize(
                    LevelData::Block::InitStatuses[index][i].signIndex_,
                    {
                        LevelData::Block::InitStatuses[index][i].pos_.x_,
                        LevelData::Block::InitStatuses[index][i].pos_.y_,
                        0.0f,
                    });

                // �}��
                objMan_.PushBack(newBlock.get());

                // �}��
                blocks_.push_back(std::move(newBlock));
            }
        }

        // �΂�
        {
            for (size_t i = 0; i < LevelData::Spring::InitStatuses[index].size(); i++)
            {
                // �C���X�^���X����
                std::unique_ptr<Spring> newSpring = std::make_unique<Spring>();

                // ������
                newSpring->Initialize(
                    LevelData::Spring::InitStatuses[index][i].signIndex_,
                    {
                        LevelData::Spring::InitStatuses[index][i].pos_.x_,
                        LevelData::Spring::InitStatuses[index][i].pos_.y_,
                        0.0f,
                    },
                    LevelData::Spring::InitStatuses[index][i].jumpPowar_);

                // �}��
                objMan_.PushBack(newSpring.get());

                // �}��
                springs_.push_back(std::move(newSpring));
            }
        }

        // ����
        {
            for (size_t i = 0; i < LevelData::Platform::InitStatuses[index].size(); i++)
            {
                // �C���X�^���X����
                std::unique_ptr<Platform> newPlatform = std::make_unique<Platform>();

                // ������
                newPlatform->Initialize(
                    LevelData::Platform::InitStatuses[index][i].signIndex_,
                    {
                        LevelData::Platform::InitStatuses[index][i].pos_.x_,
                        LevelData::Platform::InitStatuses[index][i].pos_.y_,
                        0.0f,
                    },
                    LevelData::Platform::InitStatuses[index][i].length_);

                // �}��
                objMan_.PushBack(newPlatform.get());

                // �}��
                platforms_.push_back(std::move(newPlatform));
            }
        }

        // ���[�U�[
        {
            for (size_t i = 0; i < LevelData::Laser::InitStatuses[index].size(); i++)
            {
                // �C���X�^���X����
                std::unique_ptr<Laser> newLaser = std::make_unique<Laser>();

                // ������
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

                // �}��
                objMan_.PushBack(newLaser.get());

                // �}��
                lasers_.push_back(std::move(newLaser));
            }
        }

        // �X�C�b�`
        {
            for (size_t i = 0; i < LevelData::Switch::InitStatuses[index].size(); i++)
            {
                // �C���X�^���X����
                std::unique_ptr<Switch> newSwitch = std::make_unique<Switch>();

                // ������
                newSwitch->Initialize(
                    LevelData::Switch::InitStatuses[index][i].signIndex_,
                    {
                        LevelData::Switch::InitStatuses[index][i].pos_.x_,
                        LevelData::Switch::InitStatuses[index][i].pos_.y_,
                        0.0f,
                    },
                    LevelData::Switch::InitStatuses[index][i].isAct_);

                // �}��
                objMan_.PushBack(newSwitch.get());

                // �}��
                switches_.push_back(std::move(newSwitch));
            }
        }

        // ��
        {
            for (size_t i = 0; i < LevelData::Key::InitStatuses[index].size(); i++)
            {
                // �C���X�^���X����
                std::unique_ptr<Key> newKey = std::make_unique<Key>();

                // ������
                newKey->Initialize(
                    LevelData::Key::InitStatuses[index][i].signIndex_,
                    {
                        LevelData::Key::InitStatuses[index][i].pos_.x_,
                        LevelData::Key::InitStatuses[index][i].pos_.y_,
                        0.0f,
                    });

                // �}��
                objMan_.PushBack(newKey.get());

                // �}��
                keys_.push_back(std::move(newKey));
            }
        }

        // �S�[��
        {
            // �S�[������
            goal_ = std::make_unique<Goal>();

            // �S�[��������
            goal_->Initialize(
                LevelData::Goal::InitStatuses[index].signIndex_,
                {
                    LevelData::Goal::InitStatuses[index].pos_.x_,
                    LevelData::Goal::InitStatuses[index].pos_.y_,
                    0.0f
                },
                LevelData::Goal::InitStatuses[index].isRock_);

            // �}��
            objMan_.PushBack(goal_.get());
        }
    }

    // �w�i������
    background_.Initialize();

    // HUD������
    hud_.Initialize();


    // �J����
    camera_.Initialize({ +10.0f,-20.0f,-80.0f }, {});

    // �r���[�v���W�F�N�V����������
    transferVP_.Initialize();

    // �r���[�v���W�F�N�V�����ɃJ�������
    transferVP_ = camera_.GetViewProjection();


    // �v���CBGM�J�n
    //pPlayBGM_->Play(true);
}

#pragma endregion


#pragma region �I������

void PlayScene::Finalize()
{
    // �v���CBGM��~
    pPlayBGM_->Stop();
}

#pragma endregion


#pragma region �X�V

void PlayScene::Update()
{
    // �}�E�X�R���C�_�[�ÓI�X�V
    MouseColliderCommon::StaticUpdate();

    // ���͕`��ÓI�X�V
    InputDrawerCommon::StaticUpdate();

    // �J�����ʒu�X�V
    CameraUpdate();

    // HUD�X�V
    hud_.Update();

    // �|�[�Y���Ȃ�e��
    if (hud_.IsElderPause()) { return; }

    // ------------ �� �v���C�V�[���̏��� �� ------------//

    sign_.Update();
    //stage_.Update();

    // ------------ �� �v���C�V�[���̏��� �� ------------//

    // �I�u�W�F�N�g�}�l�[�W���[�X�V
    objMan_.Update();

    // �w�i�X�V
    background_.Update();

    // DrawerHelper�X�V
    DrawerHelper::StaticUpdate();


    // �p�[�e�B�N���X�V
    particleMan_.Update();


    // �J�����X�V
    camera_.Update();

    // �r���[�v���W�F�N�V�����ɃJ�������
    transferVP_ = camera_.GetViewProjection();

    // �r���[�v���W�F�N�V����
    transferVP_.UpdateMatrix();

    //�S�[������
    //if ()
    //{
    //	StageConfig::GetInstance()->ClearStage(StageConfig::GetInstance()->GetCurrentStageIndex() - 1);
    //	SceneExecutive::GetInstance()->Change("SELECT", "INFECTION", 5, 10);
    //}

    // ���Z�b�g
    if (sKeys_->IsTrigger(DIK_R))
    {
        SceneManager::GetInstance()->Change("PLAY");
    }

}
#pragma endregion


#pragma region �`��

void PlayScene::Draw()
{
    // �w�i�`��
    background_.Draw();

    // ------------ �� �v���C�V�[���̕`�� �� ------------//

    sign_.Draw();
    //stage_.Draw();

    // ------------ �� �v���C�V�[���̕`�� �� ------------//

    // �I�u�W�F�N�g�`��
    objMan_.Draw();

    // HUD�`��
    hud_.Draw();

    // �p�[�e�B�N���`��
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
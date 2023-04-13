#include "PlayScene.h"
#include "SceneManager.h"
#include "MathUtillity.h"
#include "CalcTransform.h"
#include "Def.h"
#include <cassert>
#include "imgui.h"

#include "DrawerManager.h"

#pragma region ���O��Ԑ錾
using YScene::PlayScene;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;
#pragma endregion 

#pragma region Static�֘A
#pragma endregion 

#pragma region �ǂݍ���
void PlayScene::Load()
{
	// ----- �e�N�X�`�� ----- //

	// ----- �I�[�f�B�I ----- //

	// ----- �X�v���C�g (2D) ----- //

	// ----- �X�v���C�g (3D) ----- //
	
	// ------- ���f�� ------- //

	// ----- �ÓI������ ----- //

	// �p�[�e�B�N��
	ParticleManager::StaticInitialize(&transferVP_);

	// �G�t�F�N�g
	EffectManager::StaticInitialize(&particleMan_);

	// �`��N���X�S��
	DrawerManager::StaticInitialize(&transferVP_, &particleMan_);
}
#pragma endregion


#pragma region ������
void PlayScene::Initialize()
{
	// �v���C���[���쏉����
	isPlayer_ = true;

	float scaleVal = 1.0f;
	Vector3 scale = { scaleVal,scaleVal,scaleVal };

	// ----- �v���C���[ ----- //

	// �g�����X�t�H�[�� (�ʒu�A��]�A�傫��)
	player_.Initialize({ {-50.0f,0.0f,0.0f}, {}, scale * 2.0f });
	// ����
	direction_ = { +1.0f,0.0f,0.0f };
	// �`��p�N���X������ (�e�g�����X�t�H�[���A�����A�����F)
	playerDra_.Initialize(&player_, &direction_, IDrawer::Mode::Red);
	
	
	// ----- �t�B���^�[ ----- //
	
	// �g�����X�t�H�[�� (�ʒu�A��]�A�傫��)
	filter_.Initialize({ {0.0f,0.0f,0.0f}, {}, {6.0f,4.0f,1.0f} });
	// �`��p�N���X������ (�e�g�����X�t�H�[��)
	filterDra_.Initialize(&filter_);

	
	// ----- �u���b�N ----- //
	
	for (size_t i = 0; i < idx - 1; i++)
	{
		// �g�����X�t�H�[�� (�ʒu�A��]�A�傫��)
		block_[i].Initialize({{-40.0f + scaleVal * 4.0f * i,-4.0f * scaleVal,0.0f}, {}, scale});
		// �`��p�N���X������ (�e�g�����X�t�H�[���A�����F)
		blockDra_[i].Initialize(&block_[i], IDrawer::Mode::Normal);
	}

	// �g�����X�t�H�[�� (�ʒu�A��]�A�傫��)
	block_[idx - 1].Initialize({ {0.0f,0.0f,0.0f}, {}, scale });
	// �`��p�N���X������ (�e�g�����X�t�H�[���A�����F)
	blockDra_[idx - 1].Initialize(&block_[idx - 1], IDrawer::Mode::Red);

	
	// ----- �Q�[�g ----- //
	
	// �g�����X�t�H�[�� (�ʒu�A��]�A�傫��)
	gate_.Initialize({ {-20.0f,0.0f,0.0f}, {}, scale });
	// �`��p�N���X������ (�e�g�����X�t�H�[���A�����F)
	gateDra_.Initialize(&gate_, IDrawer::Mode::Red);

	
	// ----- �S�[�� ----- //
	
	// �g�����X�t�H�[�� (�ʒu�A��]�A�傫��)
	goal_.Initialize({ {+4.0f * scaleVal,0.0f,0.0f}, {}, scale });
	// �`��p�N���X������ (�e�g�����X�t�H�[��)
	goalDra_.Initialize(&goal_);


	// �V��������
	skydome_.Initialize();
	
	// HUD������
	hud_.Initalize();

	// �p�[�e�B�N��������
	particleMan_.Initialize();

	// �X�N���[���J����
	scrollCamera_.Initialize({ 0,+10,-50 }, &player_.pos_, { 0.0f,0.0f,0.0f });

	// �r���[�v���W�F�N�V����������
	transferVP_.Initialize({});
}
#pragma endregion

#pragma region �I������
void PlayScene::Finalize()
{

}
#pragma endregion

#pragma region �X�V
void PlayScene::Update()
{
	// HUD�X�V
	hud_.Update();

	// �|�[�Y���Ȃ�e��
	if (hud_.IsPause()) { return; }


	// ����؂�ւ�
	if (sKeys_->IsTrigger(DIK_SPACE))
	{
		isPlayer_ = !isPlayer_;
		if (isPlayer_) 
		{
			hud_.SetPilot(HUDDrawerCommon::Pilot::Player);
			scrollCamera_.SetFollowPoint(&player_.pos_);
		}
		else 
		{
			hud_.SetPilot(HUDDrawerCommon::Pilot::Filter); 
			scrollCamera_.SetFollowPoint(&filter_.pos_);
		}
	}


	// �v���C���[
	if (isPlayer_)
	{
		playerSpeed_.x_ = sKeys_->Horizontal(Keys::MoveStandard::WASD) * 2.0f;

		if (sKeys_->IsTrigger(DIK_W))
		{
			playerDra_.JumpAnimation();
			playerSpeed_.y_ = 1.5f;
		}
		if (player_.pos_.y_ > 0.0f)
		{
			playerSpeed_.y_ -= 0.1f;
		}
	}

	player_.pos_ += playerSpeed_;
	if (player_.pos_.y_ < 0.0f)
	{
		playerDra_.LandingAnimation();
		playerSpeed_.y_ = 0.0f;
		player_.pos_.y_ = 0.0f;
	}

	player_.UpdateMatrix();
	
	if (sKeys_->IsTrigger(DIK_K))
	{
		playerDra_.ChangeColorAnimation(IDrawer::Mode::Normal);
	}
	if (sKeys_->IsTrigger(DIK_L))
	{
		playerDra_.ChangeColorAnimation(IDrawer::Mode::Red);
	}
	playerDra_.Update();


	// �t�B���^�[
	if (isPlayer_ == false)
	{
		filter_.pos_.x_ += sKeys_->Horizontal(Keys::MoveStandard::WASD) * 2.0f;
		filter_.pos_.y_ += sKeys_->Vertical(Keys::MoveStandard::WASD) * 2.0f;
	}

	filter_.UpdateMatrix();
	filterDra_.Update();

	// �u���b�N
	for (size_t i = 0; i < idx; i++)
	{
		block_[i].UpdateMatrix();
		blockDra_[i].Update();
	}

	// �Q�[�g
	gate_.UpdateMatrix();
	gateDra_.Update();

	// �S�[��
	goal_.UpdateMatrix();
	goalDra_.Update();

	// �V���X�V
	skydome_.Update();


	// �p�[�e�B�N���X�V
	particleMan_.Update();



	// �J�����X�V
	scrollCamera_.Update();

	// �r���[�v���W�F�N�V�����ɃJ�������
	transferVP_ = scrollCamera_.GetViewProjection();

	// �r���[�v���W�F�N�V����
	transferVP_.UpdateMatrix();


	// ���̃V�[����
	if (sKeys_->IsTrigger(DIK_0))
	{
		SceneManager::GetInstance()->Change("RESULT", "INFECTION");
	}
}
#pragma endregion


#pragma region �`��
void PlayScene::DrawBackSprite2Ds()
{
	
}

void PlayScene::DrawModels()
{
	// �V���`��
	skydome_.Draw();

	// ----- Pre ----- // 
	
	// �v���C���[�O�`��
	playerDra_.PreDraw();
	
	// �u���b�N�O�`��
	for (size_t i = 0; i < idx; i++)
	{
		blockDra_[i].Draw();
	}
	// �Q�[�g�O�`��
	gateDra_.PreDraw();

	// �S�[���`��
	goalDra_.Draw();


	// �p�[�e�B�N��
	particleMan_.Draw();

	// �G�t�F�N�g
	effectMan_.Draw();

	// --------------- //


	// �t�B���^�[�`��
	filterDra_.Draw();


	// ----- Post ----- //
	
	// �v���C���[��`��
	playerDra_.PostDraw();
	
	// �Q�[�g��`��
	gateDra_.PostDraw();

	// --------------- //
}

void PlayScene::DrawSprite3Ds()
{

}

void PlayScene::DrawFrontSprite2Ds()
{
	// HUD�`��
	hud_.Draw();
}

void PlayScene::Draw()
{
	// -------------------------- //
	Sprite2D::Common::StaticSetPipeline();
	// ----- �w�i�X�v���C�g ----- //

	DrawBackSprite2Ds();

	// -------------------------- //
	Model::Common::StaticSetPipeline();
	// --------- ���f�� --------- //

	DrawModels();

	// -------------------------- //
	Sprite3D::Common::StaticSetPipeline();
	// ------- �r���{�[�h ------- //

	DrawSprite3Ds();

	// -------------------------- //
	Sprite2D::Common::StaticSetPipeline();
	// ----- �O�i�X�v���C�g ----- //

	DrawFrontSprite2Ds();

	// -------------------------- //
}
#pragma endregion
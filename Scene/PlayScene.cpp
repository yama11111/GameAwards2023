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

	plainTex_ = spTexManager_->Load("white1x1.png", false);

	// ----- �I�[�f�B�I ----- //

	//aA_ = pAudioManager_->Load("Resources/Audios/fanfare.wav");

	// ----- �X�v���C�g (2D) ----- //

	windowSpr_.reset(Sprite2D::Create({ WinSize }, { plainTex_ }));

	// ----- �X�v���C�g (3D) ----- //

	
	// ------- ���f�� ------- //

	cubeMod_.reset(Model::Create());

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
	// ----- �v���C���[ ----- //

	// �g�����X�t�H�[�� (�ʒu�A��]�A�傫��)
	player_.Initialize({ {}, {}, {5.0f,5.0f,5.0f} });
	// ����
	direction_ = { +1.0f,0.0f,0.0f };
	// �`��p�N���X������ (�e�s��A�����A�����F)
	playerDra_.Initialize(&player_.m_, &direction_, IDrawer::Mode::Red);
	
	
	// ----- �t�B���^�[ ----- //
	
	// �g�����X�t�H�[�� (�ʒu�A��]�A�傫��)
	filter_.Initialize({ {0.0f,0.0f,-10.0f}, {}, {5.0f,5.0f,5.0f} });
	// �`��p�N���X������ (�e�s��)
	filterDra_.Initialize(&filter_.m_);

	
	// ----- �u���b�N ----- //
	
	// �g�����X�t�H�[�� (�ʒu�A��]�A�傫��)
	block_.Initialize({ {0.0f,-20.0f,0.0f}, {}, {5.0f,5.0f,5.0f} });
	// �`��p�N���X������ (�e�s��A�����F)
	blockDra_.Initialize(&block_.m_, IDrawer::Mode::Red);

	
	// ----- �Q�[�g ----- //
	
	// �g�����X�t�H�[�� (�ʒu�A��]�A�傫��)
	gate_.Initialize({ {0.0f,0.0f,0.0f}, {}, {5.0f,5.0f,5.0f} });
	// �`��p�N���X������ (�e�s��A�����F)
	gateDra_.Initialize(&gate_.m_, IDrawer::Mode::Red);

	
	// ----- �S�[�� ----- //
	
	// �g�����X�t�H�[�� (�ʒu�A��]�A�傫��)
	goal_.Initialize({ {+20.0f,0.0f,0.0f}, {}, {5.0f,5.0f,5.0f} });
	// �`��p�N���X������ (�e�s��)
	goalDra_.Initialize(&goal_.m_);


	// �V��������
	skydome_.Initialize();
	
	// �p�[�e�B�N��������
	particleMan_.Initialize();

	// �r���[�v���W�F�N�V����������
	transferVP_.Initialize({ {0,0,-100} });
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
	// ���Z�b�g
	if (sKeys_->IsTrigger(DIK_R))
	{
	}

	// ���̃V�[����
	if (sKeys_->IsTrigger(DIK_0))
	{
		SceneManager::GetInstance()->Change("RESULT");
	}

	// �v���C���[
	player_.pos_.x_ += sKeys_->Horizontal(Keys::MoveStandard::WASD) * 2.0f;
	player_.pos_.y_ += sKeys_->Vertical(Keys::MoveStandard::WASD) * 2.0f;

	player_.UpdateMatrix();
	playerDra_.Update();
	
	// �t�B���^�[
	filter_.pos_.x_ += sKeys_->Horizontal(Keys::MoveStandard::Arrow) * 2.0f;
	filter_.pos_.y_ += sKeys_->Vertical(Keys::MoveStandard::Arrow) * 2.0f;

	filter_.UpdateMatrix();
	filterDra_.Update();

	// �u���b�N
	block_.UpdateMatrix();
	blockDra_.Update();

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

	// �r���[�v���W�F�N�V����
	transferVP_.UpdateMatrix();
}
#pragma endregion


#pragma region �`��
void PlayScene::DrawBackSprite2Ds()
{
	
}

void PlayScene::DrawBackSprite3Ds()
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
	blockDra_.PreDraw();
	
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
	
	// �u���b�N��`��
	blockDra_.PostDraw();
	
	// �Q�[�g��`��
	gateDra_.PostDraw();

	// --------------- //
}

void PlayScene::DrawFrontSprite3Ds()
{

}

void PlayScene::DrawFrontSprite2Ds()
{

}

void PlayScene::Draw()
{
	// -------------------------- //
	Sprite2DCommon::StaticSetDrawCommand();
	// ----- �w�i�X�v���C�g2D----- //

	DrawBackSprite2Ds();

	// -------------------------- //
	Sprite3DCommon::StaticSetDrawCommand();
	// ----- �O�i�X�v���C�g3D ----- //

	DrawBackSprite3Ds();

	// -------------------------- //
	ModelCommon::StaticSetDrawCommand();
	// --------- ���f�� --------- //

	DrawModels();

	// -------------------------- //
	Sprite3DCommon::StaticSetDrawCommand();
	// ----- �O�i�X�v���C�g3D ----- //

	DrawFrontSprite3Ds();

	// -------------------------- //
	Sprite2DCommon::StaticSetDrawCommand();
	// ----- �O�i�X�v���C�g2D ----- //

	DrawFrontSprite2Ds();
	
	// -------------------------- //
}
#pragma endregion
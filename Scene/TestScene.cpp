#include "TestScene.h"
#include "SceneManager.h"
#include "MathUtillity.h"
#include "CalcTransform.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#include "DrawerManager.h"

#pragma region ���O��Ԑ錾
using YScene::TestScene;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;
#pragma endregion 

#pragma region Static�֘A
#pragma endregion 

#pragma region �ǂݍ���
void TestScene::Load()
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
void TestScene::Initialize()
{
	// �j������
	core_.Initialize({ {}, {}, {3.0f,3.0f,3.0f} });

	// �v���C���[�ő���J�n
	isPlayer_ = true;

	// �v���C���[�`��p�N���X������
	playerDra_.Initialize(&core_, &direction_, IDrawer::Mode::Normal);
	// ����
	direction_ = { +1.0f,0.0f,0.0f };
	// �v���C���[�`�悷�邩
	isDrawPlayer_ = false;

	// �t�B���^�[�`��p�N���X������
	filterDra_.Initialize(&core_);
	// �t�B���^�[�`�悷�邩
	isDrawFilter_ = false;
	
	// �u���b�N�`��p�N���X������
	blockDra_.Initialize(&core_, IDrawer::Mode::Normal);
	// �u���b�N�`�悷�邩
	isDrawBlock_ = true;

	// �Q�[�g�`��p�N���X������
	gateDra_.Initialize(&core_, IDrawer::Mode::Red);
	// �Q�[�g�`�悷�邩
	isDrawGate_ = false;

	// �S�[���`��p�N���X������
	goalDra_.Initialize(&core_);
	// �S�[���`�悷�邩
	isDrawGoal_ = false;


	// �V��������
	skydome_.Initialize();
	// �V���`�悷�邩
	isDrawSkydome_ = true;

	// HUD������
	hud_.Initalize();
	// HUD�`�悷�邩
	isDrawHUD_ = false;

	// �p�[�e�B�N��������
	particleMan_.Initialize();
	
	// �G�t�F�N�g������
	effectMan_.Initialize();

	// �X�N���[���J����
	scrollCamera_.Initialize({ 0,+10,-50 }, &core_.pos_, { 0.0f,0.0f,0.0f });

	// �r���[�v���W�F�N�V����������
	transferVP_.Initialize({});

}
#pragma endregion

#pragma region �I������
void TestScene::Finalize()
{

}
#pragma endregion

#pragma region �X�V
void TestScene::Update()
{
	// �`�悷�邩
	ImGui::Begin("isDraw");
	ImGui::Checkbox("Player", &isDrawPlayer_);
	ImGui::Checkbox("Filter", &isDrawFilter_);
	ImGui::Checkbox("Block", &isDrawBlock_);
	ImGui::Checkbox("Gate", &isDrawGate_);
	ImGui::Checkbox("Goal", &isDrawGoal_);
	ImGui::Checkbox("Skydome", &isDrawSkydome_);
	ImGui::Checkbox("HUD", &isDrawHUD_);
	ImGui::End();

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
		}
		else
		{
			hud_.SetPilot(HUDDrawerCommon::Pilot::Filter);
		}
	}


	// �v���C���[
	if (sKeys_->IsTrigger(DIK_W))
	{
		playerDra_.JumpAnimation();
	}
	if (sKeys_->IsTrigger(DIK_S))
	{
		playerDra_.LandingAnimation();
	}
	if (sKeys_->IsTrigger(DIK_K))
	{
		playerDra_.ChangeColorAnimation(IDrawer::Mode::Normal);
	}
	if (sKeys_->IsTrigger(DIK_L))
	{
		playerDra_.ChangeColorAnimation(IDrawer::Mode::Red);
	}
	if (sKeys_->IsTrigger(DIK_N))
	{
		playerDra_.RespawnAnimation();
	}

	playerDra_.Update();


	// �t�B���^�[

	filterDra_.Update();

	
	// �u���b�N
	if (sKeys_->IsTrigger(DIK_N))
	{
		blockDra_.FadeInAnimation(40);
	}

	blockDra_.Update();

	
	// �Q�[�g

	gateDra_.Update();

	
	// �S�[��

	goalDra_.Update();

	
	// �V���X�V
	skydome_.Update();

	// �p�[�e�B�N���X�V
	particleMan_.Update();

	// �G�t�F�N�g�X�V
	effectMan_.Update();

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
void TestScene::DrawBackSprite2Ds()
{

}

void TestScene::DrawModels()
{
	// �V���`��
	if (isDrawSkydome_) { skydome_.Draw(); }

	// ----- Pre ----- // 

	// �v���C���[�O�`��
	if (isDrawPlayer_) { playerDra_.PreDraw(); }

	// �u���b�N�O�`��
	if (isDrawBlock_) { blockDra_.Draw(); }
	
	// �Q�[�g�O�`��
	if (isDrawGate_) { gateDra_.PreDraw(); }

	// �S�[���`��
	if (isDrawGoal_) { goalDra_.Draw(); }


	// �p�[�e�B�N��
	particleMan_.Draw();

	// �G�t�F�N�g
	effectMan_.Draw();

	// --------------- //


	// �t�B���^�[�`��
	if (isDrawFilter_) { filterDra_.Draw(); }


	// ----- Post ----- //

	// �v���C���[��`��
	if (isDrawPlayer_) { playerDra_.PostDraw(); }

	// �Q�[�g��`��
	if (isDrawGate_) { gateDra_.PostDraw(); }

	// --------------- //
}

void TestScene::DrawSprite3Ds()
{

}

void TestScene::DrawFrontSprite2Ds()
{
	// HUD�`��
	if (isDrawHUD_) { hud_.Draw(); }
}

void TestScene::Draw()
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
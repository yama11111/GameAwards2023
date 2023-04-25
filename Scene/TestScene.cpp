#include "TestScene.h"
#include "SceneManager.h"
#include "MathUtillity.h"
#include "CalcTransform.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#include "DrawerHelper.h"

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
	DrawerHelper::StaticInitialize(&transferVP_, &camera_, &particleMan_);
}
#pragma endregion


#pragma region ������
void TestScene::Initialize()
{
	// �p�[�e�B�N��������
	particleMan_.Initialize();
	// �p�[�e�B�N���`�悷�邩
	isDrawParticle_ = true;

	// �G�t�F�N�g������
	effectMan_.Initialize();
	// �G�t�F�N�g�`�悷�邩
	isDrawEffect_ = true;

	// �j������
	core_.Initialize({ {}, {}, {3.0f,3.0f,3.0f} });

	// �v���C���[�ő���J�n
	isPlayer_ = true;

	// �v���C���[�`��p�N���X������
	playerDra_.Initialize(&core_, &direction_);
	// ����
	direction_ = { +1.0f,0.0f,0.0f };
	// �v���C���[�`�悷�邩
	isDrawPlayer_ = false;
	
	// �u���b�N�`��p�N���X������
	blockDra_.Initialize(&core_, IMode::Type::Normal);
	// �u���b�N�`�悷�邩
	isDrawBlock_ = false;

	// �O���b�h
	grid_.Initialize({ 0.0f,0.0f,-0.1f }, { 20.0f,20.0f,1.0f }, 6.0f);
	// �O���b�h�`�悷�邩
	isDrawGrid_ = false;

	// �Q�[�g�`��p�N���X������
	gateDra_.Initialize(&core_);
	// �Q�[�g�`�悷�邩
	isDrawGate_ = false;

	// �S�[���`��p�N���X������
	goalDra_.Initialize(&core_);
	// �S�[���`�悷�邩
	isDrawGoal_ = true;


	// �w�i������
	background_.Initialize();
	// �w�i�`�悷�邩
	isDrawBackground_ = true;

	// HUD������
	hud_.Initialize();
	// HUD�`�悷�邩
	isDrawHUD_ = false;


	// �J���������p
	noneVP_.Initialize({});

	// �J����
	camera_.Initialize({ 0,0,-50 }, {});

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
	ImGui::Checkbox("Block", &isDrawBlock_);
	ImGui::Checkbox("Grid", &isDrawGrid_);
	ImGui::Checkbox("Gate", &isDrawGate_);
	ImGui::Checkbox("Goal", &isDrawGoal_);
	ImGui::Checkbox("Background", &isDrawBackground_);
	ImGui::Checkbox("HUD", &isDrawHUD_);
	ImGui::Checkbox("Particle", &isDrawParticle_);
	ImGui::Checkbox("Effect", &isDrawEffect_);
	ImGui::End();

#pragma region HUD

	// HUD�X�V
	hud_.Update();

	// �|�[�Y���Ȃ�e��
	if (hud_.IsPause()) { return; }

#pragma endregion


#pragma region Object

	// �v���C���[
	if (sKeys_->IsTrigger(DIK_W))
	{
		playerDra_.JumpAnimation();
	}
	if (sKeys_->IsTrigger(DIK_S))
	{
		playerDra_.LandingAnimation();
	}
	if (sKeys_->IsTrigger(DIK_N))
	{
		playerDra_.RespawnAnimation();
	}

	playerDra_.Update();

	
	// �u���b�N
	if (isDrawBlock_)
	{
		ImGui::Begin("Block");
		
		ImGui::Text("---------------");
		
		if (ImGui::Button("Reset (Normal)"))
		{
			blockDra_.Reset(IMode::Type::Normal);
		}
		if (ImGui::Button("Reset (Movable)"))
		{
			blockDra_.Reset(IMode::Type::Movable);
		}

		ImGui::Text("---------------");

		if (ImGui::Button("Catch"))
		{
			blockDra_.CatchAnimation();
		}
		if (ImGui::Button("FailToCatch"))
		{
			blockDra_.FailToCatchAnimation();
		}

		ImGui::Checkbox("IsCanCatch", &isCanCatch_);
		blockDra_.SetIsCanCatch(isCanCatch_);

		ImGui::Text("---------------");

		if (ImGui::Button("Place"))
		{
			blockDra_.PlaceAnimation();
		}
		if (ImGui::Button("FailToPlace"))
		{
			blockDra_.FailToPlaceAnimation();
		}

		ImGui::Checkbox("IsCanPlace", &isCanPlace_);
		blockDra_.SetIsCanPlace(isCanPlace_);

		ImGui::End();
	}

	blockDra_.Update();

	// �O���b�h
	if (sKeys_->IsTrigger(DIK_N))
	{
		grid_.ActAlphaAnimation();
	}

	grid_.Update();
	
	// �Q�[�g
	gateDra_.Update();

	
	// �S�[��
	if (isDrawGoal_)
	{
		ImGui::Begin("Goal");
		if (ImGui::Button("Reset"))
		{
			// ���Z�b�g
			goalDra_.Reset();
		}
		if (ImGui::Button("Clear"))
		{
			// �N���A
			goalDra_.ActivateClearAnimation(Vector3(+20.0f, 0.0f, 0.0f));
		}
		ImGui::End();
	}

	goalDra_.Update();

	
	// �w�i�X�V
	background_.Update();


	ImGui::Begin("DrawerHelper");
	if (ImGui::Button("Reset"))
	{
		// ���Z�b�g
		DrawerHelper::StaticReset();
	}
	if(ImGui::Button("Clear"))
	{
		// �N���A
		DrawerHelper::StaticClear();
	}
	ImGui::End();

	// �`��N���X�ÓI�X�V
	DrawerHelper::StaticUpdate();

#pragma endregion


#pragma region Particle

	// �p�[�e�B�N���X�V
	particleMan_.Update();

	// �G�t�F�N�g�X�V
	effectMan_.Update();

#pragma endregion


#pragma region Camera

	// �J�����ݒ�
	ImGui::Begin("CameraConfig");

	bool isChecks[3] = { false, false, false };

	if (cameraConfig_ == CameraConfig::None)
	{
		ImGui::Text("Current : None (%d)", static_cast<int>(CameraConfig::None));
		isChecks[0] = true;
	}
	else if (cameraConfig_ == CameraConfig::Camera1)
	{
		ImGui::Text("Current : Camera1 (%d)", static_cast<int>(CameraConfig::Camera1));
		isChecks[1] = true;
	}
	else if (cameraConfig_ == CameraConfig::ScrollCamera)
	{
		ImGui::Text("Current : ScrollCamera (%d)", static_cast<int>(CameraConfig::ScrollCamera));
		isChecks[2] = true;
	}

	if (ImGui::Checkbox("None", &isChecks[0])) { cameraConfig_ = CameraConfig::None; }
	if (ImGui::Checkbox("Camera1", &isChecks[1])) { cameraConfig_ = CameraConfig::Camera1; }
	if (ImGui::Checkbox("ScrollCamera", &isChecks[2])) { cameraConfig_ = CameraConfig::ScrollCamera; }

	ImGui::End();

	// �J���������p�X�V
	noneVP_.UpdateMatrix();

	// �J�����X�V
	camera_.Update();
	
	// �X�N���[���J�����X�V
	scrollCamera_.Update();
	
	// �J����1�Ȃ�
	if (cameraConfig_ == CameraConfig::None)
	{
		// �r���[�v���W�F�N�V�����ɃJ�������
		transferVP_ = noneVP_;
	}
	else if (cameraConfig_ == CameraConfig::Camera1)
	{
		// �r���[�v���W�F�N�V�����ɃJ�������
		transferVP_ = camera_.GetViewProjection();
	}
	// �X�N���[���J�����Ȃ�
	else if (cameraConfig_ == CameraConfig::ScrollCamera)
	{
		// �r���[�v���W�F�N�V�����ɃJ�������
		transferVP_ = scrollCamera_.GetViewProjection();
	}

	// �r���[�v���W�F�N�V����
	transferVP_.UpdateMatrix();

#pragma endregion


#pragma region SceneChange

	// ���̃V�[����
	if (sKeys_->IsTrigger(DIK_0))
	{
		SceneManager::GetInstance()->Change("RESULT", "INFECTION");
	}

#pragma endregion


}
#pragma endregion


#pragma region �`��
void TestScene::DrawBackSprite2Ds()
{

}

void TestScene::DrawModels()
{
	// �w�i�`��
	if (isDrawBackground_) { background_.Draw(); }

	// �v���C���[�O�`��
	if (isDrawPlayer_) { playerDra_.Draw(); }

	// �u���b�N�O�`��
	if (isDrawBlock_) { blockDra_.Draw(); }
	
	// �O���b�h�`��
	if (isDrawGrid_) { grid_.Draw(); }

	// �Q�[�g�O�`��
	if (isDrawGate_) { gateDra_.Draw(); }

	// �S�[���`��
	if (isDrawGoal_) { goalDra_.Draw(); }

	// �p�[�e�B�N��
	if (isDrawParticle_) { particleMan_.Draw(); }

	// �G�t�F�N�g
	if (isDrawEffect_) { effectMan_.Draw(); }
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
	Sprite2D::Pipeline::StaticSetDrawCommond();
	// ----- �w�i�X�v���C�g ----- //

	DrawBackSprite2Ds();

	// -------------------------- //
	Model::Pipeline::StaticSetDrawCommond();
	// --------- ���f�� --------- //

	DrawModels();

	// -------------------------- //
	Sprite3D::Pipeline::StaticSetDrawCommond();
	// ------- �r���{�[�h ------- //

	DrawSprite3Ds();

	// -------------------------- //
	Sprite2D::Pipeline::StaticSetDrawCommond();
	// ----- �O�i�X�v���C�g ----- //

	DrawFrontSprite2Ds();

	// -------------------------- //
}
#pragma endregion
#include "TestScene.h"
#include "SceneManager.h"
#include "MathUtillity.h"
#include "CalcTransform.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#include "DrawerHelper.h"
#include "MouseCollider.h"

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
	ParticleManager::StaticInitialize(&transferVP_);

	// �`��N���X�S��
	DrawerHelper::StaticInitialize(&transferVP_, &camera_, &particleMan_);
}

#pragma endregion


#pragma region ������

void TestScene::Initialize()
{
	// �p�[�e�B�N��������
	particleMan_.Initialize();


	// �傫��
	Vector3 scale = { 5.0f,5.0f,5.0f };
	
	// �j������
	core_.Initialize({ {}, {}, scale });


	// �v���C���[�`��p�N���X������
	playerDra_.Initialize(&core_, &direction_);
	// ����
	direction_ = { +1.0f,0.0f,0.0f };
	
	// �u���b�N�`��p�N���X������
	blockDra_.Initialize(&core_, BlockDrawerCommon::Type::eWhite);

	// �΂˕`��p�N���X������
	springDra_.Initialize(&core_);
	
	// ����`��p�N���X������
	platform_.Initialize({ {},{},Vector3(26.0f, 2.0f, 2.0f) });
	platformDra_.Initialize(&platform_);
	
	// �ڑ����`��p�N���X������
	junctions_[0].Initialize({ {-20.0f,+10.0f,0.0f},{},scale });
	junctions_[1].Initialize({ {+20.0f,-10.0f,0.0f},{},scale });
	junctionDras_[0].Initialize(&junctions_[0], Vector3(0, -1, 0), JunctionDrawerCommon::Type::eGreen);
	junctionDras_[1].Initialize(&junctions_[1], Vector3(-1, 0, 0), JunctionDrawerCommon::Type::eGreen);

	// ���[�U�[�`��p�N���X������
	length_ = 3.0f;
	laserDra_.Initialize(&core_, &length_);

	// ���`��p�N���X������
	keyDra_.Initialize(&core_);

	// �X�C�b�`�`��p�N���X������
	switchDra_.Initialize(&core_, SwitchDrawerCommon::Type::eBlue);

	// �Q�[�g�`��p�N���X������
	gateDra_.Initialize(&core_);

	// �S�[���`��p�N���X������
	goalDra_.Initialize(&core_, false);


	// �w�i������
	background_.Initialize();

	// HUD������
	hud_.Initialize();

	
	// �p�[�e�B�N��
	isDrawParticle_ = true;
	
	// �v���C���[
	isDrawPlayer_ = false;
	// �u���b�N
	isDrawBlock_ = true;
	// ����
	isDrawPlatform_ = false;
	// �΂�
	isDrawSpring_ = false;
	// �ڍ���
	isDrawJunction_ = false;
	// �ڍ���
	isDrawLaser_ = false;
	// �Q�[�g
	isDrawGate_ = false;
	// ��
	isDrawKey_ = false;
	// �X�C�b�`
	isDrawSwitch_ = false;
	// �S�[��
	isDrawGoal_ = false;
	// �w�i
	isDrawBackground_ = true;
	// HUD
	isDrawHUD_ = false;


	// �J���������p
	noneVP_.Initialize();

	// �J����
	camera_.Initialize({ 0,0,-50 }, {});

	// �X�N���[���J����
	scrollCamera_.Initialize({ 0,+10,-50 }, &core_.pos_, { 0.0f,0.0f,0.0f });

	// �r���[�v���W�F�N�V����������
	transferVP_.Initialize();
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
	ImGui::Checkbox("Platform", &isDrawPlatform_);
	ImGui::Checkbox("Spring", &isDrawSpring_);
	ImGui::Checkbox("Junction", &isDrawJunction_);
	ImGui::Checkbox("Laser", &isDrawLaser_);
	ImGui::Checkbox("Key", &isDrawKey_);
	ImGui::Checkbox("Switch", &isDrawSwitch_);
	ImGui::Checkbox("Gate", &isDrawGate_);
	ImGui::Checkbox("Goal", &isDrawGoal_);
	ImGui::Checkbox("Background", &isDrawBackground_);
	ImGui::Checkbox("HUD", &isDrawHUD_);
	ImGui::Checkbox("Particle", &isDrawParticle_);
	
	ImGui::End();

#pragma region HUD

	// HUD�X�V
	hud_.Update();

	// �|�[�Y���Ȃ�e��
	if (hud_.IsPause()) { return; }

#pragma endregion


#pragma region Object


#pragma region Player

	// �v���C���[
	if (isDrawPlayer_)
	{
		ImGui::Begin("Player");

		ImGui::Text("---------------");

		if (ImGui::Button("Reset"))
		{
			// ���Z�b�g
			playerDra_.Reset();
		}

		ImGui::Text("---------------");

		if (ImGui::Button("Jump"))
		{
			playerDra_.JumpAnimation();
		}
		if (ImGui::Button("Landing"))
		{
			playerDra_.LandingAnimation();
		}
		if (ImGui::Button("Respawn"))
		{
			playerDra_.RespawnAnimation();
		}

		ImGui::End();
	}

	playerDra_.Update();

#pragma endregion
	

#pragma region Block

	// �u���b�N
	if (isDrawBlock_)
	{
		ImGui::Begin("Block");
		
		ImGui::Text("---------------");
		
		if (ImGui::Button("Reset (White)"))
		{
			blockDra_.Reset(BlockDrawerCommon::Type::eWhite);
		}
		if (ImGui::Button("Reset (Red)"))
		{
			blockDra_.Reset(BlockDrawerCommon::Type::eBlack);
		}

		ImGui::End();
	}

	blockDra_.Update();

#pragma endregion


#pragma region Spring

	// �΂�
	if (isDrawSpring_)
	{
		ImGui::Begin("Spring");

		ImGui::Text("---------------");

		if (ImGui::Button("Reset"))
		{
			// ���Z�b�g
			springDra_.Reset();
		}

		ImGui::Text("---------------");

		if (ImGui::Button("Jump"))
		{
			// �W�����v�A�j���[�V����
			springDra_.AnimateJump();
		}

		ImGui::End();
	}

	springDra_.Update();

#pragma endregion


#pragma region Platform

	// ����
	if (isDrawPlatform_)
	{
		ImGui::Begin("Platform");

		ImGui::Text("---------------");

		if (ImGui::Button("Reset"))
		{
			// ���Z�b�g
			platformDra_.Reset();
		}

		ImGui::Text("---------------");

		ImGui::SliderFloat("Width", &platform_.scale_.x_, 1.0f, 24.0f);


		ImGui::End();
	}

	platform_.UpdateMatrix();
	platformDra_.Update();

#pragma endregion


#pragma region Junction

	// �ڍ���
	if (isDrawJunction_)
	{
		ImGui::Begin("Junction");

		ImGui::Text("---------------");

		if (ImGui::Button("Reset"))
		{
			// ���Z�b�g
			junctionDras_[0].Reset(Vector3(0, -1, 0), JunctionDrawerCommon::Type::eGreen);
			junctionDras_[1].Reset(Vector3(-1, 0, 0), JunctionDrawerCommon::Type::eGreen);
		}

		ImGui::Text("---------------");

		if (ImGui::Button("Connection"))
		{
			// �ڑ�
			junctionDras_[0].AnimateConnection(&junctionDras_[1]);
			junctionDras_[1].AnimateConnection(&junctionDras_[0]);
		}

		ImGui::End();
	}

	junctionDras_[0].Update();
	junctionDras_[1].Update();

#pragma endregion


#pragma region Laser

	// ���[�U�[
	if (isDrawLaser_)
	{
		ImGui::Begin("Laser");

		ImGui::Text("---------------");

		if (ImGui::Button("Reset"))
		{
			// ���Z�b�g
			laserDra_.Reset();
		}

		ImGui::Text("---------------");

		if (ImGui::Button("Shoot"))
		{
			laserDra_.AnimateShoot();
		}

		ImGui::End();
	}

	laserDra_.Update();

#pragma endregion


#pragma region Key

	// ��
	if (isDrawKey_)
	{
		ImGui::Begin("Key");

		ImGui::Text("---------------");

		if (ImGui::Button("Reset"))
		{
			// ���Z�b�g
			keyDra_.Reset();
		}

		ImGui::End();
	}

	keyDra_.Update();

#pragma endregion


#pragma region Switch

	// �X�C�b�`
	if (isDrawSwitch_)
	{
		ImGui::Begin("Swicth");

		ImGui::Text("---------------");

		if (ImGui::Button("Reset"))
		{
			// ���Z�b�g
			switchDra_.Reset(SwitchDrawerCommon::Type::eBlue);
		}

		ImGui::Text("---------------");

		if (ImGui::Button("SwitchOn"))
		{
			// �X�C�b�`�I��
			switchDra_.AnimateSwitch(true);
		}
		if (ImGui::Button("SwitchOff"))
		{
			// �X�C�b�`�I�t
			switchDra_.AnimateSwitch(false);
		}

		ImGui::End();
	}

	switchDra_.Update();

#pragma endregion


#pragma region Gate

	// �Q�[�g
	if (isDrawGate_)
	{
		ImGui::Begin("Gate");

		ImGui::Text("---------------");

		if (ImGui::Button("Reset"))
		{
			// ���Z�b�g
			gateDra_.Reset();
		}
		ImGui::End();
	}

	gateDra_.Update();

#pragma endregion

	
#pragma region Goal

	// �S�[��
	if (isDrawGoal_)
	{
		ImGui::Begin("Goal");

		ImGui::Text("---------------");

		if (ImGui::Button("Reset"))
		{
			// ���Z�b�g
			goalDra_.Reset(false);
		}
		if (ImGui::Button("Reset (Rock)"))
		{
			// ���Z�b�g
			goalDra_.Reset(true);
		}
		if (ImGui::Button("Clear"))
		{
			// �N���A
			goalDra_.ActivateClearAnimation(Vector3(+20.0f, 0.0f, 0.0f));
		}
		ImGui::End();
	}

	goalDra_.Update();

#pragma endregion


#pragma region Background

	// �w�i
	if (isDrawBackground_)
	{
		ImGui::Begin("Background");

		ImGui::Text("---------------");

		if (ImGui::Button("Reset"))
		{
			// ���Z�b�g
			background_.Reset();
		}
		ImGui::End();
	}

	background_.Update();

#pragma endregion


	ImGui::Begin("DrawerHelper");

	ImGui::Text("---------------");

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
		//SceneManager::GetInstance()->Change("RESULT", "INFECTION");
	}

#pragma endregion


}

#pragma endregion


#pragma region �`��

void TestScene::Draw()
{
	// �w�i�`��
	if (isDrawBackground_) { background_.Draw(); }

	// �v���C���[�`��
	if (isDrawPlayer_) { playerDra_.Draw(); }

	// �u���b�N�`��
	if (isDrawBlock_) { blockDra_.Draw(); }

	// �΂˕`��
	if (isDrawSpring_) { springDra_.Draw(); }

	// �ڍ����`��
	if (isDrawJunction_) 
	{
		junctionDras_[0].Draw();
		junctionDras_[1].Draw();
	}

	// ���[�U�[�`��
	if (isDrawLaser_) { laserDra_.Draw(); }

	// ���`��
	if (isDrawKey_) { keyDra_.Draw(); }

	// �X�C�b�`�`��
	if (isDrawSwitch_) { switchDra_.Draw(); }

	// �Q�[�g�O�`��
	if (isDrawGate_) { gateDra_.Draw(); }

	// �S�[���`��
	if (isDrawGoal_) { goalDra_.Draw(); }

	// HUD�`��
	if (isDrawHUD_) { hud_.Draw(); }
	
	// �p�[�e�B�N��
	if (isDrawParticle_) { particleMan_.Draw(); }

	// ����`��
	if (isDrawPlatform_) { platformDra_.Draw(); }
}

#pragma endregion
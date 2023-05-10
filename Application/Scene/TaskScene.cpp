#include "TaskScene.h"
#include "SceneManager.h"
#include "MathUtillity.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#pragma region ���O��Ԑ錾

using YScene::TaskScene;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;

#pragma endregion 


#pragma region Static�֘A

#pragma endregion 


#pragma region �ǂݍ���

void TaskScene::Load()
{
	// ���f��
	pCube_ = Model::CreateCube();
	pSphere_ = Model::LoadObj("sphere", true);
}

#pragma endregion


#pragma region ������

void TaskScene::Initialize()
{
	// �r���[�v���W�F�N�V����������
	transferVP_.Initialize({ {0.0f, 20.0f, -100.0f} });

	// �����O���|�v������
	lightGroup_.reset(LightGroup::Create());
	lightGroup_->SetDirectionalLightActive(0, true);
	lightGroup_->SetDirectionalLightDirection(0, Vector3(-1.0f, +1.0f, -1.0f).Normalized());
	lightGroup_->SetDirectionalLightColor(0, Vector3(1.0f, 1.0f, 1.0f));

	// �F������
	color_.reset(Color::Create({ 1.0f,0.0f,0.0f,1.0f }));

	// �}�e���A��������
	material_.reset(Material::Create(Vector3(0.5f, 0.5f, 0.5f), Vector3(1.0f, 1.0f, 1.0f)));

	// �I�u�W�F�N�g������
	cubeObj_.reset(Model::Object::Create(
		{ {+30.0f,0.0f,0.0f}, {0.0f,0.0f,0.0f}, {10.0f,10.0f,10.0f} },
		&transferVP_,
		color_.get(),
		lightGroup_.get(),
		material_.get()));
	sphereObj_.reset(Model::Object::Create(
		{ {-30.0f,0.0f,0.0f}, {}, {10.0f,10.0f,10.0f} },
		&transferVP_,
		color_.get(),
		lightGroup_.get(),
		material_.get()));
}

#pragma endregion


#pragma region �I������

void TaskScene::Finalize()
{

}

#pragma endregion


#pragma region �X�V

void TaskScene::Update()
{
	// ��]
	cubeObj_->rota_.x_ += 0.005f;
	if (cubeObj_->rota_.y_ >= 2.0f * PI) { cubeObj_->rota_.x_ -= 2.0f * PI; }
	cubeObj_->rota_.y_ += 0.005f;
	if (cubeObj_->rota_.y_ >= 2.0f * PI) { cubeObj_->rota_.y_ -= 2.0f * PI; }
	cubeObj_->rota_.z_ += 0.005f;
	if (cubeObj_->rota_.y_ >= 2.0f * PI) { cubeObj_->rota_.z_ -= 2.0f * PI; }

	// �s��X�V
	cubeObj_->UpdateMatrix();
	sphereObj_->UpdateMatrix();

	// �r���[�v���W�F�N�V����
	transferVP_.UpdateMatrix();


	// �X�y�[�X�L�[�ŃV�F�[�_�[�؂�ւ�
	if (sKeys_->IsTrigger(DIK_SPACE))
	{
		if (shaderType_ == Model::ShaderType::ePhong) { shaderType_ = Model::ShaderType::eToon; }
		else if (shaderType_ == Model::ShaderType::eToon) { shaderType_ = Model::ShaderType::ePhong; }
	}
}

#pragma endregion


#pragma region �`��

void TaskScene::Draw()
{
	// ���f���`��
	pCube_->SetDrawCommand(cubeObj_.get(), DrawLocation::Center, shaderType_);
	pSphere_->SetDrawCommand(sphereObj_.get(), DrawLocation::Center, shaderType_);
}

#pragma endregion
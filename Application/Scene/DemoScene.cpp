#include "DemoScene.h"
#include "SceneExecutive.h"
#include "Def.h"

#pragma region ���O��Ԑ錾

using YScene::DemoScene;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;

#pragma endregion 


#pragma region Static�֘A

#pragma endregion 


#pragma region �ǂݍ���

void DemoScene::Load()
{
	pLevel_ = Level::LoadJson("check01_12.json");
}

#pragma endregion


#pragma region ������

void DemoScene::Initialize()
{
	// �J����
	camera_.Initialize({ 0.0f,0.0f,-20.0f }, {});

	// �r���[�v���W�F�N�V����������
	transferVP_.Initialize();

	// �r���[�v���W�F�N�V�����ɃJ�������
	transferVP_ = camera_.GetViewProjection();
}

#pragma endregion


#pragma region �I������

void DemoScene::Finalize()
{
}

#pragma endregion


#pragma region �X�V

void DemoScene::Update()
{
	// �X�V
	pLevel_->Update();

	// ���Z�b�g
	if (sKeys_->IsTrigger(DIK_R))
	{
		SceneManager::GetInstance()->Change("DEMO");
	}
}

#pragma endregion


#pragma region �`��

void DemoScene::Draw()
{
	// �`��
	pLevel_->Draw();
}

#pragma endregion
#include "TitleScene.h"
#include "SceneManager.h"
#include "CoreColor.h"
#include "Def.h"
#include <cassert>

#pragma region ���O��Ԑ錾
using YScene::TitleScene;
using namespace YInput;
using namespace YGame;
using namespace YMath;
#pragma endregion 

#pragma region Static�֘A
#pragma endregion 

#pragma region �ǂݍ���
void TitleScene::Load()
{
	// ----- �e�N�X�`�� ----- //

	// ----- �I�[�f�B�I ----- //

	// ----- �X�v���C�g (2D) ----- //
	
	syazaiSpr_ = Sprite2D::Create({}, { Texture::Load("syazai.png") });

	// ----- �X�v���C�g (3D) ----- //

	// ------- ���f�� ------- //

	// ----- �ÓI������ ----- //

	ParticleManager::StaticInitialize(&transferVP_);

	CoreColor::StaticInitialize();
	BackgroundDrawerCommon::StaticInitialize(&transferVP_, &particleMan_);

	TitleDrawerCommon::StaticInitialize();
	InputDrawerCommon::StaticInitialize();
}
#pragma endregion


#pragma region ������
void TitleScene::Initialize()
{
	particleMan_.Initialize();

	background_.Initialize();

	inputDra_.Initialize(InputDrawer::SceneType::Title);
	
	syazaiObj_.reset(
		Sprite2DObject::Create(
			{
				Vector3(64.0f,302.0f,0.0f) + Vector3(800.0f,240.0f,0.0f) * 0.5f,
				{},
				Vector3(0.9f,0.9f,0.9f)
			}));

	dra_.Initialize();
}
#pragma endregion

#pragma region �I������
void TitleScene::Finalize()
{

}
#pragma endregion

#pragma region �X�V
void TitleScene::Update()
{
	inputDra_.Update();

	// �I��ύX
	dra_.Select(
		sKeys_->IsTrigger(DIK_W) || sKeys_->IsTrigger(DIK_D),
		sKeys_->IsTrigger(DIK_S) || sKeys_->IsTrigger(DIK_A));

	dra_.Update();

	background_.Update();

	CoreColor::StaticUpdate();
	BackgroundDrawerCommon::StaticUpdate();

	particleMan_.Update();

	syazaiObj_->UpdateMatrix();

	// ���̃V�[����
	if (sKeys_->IsTrigger(DIK_SPACE))
	{
		if (dra_.GetSelection() == TitleDrawer::Selection::Start)
		{
			SceneManager::GetInstance()->Change("SELECT", "INFECTION");
		}
		else if (dra_.GetSelection() == TitleDrawer::Selection::Exit)
		{
			SceneManager::GetInstance()->SetEnd(true);
		}
	}
}
#pragma endregion


#pragma region �`��
void TitleScene::DrawBackSprite2Ds()
{
	
}

void TitleScene::DrawModels()
{
	background_.Draw();

	dra_.DrawModel();
	
	particleMan_.Draw();
}

void TitleScene::DrawSprite3Ds()
{

}

void TitleScene::DrawFrontSprite2Ds()
{
	dra_.DrawSprite2D();

	inputDra_.Draw();

	syazaiSpr_->Draw(syazaiObj_.get());
}

void TitleScene::Draw()
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
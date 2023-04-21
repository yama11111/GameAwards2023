#include "ResultScene.h"
#include "SceneManager.h"
#include "Def.h"
#include <cassert>

#pragma region ���O��Ԑ錾
using YScene::ResultScene;
using namespace YGame;
using namespace YMath;
#pragma endregion 

#pragma region Static�֘A
#pragma endregion 

#pragma region �ǂݍ���
void ResultScene::Load()
{
	// ----- �e�N�X�`�� ----- //

	// ���S
	pLogoTex_ = Texture::Load("Result/logo.png");

	// �w�i
	pBackTex_ = Texture::Load("Result/back.png");
	// �X�y�[�X�L�[
	pSpaceKeyTex_[0] = Texture::Load("UI/key_SPACE.png");
	pSpaceKeyTex_[1] = Texture::Load("UI/key_SPACE_PUSH.png");

	// ----- �I�[�f�B�I ----- //

	// ----- �X�v���C�g (2D) ----- //

	// ���S
	pLogoSpr_ = Sprite2D::Create({}, { pLogoTex_ });

	// �w�i
	pBackSpr_ = Sprite2D::Create({}, { pBackTex_ });

	// �X�y�[�X�L�[
	pSpaceKeySpr_[0] = Sprite2D::Create({}, { pSpaceKeyTex_[0] });
	pSpaceKeySpr_[1] = Sprite2D::Create({}, { pSpaceKeyTex_[1] });

	// ----- �X�v���C�g (3D) ----- //

	// ------- ���f�� ------- //

	// ----- �ÓI������ ----- //

}
#pragma endregion


#pragma region ������
void ResultScene::Initialize()
{
	logoObj_.reset(Sprite2DObject::Create({ {WinSize.x_ / 2.0f, WinSize.y_ / 2.0f - 16.0f, 0.0f} }));

	backObj_.reset(Sprite2DObject::Create({ {WinSize.x_ / 2.0f, WinSize.y_ / 2.0f, 0.0f} }));

	spaceKeyObj_.reset(Sprite2DObject::Create({ {WinSize.x_ / 2.0f + 512.0f, WinSize.y_ / 2.0f + 304.0f, 0.0f}, {}, {2.0f,2.0f,1.0f} }));

	isPush_ = false;
}
#pragma endregion

#pragma region �I������
void ResultScene::Finalize()
{

}
#pragma endregion

#pragma region �X�V
void ResultScene::Update()
{
	// ���̃V�[����
	if (sKeys_->IsTrigger(DIK_SPACE))
	{
		isPush_ = true;

		//SceneManager::GetInstance()->Change("TITLE", "INFECTION");
		SceneManager::GetInstance()->Change("SELECT", "INFECTION");
	}

	logoObj_->UpdateMatrix();
	backObj_->UpdateMatrix();
	spaceKeyObj_->UpdateMatrix();
}
#pragma endregion


#pragma region �`��
void ResultScene::DrawBackSprite2Ds()
{
	pBackSpr_->Draw(backObj_.get());

}

void ResultScene::DrawModels()
{

}

void ResultScene::DrawSprite3Ds()
{

}

void ResultScene::DrawFrontSprite2Ds()
{
	pLogoSpr_->Draw(logoObj_.get());
	pSpaceKeySpr_[isPush_]->Draw(spaceKeyObj_.get());
}

void ResultScene::Draw()
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
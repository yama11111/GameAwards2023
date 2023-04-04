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
	logoTex_ = spTexManager_->Load("Result/logo.png");

	// �w�i
	backTex_ = spTexManager_->Load("Result/back.png");

	// �X�y�[�X�L�[
	spaceKeyTex_[0] = spTexManager_->Load("UI/key_SPACE.png");
	spaceKeyTex_[1] = spTexManager_->Load("UI/key_SPACE_PUSH.png");


	// ----- �I�[�f�B�I ----- //

	// ----- �X�v���C�g (2D) ----- //

	// ���S
	logoSpr_.reset(Sprite2D::Create({}, { logoTex_ }));

	// �w�i
	backSpr_.reset(Sprite2D::Create({}, { backTex_ }));

	// �X�y�[�X�L�[
	spaceKeySpr_[0].reset(Sprite2D::Create({}, { spaceKeyTex_[0] }));
	spaceKeySpr_[1].reset(Sprite2D::Create({}, { spaceKeyTex_[1] }));

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

		SceneManager::GetInstance()->Change("TITLE", "INFECTION");
	}

	logoObj_->UpdateMatrix();
	backObj_->UpdateMatrix();
	spaceKeyObj_->UpdateMatrix();
}
#pragma endregion


#pragma region �`��
void ResultScene::DrawBackSprite2Ds()
{
	backSpr_->Draw(backObj_.get());

}

void ResultScene::DrawModels()
{

}

void ResultScene::DrawSprite3Ds()
{

}

void ResultScene::DrawFrontSprite2Ds()
{
	logoSpr_->Draw(logoObj_.get());
	spaceKeySpr_[isPush_]->Draw(spaceKeyObj_.get());
}

void ResultScene::Draw()
{
	// -------------------------- //
	Sprite2DCommon::StaticSetDrawCommand();
	// ----- �w�i�X�v���C�g ----- //

	DrawBackSprite2Ds();

	// -------------------------- //
	ModelCommon::StaticSetDrawCommand();
	// --------- ���f�� --------- //

	DrawModels();

	// -------------------------- //
	Sprite3DCommon::StaticSetDrawCommand();
	// ------- �r���{�[�h ------- //

	DrawSprite3Ds();

	// -------------------------- //
	Sprite2DCommon::StaticSetDrawCommand();
	// ----- �O�i�X�v���C�g ----- //

	DrawFrontSprite2Ds();

	// -------------------------- //
}
#pragma endregion
#include "TitleScene.h"
#include "SceneManager.h"
#include "Def.h"
#include <cassert>

#pragma region ���O��Ԑ錾
using YScene::TitleScene;
using namespace YGame;
using namespace YMath;
#pragma endregion 

#pragma region Static�֘A
#pragma endregion 

#pragma region �ǂݍ���
void TitleScene::Load()
{
	// ----- �e�N�X�`�� ----- //

	// ���S
	logoTex_ = spTexManager_->Load("Title/logo.png");
	
	// �w�i
	backTex_ = spTexManager_->Load("Title/back.png");
	
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
void TitleScene::Initialize()
{
	logoObj_.reset(Sprite2DObject::Create({ {WinSize.x_ / 2.0f, WinSize.y_ / 2.0f - 128.0f, 0.0f} }));
	
	backObj_.reset(Sprite2DObject::Create({ {WinSize.x_ / 2.0f, WinSize.y_ / 2.0f, 0.0f} }));
	
	spaceKeyObj_.reset(Sprite2DObject::Create({ {WinSize.x_ / 2.0f, WinSize.y_ / 2.0f + 192.0f, 0.0f}, {}, {3.0f,3.0f,1.0f} }));

	isPush_ = false;
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
	// ���̃V�[����
	if (sKeys_->IsTrigger(DIK_SPACE))
	{
		isPush_ = true;

		SceneManager::GetInstance()->Change("PLAY", "BLACKOUT");
	}
	
	logoObj_->UpdateMatrix();
	backObj_->UpdateMatrix();
	spaceKeyObj_->UpdateMatrix();
}
#pragma endregion


#pragma region �`��
void TitleScene::DrawBackSprite2Ds()
{
	backSpr_->Draw(backObj_.get());
}

void TitleScene::DrawModels()
{
	
}

void TitleScene::DrawSprite3Ds()
{

}

void TitleScene::DrawFrontSprite2Ds()
{
	logoSpr_->Draw(logoObj_.get());
	spaceKeySpr_[isPush_]->Draw(spaceKeyObj_.get());
}

void TitleScene::Draw()
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
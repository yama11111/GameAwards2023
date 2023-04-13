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
	pLogoTex_ = Texture::Load("Title/logo.png");
	
	// �w�i
	pBackTex_ = Texture::Load("Title/back.png");
	
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

		SceneManager::GetInstance()->Change("SELECT", "INFECTION");
	}
	
	logoObj_->UpdateMatrix();
	backObj_->UpdateMatrix();
	spaceKeyObj_->UpdateMatrix();
}
#pragma endregion


#pragma region �`��
void TitleScene::DrawBackSprite2Ds()
{
	pBackSpr_->Draw(backObj_.get());
}

void TitleScene::DrawModels()
{
	
}

void TitleScene::DrawSprite3Ds()
{

}

void TitleScene::DrawFrontSprite2Ds()
{
	pLogoSpr_->Draw(logoObj_.get());
	pSpaceKeySpr_[isPush_]->Draw(spaceKeyObj_.get());
}

void TitleScene::Draw()
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
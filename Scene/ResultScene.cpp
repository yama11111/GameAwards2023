#include "ResultScene.h"
#include "SceneManager.h"
#include "Def.h"
#include <cassert>

#pragma region 名前空間宣言
using YScene::ResultScene;
using namespace YGame;
using namespace YMath;
#pragma endregion 

#pragma region Static関連
#pragma endregion 

#pragma region 読み込み
void ResultScene::Load()
{
	// ----- テクスチャ ----- //

	// ロゴ
	pLogoTex_ = Texture::Load("Result/logo.png");

	// 背景
	pBackTex_ = Texture::Load("Result/back.png");
	// スペースキー
	pSpaceKeyTex_[0] = Texture::Load("UI/key_SPACE.png");
	pSpaceKeyTex_[1] = Texture::Load("UI/key_SPACE_PUSH.png");

	// ----- オーディオ ----- //

	// ----- スプライト (2D) ----- //

	// ロゴ
	pLogoSpr_ = Sprite2D::Create({}, { pLogoTex_ });

	// 背景
	pBackSpr_ = Sprite2D::Create({}, { pBackTex_ });

	// スペースキー
	pSpaceKeySpr_[0] = Sprite2D::Create({}, { pSpaceKeyTex_[0] });
	pSpaceKeySpr_[1] = Sprite2D::Create({}, { pSpaceKeyTex_[1] });

	// ----- スプライト (3D) ----- //

	// ------- モデル ------- //

	// ----- 静的初期化 ----- //

}
#pragma endregion


#pragma region 初期化
void ResultScene::Initialize()
{
	logoObj_.reset(Sprite2DObject::Create({ {WinSize.x_ / 2.0f, WinSize.y_ / 2.0f - 16.0f, 0.0f} }));

	backObj_.reset(Sprite2DObject::Create({ {WinSize.x_ / 2.0f, WinSize.y_ / 2.0f, 0.0f} }));

	spaceKeyObj_.reset(Sprite2DObject::Create({ {WinSize.x_ / 2.0f + 512.0f, WinSize.y_ / 2.0f + 304.0f, 0.0f}, {}, {2.0f,2.0f,1.0f} }));

	isPush_ = false;
}
#pragma endregion

#pragma region 終了処理
void ResultScene::Finalize()
{

}
#pragma endregion

#pragma region 更新
void ResultScene::Update()
{
	// 次のシーンへ
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


#pragma region 描画
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
	// ----- 背景スプライト ----- //

	DrawBackSprite2Ds();

	// -------------------------- //
	Model::Pipeline::StaticSetDrawCommond();
	// --------- モデル --------- //

	DrawModels();

	// -------------------------- //
	Sprite3D::Pipeline::StaticSetDrawCommond();
	// ------- ビルボード ------- //

	DrawSprite3Ds();

	// -------------------------- //
	Sprite2D::Pipeline::StaticSetDrawCommond();
	// ----- 前景スプライト ----- //

	DrawFrontSprite2Ds();

	// -------------------------- //
}
#pragma endregion
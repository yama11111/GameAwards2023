#include "TitleScene.h"
#include "SceneManager.h"
#include "Def.h"
#include <cassert>

#pragma region 名前空間宣言
using YScene::TitleScene;
using namespace YGame;
using namespace YMath;
#pragma endregion 

#pragma region Static関連
#pragma endregion 

#pragma region 読み込み
void TitleScene::Load()
{
	// ----- テクスチャ ----- //

	// ロゴ
	pLogoTex_ = Texture::Load("Title/logo.png");
	
	// 背景
	pBackTex_ = Texture::Load("Title/back.png");
	
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
void TitleScene::Initialize()
{
	logoObj_.reset(Sprite2DObject::Create({ {WinSize.x_ / 2.0f, WinSize.y_ / 2.0f - 128.0f, 0.0f} }));
	
	backObj_.reset(Sprite2DObject::Create({ {WinSize.x_ / 2.0f, WinSize.y_ / 2.0f, 0.0f} }));
	
	spaceKeyObj_.reset(Sprite2DObject::Create({ {WinSize.x_ / 2.0f, WinSize.y_ / 2.0f + 192.0f, 0.0f}, {}, {3.0f,3.0f,1.0f} }));

	isPush_ = false;
}
#pragma endregion

#pragma region 終了処理
void TitleScene::Finalize()
{

}
#pragma endregion

#pragma region 更新
void TitleScene::Update()
{
	// 次のシーンへ
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


#pragma region 描画
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
	// ----- 背景スプライト ----- //

	DrawBackSprite2Ds();

	// -------------------------- //
	Model::Common::StaticSetPipeline();
	// --------- モデル --------- //

	DrawModels();

	// -------------------------- //
	Sprite3D::Common::StaticSetPipeline();
	// ------- ビルボード ------- //

	DrawSprite3Ds();

	// -------------------------- //
	Sprite2D::Common::StaticSetPipeline();
	// ----- 前景スプライト ----- //

	DrawFrontSprite2Ds();

	// -------------------------- //
}
#pragma endregion
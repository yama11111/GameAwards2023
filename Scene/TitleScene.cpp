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
	logoTex_ = spTexManager_->Load("Title/logo.png");
	
	// 背景
	backTex_ = spTexManager_->Load("Title/back.png");
	
	// スペースキー
	spaceKeyTex_[0] = spTexManager_->Load("UI/key_SPACE.png");
	spaceKeyTex_[1] = spTexManager_->Load("UI/key_SPACE_PUSH.png");


	// ----- オーディオ ----- //

	// ----- スプライト (2D) ----- //
	
	// ロゴ
	logoSpr_.reset(Sprite2D::Create({}, { logoTex_ }));
	
	// 背景
	backSpr_.reset(Sprite2D::Create({}, { backTex_ }));

	// スペースキー
	spaceKeySpr_[0].reset(Sprite2D::Create({}, { spaceKeyTex_[0] }));
	spaceKeySpr_[1].reset(Sprite2D::Create({}, { spaceKeyTex_[1] }));

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

		SceneManager::GetInstance()->Change("PLAY", "BLACKOUT");
	}
	
	logoObj_->UpdateMatrix();
	backObj_->UpdateMatrix();
	spaceKeyObj_->UpdateMatrix();
}
#pragma endregion


#pragma region 描画
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
	// ----- 背景スプライト ----- //

	DrawBackSprite2Ds();

	// -------------------------- //
	ModelCommon::StaticSetDrawCommand();
	// --------- モデル --------- //

	DrawModels();

	// -------------------------- //
	Sprite3DCommon::StaticSetDrawCommand();
	// ------- ビルボード ------- //

	DrawSprite3Ds();

	// -------------------------- //
	Sprite2DCommon::StaticSetDrawCommand();
	// ----- 前景スプライト ----- //

	DrawFrontSprite2Ds();

	// -------------------------- //
}
#pragma endregion
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
	logoTex_ = spTexManager_->Load("Result/logo.png");

	// 背景
	backTex_ = spTexManager_->Load("Result/back.png");

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

		SceneManager::GetInstance()->Change("TITLE", "INFECTION");
	}

	logoObj_->UpdateMatrix();
	backObj_->UpdateMatrix();
	spaceKeyObj_->UpdateMatrix();
}
#pragma endregion


#pragma region 描画
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
#include "TitleScene.h"
#include "SceneManager.h"
#include "CoreColor.h"
#include "Def.h"
#include <cassert>

#pragma region 名前空間宣言
using YScene::TitleScene;
using namespace YInput;
using namespace YGame;
using namespace YMath;
#pragma endregion 

#pragma region Static関連
#pragma endregion 

#pragma region 読み込み
void TitleScene::Load()
{
	// ----- テクスチャ ----- //

	// ----- オーディオ ----- //

	// ----- スプライト (2D) ----- //
	
	syazaiSpr_ = Sprite2D::Create({}, { Texture::Load("syazai.png") });

	// ----- スプライト (3D) ----- //

	// ------- モデル ------- //

	// ----- 静的初期化 ----- //

	ParticleManager::StaticInitialize(&transferVP_);

	CoreColor::StaticInitialize();
	BackgroundDrawerCommon::StaticInitialize(&transferVP_, &particleMan_);

	TitleDrawerCommon::StaticInitialize();
	InputDrawerCommon::StaticInitialize();
}
#pragma endregion


#pragma region 初期化
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

#pragma region 終了処理
void TitleScene::Finalize()
{

}
#pragma endregion

#pragma region 更新
void TitleScene::Update()
{
	inputDra_.Update();

	// 選択変更
	dra_.Select(
		sKeys_->IsTrigger(DIK_W) || sKeys_->IsTrigger(DIK_D),
		sKeys_->IsTrigger(DIK_S) || sKeys_->IsTrigger(DIK_A));

	dra_.Update();

	background_.Update();

	CoreColor::StaticUpdate();
	BackgroundDrawerCommon::StaticUpdate();

	particleMan_.Update();

	syazaiObj_->UpdateMatrix();

	// 次のシーンへ
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


#pragma region 描画
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
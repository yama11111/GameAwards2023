#include "SelectScene.h"
#include "SceneManager.h"
#include "MathUtillity.h"
#include "Def.h"
#include "StageConfig.h"
#include <cassert>

#pragma region 名前空間宣言
using YScene::SelectScene;
using namespace YGame;
#pragma endregion 

#pragma region Static関連
#pragma endregion 

#pragma region 読み込み
void SelectScene::Load()
{
	// ----- テクスチャ ----- //

	// ----- オーディオ ----- //

	// ----- スプライト (2D) ----- //

	// ----- スプライト (3D) ----- //

	// ------- モデル ------- //

	// ----- 静的初期化 ----- //

	LetterBoxDrawerCommon::StaticInitialize();
	SkydomeDrawerCommon::StaticInitialize();
	StageDrawerCommon::StaticInitialize(&transferVP_);
	SelectDrawerCommon::StaticInitialize(&transferVP_);
}
#pragma endregion


#pragma region 初期化
void SelectScene::Initialize()
{
	// ステージ番号
	stageIdx_ = 1;

	// 描画用クラス初期化
	dra_.Initalize(&stageIdx_);
	dra_.SetActive(true);

	// 天球初期化
	skydome_.Initialize();

	// レターボックス初期化
	lbDra_.Initialize(96.0f, 96.0f);

	// カメラ初期化
	camera_.Initialize({ {+4.0f,+31.0f,-15.0f}, {-PI / 15.0f,-PI / 30.0f,-PI / 45.0f} });
	//camera_.Initialize({ {0,0,-100}, {} });

	// ビュープロジェクション初期化
	transferVP_.Initialize({});
}
#pragma endregion

#pragma region 終了処理
void SelectScene::Finalize()
{

}
#pragma endregion

#pragma region 更新
void SelectScene::Update()
{
	// ステージ選択 (A or D)
	stageIdx_ += sKeys_->IsTrigger(DIK_D) - sKeys_->IsTrigger(DIK_A);

	// ステージ番号クランプ
	stageIdx_ = YMath::Clamp(stageIdx_, 1, StageNum);


	// 次のシーンへ (SPACE)
	if (sKeys_->IsTrigger(DIK_SPACE))
	{
		SceneManager::GetInstance()->Change("PLAY", "INFECTION");
	}


	// 描画用クラス更新
	dra_.Update();

	// 天球更新
	skydome_.Update();

	// レターボックス更新
	lbDra_.Update();

	// カメラ更新 + 代入
	camera_.Update();
	transferVP_ = camera_.GetViewProjection();
}
#pragma endregion


#pragma region 描画
void SelectScene::DrawBackSprite2Ds()
{

}

void SelectScene::DrawModels()
{
	// 天球描画
	skydome_.Draw();

	// 描画用クラス更新
	dra_.DrawModel();
}

void SelectScene::DrawSprite3Ds()
{
	// 描画用クラス更新
	dra_.DrawSprite3D();
}

void SelectScene::DrawFrontSprite2Ds()
{
	// レターボックス描画
	lbDra_.Draw();

	// 描画用クラス更新
	dra_.DrawSprite2D();
}

void SelectScene::Draw()
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
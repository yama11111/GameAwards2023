#include "PlayScene.h"
#include "SceneManager.h"
#include "MathUtillity.h"
#include "CalcTransform.h"
#include "Def.h"
#include <cassert>
#include "imgui.h"

#include "DrawerManager.h"

#pragma region 名前空間宣言
using YScene::PlayScene;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;
#pragma endregion 

#pragma region Static関連
#pragma endregion 

#pragma region 読み込み
void PlayScene::Load()
{
	// ----- テクスチャ ----- //

	plainTex_ = spTexManager_->Load("white1x1.png", false);

	// ----- オーディオ ----- //

	//aA_ = pAudioManager_->Load("Resources/Audios/fanfare.wav");

	// ----- スプライト (2D) ----- //

	windowSpr_.reset(Sprite2D::Create({ WinSize }, { plainTex_ }));

	// ----- スプライト (3D) ----- //

	
	// ------- モデル ------- //

	cubeMod_.reset(Model::Create());

	// ----- 静的初期化 ----- //

	// パーティクル
	ParticleManager::StaticInitialize(&transferVP_);

	// エフェクト
	EffectManager::StaticInitialize(&particleMan_);

	// 描画クラス全て
	DrawerManager::StaticInitialize(&transferVP_, &particleMan_);
}
#pragma endregion


#pragma region 初期化
void PlayScene::Initialize()
{
	// ----- プレイヤー ----- //

	// トランスフォーム (位置、回転、大きさ)
	player_.Initialize({ {}, {}, {5.0f,5.0f,5.0f} });
	// 向き
	direction_ = { +1.0f,0.0f,0.0f };
	// 描画用クラス初期化 (親行列、向き、初期色)
	playerDra_.Initialize(&player_.m_, &direction_, IDrawer::Mode::Red);
	
	
	// ----- フィルター ----- //
	
	// トランスフォーム (位置、回転、大きさ)
	filter_.Initialize({ {0.0f,0.0f,-10.0f}, {}, {5.0f,5.0f,5.0f} });
	// 描画用クラス初期化 (親行列)
	filterDra_.Initialize(&filter_.m_);

	
	// ----- ブロック ----- //
	
	// トランスフォーム (位置、回転、大きさ)
	block_.Initialize({ {0.0f,-20.0f,0.0f}, {}, {5.0f,5.0f,5.0f} });
	// 描画用クラス初期化 (親行列、初期色)
	blockDra_.Initialize(&block_.m_, IDrawer::Mode::Red);

	
	// ----- ゲート ----- //
	
	// トランスフォーム (位置、回転、大きさ)
	gate_.Initialize({ {0.0f,0.0f,0.0f}, {}, {5.0f,5.0f,5.0f} });
	// 描画用クラス初期化 (親行列、初期色)
	gateDra_.Initialize(&gate_.m_, IDrawer::Mode::Red);

	
	// ----- ゴール ----- //
	
	// トランスフォーム (位置、回転、大きさ)
	goal_.Initialize({ {+20.0f,0.0f,0.0f}, {}, {5.0f,5.0f,5.0f} });
	// 描画用クラス初期化 (親行列)
	goalDra_.Initialize(&goal_.m_);


	// 天球初期化
	skydome_.Initialize();
	
	// パーティクル初期化
	particleMan_.Initialize();

	// ビュープロジェクション初期化
	transferVP_.Initialize({ {0,0,-100} });
}
#pragma endregion

#pragma region 終了処理
void PlayScene::Finalize()
{

}
#pragma endregion

#pragma region 更新
void PlayScene::Update()
{
	// リセット
	if (sKeys_->IsTrigger(DIK_R))
	{
	}

	// 次のシーンへ
	if (sKeys_->IsTrigger(DIK_0))
	{
		SceneManager::GetInstance()->Change("RESULT");
	}

	// プレイヤー
	player_.pos_.x_ += sKeys_->Horizontal(Keys::MoveStandard::WASD) * 2.0f;
	player_.pos_.y_ += sKeys_->Vertical(Keys::MoveStandard::WASD) * 2.0f;

	player_.UpdateMatrix();
	playerDra_.Update();
	
	// フィルター
	filter_.pos_.x_ += sKeys_->Horizontal(Keys::MoveStandard::Arrow) * 2.0f;
	filter_.pos_.y_ += sKeys_->Vertical(Keys::MoveStandard::Arrow) * 2.0f;

	filter_.UpdateMatrix();
	filterDra_.Update();

	// ブロック
	block_.UpdateMatrix();
	blockDra_.Update();

	// ゲート
	gate_.UpdateMatrix();
	gateDra_.Update();

	// ゴール
	goal_.UpdateMatrix();
	goalDra_.Update();


	// 天球更新
	skydome_.Update();

	// パーティクル更新
	particleMan_.Update();

	// ビュープロジェクション
	transferVP_.UpdateMatrix();
}
#pragma endregion


#pragma region 描画
void PlayScene::DrawBackSprite2Ds()
{
	
}

void PlayScene::DrawBackSprite3Ds()
{
}

void PlayScene::DrawModels()
{
	// 天球描画
	skydome_.Draw();

	// ----- Pre ----- // 
	
	// プレイヤー前描画
	playerDra_.PreDraw();
	
	// ブロック前描画
	blockDra_.PreDraw();
	
	// ゲート前描画
	gateDra_.PreDraw();

	// ゴール描画
	goalDra_.Draw();


	// パーティクル
	particleMan_.Draw();

	// エフェクト
	effectMan_.Draw();

	// --------------- //


	// フィルター描画
	filterDra_.Draw();


	// ----- Post ----- //
	
	// プレイヤー後描画
	playerDra_.PostDraw();
	
	// ブロック後描画
	blockDra_.PostDraw();
	
	// ゲート後描画
	gateDra_.PostDraw();

	// --------------- //
}

void PlayScene::DrawFrontSprite3Ds()
{

}

void PlayScene::DrawFrontSprite2Ds()
{

}

void PlayScene::Draw()
{
	// -------------------------- //
	Sprite2DCommon::StaticSetDrawCommand();
	// ----- 背景スプライト2D----- //

	DrawBackSprite2Ds();

	// -------------------------- //
	Sprite3DCommon::StaticSetDrawCommand();
	// ----- 前景スプライト3D ----- //

	DrawBackSprite3Ds();

	// -------------------------- //
	ModelCommon::StaticSetDrawCommand();
	// --------- モデル --------- //

	DrawModels();

	// -------------------------- //
	Sprite3DCommon::StaticSetDrawCommand();
	// ----- 前景スプライト3D ----- //

	DrawFrontSprite3Ds();

	// -------------------------- //
	Sprite2DCommon::StaticSetDrawCommand();
	// ----- 前景スプライト2D ----- //

	DrawFrontSprite2Ds();
	
	// -------------------------- //
}
#pragma endregion
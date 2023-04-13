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

	// ----- オーディオ ----- //

	// ----- スプライト (2D) ----- //

	// ----- スプライト (3D) ----- //
	
	// ------- モデル ------- //

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
	// プレイヤー操作初期化
	isPlayer_ = true;

	float scaleVal = 1.0f;
	Vector3 scale = { scaleVal,scaleVal,scaleVal };

	// ----- プレイヤー ----- //

	// トランスフォーム (位置、回転、大きさ)
	player_.Initialize({ {-50.0f,0.0f,0.0f}, {}, scale * 2.0f });
	// 向き
	direction_ = { +1.0f,0.0f,0.0f };
	// 描画用クラス初期化 (親トランスフォーム、向き、初期色)
	playerDra_.Initialize(&player_, &direction_, IDrawer::Mode::Red);
	
	
	// ----- フィルター ----- //
	
	// トランスフォーム (位置、回転、大きさ)
	filter_.Initialize({ {0.0f,0.0f,0.0f}, {}, {6.0f,4.0f,1.0f} });
	// 描画用クラス初期化 (親トランスフォーム)
	filterDra_.Initialize(&filter_);

	
	// ----- ブロック ----- //
	
	for (size_t i = 0; i < idx - 1; i++)
	{
		// トランスフォーム (位置、回転、大きさ)
		block_[i].Initialize({{-40.0f + scaleVal * 4.0f * i,-4.0f * scaleVal,0.0f}, {}, scale});
		// 描画用クラス初期化 (親トランスフォーム、初期色)
		blockDra_[i].Initialize(&block_[i], IDrawer::Mode::Normal);
	}

	// トランスフォーム (位置、回転、大きさ)
	block_[idx - 1].Initialize({ {0.0f,0.0f,0.0f}, {}, scale });
	// 描画用クラス初期化 (親トランスフォーム、初期色)
	blockDra_[idx - 1].Initialize(&block_[idx - 1], IDrawer::Mode::Red);

	
	// ----- ゲート ----- //
	
	// トランスフォーム (位置、回転、大きさ)
	gate_.Initialize({ {-20.0f,0.0f,0.0f}, {}, scale });
	// 描画用クラス初期化 (親トランスフォーム、初期色)
	gateDra_.Initialize(&gate_, IDrawer::Mode::Red);

	
	// ----- ゴール ----- //
	
	// トランスフォーム (位置、回転、大きさ)
	goal_.Initialize({ {+4.0f * scaleVal,0.0f,0.0f}, {}, scale });
	// 描画用クラス初期化 (親トランスフォーム)
	goalDra_.Initialize(&goal_);


	// 天球初期化
	skydome_.Initialize();
	
	// HUD初期化
	hud_.Initalize();

	// パーティクル初期化
	particleMan_.Initialize();

	// スクロールカメラ
	scrollCamera_.Initialize({ 0,+10,-50 }, &player_.pos_, { 0.0f,0.0f,0.0f });

	// ビュープロジェクション初期化
	transferVP_.Initialize({});
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
	// HUD更新
	hud_.Update();

	// ポーズ中なら弾く
	if (hud_.IsPause()) { return; }


	// 操作切り替え
	if (sKeys_->IsTrigger(DIK_SPACE))
	{
		isPlayer_ = !isPlayer_;
		if (isPlayer_) 
		{
			hud_.SetPilot(HUDDrawerCommon::Pilot::Player);
			scrollCamera_.SetFollowPoint(&player_.pos_);
		}
		else 
		{
			hud_.SetPilot(HUDDrawerCommon::Pilot::Filter); 
			scrollCamera_.SetFollowPoint(&filter_.pos_);
		}
	}


	// プレイヤー
	if (isPlayer_)
	{
		playerSpeed_.x_ = sKeys_->Horizontal(Keys::MoveStandard::WASD) * 2.0f;

		if (sKeys_->IsTrigger(DIK_W))
		{
			playerDra_.JumpAnimation();
			playerSpeed_.y_ = 1.5f;
		}
		if (player_.pos_.y_ > 0.0f)
		{
			playerSpeed_.y_ -= 0.1f;
		}
	}

	player_.pos_ += playerSpeed_;
	if (player_.pos_.y_ < 0.0f)
	{
		playerDra_.LandingAnimation();
		playerSpeed_.y_ = 0.0f;
		player_.pos_.y_ = 0.0f;
	}

	player_.UpdateMatrix();
	
	if (sKeys_->IsTrigger(DIK_K))
	{
		playerDra_.ChangeColorAnimation(IDrawer::Mode::Normal);
	}
	if (sKeys_->IsTrigger(DIK_L))
	{
		playerDra_.ChangeColorAnimation(IDrawer::Mode::Red);
	}
	playerDra_.Update();


	// フィルター
	if (isPlayer_ == false)
	{
		filter_.pos_.x_ += sKeys_->Horizontal(Keys::MoveStandard::WASD) * 2.0f;
		filter_.pos_.y_ += sKeys_->Vertical(Keys::MoveStandard::WASD) * 2.0f;
	}

	filter_.UpdateMatrix();
	filterDra_.Update();

	// ブロック
	for (size_t i = 0; i < idx; i++)
	{
		block_[i].UpdateMatrix();
		blockDra_[i].Update();
	}

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



	// カメラ更新
	scrollCamera_.Update();

	// ビュープロジェクションにカメラ代入
	transferVP_ = scrollCamera_.GetViewProjection();

	// ビュープロジェクション
	transferVP_.UpdateMatrix();


	// 次のシーンへ
	if (sKeys_->IsTrigger(DIK_0))
	{
		SceneManager::GetInstance()->Change("RESULT", "INFECTION");
	}
}
#pragma endregion


#pragma region 描画
void PlayScene::DrawBackSprite2Ds()
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
	for (size_t i = 0; i < idx; i++)
	{
		blockDra_[i].Draw();
	}
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
	
	// ゲート後描画
	gateDra_.PostDraw();

	// --------------- //
}

void PlayScene::DrawSprite3Ds()
{

}

void PlayScene::DrawFrontSprite2Ds()
{
	// HUD描画
	hud_.Draw();
}

void PlayScene::Draw()
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
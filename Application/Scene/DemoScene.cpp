#include "DemoScene.h"
#include "SceneExecutive.h"
#include "DrawerHelper.h"
#include "StageConfig.h"
#include "Def.h"

#pragma region 名前空間宣言

using YScene::DemoScene;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;

#pragma endregion 


#pragma region Static関連

#pragma endregion 


#pragma region 読み込み

void DemoScene::Load()
{
	// ----- オーディオ ----- //

	// プレイBGM
	pPlayBGM_ = Audio::Load("vigilante.wav");
	
	// ----- 静的初期化 ----- //

	// パーティクル
	ParticleManager::StaticInitialize(&transferVP_);

	// 描画クラス全て
	DrawerHelper::StaticInitialize(&transferVP_, &camera_, &particleMan_);

	// プレイヤー
	DemoPlayer::StaticInitialize();

	// マップチップ
	mapChipMan_.Load();

	fontSpr_ = Sprite2D::Create({}, { Texture::Load("Goal/stageClear.png") });
}

#pragma endregion


#pragma region 初期化

void DemoScene::Initialize()
{
	// パーティクル初期化
	particleMan_.Initialize();


	// ステージ番号
	uint32_t stageIdx = static_cast<uint32_t>(StageConfig::GetInstance()->GetCurrentStageIndex());

	// マップチップマネージャー初期化
	mapChipMan_.Initialize({ 0, {}, {1.0f,1.0f,1.0f} });

	
	// プレイヤー初期化
	player_.Initialize({ +10.0f,-10.0f,0.0f });
	
	// マップチップ設定
	DemoPlayer::StaticSetMapChip(mapChipMan_.CurrentMapPointer());


	// ゴール
	goal_.Initialize({ +25.0f,-7.0f,0.0f });


	goalTim_.Initialize(160);

	fontScaleTim_.Initialize(30);

	afterglowTim_.Initialize(60);

	fontScaleEas_.Initialize(Vector3(4.0f, 0.0f, 0.0f), Vector3(2.0f, 2.0f, 0.0f), 3.0f);

	fontAlphaEas_.Initialize(0.0f, 1.0f, 3.0f);

	fontColor_.reset(CBColor::Create());

	fontObj_.reset(Sprite2D::Object::Create({ {WinSize.x_ / 2.0f, WinSize.y_ / 2.0f, 0.0f} }, fontColor_.get()));


	// 背景初期化
	background_.Initialize();

	// HUD初期化
	hud_.Initialize();

	
	// カメラ
	camera_.Initialize({ +17.0f,-11.0f,-21.0f }, {});

	// ビュープロジェクション初期化
	transferVP_.Initialize({});

	// プレイBGM開始
	pPlayBGM_->Play(true);
}

#pragma endregion


#pragma region 終了処理

void DemoScene::Finalize()
{
	// プレイBGM停止
	pPlayBGM_->Stop();
}

#pragma endregion


#pragma region 更新

void DemoScene::Update()
{
	// HUD更新
	hud_.Update();

	// ポーズ中なら弾く
	if (hud_.IsElderPause()) { return; }

	// プレイヤー更新
	player_.Update();

	// ゴール
	goal_.Update();
	
	// ゴールしてないなら
	if (isGoal_ == false)
	{
		// プレイヤーとゴールでアタリ判定
		if (CollisionSphereSphere(player_, goal_))
		{
			// プレイヤー
			player_.Goal();

			// ゴール
			goal_.Goal(player_.center_);

			// ゴールフラグをtrueに
			isGoal_ = true;

			goalTim_.Reset(true);
		}
	}

	goalTim_.Update();
	if (goalTim_.IsEnd())
	{
		fontScaleTim_.SetActive(true);
	}

	fontScaleTim_.Update();
	if (fontScaleTim_.IsEnd())
	{
		afterglowTim_.SetActive(true);
		if(isAfterglow_ == false)
		{
			isAfterglow_ = true;
			particleMan_.EmitBubbleCharacter(
				24, static_cast<size_t>(afterglowTim_.End()),
				camera_.pos_ + Vector3(0.0f, 0.0f, +20.0f), Vector3(1.0f, 1.0f, 1.0f),
				0.3f, 0.6f,
				Vector3(-0.5f, -0.25f, -0.1f), Vector3(0.5f, 0.25f, 0.1f),
				Vector3(-0.5f, -0.5f, -0.5f), Vector3(+0.5f, +0.5f, +0.5f),
				Vector3(1.0f, 0.9f, 0.1f), 100.0f, YGame::DrawLocation::Center);
		}
	}

	fontObj_->scale_ = fontScaleEas_.In(fontScaleTim_.Ratio());
	fontObj_->UpdateMatrix();

	fontColor_->SetAlpha(fontAlphaEas_.In(fontScaleTim_.Ratio()));

	afterglowTim_.Update();

	// マップチップ更新
	mapChipMan_.Update();


	// 背景更新
	background_.Update();

	// DrawerHelper更新
	DrawerHelper::StaticUpdate();


	// パーティクル更新
	particleMan_.Update();


	// カメラ更新
	camera_.Update();

	// ビュープロジェクションにカメラ代入
	transferVP_ = camera_.GetViewProjection();

	// ビュープロジェクション
	transferVP_.UpdateMatrix();


	//ゴール判定
	if (afterglowTim_.IsEnd())
	{
		SceneExecutive::GetInstance()->Change("SELECT", "INFECTION", 5, 10);
	}
}

#pragma endregion


#pragma region 描画

void DemoScene::Draw()
{
	// 背景描画
	background_.Draw();


	// プレイヤー描画
	player_.Draw();

	// ゴール描画
	goal_.Draw();


	// マップチップ描画
	mapChipMan_.Draw();


	// HUD描画
	hud_.Draw();

	if (isGoal_) { fontSpr_->SetDrawCommand(fontObj_.get(), YGame::DrawLocation::Front); }

	// パーティクル
	particleMan_.Draw();

}
#pragma endregion
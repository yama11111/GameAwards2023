#include "DemoScene.h"
#include "SceneExecutive.h"
#include "DrawerHelper.h"
#include "StageConfig.h"
#include "Def.h"

#include "MouseCollider.h"
#include "LevelData.h"

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
	pPlayBGM_ = Audio::Load("BGM/select.wav");
	
	// ----- 静的初期化 ----- //

	// マウスコライダー静的初期化
	MouseColliderCommon::StaticInitialize();

	// マウスコライダーにビュープロジェクション設定
	MouseColliderCommon::StaticSetViewProjectionPointer(&transferVP_);

	// パーティクル
	ParticleManager::StaticInitialize(&transferVP_);

	// 描画クラス全て
	DrawerHelper::StaticInitialize(&transferVP_, &camera_, &particleMan_);

	// プレイヤー
	Player::StaticInitialize();
}

#pragma endregion


#pragma region 初期化

void DemoScene::Initialize()
{
	// パーティクル初期化
	particleMan_.Initialize();

	// オブジェクトマネージャー初期化
	objMan_.Initialize();


	// ステージ番号
	uint32_t stageIdx = static_cast<uint32_t>(StageConfig::GetInstance()->GetCurrentStageIndex() - 1);


	// プレイヤー
	{
		// プレイヤー生成
		player_ = std::make_unique<Player>();

		// プレイヤー初期化
		player_->Initialize(
			LevelData::Player::InitStatuses[stageIdx].signIndex_,
			{
				LevelData::Player::InitStatuses[stageIdx].pos_.x_,
				LevelData::Player::InitStatuses[stageIdx].pos_.y_,
				0.0f
			});

		// 挿入
		objMan_.PushBack(player_.get());
	}

	// ブロック
	{
		for (size_t i = 0; i < LevelData::Block::InitStatuses[stageIdx].size(); i++)
		{
			// インスタンス生成
			std::unique_ptr<Block> newBlock = std::make_unique<Block>();

			// 初期化
			newBlock->Initialize(
				LevelData::Block::InitStatuses[stageIdx][i].signIndex_,
				{
					LevelData::Block::InitStatuses[stageIdx][i].pos_.x_,
					LevelData::Block::InitStatuses[stageIdx][i].pos_.y_,
					0.0f,
				});

			// 挿入
			objMan_.PushBack(newBlock.get());

			// 挿入
			blocks_.push_back(std::move(newBlock));
		}
	}

	// ばね
	{
		for (size_t i = 0; i < LevelData::Spring::InitStatuses[stageIdx].size(); i++)
		{
			// インスタンス生成
			std::unique_ptr<Spring> newSpring = std::make_unique<Spring>();

			// 初期化
			newSpring->Initialize(
				LevelData::Spring::InitStatuses[stageIdx][i].signIndex_,
				{
					LevelData::Spring::InitStatuses[stageIdx][i].pos_.x_,
					LevelData::Spring::InitStatuses[stageIdx][i].pos_.y_,
					0.0f,
				});

			// 挿入
			objMan_.PushBack(newSpring.get());

			// 挿入
			springs_.push_back(std::move(newSpring));
		}
	}

	// 足場
	{
		for (size_t i = 0; i < LevelData::Platform::InitStatuses[stageIdx].size(); i++)
		{
			// インスタンス生成
			std::unique_ptr<Platform> newPlatform = std::make_unique<Platform>();

			// 初期化
			newPlatform->Initialize(
				LevelData::Platform::InitStatuses[stageIdx][i].signIndex_,
				{
					LevelData::Platform::InitStatuses[stageIdx][i].pos_.x_,
					LevelData::Platform::InitStatuses[stageIdx][i].pos_.y_,
					0.0f,
				},
				LevelData::Platform::InitStatuses[stageIdx][i].length_);

			// 挿入
			objMan_.PushBack(newPlatform.get());

			// 挿入
			platforms_.push_back(std::move(newPlatform));
		}
	}

	// レーザー
	{
		for (size_t i = 0; i < LevelData::Laser::InitStatuses[stageIdx].size(); i++)
		{
			// インスタンス生成
			std::unique_ptr<Laser> newLaser = std::make_unique<Laser>();

			// 初期化
			newLaser->Initialize(
				LevelData::Laser::InitStatuses[stageIdx][i].signIndex_,
				{
					LevelData::Laser::InitStatuses[stageIdx][i].pos_.x_,
					LevelData::Laser::InitStatuses[stageIdx][i].pos_.y_,
					0.0f,
				},
				{
					LevelData::Laser::InitStatuses[stageIdx][i].direction_.x_,
					LevelData::Laser::InitStatuses[stageIdx][i].direction_.y_,
					0.0f,
				});

			// 挿入
			objMan_.PushBack(newLaser.get());

			// 挿入
			lasers_.push_back(std::move(newLaser));
		}
	}

	// スイッチ
	{
		for (size_t i = 0; i < LevelData::Switch::InitStatuses[stageIdx].size(); i++)
		{
			// インスタンス生成
			std::unique_ptr<Switch> newSwitch = std::make_unique<Switch>();

			// 初期化
			newSwitch->Initialize(
				LevelData::Switch::InitStatuses[stageIdx][i].signIndex_,
				{
					LevelData::Switch::InitStatuses[stageIdx][i].pos_.x_,
					LevelData::Switch::InitStatuses[stageIdx][i].pos_.y_,
					0.0f,
				},
				LevelData::Switch::InitStatuses[stageIdx][i].isAct_);

			// 挿入
			objMan_.PushBack(newSwitch.get());

			// 挿入
			switches_.push_back(std::move(newSwitch));
		}
	}

	// 鍵
	{
		// インスタンス生成
		key_ = std::make_unique<Key>();

		// 初期化
		key_->Initialize(
			LevelData::Key::InitStatuses[stageIdx].signIndex_,
			{
				LevelData::Key::InitStatuses[stageIdx].pos_.x_,
				LevelData::Key::InitStatuses[stageIdx].pos_.y_,
				0.0f,
			});

		// 挿入
		objMan_.PushBack(key_.get());
	}

	// ゴール
	{
		// ゴール生成
		goal_ = std::make_unique<Goal>();

		// ゴール初期化
		goal_->Initialize(
			LevelData::Goal::InitStatuses[stageIdx].signIndex_,
			{
				LevelData::Goal::InitStatuses[stageIdx].pos_.x_,
				LevelData::Goal::InitStatuses[stageIdx].pos_.y_,
				0.0f
			},
			LevelData::Goal::InitStatuses[stageIdx].isRock_);

		// 挿入
		objMan_.PushBack(goal_.get());
	}


	// 背景初期化
	background_.Initialize();

	// HUD初期化
	hud_.Initialize();

	
	// カメラ
	camera_.Initialize({ 0.0f,0.0f,-50.0f }, {});

	// ビュープロジェクション初期化
	transferVP_.Initialize();

	// ビュープロジェクションにカメラ代入
	transferVP_ = camera_.GetViewProjection();


	// プレイBGM開始
	//pPlayBGM_->Play(true);
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
	// マウスコライダー静的更新
	MouseColliderCommon::StaticUpdate();

	// HUD更新
	hud_.Update();

	// ポーズ中なら弾く
	if (hud_.IsElderPause()) { return; }


	// オブジェクトマネージャー更新
	objMan_.Update();


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
	//if ()
	//{
	//	StageConfig::GetInstance()->ClearStage(StageConfig::GetInstance()->GetCurrentStageIndex() - 1);
	//	SceneExecutive::GetInstance()->Change("SELECT", "INFECTION", 5, 10);
	//}


	// リセット
	if (sKeys_->IsTrigger(DIK_R))
	{
		SceneManager::GetInstance()->Change("DEMO");
	}
}

#pragma endregion


#pragma region 描画

void DemoScene::Draw()
{
	// 背景描画
	background_.Draw();

	// オブジェクト描画
	objMan_.Draw();

	// HUD描画
	hud_.Draw();

	// パーティクル描画
	particleMan_.Draw();

}
#pragma endregion
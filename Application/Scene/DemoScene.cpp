#include "DemoScene.h"
#include "SceneExecutive.h"
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
	pLevel_ = Level::LoadJson("check01_12.json");
}

#pragma endregion


#pragma region 初期化

void DemoScene::Initialize()
{
	// カメラ
	camera_.Initialize({ 0.0f,0.0f,-20.0f }, {});

	// ビュープロジェクション初期化
	transferVP_.Initialize();

	// ビュープロジェクションにカメラ代入
	transferVP_ = camera_.GetViewProjection();
}

#pragma endregion


#pragma region 終了処理

void DemoScene::Finalize()
{
}

#pragma endregion


#pragma region 更新

void DemoScene::Update()
{
	// 更新
	pLevel_->Update();

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
	// 描画
	pLevel_->Draw();
}

#pragma endregion
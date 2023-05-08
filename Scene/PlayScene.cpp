#include "PlayScene.h"
#include "SceneManager.h"
#include "MathUtillity.h"
#include "CalcTransform.h"
#include "Def.h"
#include <cassert>
#include "imgui.h"

#include "DrawerHelper.h"

#pragma region 名前空間宣言
using YScene::PlayScene;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;
#pragma endregion 

#pragma region Static関連
#pragma endregion 

//yうえ+した－

//bool型BoxCollision
static bool BoxCollision(YGame::Transform obj1, YGame::Transform obj2, bool nibai)
{
	YMath::Vector3 obj3 = obj1.scale_;

	if (nibai)
	{
		obj3 *= 2;
	}

	//プレイヤーの上下左右
	float p_top = obj1.pos_.y_ - obj3.y_;
	float p_bottom = obj1.pos_.y_ + obj3.y_;
	float p_right = obj1.pos_.x_ + obj3.x_;
	float p_left = obj1.pos_.x_ - obj3.x_;

	obj3 = obj2.scale_;

	if (nibai)
	{
		obj3 *= 2;
	}

	//フィルターの上下左右
	float f_top = obj2.pos_.y_ - obj3.y_;
	float f_bottom = obj2.pos_.y_ + obj3.y_;
	float f_right = obj2.pos_.x_ + obj3.x_;
	float f_left = obj2.pos_.x_ - obj3.x_;

	//フィルターに当たっているか
	if (p_left < f_right &&
		p_right > f_left &&
		p_top  < f_bottom &&
		p_bottom > f_top)
	{
		return true;
	}

	return false;
}

//Posを返すBOxCollision(左右サイズ固定)
static YMath::Vector3 BoxCollision(YMath::Vector3 posP, YMath::Vector2 sizePRL, YMath::Vector2 sizePUD, YMath::Vector3 posF, YMath::Vector2 sizeF, YMath::Vector2 DS, YMath::Vector2 AW)
{
	YMath::Vector3 nowPosP = posP;
	YMath::Vector3 nowPosF = posF;

	//プレイヤーの上下左右
	float p_top = nowPosP.y_ - sizePUD.x_;
	float p_bottom = nowPosP.y_ + sizePUD.y_;
	float p_right = nowPosP.x_ + sizePRL.x_;
	float p_left = nowPosP.x_ - sizePRL.y_;

	//フィルターの上下左右
	float f_top = nowPosF.y_ - sizeF.y_;
	float f_bottom = nowPosF.y_ + sizeF.y_;
	float f_right = nowPosF.x_ + sizeF.x_;
	float f_left = nowPosF.x_ - sizeF.x_;

	//フィルターに当たっているか
	if (p_left < f_right &&
		p_right > f_left &&
		p_top  < f_bottom &&
		p_bottom > f_top)
	{
		while (p_left < f_right &&
			p_right > f_left &&
			p_top  < f_bottom &&
			p_bottom > f_top)
		{
			nowPosP.x_ -= DS.x_ * 0.01f;
			nowPosP.y_ -= DS.y_ * 0.01f;

			nowPosP.x_ += AW.x_ * 0.01f;
			nowPosP.y_ += AW.y_ * 0.01f;

			//プレイヤーの上下左右
			p_top = nowPosP.y_ - sizePUD.x_;
			p_bottom = nowPosP.y_ + sizePUD.y_;
			p_right = nowPosP.x_ + sizePRL.x_;
			p_left = nowPosP.x_ - sizePRL.y_;
		}
	}

	return nowPosP;
}

//Posを返すBOxCollision(左右サイズバラバラ)
static YMath::Vector3 BoxCollision(YMath::Vector3 posP, YMath::Vector2 sizePRL, YMath::Vector2 sizePUD, YMath::Vector3 posF, YMath::Vector2 sizeLR, YMath::Vector2 sizeUD, YMath::Vector2 DS, YMath::Vector2 AW)
{
	YMath::Vector3 nowPosP = posP;
	YMath::Vector3 nowPosF = posF;

	YMath::Vector2 Ds = DS;
	YMath::Vector2 Aw = AW;

	Ds.x_ *= 0.1f;
	Ds.y_ *= 0.1f;
	Aw.x_ *= 0.1f;
	Aw.y_ *= 0.1f;

	//プレイヤーの上下左右
		//プレイヤーの上下左右
	float p_top = nowPosP.y_ - sizePUD.x_;
	float p_bottom = nowPosP.y_ + sizePUD.y_;
	float p_right = nowPosP.x_ + sizePRL.x_;
	float p_left = nowPosP.x_ - sizePRL.y_;

	//フィルターの上下左右
	float f_top = nowPosF.y_ - sizeUD.x_;
	float f_bottom = nowPosF.y_ + sizeUD.y_;
	float f_right = nowPosF.x_ + sizeLR.y_;
	float f_left = nowPosF.x_ - sizeLR.x_;

	//フィルターに当たっているか
	if (p_left < f_right &&
		p_right > f_left &&
		p_top  < f_bottom &&
		p_bottom > f_top)
	{
		while (p_left < f_right &&
			p_right > f_left &&
			p_top  < f_bottom &&
			p_bottom > f_top)
		{
			nowPosP.x_ -= DS.x_ * 0.1f;
			nowPosP.y_ -= DS.y_ * 0.1f;

			nowPosP.x_ += AW.x_ * 0.1f;
			nowPosP.y_ += AW.y_ * 0.1f;

			//プレイヤーの上下左右
			p_top = nowPosP.y_ - sizePUD.x_;
			p_bottom = nowPosP.y_ + sizePUD.y_;
			p_right = nowPosP.x_ + sizePRL.x_;
			p_left = nowPosP.x_ - sizePRL.y_;
		}
	}

	return nowPosP;
}

//Posを返すBoxCollision(Transformのみ)
static YMath::Vector3 BoxCollision(YGame::Transform posP, YGame::Transform posF, YMath::Vector2 DS, YMath::Vector2 AW)
{
	YGame::Transform nowPosP = posP;
	YGame::Transform nowPosF = posF;

	posP.scale_ *= 2;
	posF.scale_ *= 2;

	//プレイヤーの上下左右
	float p_top = nowPosP.pos_.y_ - posP.scale_.y_;
	float p_bottom = nowPosP.pos_.y_ + posP.scale_.y_;
	float p_right = nowPosP.pos_.x_ + posP.scale_.x_;
	float p_left = nowPosP.pos_.x_ - posP.scale_.x_;

	//フィルターの上下左右
	float f_top = nowPosF.pos_.y_ - posF.scale_.y_;
	float f_bottom = nowPosF.pos_.y_ + posF.scale_.y_;
	float f_right = nowPosF.pos_.x_ + posF.scale_.x_;
	float f_left = nowPosF.pos_.x_ - posF.scale_.x_;

	//フィルターに当たっているか
	if (p_left < f_right &&
		p_right > f_left &&
		p_top  < f_bottom &&
		p_bottom > f_top)
	{
		while (p_left < f_right &&
			p_right > f_left &&
			p_top  < f_bottom &&
			p_bottom > f_top)
		{
			nowPosP.pos_.x_ -= DS.x_ * 0.01f;
			nowPosP.pos_.y_ -= DS.y_ * 0.01f;

			nowPosP.pos_.x_ += AW.x_ * 0.01f;
			nowPosP.pos_.y_ += AW.y_ * 0.01f;

			//プレイヤーの上下左右
			p_top = nowPosP.pos_.y_ - posP.scale_.y_;
			p_bottom = nowPosP.pos_.y_ + posP.scale_.y_;
			p_right = nowPosP.pos_.x_ + posP.scale_.x_;
			p_left = nowPosP.pos_.x_ - posP.scale_.x_;
		}
	}

	return nowPosP.pos_;
}

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
	DrawerHelper::StaticInitialize(&transferVP_, &camera_, &particleMan_);
}
#pragma endregion


#pragma region 初期化
void PlayScene::Initialize()
{
	// パーティクル初期化
	particleMan_.Initialize();


	float scaleVal = 1.0f;
	Vector3 scale = { scaleVal,scaleVal,scaleVal };

	// ----- プレイヤー ----- //

	// 生成
	player.reset(new Player());

	// トランスフォーム (位置、回転、大きさ)
	player->Initialize({ -50.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f }, { scale.x_ * 2.0f - 0.2f,scale.y_ * 2.0f - 0.2f,scale.z_ * 2.0f - 0.2f });

	//ディレクション(向き)
	player->SetDirection(YMath::Vector3{ +1.0f, 0.0f, 0.0f });

	//一回リセット
	player->Reset();

	//パズルマット
	//puzzleMat.reset(new PuzzleMat(3,2));

	////config
	//stageConfig_ = StageConfig::GetInstance();

	////数値を代入
	//int Idx = stageConfig_->GetCurrentStageIndex();

	////map入れ替え
	//switch (Idx)
	//{
	//case 1:

	//	for (int i = 0; i < blockCountY; i++)
	//	{
	//		for (int j = 0; j < blockCountX; j++)
	//		{
	//			map[i][j] = map1[i][j];
	//		}
	//	}

	//	break;

	//default:
	//	for (int i = 0; i < blockCountY; i++)
	//	{
	//		for (int j = 0; j < blockCountX; j++)
	//		{
	//			map[i][j] = map1[i][j];
	//		}
	//	}
	//	break;
	//}

	// ----- ゴール ----- //

	// トランスフォーム (位置、回転、大きさ)
	goal_.Initialize({ {+4.0f * scaleVal,0.0f,0.0f}, {}, scale });
	// 描画用クラス初期化 (親トランスフォーム)
	goalDra_.Initialize(&goal_);

	//---ピース---

	// 生成
	pises.reset(new Pises());

	//初期化
	pises->Initialize();

	//複数のピース生成
	for (int i = 0; i < 2; i++)
	{
		//生成
		std::unique_ptr<Pises> newPises;
		newPises.reset(new Pises());

		//初期化
		newPises->Initialize({ i * 20.0f,5.0f,0.0f }, {},{});

		//格納
		piseses.push_back(std::move(newPises));
	}

	// 背景初期化
	background_.Initialize();

	// HUD初期化
	hud_.Initialize();

	// カメラ追従点
	followPoint_ = {};

	// カメラ
	camera_.Initialize({ 0,+10,-40 }, {});

	// スクロールカメラ
	scrollCamera_.Initialize({ 0,0,-50 }, &followPoint_, { 0.0f,0.0f,0.0f });

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
	if (hud_.IsElderPause()) { return; }

	//spaceでモード切替
	if (sKeys_->IsTrigger(DIK_SPACE))
	{
		nowMode = !nowMode;
	}

	//右で右回転
	if (sKeys_->IsTrigger(DIK_RIGHT))
	{
		for (int i = 0; i < piseses.size(); i++)
		{
			piseses[i]->SerRotRight(true);
		}
	}


	//----- Update ---------

	//PlayerのUpdate
	player->Update();

	//PisesのUpdate
	for (int i = 0; i < piseses.size(); i++)
	{
		piseses[i]->Update();
	}

	pises->Update();

	//ピース更新
	//puzzleMat->Update();

	// ゴール
	goal_.UpdateMatrix();
	goalDra_.Update();

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

	//---- other ----------

	//ゴール判定
	if (BoxCollision(player->GetTransform(), goal_, false))
	{
		SceneManager::GetInstance()->Change("SELECT", "INFECTION");
	}

	//死亡判定
	if (player->GetPos().y_ < -15)
	{
		SceneManager::GetInstance()->Change("PLAY", "BLACKOUT");
		player->Reset();
	}
}
#pragma endregion


#pragma region 描画
void PlayScene::DrawBackSprite2Ds()
{

}

void PlayScene::DrawModels()
{
	// 背景描画
	background_.Draw();

	// プレイヤー描画
	player->Draw();

	// ゴール描画
	goalDra_.Draw();

	// パーティクル
	particleMan_.Draw();

	// エフェクト
	effectMan_.Draw();

	//ブロックかピースを描画
	if (nowMode)
	{
		//pises->DrawPiese();

		for (int i = 0; i < piseses.size(); i++)
		{
			piseses[i]->DrawPiese();
		}
	}
	else
	{
	//	pises->DrawBlock();

		for (int i = 0; i < piseses.size(); i++)
		{
			piseses[i]->DrawBlock();
		}
	}

	//ピース表示
	//puzzleMat->Draw();
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
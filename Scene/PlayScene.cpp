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

YMath::Vector3 BoxCollision(Vector3 posP, Vector2 sizePRL, Vector2 sizePUD, Vector3 posF, Vector2 sizeF, Vector2 DS, Vector2 AW)
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
			nowPosP.x_ -= DS.x_;
			nowPosP.y_ -= DS.y_;

			nowPosP.x_ += AW.x_;
			nowPosP.y_ += AW.y_;

			//プレイヤーの上下左右
			p_top = nowPosP.y_ - sizePUD.x_;
			p_bottom = nowPosP.y_ + sizePUD.y_;
			p_right = nowPosP.x_ + sizePRL.x_;
			p_left = nowPosP.x_ - sizePRL.y_;
		}
	}

	return nowPosP;
}

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
	// プレイヤー
	player.Inilialize();

	// フィルター
	filter.Inilialize();

	// ブロック
	block.Inilialize();

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
	player.player_.pos_.x_ += sKeys_->Horizontal(Keys::MoveStandard::WASD) * 2.0f;
	player.player_.pos_.y_ += sKeys_->Vertical(Keys::MoveStandard::WASD) * 2.0f;

	// フィルター
	filter.filter_.pos_.x_ += sKeys_->Horizontal(Keys::MoveStandard::Arrow) * 2.0f;
	filter.filter_.pos_.y_ += sKeys_->Vertical(Keys::MoveStandard::Arrow) * 2.0f;

	RL.x_ = player.player_.scale_.x_ * 2.0f;
	RL.y_ = player.player_.scale_.x_ * 2.0f;

	WS.x_ = player.player_.scale_.y_ * 2.0f;
	WS.y_ = player.player_.scale_.y_ * 2.0f;

	filterSize.x_ = filter.filter_.scale_.x_ * 2.0f;
	filterSize.y_ = filter.filter_.scale_.y_ * 2.0f;

	DS.x_ = (float)sKeys_->IsRight(Keys::MoveStandard::WASD);
	DS.y_ = (float)sKeys_->IsUp(Keys::MoveStandard::WASD);
	AW.x_ = (float)sKeys_->IsLeft(Keys::MoveStandard::WASD);
	AW.y_ = (float)sKeys_->IsUnder(Keys::MoveStandard::WASD);

	/*DS.x_ = (float)sKeys_->IsRight(Keys::MoveStandard::WASD) || (float)sKeys_->IsRight(Keys::MoveStandard::Arrow);
	DS.y_ = (float)sKeys_->IsUp(Keys::MoveStandard::WASD) || (float)sKeys_->IsUp(Keys::MoveStandard::Arrow);
	AW.x_ = (float)sKeys_->IsLeft(Keys::MoveStandard::WASD) || (float)sKeys_->IsLeft(Keys::MoveStandard::Arrow);
	AW.y_ = (float)sKeys_->IsUnder(Keys::MoveStandard::WASD) || (float)sKeys_->IsUnder(Keys::MoveStandard::Arrow);*/

	/*DS.x_ = 0;
	DS.y_ = 1;
	AW.x_ = 0;
	AW.y_ = 0;*/

	// プレイヤー
	player.Update();

	// フィルター
	filter.Update();

	// ブロック
	block.Update();

	YMath::Vector3 playerPosFold = player.player_.pos_ * 2;
	YMath::Vector3 filterPosFold = filter.filter_.pos_ * 2;

	//Transform posP, Vector2 sizePRL, Vector2 sizePUD, Transform posF, Vector2 sizeF, Vector2 DS, Vector2 AW
	player.player_.pos_ =
		BoxCollision(
			player.player_.pos_,
			RL,
			WS,
			filter.filter_.pos_,
			filterSize,
			DS,
			AW
		);

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
	player.playerDra_.PreDraw();

	// ブロック前描画
	block.blockDra_.PreDraw();

	// パーティクル
	particleMan_.Draw();

	// エフェクト
	effectMan_.Draw();

	// --------------- //


	// フィルター描画
	filter.filterDra_.Draw();


	// ----- Post ----- //

	// プレイヤー後描画
	player.playerDra_.PostDraw();

	// ブロック後描画
	block.blockDra_.PostDraw();

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
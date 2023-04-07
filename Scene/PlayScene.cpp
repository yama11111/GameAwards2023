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

bool BoxCollision(YGame::Transform obj1, YGame::Transform obj2)
{
	//プレイヤーの上下左右
	float p_top = obj1.pos_.y_ - obj1.scale_.x_;
	float p_bottom = obj1.pos_.y_ + obj1.scale_.y_;
	float p_right = obj1.pos_.x_ + obj1.scale_.x_;
	float p_left = obj1.pos_.x_ - obj1.scale_.y_;

	//フィルターの上下左右
	float f_top = obj2.pos_.y_ - obj2.scale_.x_;
	float f_bottom = obj2.pos_.y_ + obj2.scale_.y_;
	float f_right = obj2.pos_.x_ + obj2.scale_.x_;
	float f_left = obj2.pos_.x_ - obj2.scale_.x_;

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

//yうえ+した－
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

YMath::Vector3 BoxCollision(Vector3 posP, Vector2 sizePRL, Vector2 sizePUD, Vector3 posF, Vector2 sizeLR, Vector2 sizeUD, Vector2 DS, Vector2 AW)
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
	DrawerManager::StaticInitialize(&isPlayer_, &transferVP_, &particleMan_);
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

	//// トランスフォーム (位置、回転、大きさ)
	//player_.Initialize({ {-50.0f,0.0f,0.0f}, {}, scale * 2.0f });
	//// 向き
	//direction_ = { +1.0f,0.0f,0.0f };
	//// 描画用クラス初期化 (親トランスフォーム、向き、初期色)
	//playerDra_.Initialize(&player_, &direction_, IDrawer::Mode::Red);
	//
	//
	//// ----- フィルター ----- //
	//
	//// トランスフォーム (位置、回転、大きさ)
	//filter_.Initialize({ {0.0f,0.0f,0.0f}, {}, {6.0f,4.0f,1.0f} });
	//// 描画用クラス初期化 (親トランスフォーム)
	//filterDra_.Initialize(&filter_);

	//
	//// ----- ブロック ----- //
	//
	//for (size_t i = 0; i < idx - 1; i++)
	//{
	//	// トランスフォーム (位置、回転、大きさ)
	//	block_[i].Initialize({{-40.0f + scaleVal * 4.0f * i,-4.0f * scaleVal,0.0f}, {}, scale});
	//	// 描画用クラス初期化 (親トランスフォーム、初期色)
	//	blockDra_[i].Initialize(&block_[i], IDrawer::Mode::Normal);
	//}

	player.Inilialize();

	// フィルター
	filter.Inilialize();

	// ----- ゲート ----- //

	// トランスフォーム (位置、回転、大きさ)
	gate_.Initialize({ {-20.0f,0.0f,0.0f}, {}, scale });
	// 描画用クラス初期化 (親トランスフォーム、初期色)
	gateDra_.Initialize(&gate_, IDrawer::Mode::Red);


	// ----- ゴール ----- //

	// トランスフォーム (位置、回転、大きさ)
	goal_.Initialize({ {+4.0f * scaleVal,0.0f,0.0f}, {}, Vector3{0.5f,0.5f,0.5f} });
	// 描画用クラス初期化 (親トランスフォーム)
	goalDra_.Initialize(&goal_);


	//ブロック
	for (int i = 0; i < blockCountY; i++)
	{
		for (int j = 0; j < blockCountX; j++)
		{
			Block* newBlock = new Block();

			newBlock->Inilialize();

			newBlock->nowKind = map[i][j];

			newBlock->sukeF = false;

			float size = 2.0f;

			newBlock->block_.pos_.x_ = (j - (blockCountX / 3)) * size - 8;
			newBlock->block_.pos_.y_ = ((blockCountY / 2) - i) * size;

			newBlock->block_.scale_.x_ = size / 4.0f;
			newBlock->block_.scale_.y_ = size / 4.0f;

			if (newBlock->nowKind == Start)
			{
				player.player_.pos_.x_ = (j - (blockCountX / 3)) * size - 8;
				player.player_.pos_.y_ = ((blockCountY / 2) - i) * size;

				player.startPos.x_ = (j - (blockCountX / 3)) * size - 8;
				player.startPos.y_ = ((blockCountY / 2) - i) * size;

				newBlock->nowKind = Normal;
			}

			if (map[i][j] == Gorl)
			{
				goal_.pos_.x_ = (j - (blockCountX / 3)) * size - 8;
				goal_.pos_.y_ = ((blockCountY / 2) - i) * size;

				goal_.scale_.x_ = size / 4.0f;
				goal_.scale_.y_ = size / 4.0f;

				newBlock->nowKind = None;
			}

			if (map[i][j] == Collect)
			{
				//player.player_.pos_.x_ = (j - (blockCountX / 3)) * size - 5;
				//player.player_.pos_.y_ = ((blockCountY / 2) - i) * size;
			}

			//格納
			block.push_back(newBlock);
		}
	}

	for (int i = 0; i < block.size(); i++)
	{
		block[i]->SetMode();
	}

	// ブロック
	/*for (int i = 0; i < blockCount; i++)
	{
		block[i].Inilialize();
		block[i].block_.pos_.x_ = (i - (blockCount / 2)) * 8;
		block[i].block_.pos_.y_ = -10;
		block[i].block_.scale_.x_ = 2;
		block[i].block_.scale_.y_ = 2;
	}*/

	nowMode = true;

	//// トランスフォーム (位置、回転、大きさ)
	//block_[idx - 1].Initialize({ {0.0f,0.0f,0.0f}, {}, scale });
	//// 描画用クラス初期化 (親トランスフォーム、初期色)
	//blockDra_[idx - 1].Initialize(&block_[idx - 1], IDrawer::Mode::Red);

	// 天球初期化
	skydome_.Initialize();

	// HUD初期化
	hud_.Initalize();

	// パーティクル初期化
	particleMan_.Initialize();

	// ビュープロジェクション初期化
	transferVP_.Initialize({ {0,0,-50} });
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
		/*isPlayer_ = !isPlayer_;
		if (isPlayer_) { hud_.SetPilot(HUDDrawerCommon::Pilot::Player); }
		else { hud_.SetPilot(HUDDrawerCommon::Pilot::Filter); }*/
	}

	// リセット
	if (sKeys_->IsTrigger(DIK_R))
	{
		player.Reset();
		filter.Reset();


		/*for (int i = 0; i < block.size(); i++)
		{
			block[i]->Reset();
		}*/

		/*for (int i = 0; i < blockCount; i++)
		{
			block[i].Reset();

			block[i].block_.pos_.x_ = (i - (blockCount / 2)) * 8;
			block[i].block_.pos_.y_ = -10;
			block[i].block_.scale_.x_ = 2;
			block[i].block_.scale_.y_ = 2;
		}*/
	}

	//player_.UpdateMatrix();

	if (sKeys_->IsTrigger(DIK_K))
	{
		player.playerDra_.ChangeColorAnimation(IDrawer::Mode::Normal);
	}
	if (sKeys_->IsTrigger(DIK_L))
	{
		player.playerDra_.ChangeColorAnimation(IDrawer::Mode::Red);
	}
	//playerDra_.Update();

	// 衝突
	if (sKeys_->IsTrigger(DIK_N))
	{
		player.playerDra_.SetIsCollFilter(true);
		filter.filterDra_.SetIsCollPlayer(true);
	}
	if (sKeys_->IsTrigger(DIK_M))
	{
		player.playerDra_.SetIsCollFilter(false);
		filter.filterDra_.SetIsCollPlayer(false);
	}

	if (sKeys_->IsTrigger(DIK_SPACE))
	{
		if (player.GetsukeFlag() == false)
		{
			nowMode = !nowMode;

			isPlayer_ = !isPlayer_;
			if (isPlayer_) { hud_.SetPilot(HUDDrawerCommon::Pilot::Player); }
			else { hud_.SetPilot(HUDDrawerCommon::Pilot::Filter); }
		}
	}

	//重力
	//player.player_.pos_.y_ -= 0.2f;


	if (nowMode)
	{
		//// プレイヤー
		//player.player_.pos_.x_ += sKeys_->Horizontal(Keys::MoveStandard::WASD) * 0.5f;
		//player.player_.pos_.y_ += sKeys_->Vertical(Keys::MoveStandard::WASD) * 0.5f;
		if (sKeys_->IsTrigger(DIK_W) && player.JumpFlag == false)
		{
			//if (player.player_.pos_.y_ - 0.2f)
			//{
			player.Jump = 10;
			player.JumpPower = 0;

			player.JumpFlag = true;

			player.Gravity = 0;
			player.GravityPower = 0;
			//}
		}
	}
	else {
		// フィルター
		filter.filter_.pos_.x_ += sKeys_->Horizontal(Keys::MoveStandard::WASD) * 0.5f;
		filter.filter_.pos_.y_ += sKeys_->Vertical(Keys::MoveStandard::WASD) * 0.5f;
	}

	RL.x_ = player.player_.scale_.x_ * 2;
	RL.y_ = player.player_.scale_.x_ * 2;

	WS.x_ = player.player_.scale_.y_ * 2;
	WS.y_ = player.player_.scale_.y_ * 2;

	filterSize.x_ = filter.filter_.scale_.x_;
	filterSize.y_ = filter.filter_.scale_.y_;

	Vector2 nowFSizeX = { filterSize.x_ * 3,filterSize.x_ * 3 };
	Vector2 nowFSizeY = { filterSize.y_ * 3,filterSize.y_ * 3 };

	// フィルター
	filter.Update();

	// プレイヤー
	//player.Update(filter.filter_, nowFSizeX, nowFSizeY);

	player.player_.UpdateMatrix();
	player.playerDra_.Update();

	// ブロック

	for (int i = 0; i < block.size(); i++)
	{
		block[i]->Update(filter.filter_);
	}

	/*for (int i = 0; i < blockCount; i++)
	{
		block[i].Update(filter.filter_);
	}*/

	//YMath::Vector3 playerPosFold = player.player_.pos_ * 2;
	//YMath::Vector3 filterPosFold = filter.filter_.pos_ * 2;

	//プレイヤーの上下左右
	float p_top = player.player_.pos_.y_ - player.player_.scale_.y_;
	float p_bottom = player.player_.pos_.y_ + player.player_.scale_.y_;
	float p_right = player.player_.pos_.x_ + player.player_.scale_.x_;
	float p_left = player.player_.pos_.x_ - player.player_.scale_.x_;

	//フィルターの上下左右
	float g_top = goal_.pos_.y_ - goal_.scale_.y_;
	float g_bottom = goal_.pos_.y_ + goal_.scale_.y_;
	float g_right = goal_.pos_.x_ + goal_.scale_.x_;
	float g_left = goal_.pos_.x_ - goal_.scale_.x_;

	//フィルターに当たっているか
	if (BoxCollision(player.player_, goal_))
	{
		SceneManager::GetInstance()->Change("RESULT", "BLACKOUT");
	}

	if (nowMode)
	{
		if (player.JumpFlag == false)
		{
			if (player.Gravity < 2.0f)
				player.Gravity += player.GravityPower;

			if (player.GravityPower < 0.1f)
				player.GravityPower += 0.02f;
		}
		else if (player.JumpFlag == true)
		{
			//player.Gravity = 0;
			//player.GravityPower = 0;

			player.Jump -= player.JumpPower;

			if (player.JumpPower < 0.1f)
				player.JumpPower += 0.05f;

			//playerPos.y -= Jump;

			if (player.Jump < 9.5f)
			{
				player.JumpFlag = false;
				player.Jump = 0;
			}
		}

		if (!player.JumpFlag)
		{
			DS.x_ = 0;
			DS.y_ = 0;
			AW.x_ = 0;
			AW.y_ = 1;

			player.player_.pos_.y_ -= player.Gravity * 0.1f;

			if (player.GetsukeFlag() == false)
			{
				for (int i = 0; i < block.size(); i++)
				{
					if (block[i]->nowKind != None)
					{
						if (block[i]->sukeF == false)
						{
							YMath::Vector2 BlockSize;
							BlockSize.x_ = block[i]->block_.scale_.x_;
							BlockSize.y_ = block[i]->block_.scale_.y_;

							player.player_.pos_ =
								BoxCollision(
									player.player_.pos_,
									RL,
									WS,
									block[i]->block_.pos_,
									BlockSize,
									DS,
									AW
								);
						}
					}
				}
			}

			player.player_.UpdateMatrix();
			player.playerDra_.Update();
		}

		if (player.JumpFlag)
		{
			DS.x_ = 0;
			DS.y_ = 1;
			AW.x_ = 0;
			AW.y_ = 0;

			player.player_.pos_.y_ += player.Jump * 0.1f;

			if (player.GetsukeFlag() == false)
			{
				for (int i = 0; i < block.size(); i++)
				{
					if (block[i]->nowKind != None)
					{
						if (block[i]->sukeF == false)
						{
							YMath::Vector2 BlockSize;
							BlockSize.x_ = block[i]->block_.scale_.x_;
							BlockSize.y_ = block[i]->block_.scale_.y_;

							player.player_.pos_ =
								BoxCollision(
									player.player_.pos_,
									RL,
									WS,
									block[i]->block_.pos_,
									BlockSize,
									DS,
									AW
								);
						}
					}
				}
			}

			player.player_.UpdateMatrix();
			player.playerDra_.Update();
		}

		if (sKeys_->IsDown(DIK_D))
		{
			DS.x_ = 1;
			DS.y_ = 0;
			AW.x_ = 0;
			AW.y_ = 0;

			if (nowMode)
			{
				player.player_.pos_.x_ += sKeys_->Horizontal(Keys::MoveStandard::WASD) * 0.2f;
			}

			if (player.GetsukeFlag() == false)
			{
				for (int i = 0; i < block.size(); i++)
				{
					if (block[i]->nowKind != None)
					{
						if (block[i]->sukeF == false)
						{
							YMath::Vector2 BlockSize;
							BlockSize.x_ = block[i]->block_.scale_.x_;
							BlockSize.y_ = block[i]->block_.scale_.y_;

							player.player_.pos_ =
								BoxCollision(
									player.player_.pos_,
									RL,
									WS,
									block[i]->block_.pos_,
									BlockSize,
									DS,
									AW
								);
						}
					}
				}
			}
		}

		if (sKeys_->IsDown(DIK_A))
		{
			DS.x_ = 0;
			DS.y_ = 0;
			AW.x_ = 1;
			AW.y_ = 0;

			if (nowMode)
			{
				player.player_.pos_.x_ += sKeys_->Horizontal(Keys::MoveStandard::WASD) * 0.2f;
			}

			if (player.GetsukeFlag() == false)
			{
				for (int i = 0; i < block.size(); i++)
				{
					if (block[i]->nowKind != None)
					{
						if (block[i]->sukeF == false)
						{
							YMath::Vector2 BlockSize;
							BlockSize.x_ = block[i]->block_.scale_.x_;
							BlockSize.y_ = block[i]->block_.scale_.y_;

							player.player_.pos_ =
								BoxCollision(
									player.player_.pos_,
									RL,
									WS,
									block[i]->block_.pos_,
									BlockSize,
									DS,
									AW
								);
						}
					}
				}
			}
		}
	}


	transferVP_.eye_.x_ += sKeys_->Horizontal(Keys::MoveStandard::Arrow) * 0.1f;
	transferVP_.target_.x_ += sKeys_->Horizontal(Keys::MoveStandard::Arrow) * 0.1f;
	//}

	// プレイヤー
	player.Update(filter.filter_, nowFSizeX, nowFSizeY);

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


	// 次のシーンへ
	if (sKeys_->IsTrigger(DIK_0))
	{
		SceneManager::GetInstance()->Change("RESULT", "BLACKOUT");
	}
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
	//playerDra_.PreDraw();
	//
	//// ブロック前描画
	//for (size_t i = 0; i < idx; i++)
	//{
	//	blockDra_[i].PreDraw();
	//}


	player.playerDra_.PreDraw();

	// ブロック前描画
	for (int i = 0; i < block.size(); i++)
	{
		if (block[i]->nowKind == Normal || block[i]->nowKind == ColorB)
		{
			if (!block[i]->sukeF)
			{
				block[i]->blockDra_.PreDraw();
			}
		}
	}
	/*for (int i = 0; i < blockCount; i++)
	{
		block[i].blockDra_.PreDraw();
	}*/
	/*for (int i = 0; i < blockCount - (int)player.GetkadoFlag() - (int)player.GetsukeFlag(); i++)
	{
		block[i].blockDra_.PostDraw();
	}*/
	/*for (int i = 1; i < blockCountX - 2; i++)
	{
		block[i].blockDra_.PreDraw();
	}

	if (player.GetkadoFlag())
	{
		block[4].blockDra_.PreDraw();
	}

	if (player.GetsukeFlag())
	{
		block[3].blockDra_.PreDraw();
	}

	if (!player.JumpFlag)
	{
		block[1].blockDra_.PreDraw();
	}*/


	// ゲート前描画
	//gateDra_.PreDraw();

	// ゴール描画
	goalDra_.Draw();


	// パーティクル
	particleMan_.Draw();

	// エフェクト
	effectMan_.Draw();

	// --------------- //


	// フィルター描画
	filter.Draw();


	// ----- Post ----- //

	//// プレイヤー後描画
	//playerDra_.PostDraw();
	//
	//// ブロック後描画
	//for (size_t i = 0; i < idx; i++)
	//{
	//	blockDra_[i].PostDraw();
	//}

	player.playerDra_.PostDraw();

	// ブロック後描画
	for (int i = 0; i < block.size(); i++)
	{
		if (block[i]->nowKind == Normal || block[i]->nowKind == ColorB)
		{
			if (!block[i]->sukeF)
			{
				block[i]->blockDra_.PostDraw();
			}
		}
	}
	/*for (int i = 0; i < blockCount; i++)
	{
		block[i].blockDra_.PostDraw();
	}*/

	/*for (int i = 1; i < blockCount - 2; i++)
	{
		block[i].blockDra_.PostDraw();
	}

	if (player.GetkadoFlag())
	{
		block[4].blockDra_.PostDraw();
	}

	if (player.GetsukeFlag())
	{
		block[3].blockDra_.PostDraw();
	}

	if (!player.JumpFlag)
	{
		block[1].blockDra_.PostDraw();
	}*/

	// ゲート後描画
	//gateDra_.PostDraw();

	// --------------- //
}

void PlayScene::DrawFrontSprite3Ds()
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
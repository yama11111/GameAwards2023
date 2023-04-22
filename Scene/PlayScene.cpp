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

	conSpr_ = Sprite2D::Create({}, { Texture::Load("operateSign.png") });
	conSpr2_ = Sprite2D::Create({}, { Texture::Load("forFilter.png") });
	conSpr3_ = Sprite2D::Create({}, { Texture::Load("forFilter2.png") });

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
	conObj_.reset(Sprite2DObject::Create({ {WinSize.x_ / 2.0f + 220, WinSize.y_ - 100, 0.0f},{},{0.5f,0.5f,0.0f} }));
	conObj2_.reset(Sprite2DObject::Create({ {WinSize.x_ - 165, WinSize.y_ - 180, 0.0f},{},{0.5f,0.5f,0.0f} }));
	conObj3_.reset(Sprite2DObject::Create({ {WinSize.x_ - 165, WinSize.y_ - 70, 0.0f},{},{0.5f,0.5f,0.0f} }));

	float scaleVal = 1.0f;
	Vector3 scale = { scaleVal,scaleVal,scaleVal };

	// ----- プレイヤー ----- //

	// 生成
	player.reset(new Player());

	// トランスフォーム (位置、回転、大きさ)
	player->Initialize({ -50.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f }, { scale.x_ * 2.0f - 0.2f,scale.y_ * 2.0f - 0.2f,scale.z_ * 2.0f - 0.2f });

	//ディレクション(向き)
	player->SetDirection(YMath::Vector3{ +1.0f, 0.0f, 0.0f });

	player->Reset();

	//config
	stageConfig_ = StageConfig::GetInstance();
	//StageConfig::GetCurrentStageIndex();
	//
	//player_->SetClearFlag(true);

	int Idx = stageConfig_->GetCurrentStageIndex();

	switch (Idx)
	{
	case 1:

		for (int i = 0; i < blockCountY; i++)
		{
			for (int j = 0; j < blockCountX; j++)
			{
				map[i][j] = map1[i][j];
			}
		}

		break;

	case 2:

		for (int i = 0; i < blockCountY; i++)
		{
			for (int j = 0; j < blockCountX; j++)
			{
				map[i][j] = map2[i][j];
			}
		}
		break;

	case 3:

		for (int i = 0; i < blockCountY; i++)
		{
			for (int j = 0; j < blockCountX; j++)
			{
				map[i][j] = map3[i][j];
			}
		}
		break;

	case 4:
		for (int i = 0; i < blockCountY; i++)
		{
			for (int j = 0; j < blockCountX; j++)
			{
				map[i][j] = map4[i][j];
			}
		}

		break;

	case 5:

		for (int i = 0; i < blockCountY; i++)
		{
			for (int j = 0; j < blockCountX; j++)
			{
				map[i][j] = map5[i][j];
			}
		}
		break;

	case 6:

		for (int i = 0; i < blockCountY; i++)
		{
			for (int j = 0; j < blockCountX; j++)
			{
				map[i][j] = map6[i][j];
			}
		}
		break;

	case 7:
		for (int i = 0; i < blockCountY; i++)
		{
			for (int j = 0; j < blockCountX; j++)
			{
				map[i][j] = map7[i][j];
			}
		}

		break;

	case 8:
		for (int i = 0; i < blockCountY; i++)
		{
			for (int j = 0; j < blockCountX; j++)
			{
				map[i][j] = map8[i][j];
			}
		}

		break;

	case 9:

		for (int i = 0; i < blockCountY; i++)
		{
			for (int j = 0; j < blockCountX; j++)
			{
				map[i][j] = map9[i][j];
			}
		}
		break;

	case 10:

		for (int i = 0; i < blockCountY; i++)
		{
			for (int j = 0; j < blockCountX; j++)
			{
				map[i][j] = map10[i][j];
			}
		}
		break;

	default:
		for (int i = 0; i < blockCountY; i++)
		{
			for (int j = 0; j < blockCountX; j++)
			{
				map[i][j] = map1[i][j];
			}
		}
		break;
	}

	// ----- フィルター ----- //

	// 生成
	filter.reset(new Filter());

	// トランスフォーム (位置、回転、大きさ)
	filter->Initialize({ -10.0f, 0.0f, 3.0f }, {}, { 1.5f,1.5f,1.5f });

	filter->Reset();

	// ----- ゴール ----- //

	// トランスフォーム (位置、回転、大きさ)
	goal_.Initialize({ {+4.0f * scaleVal,0.0f,0.0f}, {}, scale });
	// 描画用クラス初期化 (親トランスフォーム)
	goalDra_.Initialize(&goal_);

	// ----- ブロック ----- //

	//ブロック
	for (int i = 0; i < blockCountY; i++)
	{
		for (int j = 0; j < blockCountX; j++)
		{
			//Noneだったらのぞく(return)
			if (map[i][j] == None)
			{
				continue;
			}

			//サイズ
			float size = harfScale * 2;

			//格納用Vector
			YMath::Vector3 result;

			//種類によって
			//初期地点
			if (map[i][j] == Start)
			{
				//posXY
				result.x_ = (j - (blockCountX / 3)) * size;
				result.y_ = ((blockCountY / 2) - i) * size;

				//pos格納
				player->SetPos(result);

				//StartPos格納
				player->SetStartPos(result);

				////種類を空白に
				//newBlock->SetKind(None);

				//次へ
				continue;
			}

			//ゴール地点
			if (map[i][j] == Gorl)
			{
				//pos格納
				goal_.pos_.x_ = (j - (blockCountX / 3)) * size - 8;
				goal_.pos_.y_ = ((blockCountY / 2) - i) * size;

				//scale格納
				goal_.scale_.x_ = size / 4.0f;
				goal_.scale_.y_ = size / 4.0f;

				////種類を空白に
				//newBlock->SetKind(None);

				//次へ
				continue;
			}

			//コレクトアイテム
			if (map[i][j] == Collect)
			{

				////種類を空白に
				//newBlock->SetKind(None);

				//次へ
				continue;
			}

			//生成
			std::unique_ptr<Block> newBlock;
			newBlock.reset(new Block());

			//初期化
			newBlock->Initialize();

			//種類を格納
			newBlock->SetKind(map[i][j]);

			////サイズ
			//float size = harfScale * 2;

			////格納用Vector
			//YMath::Vector3 result;

			//zは特にいじらない
			result.z_ = size / 4;

			//posXY
			result.x_ = (j - (blockCountX / 3)) * size - 8;
			result.y_ = ((blockCountY / 2) - i) * size;

			//pos格納
			newBlock->SetPos(result);

			//scaleXY
			result.x_ = size / 4;
			result.y_ = size / 4;

			//scale格納
			newBlock->SetScale(result);

			//格納
			block.push_back(std::move(newBlock));
		}
	}

	//種類によってブロックを変更
	for (int i = 0; i < block.size(); i++)
	{
		block[i]->SetMode();
	}

	//フィルターの位置をプレイヤーの上に
	YMath::Vector3 Ppos = player->GetPos();
	Ppos.y_ += harfScale * 10;
	filter->SetPos(Ppos);

	for (int i = 0; i < blockCountY; i++)
	{
		for (int j = 0; j < blockCountX; j++)
		{
			filter->InitializeMap(i, j, map[i][j]);
		}
	}

	// 天球初期化
	skydome_.Initialize();

	// HUD初期化
	hud_.Initalize();

	// パーティクル初期化
	particleMan_.Initialize();

	// カメラ追従点
	followPoint_ = {};

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
	if (hud_.IsPause()) { return; }


	// 操作切り替え
	if (sKeys_->IsTrigger(DIK_SPACE))
	{
		//プレイヤーとフィルターが当たってないなら
		if (!BoxCollision(player->GetTransform(), filter->GetTransform(), true))
		{
			//操作フラグを反転
			player->ChengePlayFlag();

			//操作してるobjを表示するスプライトの変更
			if (player->GetPlayFlag()) { hud_.SetPilot(HUDDrawerCommon::Pilot::Player); }
			else { hud_.SetPilot(HUDDrawerCommon::Pilot::Filter); }
		}
		else
		{
			// カメラ揺れる
			scrollCamera_.Shaking(10, 2);
		}
	}

	////デバッグ用のリセットボタン
	//if (sKeys_->IsTrigger(DIK_R))
	//{
	//	player->Reset();
	//	filter->Reset();
	//}

	//格納用Vector
	YMath::Vector3 result(0.0f, 0.0f, 0.0f);

	//値を0に
	player->SetMovePos(result);
	filter->SetMovePos(result);

	//入力状態を入手
	result.x_ = sKeys_->Horizontal(Keys::MoveStandard::WASD);
	result.y_ = sKeys_->Vertical(Keys::MoveStandard::WASD);
	result.z_ = 0.0f;

	//移動量
	float playerA = harfScale * 2;
	float filterA = harfScale * 2;

	//今のアクティブ状態
	if (player->GetPlayFlag())
	{
		//移動量
		//result.x_ *= playerA;
		result.x_ = filterA * (sKeys_->IsTrigger(DIK_D) - sKeys_->IsTrigger(DIK_A));

		//プレイヤーはy軸はジャンプのみ
		result.y_ = 0.0f;

		//プレイヤーの移動量格納
		player->SetMovePos(result);
	}
	else
	{
		//移動量
		result.x_ = filterA * (sKeys_->IsTrigger(DIK_D) - sKeys_->IsTrigger(DIK_A));
		result.y_ = filterA * (sKeys_->IsTrigger(DIK_W) - sKeys_->IsTrigger(DIK_S));

		//フィルターの移動量格納
		filter->SetMovePos(result);
	}

	//PlayerのUpdate
	player->Update(filter->GetTransform());

	//filterのUpdate
	filter->Update();

	// ブロック
	for (int i = 0; i < block.size(); i++)
	{
		//更新
		block[i]->Update(filter->GetTransform());
		 
		//フィルターと当たってたら
		for (int j = 0; j < 12; j++)
		{
			if (filter->GetDrawFlag(j) == true)
			{
				if (block[i]->GetClearFlag() == false)
				{
					if (BoxCollision(block[i]->GetTransform(), filter->GetTransform(j), true))
					{
						filter->SetDrawFlag(j, false);

						//透けるフラグをonに
						block[i]->SetClearFlag(true);

						// カメラ揺れる
						scrollCamera_.Shaking(10, 2);
					}
				}
			}
		}

		//赤い色なら
		if (block[i]->GetKind() == ColorB)
		{
			//playerと当たってたら延長
			if (BoxCollision(block[i]->GetTransform(), player->GetTransform(), true))
			{
				//タイマーを設定
				block[i]->SetTimer(10);
			}

			////フィルターと当たってたら
			//if (BoxCollision(block[i]->GetTransform(), filter->GetTransform(), true))
			//{
			//	//透けるフラグをonに
			//	block[i]->SetClearFlag(true);

			//	//タイマーを設定
			//	block[i]->SetTimer(50);
			//}
		}

		//通常ブロック処理
		//if (block[i]->GetKind() == Normal)
		//{
		//	//透けるフラグをonに
		//	block[i]->SetClearFlag(false);

		//	if (BoxCollision(block[i]->GetTransform(), filter->GetTransform(), true))
		//	{
		//		//透けるフラグをonに
		//		block[i]->SetClearFlag(true);
		//	}
		//}

		//ブロック上げ下げ処置
		if (player->GetPlayFlag())
		{
			//上がるフラグがonなら
			if (block[i]->GetUpFlag())
			{
				//ブロックのpos,scaleを拡大
				block[i]->MovePosYUp(blockcount);
			}
			else
			{
				//ブロックのpos,scaleを縮小
				block[i]->MovePosYDown();

				if (sKeys_->IsTrigger(DIK_7))
				{
					blockcount = 1;
				}

				if (sKeys_->IsTrigger(DIK_8))
				{
					blockcount = 2;
				}

				if (sKeys_->IsTrigger(DIK_9))
				{
					blockcount = 3;
				}
			}
		}
	}

	//格納
	YGame::Transform CheckTrans1;

	//格納
	YGame::Transform CheckTrans2;

	//プレイヤー操作モードがnの時
	if (player->GetPlayFlag())
	{
		//プレイヤーを操作しているときカウントを進める
		for (int i = 0; i < block.size(); i++)
		{
			block[i]->CountDown();
		}

		//Wを押してジャンプ処理
		if (sKeys_->IsTrigger(DIK_W))
		{
			//ジャンプフラグがoffの時
			if (!player->GetJumpFlag())
			{
				//重力関係リセット
				player->JumpReset();
			}
		}

		//プレイヤージャンプ処理

		//重力、浮力を加算
		player->AddGravity();

		//フィルターと重なっているか
		//player->SetClearFlag(BoxCollision(player->GetTransform(), filter->GetTransform(), true));

		//ジャンプフラグがONなら
		if (player->GetJumpFlag())
		{
			if (player->GetJump() < 0.0f)
			{
				//入力方向手動代入
				DS.x_ = 0;
				DS.y_ = 0.0f;
				AW.x_ = 0;
				AW.y_ = 1.0f;
			}
			else
			{
				//入力方向手動代入
				DS.x_ = 0;
				DS.y_ = 1.0f;
				AW.x_ = 0;
				AW.y_ = 0.0f;
			}

			//フィルターの中にいるか
			if (player->GetClearFlag() == false)
			{
				//ブロック分繰り返す
				for (int i = 0; i < block.size(); i++)
				{
					//ブロックの種類が空白か
					if (block[i]->GetKind() != None)
					{
						//ブロックがフィルターの中にいるか
						if (block[i]->GetClearFlag() == false)
						{
							//プレイヤーのTransformを代入
							CheckTrans1 = player->GetTransform();

							//ブロックのTransformを代入
							CheckTrans2 = block[i]->GetTransform();

							if (BoxCollision(CheckTrans1, CheckTrans2, true))
							{
								player->SetPos(BoxCollision(CheckTrans1, CheckTrans2, DS, AW));

								//下に埋まった瞬間ジャンプフラグをfalseに
								player->SetJumpFlag(false);

								//重力関係リセット
								player->JumpReset();

								//フラグをOFFに
								player->SetJumpFlag(false);
							}
						}
					}
				}
			}
		}
		//ジャンプがfalseなら上に修正
		//ジャンプがtrueなら下に修正
		//if (true)//player->GetJumpFlag())
		else
		{
			//重力加算
			player->SetGravity(0.3f);

			//入力方向手動代入
			DS.x_ = 0;
			DS.y_ = 0.0f;
			AW.x_ = 0;
			AW.y_ = 1.0f;

			//フィルターの中にいるか
			if (player->GetClearFlag() == false)
			{
				//ブロック分繰り返す
				for (int i = 0; i < block.size(); i++)
				{
					//ブロックの種類が空白か
					if (block[i]->GetKind() != None)
					{
						//ブロックがフィルターの中にいるか
						if (block[i]->GetClearFlag() == false)
						{
							//プレイヤーのTransformを代入
							CheckTrans1 = player->GetTransform();

							//ブロックのTransformを代入
							CheckTrans2 = block[i]->GetTransform();

							if (BoxCollision(CheckTrans1, CheckTrans2, true))
							{
								player->SetPos(BoxCollision(CheckTrans1, CheckTrans2, DS, AW));

								//下に埋まった瞬間ジャンプフラグをfalseに
								player->SetJumpFlag(false);
								//player->Landing();


								if (sKeys_->IsTrigger(DIK_C))
								{
									if (block[i]->GetUpFlag() == false)
									{
										block[i]->SetUpFlag(true);
										block[i]->SetUpTimer(50);
									}
								}
							}
						}
					}
				}
			}
		}

		//右を押してるとき左に修正
		if (sKeys_->IsDown(DIK_D))
		{
			//入力方向手動代入
			DS.x_ = 1.0f;
			DS.y_ = 0;
			AW.x_ = 0;
			AW.y_ = 0;

			//横移動
			player->PlayerMove(player->GetMovePos());

			//フィルターの中にいるか
			if (player->GetClearFlag() == false)
			{
				//ブロック分繰り返す
				for (int i = 0; i < block.size(); i++)
				{
					//ブロックの種類が空白か
					if (block[i]->GetKind() != None)
					{
						//ブロックがフィルターの中にいるか
						if (block[i]->GetClearFlag() == false)
						{
							//プレイヤーのTransformを代入
							CheckTrans1 = player->GetTransform();

							//ブロックのTransformを代入
							CheckTrans2 = block[i]->GetTransform();

							if (BoxCollision(CheckTrans1, CheckTrans2, true))
							{
								//ちょっと戻す
								player->SetPos(BoxCollision(CheckTrans1, CheckTrans2, DS, AW));
							}
						}
					}
				}
			}
		}

		//左を押してるとき右に修正
		if (sKeys_->IsDown(DIK_A))
		{
			//入力方向手動代入
			DS.x_ = 0;
			DS.y_ = 0;
			AW.x_ = 1.0f;
			AW.y_ = 0;

			//横移動
			player->PlayerMove(player->GetMovePos());

			//フィルターの中にいるか
			if (player->GetClearFlag() == false)
			{
				//ブロック分繰り返す
				for (int i = 0; i < block.size(); i++)
				{
					//ブロックの種類が空白か
					if (block[i]->GetKind() != None)
					{
						//ブロックがフィルターの中にいるか
						if (block[i]->GetClearFlag() == false)
						{
							//プレイヤーのTransformを代入
							CheckTrans1 = player->GetTransform();

							//ブロックのTransformを代入
							CheckTrans2 = block[i]->GetTransform();

							//判定外に出るまで繰り返す
							//while (BoxCollision(CheckTrans1, CheckTrans2, true))
							//{
								//ちょっと戻す
							//player->PlayerMove(Vector3((AW.x_ - DS.x_), (AW.y_ - DS.y_), 0.0f));

							if (BoxCollision(CheckTrans1, CheckTrans2, true))
							{
								player->SetPos(BoxCollision(CheckTrans1, CheckTrans2, DS, AW));
							}
							//再代入
						//	CheckTrans1 = player->GetTransform();
						//}
						}
					}
				}
			}
		}
	}

	//位置更新
	player->Update();

	// ゴール
	goal_.UpdateMatrix();
	goalDra_.Update();


	// 天球更新
	skydome_.Update();


	// パーティクル更新
	particleMan_.Update();


	// プレイヤー操縦なら
	if (player->GetPlayFlag())
	{
		// プレイヤー追従
		followPoint_ = player->GetPos();
	}
	// それ以外なら
	else
	{
		// プレイヤー追従
		followPoint_ = filter->GetTransform(5).pos_;
	}

	// カメラ更新
	scrollCamera_.Update();

	// ビュープロジェクションにカメラ代入
	transferVP_ = scrollCamera_.GetViewProjection();

	// ビュープロジェクション
	transferVP_.UpdateMatrix();

	//ゴール判定
	if (BoxCollision(player->GetTransform(), goal_, false))
	{
		SceneManager::GetInstance()->Change("RESULT", "BLACKOUT");
	}

	// 次のシーンへ
	//if (sKeys_->IsTrigger(DIK_0))
	//{
	//	SceneManager::GetInstance()->Change("SELECT", "INFECTION");
	//	//SceneManager::GetInstance()->Change("RESULT", "INFECTION");
	//}

	//死亡判定
	if (player->GetPos().y_ < -15)
	{
		SceneManager::GetInstance()->Change("PLAY", "BLACKOUT");
		player->Reset();
		filter->Reset();
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
	player->PreDraw();

	// ブロック前描画
	for (size_t i = 0; i < block.size(); i++)
	{
		block[i]->Draw();
	}

	// ゴール描画
	goalDra_.Draw();


	// パーティクル
	particleMan_.Draw();

	// エフェクト
	effectMan_.Draw();

	// --------------- //


	// フィルター描画
	filter->Draw();


	// ----- Post ----- //

	// プレイヤー後描画
	player->PostDraw();

	// --------------- //
}

void PlayScene::DrawSprite3Ds()
{

}

void PlayScene::DrawFrontSprite2Ds()
{
	// HUD描画
	hud_.Draw();

	conSpr_->Draw(conObj_.get());
	conSpr2_->Draw(conObj2_.get());
	conSpr3_->Draw(conObj3_.get());
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
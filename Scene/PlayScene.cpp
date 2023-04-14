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

	// ----- スプライト (3D) ----- //

	// ------- モデル ------- //

	// ----- 静的初期化 ----- //

	// パーティクル
	ParticleManager::StaticInitialize(&transferVP_);

	// エフェクト
	EffectManager::StaticInitialize(&particleMan_);

	bool IsplayF = player->GetClearFlag();

	// 描画クラス全て
	DrawerManager::StaticInitialize(&IsplayF, &transferVP_, &particleMan_);
}
#pragma endregion


#pragma region 初期化
void PlayScene::Initialize()
{
	// プレイヤー操作初期化
	//isPlayer_ = true;
	//player_->SetClearFlag(true);
	//filter_->SetNowMove(player_->GetClearFlag());

	float scaleVal = harfScale;
	Vector3 scale = { scaleVal,scaleVal,scaleVal };

	// ----- プレイヤー ----- //

	// トランスフォーム (位置、回転、大きさ)
	player->Initialize({ -50.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f }, { scale.x_ * 2.0f - 0.2f,scale.y_ * 2.0f - 0.2f,scale.z_ * 2.0f - 0.2f });

	//ディレクション(向き)
	player->SetDirection(YMath::Vector3{ +1.0f, 0.0f, 0.0f });

	player->Reset();

	//
	//player_->SetClearFlag(true);

	// ----- フィルター ----- //

	// トランスフォーム (位置、回転、大きさ)
	filter->Initialize({ 0.0f, 0.0f, 3.0f }, {}, { 1.5f,1.5f,1.5f });

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
			Block* newBlock = new Block();

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
			block.push_back(newBlock);
		}
	}

	//種類によってブロックを変更
	for (int i = 0; i < block.size(); i++)
	{
		block[i]->SetMode();
	}

	// ----- ゲート ----- //

	// トランスフォーム (位置、回転、大きさ)
	gate_.Initialize({ {-20.0f,0.0f,0.0f}, {}, scale });
	// 描画用クラス初期化 (親トランスフォーム、初期色)
	gateDra_.Initialize(&gate_, IDrawer::Mode::Red);


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
		//プレイヤーとフィルターが当たってないなら
		if (!BoxCollision(player->GetTransform(), filter->GetTransform(), true))
		{
			//操作フラグを反転
			player->ChengePlayFlag();

			//操作してるobjを表示するスプライトの変更
			if (player->GetPlayFlag()) { hud_.SetPilot(HUDDrawerCommon::Pilot::Player); }
			else { hud_.SetPilot(HUDDrawerCommon::Pilot::Filter); }
		}
	}

	//デバッグ用のリセットボタン
	if (sKeys_->IsTrigger(DIK_R))
	{
		player->Reset();
		filter->Reset();
	}

	//格納用Vector
	YMath::Vector3 result(0.0f, 0.0f, 0.0f);

	//値を0に
	player->SetMovePos(result);
	filter->SetMovePos(result);

	//入力状態を入手
	result.x_ = sKeys_->Horizontal(Keys::MoveStandard::WASD);
	result.y_ = sKeys_->Vertical(Keys::MoveStandard::WASD);
	result.z_ = 0.0f;

	float playerA = 0.3f;
	float filterA = 0.3f;

	//今のアクティブ状態
	if (player->GetPlayFlag())
	{
		result.x_ *= playerA;

		//プレイヤーはy軸はジャンプのみ
		result.y_ = 0.0f;

		//プレイヤーの移動量格納
		player->SetMovePos(result);
	}
	else
	{
		result.x_ *= filterA;

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

		if (block[i]->GetKind() == ColorB)
		{
			if (BoxCollision(block[i]->GetTransform(), player->GetTransform(), true))
			{
				//タイマーを設定
				block[i]->SetTimer(10);
			}

			//フィルターと当たってたら
			if (BoxCollision(block[i]->GetTransform(), filter->GetTransform(), true))
			{
				//透けるフラグをonに
				block[i]->SetClearFlag(true);

				//タイマーを設定
				block[i]->SetTimer(50);
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
		//if (player->GetJumpFlag())
		//{
		//	//重力0
		//	player->SetGravity(0.0f);
		//	player->SetGravityPower(0.00f);
		//}

		//重力、浮力を加算
		player->AddGravity();

		//フィルターと重なっているか
		player->SetClearFlag(BoxCollision(player->GetTransform(), filter->GetTransform(), true));

		//ジャンプフラグがONなら
		if (player->GetJumpFlag())
		{
			//if (player->GetGravity() < 0.3f)
			//{
			//	//入力方向手動代入
			//	DS.x_ = 0;
			//	DS.y_ = 1.0f;
			//	AW.x_ = 0;
			//	AW.y_ = 0.0f;
			//}
			//else
			{
				//入力方向手動代入
				DS.x_ = 0;
				DS.y_ = 0.0f;
				AW.x_ = 0;
				AW.y_ = 1.0f;
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

							////判定外に出るまで繰り返す
							//while (BoxCollision(CheckTrans1, CheckTrans2, false))
							//{
							//	//ちょっと戻す
							//	player->PlayerMove(Vector3((AW.x_ - DS.x_), (AW.y_ - DS.y_), 0.0f));

							//	//再代入
							//	CheckTrans1 = player->GetTransform();

							//	//下に埋まった瞬間ジャンプフラグをfalseに
							//	player->SetJumpFlag(false);
							//}
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
			player->SetGravity(0.1f);

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
							}

							////判定外に出るまで繰り返す
							//while (BoxCollision(CheckTrans1, CheckTrans2, false))
							//{
							//	//ちょっと戻す
							//	player->PlayerMove(Vector3((AW.x_ - DS.x_), (AW.y_ - DS.y_), 0.0f));

							//	//再代入
							//	CheckTrans1 = player->GetTransform();
							//}
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

							//判定外に出るまで繰り返す
							/*while (BoxCollision(CheckTrans1, CheckTrans2, true))
							{*/

							if (BoxCollision(CheckTrans1, CheckTrans2, true))
							{
								//ちょっと戻す
								player->SetPos(BoxCollision(CheckTrans1, CheckTrans2, DS, AW));
							}

							//再代入
							//CheckTrans1 = player->GetTransform();
						//}

						//player->PlayerMove(Vector3((AW.x_ - DS.x_), (AW.y_ - DS.y_), 0.0f));
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

	//ゴール判定
	if (BoxCollision(player->GetTransform(), goal_, false))
	{
		SceneManager::GetInstance()->Change("RESULT", "BLACKOUT");
	}

	// 次のシーンへ
	if (sKeys_->IsTrigger(DIK_0))
	{
		SceneManager::GetInstance()->Change("RESULT", "INFECTION");
	}

	/*bool check = BoxCollision(player->GetTransform(), filter->GetTransform(), true);

	ImGui::Begin("F");
	ImGui::Checkbox("F", &check);
	ImGui::End();*/

	//rightleftで横移動
	//transferVP_.eye_.x_ += sKeys_->Horizontal(Keys::MoveStandard::Arrow) * 0.1f;
	//transferVP_.target_.x_ += sKeys_->Horizontal(Keys::MoveStandard::Arrow) * 0.1f;

	////updownで奥行き確認
	//transferVP_.eye_.z_ += sKeys_->Vertical(Keys::MoveStandard::Arrow) * 0.1f;

	transferVP_.target_.x_ = player->GetTransform().pos_.x_;
	transferVP_.target_.y_ = player->GetTransform().pos_.y_;
	transferVP_.eye_.x_ = player->GetTransform().pos_.x_;
	transferVP_.eye_.y_ = player->GetTransform().pos_.y_;

	//// ビュープロジェクション
	//transferVP_.UpdateMatrix();
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
	player->PreDraw();

	// ブロック前描画
	for (size_t i = 0; i < block.size(); i++)
	{
		block[i]->PreDraw();
	}

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
	filter->Draw();


	// ----- Post ----- //

	// プレイヤー後描画
	player->PostDraw();

	// ブロック後描画
	for (size_t i = 0; i < block.size(); i++)
	{
		block[i]->PostDraw();
	}

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
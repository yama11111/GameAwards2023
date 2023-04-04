#include "SelectDrawer.h"
#include "CalcTransform.h"
#include "DrawerConfig.h"
#include "StageConfig.h"
#include <cassert>
#include <cmath>

#pragma region 名前空間

using std::array;
using std::vector;
using std::unique_ptr;
using YGame::Transform;
using YGame::Sprite2DObject;
using YGame::Sprite2D;
using YGame::ModelObject;
using YGame::Model;
using YGame::TextureManager;
using YGame::Color;
using YGame::SlimeActor;
using YMath::Vector3;
using namespace DrawerConfig::Select;

#pragma endregion

std::array<std::unique_ptr<YGame::Sprite2D>, 10> SelectDrawerCommon::sNumberSpr_ =
{ nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
std::unique_ptr<YGame::Model> SelectDrawerCommon::sEarthModel_ = nullptr;
YGame::ViewProjection* SelectDrawerCommon::spVP_ = nullptr;

void SelectDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP)
{
	// nullチェック
	assert(pVP);
	// 代入
	spVP_ = pVP;

	// テクスチャマネージャー取得
	TextureManager* pTexMan = TextureManager::GetInstance();

	// ----- スプライト読み込み ----- //

	// 数字
	sNumberSpr_[0].reset(Sprite2D::Create({}, { pTexMan->Load("Numbers/0.png", false) }));
	sNumberSpr_[1].reset(Sprite2D::Create({}, { pTexMan->Load("Numbers/1.png", false) }));
	sNumberSpr_[2].reset(Sprite2D::Create({}, { pTexMan->Load("Numbers/2.png", false) }));
	sNumberSpr_[3].reset(Sprite2D::Create({}, { pTexMan->Load("Numbers/3.png", false) }));
	sNumberSpr_[4].reset(Sprite2D::Create({}, { pTexMan->Load("Numbers/4.png", false) }));
	sNumberSpr_[5].reset(Sprite2D::Create({}, { pTexMan->Load("Numbers/5.png", false) }));
	sNumberSpr_[6].reset(Sprite2D::Create({}, { pTexMan->Load("Numbers/6.png", false) }));
	sNumberSpr_[7].reset(Sprite2D::Create({}, { pTexMan->Load("Numbers/7.png", false) }));
	sNumberSpr_[8].reset(Sprite2D::Create({}, { pTexMan->Load("Numbers/8.png", false) }));
	sNumberSpr_[9].reset(Sprite2D::Create({}, { pTexMan->Load("Numbers/9.png", false) }));

	// ----- モデル読み込み ----- //

	// 地球
	sEarthModel_.reset(Model::LoadObj("earth", true));
}

void SelectDrawer::Initalize(int* pStageIdx)
{
	// nullチェック
	assert(pStageIdx);
	// 代入
	pStageIdx_ = pStageIdx;

	// ----- 生成 ----- //

	// 核
	core_.reset(new Transform());

	// 色
	color_.reset(Color::Create());

	// 地球
	earthObj_.reset(YGame::ModelObject::Create({}, spVP_, color_.get(), nullptr));
	earthObj_->parent_ = &core_->m_;

	// ステージトランスフォーム (使う用)
	for (size_t i = 0; i < aliveStages_.size(); i++)
	{
		aliveStages_[i].reset(new Transform());
		aliveStages_[i]->parent_ = &core_->m_;
	}
	
	// ステージトランスフォーム (使わない用)
	deadStage_.reset(new Transform());
	
	// ステージ描画クラス
	stageDras_.resize(StageNum); // リサイズ
	for (size_t i = 0; i < stageDras_.size(); i++)
	{
		stageDras_[i].reset(new StageDrawer());
	}

	// ステージ回転用パワー
	stageRotaPows_.resize(static_cast<size_t>(StageNum - 1)); // リサイズ

	// リセット
	Reset();
}

void SelectDrawer::Reset()
{
	// ----- オブジェクト初期化 ----- //
	
	// 核
	core_->Initialize({ {},{0.0f,0.0f,0.0f},{1.0f,1.0f,1.0f} });

	// 大きさの量
	float earthScaleVal = Earth::Scale;
	// 回転の量
	float rotaVal = (PI * 2.0f) / static_cast<float>(aliveStages_.size());

	// 地球
	earthObj_->Initialize({ {},{},{earthScaleVal,earthScaleVal,earthScaleVal} });
	color_->Initialize({ 0.1f,0.0f,0.1f,1.0f });

	// ステージトランスフォーム (使う用)
	for (size_t i = 0; i < aliveStages_.size(); i++)
	{
		// 位置
		float pos = earthScaleVal - 0.5f;

		// 回転 ((360 / size) * idx)
		float rota = rotaVal * i;

		// 回転量に合わせた位置になるように
		aliveStages_[i]->Initialize(
			{
				{ 0.0f, +pos * cosf(rota), +pos * sinf(rota) }, // 位置
				{ rota, 0, 0 }, // 回転
				{ 1.0f, 1.0f, 1.0f } // 大きさ
			}
		);
	}

	// ステージトランスフォーム (使わない用)
	deadStage_->Initialize({ {-2000,-2000,-2000}, {}, {} });

	// ステージ描画クラス
	for (size_t i = 0; i < stageDras_.size(); i++)
	{
		// 番号がトランスフォームの数より小さいなら
		if (i < aliveStages_.size())
		{
			// 使う用のトランスフォームを代入
			stageDras_[i]->Initalize(aliveStages_[i].get(), static_cast<int>(i + 1));
		}
		// それ以外なら
		else
		{
			// 使わない用のトランスフォームを代入
			stageDras_[i]->Initalize(deadStage_.get(), static_cast<int>(i + 1));
		}

		stageDras_[i]->Reset();
	}

	// ----- その他初期化 ----- //

	// 動作中か
	isAct_ = false;

	// 開始時回転用イージング
	startRotaEas_.Initialize(0.0f, -rotaVal / 2.0f, Stage::Exponent);
	
	// 開始時回転用タイマー
	startRotaTim_.Initialize(20);
	startRotaTim_.SetActive(true);


	// ステージ回転用イージング
	stageRotaEas_.Initialize(0.0f, -rotaVal, Stage::Exponent);

	// ステージ回転用パワー
	for (size_t i = 0; i < stageRotaPows_.size(); i++)
	{
		stageRotaPows_[i].Initialize(Stage::Frame);
	}
}

void SelectDrawer::UpdateRotaAnimation()
{
	// 回転量
	float rotaVal = 0.0f;

	// 開始時回転タイマー更新
	startRotaTim_.Update();
	// 開始時回転を代入
	rotaVal += startRotaEas_.In(startRotaTim_.Ratio());

	// ステージ数分回転させる
	// 回転をその分スタート
	for (size_t i = 0; i < stageRotaPows_.size(); i++)
	{
		//回転させるか
		bool isRotaAct = false;
		
		// 現在のステージ数より番号が小さいなら
		if (i < static_cast<size_t>(*pStageIdx_ - 1))
		{
			// 動作する
			isRotaAct = true;
		}

		// 更新
		stageRotaPows_[i].Update(isRotaAct);

		// 回転させるならイーズイン
		if (isRotaAct) { rotaVal += stageRotaEas_.In(stageRotaPows_[i].Ratio()); }
		// それ以外ならイーズアウト
		else { rotaVal += stageRotaEas_.Out(stageRotaPows_[i].Ratio()); }

		//rotaVal += stageRotaEas_.In(stageRotaPows_[i].Ratio());
	}

	// 核に代入 (回転)
	core_->rota_.x_ = rotaVal;
}

void SelectDrawer::Update()
{
	// 動作中じゃないなら弾く
	if (isAct_ == false) { return; }

	// アニメーションの回転更新
	UpdateRotaAnimation();

	// 核
	core_->UpdateMatrix();

	// 地球
	earthObj_->UpdateMatrix();

	// ステージオブジェクト
	for (size_t i = 0; i < aliveStages_.size(); i++)
	{
		aliveStages_[i]->UpdateMatrix();
	}

	// ステージ描画クラス
	for (size_t i = 0; i < stageDras_.size(); i++)
	{
		stageDras_[i]->Update();
	}
}

void SelectDrawer::DrawModel()
{
	// 地球
	sEarthModel_->Draw(earthObj_.get());

	// ステージ描画
	for (size_t i = 0; i < stageDras_.size(); i++)
	{
		stageDras_[i]->DrawModel();
	}
}
void SelectDrawer::DrawSprite3D()
{
	// ステージ描画
	for (size_t i = 0; i < stageDras_.size(); i++)
	{
		stageDras_[i]->DrawSprite3D();
	}
}
void SelectDrawer::DrawSprite2D()
{

}

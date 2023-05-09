#include "SelectDrawer.h"
#include "CalcTransform.h"
#include "MathUtillity.h"
#include "DrawerConfig.h"
#include "StageConfig.h"
#include "CoreColor.h"
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
using YGame::Texture;
using YGame::Color;
using YGame::SlimeActor;
using YGame::LetterBoxDrawer;
using YMath::Vector3;
using YMath::GetRand;
using namespace DrawerConfig::Select;

#pragma endregion

Model* SelectDrawerCommon::spEarthModel_ = nullptr;
Sprite2D* SelectDrawerCommon::spLogoSpr_ = nullptr;
YGame::ViewProjection* SelectDrawerCommon::spVP_ = nullptr;
StageConfig* SelectDrawerCommon::spStageConfig_ = nullptr;
std::unique_ptr<YGame::Material> SelectDrawerCommon::sMate_;
YGame::ParticleManager* SelectDrawerCommon::spParticleMan_ = nullptr;

void SelectDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP, YGame::ParticleManager* pParticleMan)
{
	// nullチェック
	assert(pVP);
	assert(pParticleMan);
	// 代入
	spVP_ = pVP;
	spParticleMan_ = pParticleMan;

	// ----- スプライト読み込み ----- //
	
	// ロゴ
	spLogoSpr_ = Sprite2D::Create({}, { Texture::Load("Select/logo.png", false) });

	// ----- モデル読み込み ----- //

	// 地球
	spEarthModel_ = Model::LoadObj("earth", true);


	// ステージ設定所得
	spStageConfig_ = StageConfig::GetInstance();


	// 生成
	sMate_.reset(YGame::Material::Create(Ambient));


	// 核色
	CoreColor::StaticInitialize();

	// タワー
	TowerDrawerCommon::StaticInitialize(pVP, sMate_.get());

	// 天球
	SkydomeDrawerCommon::StaticInitialize(CoreColor::ColorPtr(CoreColor::ColorType::Red));


	// レターボックス
	YGame::LetterBoxDrawerCommon::StaticInitialize();

	// ステージ
	StageDrawerCommon::StaticInitialize(pVP);

	// カード
	CardDrawerCommon::StaticInitialize();
}

void SelectDrawer::Initialize()
{
	// ----- 生成 ----- //

	// 核
	core_.reset(new Transform());

	// 色
	color_.reset(Color::Create());

	// 地球
	earthObj_.reset(YGame::ModelObject::Create({}, spVP_, color_.get(), nullptr, sMate_.get()));
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
	stageDras_.resize(spStageConfig_->StageNum_); // リサイズ
	for (size_t i = 0; i < stageDras_.size(); i++)
	{
		stageDras_[i].reset(new StageDrawer());

		// 番号がトランスフォームの数より小さいなら
		if (i < aliveStages_.size())
		{
			// 使う用のトランスフォームを代入
			stageDras_[i]->Initialize(aliveStages_[i].get(), static_cast<int>(i + 1));
		}
		// それ以外なら
		else
		{
			// 使わない用のトランスフォームを代入
			stageDras_[i]->Initialize(deadStage_.get(), static_cast<int>(i + 1));
		}
	}
	

	// ステージカード
	cards_.resize(spStageConfig_->StageNum_);
	for (size_t i = 0; i < cards_.size(); i++)
	{
		cards_[i].reset(new Transform());
	}

	// ステージカード描画クラス
	cardDras_.resize(spStageConfig_->StageNum_);
	for (size_t i = 0; i < cardDras_.size(); i++)
	{
		cardDras_[i].reset(new CardDrawer());
		cardDras_[i]->Initialize(cards_[i].get(), static_cast<int>(i + 1));
	}

	// レターボックス初期化
	lbDra_.reset(new LetterBoxDrawer());
	lbDra_->Initialize(LetterBox::TopHeight, LetterBox::BottomHeight);


	// ロゴ初期化
	logoObj_.reset(Sprite2DObject::Create({}));


	// 天球
	skydome_.reset(new Transform());
	skydomeDra_.Initialize(&skydome_->m_, 800.0f);

	// ----- イージング ----- //

	// ステージ回転用パワー
	int staNum = spStageConfig_->StageNum_ - 1;
	stageRotaPows_.resize(static_cast<size_t>(staNum)); // リサイズ

	// 泡グリッド発生用タイマー
	emitBubbleGridTim_.Initialize(BubbleGrid::IntervalFrame);

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
	color_->Initialize({ 0.01f,0.0f,0.0f,1.0f });

	// ----- ステージ ----- //

	// トランスフォーム (使う用)
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
	// トランスフォーム (使わない用)
	deadStage_->Initialize({ {-2000,-2000,-2000}, {}, {} });
	// 描画クラス
	for (size_t i = 0; i < stageDras_.size(); i++)
	{
		stageDras_[i]->Reset();
	}

	// ----- ステージカード ----- //

	// 高さの幅
	float heightVal = Card::TotalHeight / static_cast<float>(spStageConfig_->StageNum_ - 1);

	// トランスフォーム (親)
	for (size_t i = 0; i < cards_.size(); i++)
	{
		// y の位置
		float y = Card::CenterHeight + (Card::TotalHeight / 2.0f)
			- heightVal * static_cast<float>(i);
		
		cards_[i]->Initialize(
			{
				{ Card::DefPosX, y, 0.0f },
				{},
				{ 1.0f, 1.0f, 1.0f }
			}
		);
	}
	// 描画クラス
	for (size_t i = 0; i < cardDras_.size(); i++)
	{
		cardDras_[i]->Reset();
	}


	// レターボックス
	lbDra_->Reset();


	// ロゴ
	logoObj_->Initialize({ Logo::Pos });

	// 天球
	skydomeDra_.Reset(800.0f);

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

	// 泡グリッド発生用タイマー
	emitBubbleGridTim_.Reset(true);

	// 泡グリッド発生
	EmitBubbleCharacter();
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
		int staIdx = spStageConfig_->GetCurrentStageIndex() - 1;
		if (i < static_cast<size_t>(staIdx))
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

	// ----- ステージ ----- //
	
	// トランスフォーム
	for (size_t i = 0; i < aliveStages_.size(); i++)
	{
		aliveStages_[i]->UpdateMatrix();
	}
	// 描画クラス
	for (size_t i = 0; i < stageDras_.size(); i++)
	{
		stageDras_[i]->Update();
	}

	// ----- ステージカード ----- //

	// トランスフォーム
	for (size_t i = 0; i < cards_.size(); i++)
	{
		cards_[i]->UpdateMatrix();
	}
	// 描画クラス
	for (size_t i = 0; i < cardDras_.size(); i++)
	{
		cardDras_[i]->Update();
		
		// 選択中か
		bool isSelect = false;

		// 選択中のステージ番号のとき
		int staIdx = spStageConfig_->GetCurrentStageIndex() - 1;
		if (i == staIdx)
		{
			// 選択
			isSelect = true;
		}

		// 選択中か設定
		cardDras_[i]->SetSelect(isSelect);
	}


	// レターボックス
	lbDra_->Update();

	// 天球
	skydomeDra_.Update();

	// エミッター更新
	UpdateEmitter();
}

void SelectDrawer::UpdateEmitter()
{
	// 発生タイマー更新
	emitBubbleGridTim_.Update();

	// タイマー終了時
	if (emitBubbleGridTim_.IsEnd())
	{
		// 泡グリッド発生
		EmitBubbleCharacter();

		// タイマーリセット + 開始
		emitBubbleGridTim_.Reset(true);
	}
}

void SelectDrawer::EmitBubbleCharacter()
{
	// ランダムな数発生
	size_t emitNum = GetRand(BubbleGrid::MinNum, BubbleGrid::MaxNum);

	// パーティクル発生
	spParticleMan_->EmitBubbleCharacter(
		emitNum,
		BubbleGrid::AliveFrame,
		BubbleGrid::Center, BubbleGrid::Range,
		BubbleGrid::MinScaleSize, BubbleGrid::MaxScaleSize,
		BubbleGrid::MinMoveSpeed, BubbleGrid::MaxMoveSpeed,
		BubbleGrid::MinRotaSpeed, BubbleGrid::MaxRotaSpeed,
		BubbleGrid::Color, BubbleGrid::Place,
		YGame::DrawLocation::Back);

}


void SelectDrawer::Draw()
{
	// 天球
	skydomeDra_.Draw();

	// ステージ描画
	for (size_t i = 0; i < stageDras_.size(); i++)
	{
		stageDras_[i]->Draw();
	}

	// 地球
	spEarthModel_->SetDrawCommand(earthObj_.get(), YGame::DrawLocation::Center);
	
	// レターボックス描画
	lbDra_->Draw(YGame::DrawLocation::Front);

	// カード描画 (後ろから)
	for (int i = static_cast<int>(cardDras_.size()) - 1; i >= 0; i--)
	{
		cardDras_[i]->Draw();
	}

	// ロゴ描画
	spLogoSpr_->SetDrawCommand(logoObj_.get(), YGame::DrawLocation::Front);
}
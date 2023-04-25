#include "BackgroundDrawer.h"
#include "CalcTransform.h"
#include "MathUtillity.h"
#include "CoreColor.h"
#include "DrawerConfig.h"
#include <cassert>

#pragma region 名前空間

using std::array;
using std::unique_ptr;

using YGame::Transform;
using YGame::ModelObject;
using YGame::Model;
using YGame::Color;
using YGame::Material;

using YMath::Ease;
using YMath::Timer;
using YMath::Power;
using YMath::Vector3;
using YMath::Vector4;
using YMath::GetRand;

using namespace DrawerConfig::Background;

#pragma endregion

#pragma region Static

YGame::ParticleManager* BackgroundDrawerCommon::spParticleMan_ = nullptr;
unique_ptr<Material> BackgroundDrawerCommon::sBackMate_;
bool BackgroundDrawerCommon::sIsUnify_ = false;
Timer BackgroundDrawerCommon::sUnifyTim_;
Ease<Vector3> BackgroundDrawerCommon::sUnifyAmbientEas_;

#pragma endregion

void BackgroundDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP, YGame::ParticleManager* pParticleMan)
{
	// nullチェック
	assert(pParticleMan);
	
	// 代入
	spParticleMan_ = pParticleMan;


	// 生成
	sBackMate_.reset(YGame::Material::Create(Ambient));


	// クリア時アンビエント用タイマー
	sUnifyTim_.Initialize(Unify::Frame);

	// クリア時背景アンビエントイージング
	sUnifyAmbientEas_.Initialize(Ambient, ClearAmbient, Unify::Exponent);
	

	// タワー
	TowerDrawerCommon::StaticInitialize(pVP, sBackMate_.get());

	// 天球
	SkydomeDrawerCommon::StaticInitialize(CoreColor::ColorPtr(CoreColor::ColorType::Red));
}

void BackgroundDrawerCommon::StaticReset()
{
	// 統一フラグ
	sIsUnify_ = false;

	// クリア時アンビエント用タイマー
	sUnifyTim_.Reset(false);
}

void BackgroundDrawerCommon::StaticUpdate()
{
	// クリア時アンビエント用タイマー
	sUnifyTim_.Update();

	// イーズイン
	Vector3 ambient = sUnifyAmbientEas_.In(sUnifyTim_.Ratio());

	// アンビエント設定
	sBackMate_->SetAmbient(ambient);
}

void BackgroundDrawerCommon::StaticUnify()
{
	// 統一開始
	sIsUnify_ = true;

	// タイマーリセット + 開始
	sUnifyTim_.Reset(true);
}

void BackgroundDrawer::Initialize()
{
	// 天球
	skydome_.Initialize({});
	
	// 天球描画クラス
	skydomeDra_.Initialize(&skydome_.m_, SkydomeSize);


	// 泡グリッド発生用タイマー
	emitBubbleGridTim_.Initialize(BubbleGrid::IntervalFrame);


	// リセット
	Reset();
}

void BackgroundDrawer::Reset()
{
	// タワー初期化
	InitializeTowers();

	// 天球
	skydome_.Initialize({});

	// 天球描画クラス
	skydomeDra_.Reset(SkydomeSize);


	// 泡グリッド発生用タイマー
	emitBubbleGridTim_.Reset(true);

	// 泡グリッド発生
	EmitBubbleGrid();
}

void BackgroundDrawer::Update()
{
	// タワー毎に
	for (std::unique_ptr<Tower>& tower : towers_)
	{
		//// 親トランスフォーム更新
		//tower->transform_.UpdateMatrix();

		// 描画クラス更新
		tower->drawer_.Update();
	}

	// 天球
	skydome_.UpdateMatrix();

	// 天球描画クラス
	skydomeDra_.Update();

	// エミッター更新
	UpdateEmitter();
}

void BackgroundDrawer::Draw()
{
	// タワー毎に
	for (std::unique_ptr<Tower>& tower : towers_)
	{
		// 描画
		tower->drawer_.Draw();
	}

	// 天球
	skydomeDra_.Draw();
}

void BackgroundDrawer::InitializeTowers()
{
	// タワーリストが空じゃないなら
	if (towers_.empty() == false)
	{
		// リストクリア
		towers_.clear();
	}

	// 既定の数だけ
	for (size_t i = 0; i < Towers::Num; i++)
	{
		// 新規タワー生成
		std::unique_ptr<Tower> newTower = std::make_unique<Tower>();

		// 親トランスフォーム初期化
		newTower->transform_.Initialize(
			{
				Towers::Poss[i], Towers::Rotas[i], Towers::Scales[i]
			});

		// 状態
		IMode::Type type = static_cast<IMode::Type>(Towers::ModeIdx[i]);

		// 描画クラス初期化
		newTower->drawer_.Initialize(&newTower->transform_.m_, type);

		// 挿入
		towers_.push_back(std::move(newTower));
	}
}

void BackgroundDrawer::UpdateEmitter()
{
	// 発生タイマー更新
	emitBubbleGridTim_.Update();

	// タイマー終了時
	if (emitBubbleGridTim_.IsEnd())
	{
		// 泡グリッド発生
		EmitBubbleGrid();

		// タイマーリセット + 開始
		emitBubbleGridTim_.Reset(true);
	}
}

void BackgroundDrawer::EmitBubbleGrid()
{
	// ランダムな数発生
	size_t emitNum = GetRand(BubbleGrid::MinNum, BubbleGrid::MaxNum);

	// パーティクル発生
	spParticleMan_->EmitBubbleGrid(
		emitNum,
		BubbleGrid::AliveFrame,
		BubbleGrid::Center, BubbleGrid::Range,
		BubbleGrid::MinScaleSize, BubbleGrid::MaxScaleSize,
		BubbleGrid::MinMoveSpeed, BubbleGrid::MaxMoveSpeed,
		BubbleGrid::MinRotaSpeed, BubbleGrid::MaxRotaSpeed,
		BubbleGrid::Color, BubbleGrid::Place);

}

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
	emitBubbleGridTim_.Initialize(Emit::IntervalFrame);


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
	// 発生数
	size_t emitNum = 0;

	// ランダムな数発生
	emitNum = GetRand(Emit::MinNum, Emit::MaxNum);

	// 発生の数だけ
	for (size_t i = 0; i < emitNum; i++)
	{

		// 設定用ステータス
		Transform::Status status;

		// 範囲にランダムな位置
		Vector3 range(
			GetRand(-Emit::Range.x_, Emit::Range.x_, Emit::Place),
			GetRand(-Emit::Range.y_, Emit::Range.y_, Emit::Place),
			GetRand(-Emit::Range.z_, Emit::Range.z_, Emit::Place)
		);

		// 中心 + ランダム範囲の位置に
		status.pos_ = Emit::Center + range;

		// ランダムなサイズ取得
		float scaleSize =
			GetRand(Emit::MinScaleSize, Emit::MaxScaleSize, Emit::Place);

		// ランダムなサイズ適応
		status.scale_ = Vector3(scaleSize, scaleSize, scaleSize);


		// 上方向にランダムな移動スピード
		Vector3 moveSpeed(
			0.0f,
			GetRand(Emit::MinMoveSpeed, Emit::MaxMoveSpeed, Emit::Place),
			0.0f
		);


		// 全方向にランダムな回転スピード
		Vector3 rotaSpeed(
			GetRand(Emit::MinRotaSpeed, Emit::MaxRotaSpeed, Emit::Place),
			GetRand(Emit::MinRotaSpeed, Emit::MaxRotaSpeed, Emit::Place),
			GetRand(Emit::MinRotaSpeed, Emit::MaxRotaSpeed, Emit::Place)
		);


		// パーティクル発生
		spParticleMan_->EmitBubbleGrid(
			Emit::AliveFrame,
			status, moveSpeed, rotaSpeed,
			Emit::Color);

	}
}

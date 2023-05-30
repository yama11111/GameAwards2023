#include "PlayerDrawer.h"
#include "CalcTransform.h"
#include "MathUtillity.h"
#include "DrawerConfig.h"
#include <cassert>

#pragma region 名前空間

using std::array;
using std::unique_ptr;

using YGame::Transform;
using YGame::Model;
using YGame::CBColor;

using YGame::SlimeActor;

using YMath::Vector3;
using YMath::Vector4;
using YMath::GetRand;

using namespace DrawerConfig::Player;

#pragma endregion

#pragma region Static

array<Model*, PlayerDrawerCommon::sPartsNum_> PlayerDrawerCommon::spModels_ =
{
	nullptr
};

#pragma endregion

// インデックス
static const size_t BodyIdx = static_cast<size_t>(PlayerDrawerCommon::Parts::eBody); // 体

void PlayerDrawerCommon::StaticInitialize()
{
	// ----- モデル読み込み ----- //

	spModels_[BodyIdx] = Model::LoadObj("player", true); // 体
}


void PlayerDrawer::Initialize(Transform* pParent, Vector3* pDirection)
{
	// nullチェック
	assert(pDirection);

	// 基底クラス初期化
	IDrawer::Initialze(pParent);

	// 色生成
	color_.reset(CBColor::Create());
	teleportColor_.reset(CBColor::Create());

	// オブジェクト生成 + 親行列挿入 (パーツの数)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		// 生成
		modelObjs_[i].reset(Model::Object::Create(Transform::Status::Default(), spVP_, color_.get(), spMate_));

		// 親行列代入
		modelObjs_[i]->parent_ = &core_->m_;
	}
	for (size_t i = 0; i < teleportModelObjs_.size(); i++)
	{
		// 生成
		teleportModelObjs_[i].reset(Model::Object::Create(
			{ pParent_->pos_, pParent_->rota_, pParent_->scale_ },
			spVP_, teleportColor_.get(), spMate_));
	}

	// 向きポインタ挿入
	pDirection_ = pDirection;

	// リセット
	Reset();
}

void PlayerDrawer::Reset()
{
	// リセット
	IDrawer::Reset();

	// モデル用オブジェクト初期化
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		// 初期化
		modelObjs_[i]->Initialize({ {}, {}, DefScale });
	}

	// 色初期化
	color_->SetRGB(DefColor);
	teleportColor_->SetRGB(DefColor);

	// ----- アニメーション ----- //
	
	// 移動中か
	isMove_ = false;
	// 移動していたか
	isElderMove_ = false;
	// 移動用回転パワー
	moveRotaPow_.Initialize(Move::Rota::Frame);
	// 移動用回転イージング
	moveRotaEas_.Initialize(0.0f, Move::Rota::Value, Move::Rota::Exponent);
	// 移動用エミットタイマー
	moveEmitTimer_.Initialize(Move::Smoke::IntervalFrame);

	// テレポートフラグ
	isTeleport_ = false;
	// テレポート用タイマー
	teleportTim_.Initialize(5);
	// テレポート用スケールイージング
	teleportScaleEas_.Initialize(0.0f, -1.0f, Respawn::Exponent);
	// テレポート用アルファ値イージング
	teleportAlphaEas_.Initialize(0.5f, 0.0f, Respawn::Exponent);

	// リスポーンフラグ
	isRespawn_ = false;
	// リスポーン用タイマー
	respawnTim_.Initialize(Respawn::Frame);
	// リスポーン用スケールイージング
	respScaleEas_.Initialize(-0.25f, 0.0f, Respawn::Exponent);
	// リスポーン用アルファ値イージング
	respAlphaEas_.Initialize(0.0f, 1.0f, Respawn::Exponent);

	// ゴールフラグ
	isGoal_ = false;
	// ゴール用タイマー
	goalTim_.Initialize(Respawn::Frame);
	// ゴール用スケールイージング
	goalScaleEas_.Initialize(0.0f, -1.0f, Respawn::Exponent);
	// ゴール用アルファ値イージング
	goalAlphaEas_.Initialize(1.0f, 0.0f, Respawn::Exponent);;
}

void PlayerDrawer::ResetAnimation()
{
	// ブヨブヨアニメーション初期化
	SlimeActor::Initialize();

	// 移動タイマーリセット
	moveEmitTimer_.Reset(false);

	// テレポート用タイマーリセット
	teleportTim_.Reset(false);

	// リスポーン用タイマーリセット
	respawnTim_.Reset(false);

	// ゴール用タイマーリセット
	goalTim_.Reset(false);
}

void PlayerDrawer::Update()
{
	// アニメーション用
	Vector3 pos{}, rota{}, scale{};
	// 向き合わせ
	rota = YMath::AdjustAngle(*pDirection_);

	// 基底クラス更新 
	IDrawer::Update({ pos, rota, scale });

	// アニメーション用
	animePos = animeRota = animeScale = {};
	teleportAnimePos = teleportAnimeRota = teleportAnimeScale = {};	

	UpdateMoveAnimation();
	UpdateTeleportAnimation();
	UpdateDeadAnimation();
	UpdateRespawnAnimation();
	UpdateGoalAnimation();

	// 行列更新 (子)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix({ animePos, animeRota, animeScale });
	}
	for (size_t i = 0; i < teleportModelObjs_.size(); i++)
	{
		teleportModelObjs_[i]->UpdateMatrix({ teleportAnimePos, teleportAnimeRota, teleportAnimeScale });
	}
}

void PlayerDrawer::Draw()
{
	// モデルの数描画
	for (size_t i = 0; i < spModels_.size(); i++)
	{
		spModels_[i]->SetDrawCommand(modelObjs_[i].get(), YGame::DrawLocation::Center);
		if (isTeleport_)
		{
			spModels_[i]->SetDrawCommand(teleportModelObjs_[i].get(), YGame::DrawLocation::Center);
		}
	}
}

void PlayerDrawer::UpdateSmokeEmitter()
{
	// 移動中なら
	if (isMove_)
	{
		// 前回移動していなかったら
		if (isElderMove_ == false)
		{
			// エミットタイマーリセット
			moveEmitTimer_.Reset(true);
		}

		// エミットタイマー更新
		moveEmitTimer_.Update();

		// タイマー終了したら
		if (moveEmitTimer_.IsEnd())
		{
			// エミットタイマーリセット
			moveEmitTimer_.Reset(true);

			// 向き
			float dire = 0.0f;

			// 右向きなら
			if (pDirection_->x_ > 0)
			{
				// マイナス
				dire = -1.0f;
			}
			// 左向きなら
			else if (pDirection_->x_ < 0)
			{
				// プラス
				dire = +1.0f;
			}

			// 発生数
			size_t emitNum = GetRand(Move::Smoke::MinNum, Move::Smoke::MaxNum);
			
			
			// 最小移動スピード
			Vector3 minMoveSpeed = Move::Smoke::MinMoveSpeed;
			minMoveSpeed.x_ *= dire;
			
			// 最大移動スピード
			Vector3 maxMoveSpeed = Move::Smoke::MaxMoveSpeed;
			maxMoveSpeed.x_ *= dire;

			// 最小値が最大値を超えたら
			if (maxMoveSpeed.x_ < minMoveSpeed.x_)
			{
				// 入れ替える
				float sp = maxMoveSpeed.x_;
				maxMoveSpeed.x_ = minMoveSpeed.x_;
				minMoveSpeed.x_ = sp;
			}

			// 煙発生
			spParticleMan_->EmitSmoke(
				emitNum,
				Move::Smoke::AliveFrame,
				pParent_->pos_, Move::Smoke::Range,
				Move::Smoke::MinScaleSize, Move::Smoke::MaxScaleSize,
				minMoveSpeed, maxMoveSpeed,
				Move::Smoke::MinRotaSpeed, Move::Smoke::MaxRotaSpeed,
				Move::Smoke::Color,
				Move::Smoke::Place,
				YGame::DrawLocation::Center);
		}
	}
}

void PlayerDrawer::AnimateJump()
{
	// 伸縮量
	Vector3 val = core_->scale_ * DrawerConfig::Player::Jump::SlimeAction::Value;
	val.y_ *= -1.0f;

	// つぶれる量
	Vector3 squash = +val;
	// のびる量
	Vector3 streach = -val;

	// 時間 (フレーム)
	unsigned int frame = DrawerConfig::Player::Jump::SlimeAction::Frame;
	// 指数 (緩急)
	float pow = DrawerConfig::Player::Jump::SlimeAction::Exponent;

	// ぷよぷよアニメーション
	SlimeActor::Activate(
		{
			{{}, frame, pow},
			{squash, frame, pow},
			{streach, frame, pow},
			{{}, frame, pow },
		}
	);
}
void PlayerDrawer::AnimateLanding()
{
	// つぶれる量
	Vector3 squash = core_->scale_ * DrawerConfig::Player::Landing::SlimeAction::Value;
	squash.y_ *= -1.0f;

	// 時間 (フレーム)
	unsigned int frame = DrawerConfig::Player::Landing::SlimeAction::Frame;
	// 指数 (緩急)
	float exponent = DrawerConfig::Player::Landing::SlimeAction::Exponent;

	// ぷよぷよアニメーション
	SlimeActor::Activate(
		{
			{{}, frame, exponent},
			{squash, frame, exponent},
			{{}, frame, exponent}
		}
	);
}

void PlayerDrawer::AnimateTeleport()
{
	// タイマーリセット + 開始
	teleportTim_.Reset(true);

	for (size_t i = 0; i < teleportModelObjs_.size(); i++)
	{
		// 初期化
		teleportModelObjs_[i]->Initialize({ pParent_->pos_, pParent_->rota_, pParent_->scale_ });
	}

	// テレポート
	isTeleport_ = true;
}

void PlayerDrawer::AnimateDead()
{
	// カメラブレ
	spCamera_->Shaking(0.5f, 0.1f, 100.0f);
}

void PlayerDrawer::AnimateRespawn()
{
	// アニメーションリセット
	ResetAnimation();

	// リスポーンタイマー開始
	respawnTim_.SetActive(true);

	// リスポーンアニメーション開始
	isRespawn_ = true;
}

void PlayerDrawer::AnimateGoal()
{
	// アニメーションリセット
	ResetAnimation();

	// ゴールタイマー開始
	goalTim_.SetActive(true);

	// ゴールアニメーション開始
	isGoal_ = true;
}


void PlayerDrawer::UpdateMoveAnimation()
{
	// 煙発生
	UpdateSmokeEmitter();

	// 回転パワー更新
	moveRotaPow_.Update(isMove_);

	// 回転保存用
	float moveRota = 0.0f;

	// 移動中なら
	if (isMove_)
	{
		// イーズイン
		moveRota += moveRotaEas_.In(moveRotaPow_.Ratio());
	}
	// それ以外なら
	else
	{
		// イーズアウト
		moveRota += moveRotaEas_.Out(moveRotaPow_.Ratio());
	}

	// 回転
	animeRota.x_ = moveRota;

	// 移動フラグ保存
	isElderMove_ = isMove_;
}

void PlayerDrawer::UpdateTeleportAnimation()
{
	if (isTeleport_ == false) { return; }

	// テレポート用タイマー更新
	teleportTim_.Update();
	// テレポート用のスケール計算
	float teleportSca = teleportScaleEas_.In(teleportTim_.Ratio());

	// 代入
	teleportAnimeScale += Vector3(teleportSca, teleportSca, teleportSca);

	// テレポート用のアルファ値計算
	float teleportAlpha = teleportAlphaEas_.In(teleportTim_.Ratio());

	// 代入
	teleportColor_->SetAlpha(teleportAlpha);

	if (teleportTim_.IsEnd())
	{
		isTeleport_ = false;
	}
}

void PlayerDrawer::UpdateDeadAnimation()
{
	if (isDead_ == false) { return; }
}

void PlayerDrawer::UpdateRespawnAnimation()
{
	if (isRespawn_ == false) { return; }
	
	// リスポーン用タイマー更新
	respawnTim_.Update();
	// リスポーン用のスケール計算
	float respSca = respScaleEas_.In(respawnTim_.Ratio());

	// 代入
	animeScale += Vector3(respSca, respSca, respSca);

	// リスポーン用のアルファ値計算
	float respAlpha = respAlphaEas_.In(respawnTim_.Ratio());

	// 代入
	color_->SetAlpha(respAlpha);

	if (respawnTim_.IsEnd())
	{
		isRespawn_ = false;
	}
}

void PlayerDrawer::UpdateGoalAnimation()
{
	if (isGoal_ == false) { return; }

	// リスポーン用タイマー更新
	goalTim_.Update();
	// リスポーン用のスケール計算
	float goalSca = goalScaleEas_.In(goalTim_.Ratio());

	// 代入
	animeScale += Vector3(goalSca, goalSca, goalSca);

	// リスポーン用のアルファ値計算
	float goalAlpha = goalAlphaEas_.In(goalTim_.Ratio());

	// 代入
	color_->SetAlpha(goalAlpha);
}
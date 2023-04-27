#include "Particle.h"
#include <cassert>

using YGame::IParticle;
using YGame::Smoke;
using YGame::RelayBug;
using YGame::Bubble;
using YGame::ModelObject;
using YGame::ViewProjection;
using YGame::Model;
using YGame::Color;
using YMath::Ease;
using YMath::Timer;
using YMath::Power;
using YMath::Vector3;
using YMath::Vector4;
using YMath::Matrix4;

ViewProjection* IParticle::spVP_ = nullptr;
Model* Smoke::spModel_ = nullptr;
Model* Bubble::spModel_ = nullptr;
Model* RelayBug::spModel_ = nullptr;

#pragma region IParticle


void IParticle::StaticInitialize(YGame::ViewProjection* pVP)
{
	// nullチェック
	assert(pVP);
	// 代入
	spVP_ = pVP;
}

void IParticle::Initialize(const uint32_t aliveTime)
{
	// 生存フラグ
	isAlive_ = true;

	// 生存タイマー初期化 + 開始
	aliveTim_.Initialize(aliveTime);
	aliveTim_.SetActive(true);

	// 生成
	color_.reset(Color::Create());
	obj_.reset(ModelObject::Create({}, spVP_, color_.get(), nullptr, nullptr));
}

bool IParticle::UpdateLife()
{
	// 死んでいるなら弾く
	if (isAlive_ == false) { return false; }

	// 生存タイマー更新
	aliveTim_.Update();
	// 生存タイマー終了 → 死亡
	if (aliveTim_.IsEnd()) { isAlive_ = false; }

	// 生きているか返す
	return isAlive_;
}

#pragma endregion

#pragma region Smoke

void Smoke::Emit(
	const uint32_t aliveTime, 
	const Transform::Status status, 
	const Vector3& moveSpeed, 
	const Vector3& rotaSpeed, 
	const Vector3& color)
{
	// ---------- Object ---------- //

	// 基底クラス初期化
	IParticle::Initialize(aliveTime);

	// オブジェクト初期化
	obj_->Initialize(status);

	// 色初期化
	color_->SetRGB(color);

	// ---------- Animation ---------- //

	// 移動スピード
	moveSpeed_ = moveSpeed;

	// 回転スピード
	rotaSpeed_ = rotaSpeed;

	// アルファ値イージング
	alphaEas_.Initialize(1.0f, 0.0f, 3.0f);
}

void Smoke::Update()
{
	// 生命更新
	if (IParticle::UpdateLife() == false) { return; }

	// 移動
	obj_->pos_ += moveSpeed_;

	// 回転
	obj_->rota_ += rotaSpeed_;

	// Object更新
	obj_->UpdateMatrix();

	// アルファ値イージング
	color_->SetAlpha(alphaEas_.In(aliveTim_.Ratio()));
}

void Smoke::Draw()
{
	// 描画
	spModel_->Draw(obj_.get());
}

void Smoke::StaticInitialize(YGame::Model* pModel)
{
	// nullチェック
	assert(pModel);
	// 初期化
	spModel_ = pModel;
}

#pragma endregion

#pragma region RelayBug

void RelayBug::Emit(
	const uint32_t startToRelayFrame,
	const uint32_t relayToEndFrame,
	const Vector3& start, 
	const Vector3& relay, 
	const Vector3& end,
	const Vector3& rota, 
	const Vector3& scale, 
	const Vector3& color)
{
	// ---------- Object ---------- //

	// 基底クラス初期化
	IParticle::Initialize(startToRelayFrame + relayToEndFrame);

	// オブジェクト初期化
	obj_->Initialize({ {}, rota, scale });

	// 色初期化
	color_->SetRGB(color);

	// ---------- Animation ---------- //

	// 開始地点 から 中継地点 までのフラグ を true に
	isStartToRelay_ = true;

	// 開始地点 から 中継地点 までのタイマー
	startToRelayTim_.Initialize(startToRelayFrame);
	
	// タイマー開始
	startToRelayTim_.SetActive(true);


	// 中継地点 から 終了地点 までのフラグ
	isRelayToEnd_ = false;

	// 中継地点 から 終了地点 までのタイマー
	relayToEndTim_.Initialize(relayToEndFrame);


	// 位置イージング
	posEas_.Initialize(start, relay, 3.0f);

	// 終了位置
	end_ = end;
}

void RelayBug::Update()
{
	// 生命更新
	if (IParticle::UpdateLife() == false) { return; }

	// 割合
	float ratio = 0.0f;

	// 開始地点 から 中継地点 なら
	if (isStartToRelay_)
	{
		// タイマー更新
		startToRelayTim_.Update();

		// 割合保存
		ratio = startToRelayTim_.Ratio();

		// イーズアウト
		obj_->pos_ = posEas_.Out(ratio);

		// タイマーが終了したら
		if (startToRelayTim_.IsEnd())
		{
			// 開始地点 から 中継地点 を終了
			isStartToRelay_ = false;

			// 中継地点 から 終了地点 を開始
			isRelayToEnd_ = true;

			// 位置イージング初期化
			posEas_.Initialize(obj_->pos_, end_, 3.0f);

			// タイマー開始
			relayToEndTim_.SetActive(true);
		}
	}
	// 中継地点 から 終了地点なら
	else if (isRelayToEnd_)
	{
		// タイマー更新
		relayToEndTim_.Update();

		// 割合保存
		ratio = relayToEndTim_.Ratio();

		// イーズイン
		obj_->pos_ = posEas_.In(ratio);
	}

	// Object更新
	obj_->UpdateMatrix();
}

void RelayBug::Draw()
{
	// 描画
	spModel_->Draw(obj_.get());
}

void RelayBug::StaticInitialize(YGame::Model* pModel)
{
	// nullチェック
	assert(pModel);
	// 初期化
	spModel_ = pModel;
}

#pragma endregion

#pragma region Bubble

void Bubble::Emit(
	const uint32_t aliveTime,
	const YGame::Transform::Status status,
	const Vector3& moveSpeed,
	const Vector3& rotaSpeed,
	const Vector3& color)
{
	// ---------- Object ---------- //

	// 基底クラス初期化
	IParticle::Initialize(aliveTime);

	// オブジェクト初期化
	obj_->Initialize(status);

	// 色初期化
	color_->SetRGB(color);

	// ---------- Animation ---------- //

	// 移動スピード
	moveSpeed_ = moveSpeed;

	// 回転スピード
	rotaSpeed_ = rotaSpeed;


	// 発生時は動かす
	isScalePowerSwitch_ = true;

	// スケールパワー
	scalePow_.Initialize(10);

	// スケールイージング
	scaleEas_.Initialize(0.0f, status.scale_.x_, 3.0f);
}

void Bubble::Update()
{
	// 生命更新
	if (IParticle::UpdateLife() == false) { return; }

	// 移動
	obj_->pos_ += moveSpeed_;
	
	// 回転
	obj_->rota_ += rotaSpeed_;


	// 生存時間がパワー最大値より少ななら
	if (aliveTim_.End() - aliveTim_.Current() <= scalePow_.Max())
	{
		// スイッチオフ
		isScalePowerSwitch_ = false;
	}

	// パワー更新
	scalePow_.Update(isScalePowerSwitch_);

	// 保存用スケール
	float sca = 0.0f;
	
	// スイッチオンなら
	if (isScalePowerSwitch_)
	{
		// イーズイン
		sca = scaleEas_.In(scalePow_.Ratio());

	}
	// それ以外なら
	else
	{
		// イーズアウト
		sca = scaleEas_.Out(scalePow_.Ratio());
	}

	// スケールに適用
	obj_->scale_ = Vector3(sca, sca, sca);

	// Object更新
	obj_->UpdateMatrix();
}

void Bubble::Draw()
{
	// 描画
	spModel_->Draw(obj_.get());
}

void Bubble::StaticInitialize(Model* pModel)
{
	// nullチェック
	assert(pModel);
	// 初期化
	spModel_ = pModel;
}

#pragma endregion

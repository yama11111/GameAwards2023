#include "Particle.h"
#include <cassert>

using YGame::IParticle;
using YGame::BubbleGrid;
using YGame::ModelObject;
using YGame::ViewProjection;
using YGame::Model;
using YGame::Color;
using YMath::Vector3;
using YMath::Vector4;
using YMath::Matrix4;

ViewProjection* IParticle::spVP_ = nullptr;
Model* BubbleGrid::spModel_ = nullptr;

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

#pragma region BubbleGrid

void BubbleGrid::Emit(
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

void BubbleGrid::Update()
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

void BubbleGrid::Draw()
{
	// 描画
	spModel_->Draw(obj_.get());
}

void BubbleGrid::StaticInitialize(Model* pModel)
{
	// nullチェック
	assert(pModel);
	// 初期化
	spModel_ = pModel;
}

#pragma endregion



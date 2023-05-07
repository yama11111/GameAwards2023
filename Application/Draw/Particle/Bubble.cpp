#include "Bubble.h"

using YGame::IParticleModel;
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

void Bubble::Emit(
	const uint32_t aliveTime,
	const YGame::Transform::Status status,
	const Vector3& moveSpeed,
	const Vector3& rotaSpeed,
	const Vector3& color,
	YGame::Sprite3D* pSprite3D, const DrawLocation& location)
{
	// スプライト3Dポインタ代入
	pSprite3D_ = pSprite3D;

	// ---------- Object ---------- //

	// 基底クラス初期化
	IParticle::Initialize(aliveTime, location);
	IParticleSprite3D::CreateObject(false, false);

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
	if (IParticleSprite3D::UpdateLife() == false) { return; }

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
	pSprite3D_->SetDrawCommand(obj_.get(), location_);
}
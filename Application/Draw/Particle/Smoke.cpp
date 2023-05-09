#include "Smoke.h"

using YGame::IParticleSprite3D;
using YGame::Smoke;
using YGame::ViewProjection;
using YGame::Model;
using YGame::Color;
using YMath::Ease;
using YMath::Timer;
using YMath::Power;
using YMath::Vector3;
using YMath::Vector4;
using YMath::Matrix4;


void Smoke::Emit(
	const uint32_t aliveTime,
	const Transform::Status status,
	const Vector3& moveSpeed,
	const Vector3& rotaSpeed,
	const Vector3& color,
	YGame::Model* pModel, const DrawLocation& location)
{
	// モデルポインタ代入
	pModel_ = pModel;

	// ---------- Object ---------- //

	// 基底クラス初期化
	IParticle::Initialize(aliveTime, location);
	IParticleModel::CreateObject();

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
	pModel_->SetDrawCommand(obj_.get(), location_);
}

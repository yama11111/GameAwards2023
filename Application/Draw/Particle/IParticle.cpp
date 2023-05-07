#include "IParticle.h"
#include <cassert>

using YGame::IParticle;
using YGame::IParticleModel;
using YGame::IParticleSprite3D;
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

ViewProjection* IParticleModel::spVP_ = nullptr;
ViewProjection* IParticleSprite3D::spVP_ = nullptr;

#pragma region IParticle

void IParticle::Initialize(const uint32_t aliveTime, const DrawLocation& location)
{
	// 生存フラグ
	isAlive_ = true;

	// 生存タイマー初期化 + 開始
	aliveTim_.Initialize(aliveTime);
	aliveTim_.SetActive(true);

	// 描画場所
	location_ = location;
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


#pragma region IParticleModel

void IParticleModel::StaticInitialize(YGame::ViewProjection* pVP)
{
	// nullチェック
	assert(pVP);
	// 代入
	spVP_ = pVP;
}

void IParticleModel::CreateObject()
{
	// 生成
	color_.reset(Color::Create());
	obj_.reset(ModelObject::Create({}, spVP_, color_.get(), nullptr, nullptr));
}

#pragma endregion


#pragma region IParticleSprite3D

void IParticleSprite3D::StaticInitialize(YGame::ViewProjection* pVP)
{
	// nullチェック
	assert(pVP);
	// 代入
	spVP_ = pVP;
}

void IParticleSprite3D::CreateObject(const bool isXAxisBillboard, const bool isYAxisBillboard)
{
	// 生成
	color_.reset(Color::Create());
	obj_.reset(Sprite3DObject::Create({}, isXAxisBillboard, isYAxisBillboard, spVP_, color_.get()));
}

#pragma endregion



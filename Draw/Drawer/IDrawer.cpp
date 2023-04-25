#include "IDrawer.h"
#include <cassert>

#pragma region 名前空間

using YGame::Transform;
using YGame::Color;
using YGame::SlimeActor;
using YMath::Vector3;

#pragma endregion

YGame::ViewProjection* IDrawer::spVP_ = nullptr;
YGame::Material* IDrawer::spMate_ = nullptr;
YGame::Camera* IDrawer::spCamera_ = nullptr;
YGame::ParticleManager* IDrawer::spParticleMan_ = nullptr;

void IDrawer::StaticInitialize(
	YGame::ViewProjection* pVP,
	YGame::Material* pMate,
	YGame::Camera* pCamera,
	YGame::ParticleManager* pParticleMan)
{
	// nullチェック
	assert(pVP);
	assert(pMate);	
	assert(pCamera);
	assert(pParticleMan);

	// 代入
	spVP_ = pVP;
	spMate_ = pMate;
	spCamera_ = pCamera;
	spParticleMan_ = pParticleMan;
}

void IDrawer::Initialze(YGame::Transform* pParent, const UINT intervalTime)
{
	// nullチェック
	assert(pParent);
	// 代入
	pParent_ = pParent;

	// オブジェクト生成 + 親行列挿入
	core_.reset(new Transform());
	core_->Initialize({});
	core_->parent_ = &pParent->m_;

	// 立ちモーションタイマー初期化
	idleTim_.Initialize(intervalTime);

	// リセット
	Reset();
}

void IDrawer::Reset()
{
	// 初期化
	SlimeActor::Initialize();

	// オブジェクト初期化
	core_->Initialize({});

	// 立ちモーションタイマーリセット
	idleTim_.Reset(true);
}

void IDrawer::Update(const YGame::Transform::Status& status)
{
	// 更新
	SlimeActor::Update();

	// 立ちモーションタイマー更新
	idleTim_.Update();

	// タイマーが終わったら
	if (idleTim_.IsEnd())
	{
		// 立ちモーション再生
		IdleAnimation();
		// タイマーリセット
		idleTim_.Reset(true);
	}
	
	// 行列更新 (親)
	core_->UpdateMatrix(
		{
			Vector3(0.0f, SlimeActor::JiggleValue().y_, 0.0f) + status.pos_,
			status.rota_,
			SlimeActor::JiggleValue() + status.scale_
		}
	);
}

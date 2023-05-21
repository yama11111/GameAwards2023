#include "IDrawer.h"
#include <cassert>

#pragma region 名前空間

using YGame::Transform;
using YGame::CBColor;
using YGame::SlimeActor;
using YMath::Vector3;

#pragma endregion

#pragma region Static

YGame::ViewProjection* IDrawer::spVP_ = nullptr;
YGame::CBMaterial* IDrawer::spMate_ = nullptr;
YGame::CBLightGroup* IDrawer::spLightGroup_ = nullptr;
YGame::Camera* IDrawer::spCamera_ = nullptr;
YGame::ParticleManager* IDrawer::spParticleMan_ = nullptr;

#pragma endregion

void IDrawer::StaticInitialize(
	YGame::ViewProjection* pVP,
	YGame::CBMaterial* pMate,
	YGame::CBLightGroup* pLightGroup,
	YGame::Camera* pCamera,
	YGame::ParticleManager* pParticleMan)
{
	// nullチェック
	assert(pVP);
	assert(pCamera);
	assert(pParticleMan);

	// 代入
	spVP_ = pVP;
	spMate_ = pMate;
	spLightGroup_ = pLightGroup;
	spCamera_ = pCamera;
	spParticleMan_ = pParticleMan;
}

void IDrawer::Initialze(YGame::Transform* pParent)
{
	// nullチェック
	assert(pParent);
	// 代入
	pParent_ = pParent;

	// オブジェクト生成 + 親行列挿入
	core_.reset(new Transform());
	core_->parent_ = &pParent->m_;

	// リセット
	Reset();
}

void IDrawer::Reset()
{
	// 初期化
	SlimeActor::Initialize();

	// オブジェクト初期化
	core_->Initialize();
}

void IDrawer::Update(const YGame::Transform::Status& status)
{
	// 更新
	SlimeActor::Update();
	
	// 行列更新 (親)
	core_->UpdateMatrix(
		{
			Vector3(0.0f, SlimeActor::JiggleValue().y_, 0.0f) + status.pos_,
			status.rota_,
			SlimeActor::JiggleValue() + status.scale_
		}
	);
}

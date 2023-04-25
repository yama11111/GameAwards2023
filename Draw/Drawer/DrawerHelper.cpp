#include "DrawerHelper.h"

#include "DrawerConfig.h"

#include "CoreColor.h"
#include "PlayerDrawer.h"
#include "BlockDrawer.h"
#include "GridDrawer.h"
#include "GateDrawer.h"
#include "GoalDrawer.h"
#include "BackgroundDrawer.h"
#include "HUDDrawer.h"

#include <cassert>

#pragma region 名前空間

using std::array;
using std::unique_ptr;

using YGame::Transform;
using YGame::ModelObject;
using YGame::Model;
using YGame::Color;
using YGame::Material;

using YGame::SlimeActor;

using YMath::Ease;
using YMath::Power;
using YMath::Vector3;
using YMath::Vector4;

using namespace DrawerConfig;

#pragma endregion

#pragma region Static

unique_ptr<Material> DrawerHelper::sDefMate_;
unique_ptr<Material> DrawerHelper::sBackMate_;

#pragma endregion

void DrawerHelper::StaticInitialize(YGame::ViewProjection* pVP, YGame::Camera* pCamera, YGame::ParticleManager* pParticleMan)
{
	// nullチェック
	assert(pVP);
	assert(pCamera);
	assert(pParticleMan);

	// 生成
	sDefMate_.reset(YGame::Material::Create());

	// 生成
	sBackMate_.reset(YGame::Material::Create(Background::Ambient));


	// ----- 静的初期化 ----- // 
	{
		// 基底クラス
		IDrawer::StaticInitialize(pVP, sDefMate_.get(), pCamera, pParticleMan);

		// 核色
		CoreColor::StaticInitialize();

		// プレイヤー
		PlayerDrawerCommon::StaticInitialize();

		// ブロック
		BlockDrawerCommon::StaticInitialize();

		// ゲート
		GateDrawerCommon::StaticInitialize();

		// ゴール
		GoalDrawerCommon::StaticInitialize();


		// タワー
		TowerDrawerCommon::StaticInitialize(pVP, sBackMate_.get());

		// 天球
		SkydomeDrawerCommon::StaticInitialize();

		// 背景
		BackgroundDrawerCommon::StaticInitialize(pParticleMan);


		// グリッド
		GridDrawerCommon::StaticInitialize(pVP);


		// HUD
		HUDDrawerCommon::StaticInitialize();
	}

	// リセット
	StaticReset();
}

void DrawerHelper::StaticReset()
{
	// 核色リセット
	CoreColor::StaticReset();
}

void DrawerHelper::StaticUpdate()
{
	// 核色更新
	CoreColor::StaticUpdate();
}

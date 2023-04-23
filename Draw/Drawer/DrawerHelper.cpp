#include "DrawerHelper.h"
#include <cassert>

#include "PlayerDrawer.h"
#include "FilterDrawer.h"
#include "BlockDrawer.h"
#include "GridDrawer.h"
#include "GateDrawer.h"
#include "GoalDrawer.h"
#include "BuildingDrawer.h"
#include "SkydomeDrawer.h"
#include "hUDDrawer.h"

using YGame::Model;

std::unique_ptr<YGame::Material> DrawerHelper::sDefMate_;

void DrawerHelper::StaticInitialize(YGame::ViewProjection* pVP, YGame::Camera* pCamera, YGame::ParticleManager* pParticleMan)
{
	// nullチェック
	assert(pVP);
	assert(pCamera);
	assert(pParticleMan);

	// 生成
	sDefMate_.reset(YGame::Material::Create());

	// ----- 静的初期化 ----- // 
	
	// 基底クラス
	IDrawer::StaticInitialize(pVP, sDefMate_.get(), pCamera, pParticleMan);

	// プレイヤー
	PlayerDrawerCommon::StaticInitialize();
	
	// フィルター
	FilterDrawerCommon::StaticInitialize();
	
	// ブロック
	BlockDrawerCommon::StaticInitialize();
	
	// ゲート
	GateDrawerCommon::StaticInitialize();
	
	// ゴール
	GoalDrawerCommon::StaticInitialize();


	// グリッド
	GridDrawerCommon::StaticInitialize(pVP);
	
	// ビル
	BuildingDrawerCommon::StaticInitialize(pVP);
	
	// 天球
	SkydomeDrawerCommon::StaticInitialize();

	// HUD
	HUDDrawerCommon::StaticInitialize();
}

void DrawerHelper::StaticReset()
{
	// ブロック
	BlockDrawerCommon::StaticReset();
}

void DrawerHelper::StaticUpdate()
{
	// ブロック
	BlockDrawerCommon::StaticUpdate();
}

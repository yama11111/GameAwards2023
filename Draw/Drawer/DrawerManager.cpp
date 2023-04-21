#include "DrawerManager.h"
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

void DrawerManager::StaticInitialize(YGame::ViewProjection* pVP, YGame::Camera* pCamera, YGame::ParticleManager* pParticleMan)
{
	// nullチェック
	assert(pVP);
	assert(pCamera);
	assert(pParticleMan);

	// ----- 静的初期化 ----- // 
	
	// 基底クラス
	IDrawer::StaticInitialize(pCamera, pParticleMan);

	// プレイヤー
	PlayerDrawerCommon::StaticInitialize(pVP);
	
	// フィルター
	FilterDrawerCommon::StaticInitialize(pVP);
	
	// ブロック
	BlockDrawerCommon::StaticInitialize(pVP);
	
	// ゲート
	GateDrawerCommon::StaticInitialize(pVP);
	
	// ゴール
	GoalDrawerCommon::StaticInitialize(pVP);


	// グリッド
	GridDrawerCommon::StaticInitialize(pVP);
	
	// ビル
	BuildingDrawerCommon::StaticInitialize(pVP);
	
	// 天球
	SkydomeDrawerCommon::StaticInitialize();

	// HUD
	HUDDrawerCommon::StaticInitialize();
}

#include "DrawerManager.h"
#include <cassert>

#include "PlayerDrawer.h"
#include "FilterDrawer.h"
#include "GateDrawer.h"
#include "GoalDrawer.h"
#include "BlockDrawer.h"
#include "BuildingDrawer.h"
#include "SkydomeDrawer.h"

using YGame::Model;

void DrawerManager::StaticInitialize(YGame::ViewProjection* pVP)
{
	// nullチェック
	assert(pVP);

	// ----- 静的初期化 ----- // 
	
	// プレイヤー
	PlayerDrawerCommon::StaticInitialize(pVP);
	
	// フィルター
	FilterDrawerCommon::StaticInitialize(pVP);
	
	// ゲート
	GateDrawerCommon::StaticInitialize(pVP);
	
	// ゴール
	GoalDrawerCommon::StaticInitialize(pVP);
	
	// ブロック
	BlockDrawerCommon::StaticInitialize(pVP);
	
	// ビル
	BuildingDrawerCommon::StaticInitialize(pVP);
	
	// 天球
	SkydomeDrawerCommon::StaticInitialize();
}

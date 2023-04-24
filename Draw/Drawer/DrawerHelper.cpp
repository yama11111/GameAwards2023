#include "DrawerHelper.h"
#include <cassert>

#include "PlayerDrawer.h"
#include "FilterDrawer.h"
#include "BlockDrawer.h"
#include "GridDrawer.h"
#include "GateDrawer.h"
#include "GoalDrawer.h"
#include "BackgroundDrawer.h"
#include "hUDDrawer.h"

using YGame::Model;

std::unique_ptr<YGame::Material> DrawerHelper::sDefMate_;
std::unique_ptr<YGame::Material> DrawerHelper::sBackMate_;

void DrawerHelper::StaticInitialize(YGame::ViewProjection* pVP, YGame::Camera* pCamera, YGame::ParticleManager* pParticleMan)
{
	// nullチェック
	assert(pVP);
	assert(pCamera);
	assert(pParticleMan);

	// 生成
	sDefMate_.reset(YGame::Material::Create());

	// 生成
	sBackMate_.reset(YGame::Material::Create({ 0.4f,0.3f,0.3f }));

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
	
	// タワー
	TowerDrawerCommon::StaticInitialize(pVP, sBackMate_.get());
	
	// 天球
	SkydomeDrawerCommon::StaticInitialize();

	// 背景
	BackgroundDrawerCommon::StaticInitialize(pParticleMan);

	// HUD
	HUDDrawerCommon::StaticInitialize();
}

void DrawerHelper::StaticReset()
{
	// ブロック
	BlockDrawerCommon::StaticReset();

	// タワー
	TowerDrawerCommon::StaticReset();
}

void DrawerHelper::StaticUpdate()
{
	// ブロック
	BlockDrawerCommon::StaticUpdate();

	// タワー
	TowerDrawerCommon::StaticUpdate();
}

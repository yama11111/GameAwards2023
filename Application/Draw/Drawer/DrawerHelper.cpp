#include "DrawerHelper.h"

#include "DrawerConfig.h"

#include "CoreColor.h"
#include "PlayerDrawer.h"
#include "BlockDrawer.h"
#include "GateDrawer.h"
#include "GoalDrawer.h"
#include "BackgroundDrawer.h"
#include "HUDDrawer.h"

#include <cassert>

#pragma region 名前空間

using std::array;
using std::unique_ptr;

using YGame::Transform;
using YGame::Model;
using YGame::CBColor;
using YGame::CBMaterial;

using YGame::SlimeActor;

using YMath::Ease;
using YMath::Power;
using YMath::Vector3;
using YMath::Vector4;

using namespace DrawerConfig;

#pragma endregion

#pragma region Static

unique_ptr<CBMaterial> DrawerHelper::sDefMate_;

bool DrawerHelper::sIsClear_ = false;
bool DrawerHelper::sIsElderClear_ = false;

#pragma endregion

void DrawerHelper::StaticInitialize(YGame::ViewProjection* pVP, YGame::Camera* pCamera, YGame::ParticleManager* pParticleMan)
{
	// nullチェック
	assert(pVP);
	assert(pCamera);
	assert(pParticleMan);

	// 生成
	sDefMate_.reset(YGame::CBMaterial::Create());

	// ----- 静的初期化 ----- // 
	{
		// 基底クラス
		IDrawer::StaticInitialize(pVP, sDefMate_.get(), nullptr, pCamera, pParticleMan);

		// 核色
		CoreColor::StaticInitialize(true);


		// プレイヤー
		PlayerDrawerCommon::StaticInitialize();

		// ブロック
		BlockDrawerCommon::StaticInitialize();

		// ゲート
		GateDrawerCommon::StaticInitialize();

		// ゴール
		GoalDrawerCommon::StaticInitialize();


		// 背景
		BackgroundDrawerCommon::StaticInitialize(pVP, pParticleMan);



		// HUD
		HUDDrawerCommon::StaticInitialize();
	}

	// リセット
	StaticReset();
}

void DrawerHelper::StaticReset()
{
	// クリアフラグ
	sIsClear_ = false;

	// 前回クリアフラグ
	sIsElderClear_ = false;

	// 核色リセット
	CoreColor::StaticReset();

	// 背景リセット
	BackgroundDrawerCommon::StaticReset();
}

void DrawerHelper::StaticUpdate()
{
	// ゴールした瞬間
	if (sIsClear_ && sIsElderClear_ == false)
	{
		// 色統一
		CoreColor::StaticClearAnimation(CoreColor::ColorType::eBlue);

		// 背景のマテリアル統一
		BackgroundDrawerCommon::StaticUnify();
	}

	// 核色更新
	CoreColor::StaticUpdate();

	// 背景更新
	BackgroundDrawerCommon::StaticUpdate();

	// 前回ゴールフラグ保存
	sIsElderClear_ = sIsClear_;
}

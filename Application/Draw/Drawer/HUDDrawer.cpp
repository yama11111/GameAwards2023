#include "HUDDrawer.h"
#include "HUDConfig.h"

using YGame::Sprite2D;
using YGame::CBColor;
using YGame::Texture;

#pragma region HUDDrawerCommon

void HUDDrawerCommon::StaticInitialize()
{
	// input
	InputDrawerCommon::StaticInitialize();

	// pause
	PauseDrawerCommon::StaticInitialize();
}

#pragma endregion


#pragma region HUDDrawer

void HUDDrawer::Initialize()
{
	// input
	inputDra_.Initialize();

	// pause
	pauseDra_.Initialize();
}

void HUDDrawer::Reset()
{
	// input
	inputDra_.Reset();

	// pause
	pauseDra_.Reset();
}

void HUDDrawer::Update()
{
	// pause
	pauseDra_.Update();

	// É|Å[ÉYíÜÇ»ÇÁíeÇ≠
	if (pauseDra_.IsElderPause()) { return; }


	// input
	inputDra_.Update();
}

void HUDDrawer::Draw()
{
	// input
	inputDra_.Draw();

	// pause
	pauseDra_.Draw();
}

#pragma endregion

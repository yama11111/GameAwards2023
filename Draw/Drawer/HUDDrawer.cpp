#include "HUDDrawer.h"
#include "HUDConfig.h"

using YGame::Sprite2D;
using YGame::Sprite2DObject;
using YGame::Color;
using YGame::Texture;
using namespace HUDConfig::Pilot;

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
	inputDra_.Initialize(InputDrawer::SceneType::Play);

	// pause
	pauseDra_.Initialize(PauseDrawer::SceneType::Play);
}

void HUDDrawer::Reset()
{
	// input
	inputDra_.Reset(InputDrawer::SceneType::Play);

	// pause
	pauseDra_.Reset(PauseDrawer::SceneType::Play);
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

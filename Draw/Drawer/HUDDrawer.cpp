#include "HUDDrawer.h"
#include "HUDConfig.h"

using YGame::Sprite2D;
using YGame::Sprite2DObject;
using YGame::Color;
using YGame::TextureManager;
using namespace HUDConfig::Pilot;

#pragma region HUDDrawerCommon

std::unique_ptr<Sprite2D> HUDDrawerCommon::playerSpr_ = nullptr;
std::unique_ptr<Sprite2D> HUDDrawerCommon::filterSpr_ = nullptr;

void HUDDrawerCommon::StaticInitialize()
{
	// player
	playerSpr_.reset(Sprite2D::Create({}, { TextureManager::GetInstance()->Load("UI/player.png") }));
	// filter
	filterSpr_.reset(Sprite2D::Create({}, { TextureManager::GetInstance()->Load("UI/filter.png") }));


	// input
	InputDrawerCommon::StaticInitialize();

	// pause
	PauseDrawerCommon::StaticInitialize();
}

#pragma endregion


#pragma region HUDDrawer

void HUDDrawer::Initalize(const Pilot& pilot)
{
	// ----- ¶¬ ----- //

	// playerColor
	playerColor_.reset(Color::Create());
	// player
	playerObj_.reset(Sprite2DObject::Create({}, playerColor_.get()));
	
	// filterColor
	filterColor_.reset(Color::Create());
	// filter
	filterObj_.reset(Sprite2DObject::Create({}, filterColor_.get()));


	// input
	inputDra_.Initalize(InputDrawer::SceneType::Play);

	// pause
	pauseDra_.Initalize();

	// ƒŠƒZƒbƒg
	Reset(pilot);
}

void HUDDrawer::Reset(const Pilot& pilot)
{
	// ‘€cŽmÝ’è
	SetPilot(pilot);

	// ----- Object ----- //
	
	// player
	playerObj_->Initialize({ Player, {}, Scale });
	// filter
	filterObj_->Initialize({ Filter, {}, Scale });


	// input
	inputDra_.Reset(InputDrawer::SceneType::Play);

	// pause
	pauseDra_.Reset();
}

void HUDDrawer::Update()
{
	// pause
	pauseDra_.Update();

	// ƒ|[ƒY’†‚È‚ç’e‚­
	if (pauseDra_.IsPause()) { return; }
	
	// player
	playerObj_->UpdateMatrix();
	// filter
	filterObj_->UpdateMatrix();


	// input
	inputDra_.Update();
}

void HUDDrawer::Draw()
{
	// input
	inputDra_.Draw(pilot_ == Pilot::Player);

	// player‚È‚ç
	if (pilot_ == Pilot::Player)
	{
		// filter (æ)
		filterSpr_->Draw(filterObj_.get());
		// player
		playerSpr_->Draw(playerObj_.get());
	}
	// filter‚È‚ç
	else if (pilot_ == Pilot::Filter)
	{
		// player (æ)
		playerSpr_->Draw(playerObj_.get());
		// filter
		filterSpr_->Draw(filterObj_.get());
	}

	// pause
	pauseDra_.Draw();
}

void HUDDrawer::SetPilot(const Pilot& pilot)
{
	// ‘ã“ü
	pilot_ = pilot;

	// player‚È‚ç
	if (pilot == Pilot::Player)
	{
		// ‘€c’†‚©•ª‚©‚é‚æ‚¤‚É
		playerColor_->SetRGBA(OnColor);
		filterColor_->SetRGBA(OffColor);
	}
	// filter‚È‚ç
	else if (pilot == Pilot::Filter)
	{
		// ‘€c’†‚©•ª‚©‚é‚æ‚¤‚É
		playerColor_->SetRGBA(OffColor);
		filterColor_->SetRGBA(OnColor);
	}
}

#pragma endregion

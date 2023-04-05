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
	// ----- 生成 ----- //

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

	// リセット
	Reset(pilot);
}

void HUDDrawer::Reset(const Pilot& pilot)
{
	// 操縦士設定
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

	// ポーズ中なら弾く
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

	// playerなら
	if (pilot_ == Pilot::Player)
	{
		// filter (先)
		filterSpr_->Draw(filterObj_.get());
		// player
		playerSpr_->Draw(playerObj_.get());
	}
	// filterなら
	else if (pilot_ == Pilot::Filter)
	{
		// player (先)
		playerSpr_->Draw(playerObj_.get());
		// filter
		filterSpr_->Draw(filterObj_.get());
	}

	// pause
	pauseDra_.Draw();
}

void HUDDrawer::SetPilot(const Pilot& pilot)
{
	// 代入
	pilot_ = pilot;

	// playerなら
	if (pilot == Pilot::Player)
	{
		// 操縦中か分かるように
		playerColor_->SetRGBA(OnColor);
		filterColor_->SetRGBA(OffColor);
	}
	// filterなら
	else if (pilot == Pilot::Filter)
	{
		// 操縦中か分かるように
		playerColor_->SetRGBA(OffColor);
		filterColor_->SetRGBA(OnColor);
	}
}

#pragma endregion

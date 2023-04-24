#pragma once
#include "InputDrawer.h"
#include "PauseDrawer.h"

class HUDDrawerCommon
{
public:
	// 操縦士
	enum class Pilot
	{
		Player, // プレイヤー
		Filter, // フィルター
	};
protected:	
	// player
	static YGame::Sprite2D* spPlayerSpr_;
	// filter
	static YGame::Sprite2D* spFilterSpr_;
public:
	// 静的初期化
	static void StaticInitialize();
public:
	virtual ~HUDDrawerCommon() = default;
};

class HUDDrawer : private HUDDrawerCommon
{
private:
	// 操縦士
	Pilot pilot_ = Pilot::Player;

	// player
	std::unique_ptr<YGame::Sprite2DObject> playerObj_;
	// filter
	std::unique_ptr<YGame::Sprite2DObject> filterObj_;

	// playerColor
	std::unique_ptr<YGame::Color> playerColor_;
	// filterColor
	std::unique_ptr<YGame::Color> filterColor_;


	// input
	InputDrawer inputDra_;

	// pause
	PauseDrawer pauseDra_;
public:
	// 初期化
	void Initialize(const Pilot& pilot = Pilot::Player);
	// リセット
	void Reset(const Pilot& pilot = Pilot::Player);
	// 更新
	void Update();
	// 描画
	void Draw();
public:
	// 操縦士設定
	void SetPilot(const Pilot& pilot);
	// ポーズ中か
	bool IsPause() const { return pauseDra_.IsPause(); }
};


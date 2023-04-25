#pragma once
#include "InputDrawer.h"
#include "PauseDrawer.h"

class HUDDrawerCommon
{

public:

	// 静的初期化
	static void StaticInitialize();

public:

	virtual ~HUDDrawerCommon() = default;
};

class HUDDrawer : private HUDDrawerCommon
{

private:

	// input
	InputDrawer inputDra_;

	// pause
	PauseDrawer pauseDra_;

public:
	
	// 初期化
	void Initialize();
	
	// リセット
	void Reset();
	
	// 更新
	void Update();
	
	// 描画
	void Draw();

public:
	
	// ポーズ中か
	bool IsPause() const { return pauseDra_.IsPause(); }

};


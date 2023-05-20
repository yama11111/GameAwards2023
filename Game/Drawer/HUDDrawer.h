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
	
	/// <summary> 
	/// 初期化
	/// </summary>
	void Initialize();
	
	/// <summary> 
	/// リセット
	/// </summary>
	void Reset();
	
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	
	/// <summary> 
	/// 描画
	/// </summary>
	void Draw();

public:
	
	// ポーズ中か
	bool IsPause() const { return pauseDra_.IsPause(); }

	// ポーズ中だったか
	bool IsElderPause() const { return pauseDra_.IsElderPause(); }

};


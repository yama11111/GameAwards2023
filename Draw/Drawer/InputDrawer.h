#pragma once
#include "Sprite2D.h"
#include <array>

// 多重定義回避用
namespace YInput { class Keys; }

class InputDrawerCommon
{
protected:
	// キー
	static YInput::Keys* sKeys_;

	// WASD
	static std::unique_ptr<YGame::Sprite2D> keyWASDSpr_;
	// WASD_PUSH
	static std::unique_ptr<YGame::Sprite2D> keyWPushSpr_;
	static std::unique_ptr<YGame::Sprite2D> keyAPushSpr_;
	static std::unique_ptr<YGame::Sprite2D> keySPushSpr_;
	static std::unique_ptr<YGame::Sprite2D> keyDPushSpr_;
	// S_DEAD
	static std::unique_ptr<YGame::Sprite2D> keySDeadSpr_;
	// SPACE
	static std::array<std::unique_ptr<YGame::Sprite2D>, 2> keySpaceSpr_;
	// TAB
	static std::array<std::unique_ptr<YGame::Sprite2D>, 2> keyTabSpr_;
public:
	// 静的初期化
	static void StaticInitialize();
};

class InputDrawer : private InputDrawerCommon
{
private:
	// ----- Object ----- //

	// WASD
	std::unique_ptr<YGame::Sprite2DObject> keyWASDObj_;
	// WASD_PUSH
	std::unique_ptr<YGame::Sprite2DObject> keyWObj_;
	std::unique_ptr<YGame::Sprite2DObject> keyAObj_;
	std::unique_ptr<YGame::Sprite2DObject> keySObj_;
	std::unique_ptr<YGame::Sprite2DObject> keyDObj_;
	// SPACE
	std::unique_ptr<YGame::Sprite2DObject> keySpaceObj_;
	// TAB
	std::unique_ptr<YGame::Sprite2DObject> keyTabObj_;

	// ----- フラグ ----- //

	// WASD
	bool isPushW_ = false;
	bool isPushA_ = false;
	bool isPushS_ = false;
	bool isPushD_ = false;
	// SPACE
	bool isPushSpace_ = false;
	// TAB
	bool isPushTab_ = false;
public:
	// 初期化
	void Initalize();
	// リセット
	void Reset();
	// 更新
	void Update();
	// 描画
	void Draw(const bool isPlayer);
private:
	// フラグ更新
	void UpdatePushFlags();
	// Object更新
	void UpdateObjects();
};


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
	static YGame::Sprite2D* spKeyWASDSpr_;
	// WASD_PUSH
	static YGame::Sprite2D* spKeyWPushSpr_;
	static YGame::Sprite2D* spKeyAPushSpr_;
	static YGame::Sprite2D* spKeySPushSpr_;
	static YGame::Sprite2D* spKeyDPushSpr_;
	// S_DEAD
	static YGame::Sprite2D* spKeySDeadSpr_;
	// SPACE
	static std::array<YGame::Sprite2D*, 2> spKeySpaceSpr_;
	// ESC
	static std::array<YGame::Sprite2D*, 2> spKeyEscSpr_;
public:
	// 静的初期化
	static void StaticInitialize();
public:
	virtual ~InputDrawerCommon() = default;
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
	// ESC
	std::unique_ptr<YGame::Sprite2DObject> keyEscObj_;

	// ----- フラグ ----- //

	// WASD
	bool isPushW_ = false;
	bool isPushA_ = false;
	bool isPushS_ = false;
	bool isPushD_ = false;
	// SPACE
	bool isPushSpace_ = false;
	// ESC
	bool isPushEsc_ = false;
public:
	// 初期化用シーン
	enum class SceneType
	{
		Title, // タイトル
		Select, // ステージセレクト
		Play, // ゲーム
	};
public:
	// 初期化
	void Initalize(const SceneType& sceneType);
	// リセット
	void Reset(const SceneType& sceneType);
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


#pragma once
#include "UIChargeButtonDrawer.h"

// 多重定義回避用
namespace YInput { class Keys; }
namespace YInput { class Mouse; }

class InputDrawerCommon
{

protected:
	
	// キー
	static YInput::Keys* sKeys_;
	
	// マウス
	static YInput::Mouse* sMouse_;
	
	// ----- Button ----- //

	// WASD
	static YGame::UIButtonDrawer spKeyW_;
	static YGame::UIButtonDrawer spKeyA_;
	static YGame::UIButtonDrawer spKeyS_;
	static YGame::UIButtonDrawer spKeyD_;

	// E
	static YGame::UIButtonDrawer spKeyE_;
	// F
	static YGame::UIButtonDrawer spKeyF_;
	// R
	static YGame::UIChargeButtonDrawer spKeyR_;
	
	// SPACE
	static YGame::UIButtonDrawer spKeySpace_;
	
	// LEFT
	static YGame::UIButtonDrawer spMouseL_;
	
	// ESC
	static YGame::UIButtonDrawer spKeyEsc_;


	// プレイヤー操作か
	static bool isPlayer_;

public: 
	
	/// <summary>
	/// 静的初期化
	/// </summary>
	static void StaticInitialize();

	/// <summary>
	/// 静的更新
	/// </summary>
	static void StaticUpdate();
	
	static bool StaticIsReset() { return spKeyR_.IsChargeMax(); }

public:

	static void SetIsPlayer(const bool isPlayer) { isPlayer_ = isPlayer; }

public:
	
	virtual ~InputDrawerCommon() = default;

};

class InputDrawer : private InputDrawerCommon
{

private:

	// WASD
	std::unique_ptr<YGame::Sprite2D::Object> keyWObj_;
	std::unique_ptr<YGame::Sprite2D::Object> keyAObj_;
	std::unique_ptr<YGame::Sprite2D::Object> keySObj_;
	std::unique_ptr<YGame::Sprite2D::Object> keyDObj_;
	
	// E
	std::unique_ptr<YGame::Sprite2D::Object> keyEObj_;
	// F
	std::unique_ptr<YGame::Sprite2D::Object> keyFObj_;
	// R
	std::unique_ptr<YGame::Sprite2D::Object> keyRObj_;
	
	// SPACE
	std::unique_ptr<YGame::Sprite2D::Object> keySpaceObj_;

	// LEFT
	std::unique_ptr<YGame::Sprite2D::Object> mouseLObj_;
	
	// ESC
	std::unique_ptr<YGame::Sprite2D::Object> keyEscObj_;

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
};


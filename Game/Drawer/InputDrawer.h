#pragma once
#include "UIButtonDrawer.h"

// 多重定義回避用
namespace YInput { class Keys; }

class InputDrawerCommon
{

protected:
	
	// キー
	static YInput::Keys* sKeys_;
	
	// ----- Button ----- //

	// WASD
	static YGame::UIButtonDrawer spKeyW_;
	static YGame::UIButtonDrawer spKeyA_;
	static YGame::UIButtonDrawer spKeyS_;
	static YGame::UIButtonDrawer spKeyD_;
	
	// SPACE
	static YGame::UIButtonDrawer spKeySpace_;
	
	// ESC
	static YGame::UIButtonDrawer spKeyEsc_;

public: 
	
	/// <summary>
	/// 静的初期化
	/// </summary>
	static void StaticInitialize();

	/// <summary>
	/// 静的更新
	/// </summary>
	static void StaticUpdate();

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
	
	// SPACE
	std::unique_ptr<YGame::Sprite2D::Object> keySpaceObj_;
	
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


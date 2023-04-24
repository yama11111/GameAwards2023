#pragma once
#include "Sprite2D.h"
#include <array>

// 多重定義回避用
namespace YInput { class Keys; }

class PauseDrawerCommon
{
public:
	// 選択
	enum class Select
	{
		Resume, // 戻る
		Title, // タイトル
	};
protected:
	// キー
	static YInput::Keys* sKeys_;

	// pause
	static YGame::Sprite2D* spPauseSpr_;
	// resume
	static YGame::Sprite2D* spResumeSpr_;
	// title
	static YGame::Sprite2D* spTitleSpr_;
	
	// curten
	static YGame::Sprite2D* spCurtenSpr_;
public:
	// 静的初期化
	static void StaticInitialize();
public:
	virtual ~PauseDrawerCommon() = default;
};

class PauseDrawer : private PauseDrawerCommon
{
private:
	// ----- Object ----- //

	// pause
	std::unique_ptr<YGame::Sprite2DObject> pauseObj_;
	// resume
	std::unique_ptr<YGame::Sprite2DObject> resumeObj_;
	// title
	std::unique_ptr<YGame::Sprite2DObject> titleObj_;

	// curten
	std::unique_ptr<YGame::Sprite2DObject> curtenObj_;
	
	// ----- Color ----- //

	// resumeColor
	std::unique_ptr<YGame::Color> resumeColor_;
	// titleColor
	std::unique_ptr<YGame::Color> titleColor_;

	// curtenColor
	std::unique_ptr<YGame::Color> curtenColor_;


	// ポーズ中か
	bool isPause_ = false;

	// 現在の選択
	Select current_ = Select::Resume;

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
	bool IsPause() const { return isPause_; }
};


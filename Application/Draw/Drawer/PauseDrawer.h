#pragma once
#include "Sprite2D.h"
#include "Lerp.h"
#include "Power.h"
#include <array>

// 多重定義回避用
namespace YInput { class Keys; }

class PauseDrawerCommon
{

public:
	
	// 選択
	enum class Selection
	{
		Resume, // 戻る
		Change, // 遷移
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
	// stage
	static YGame::Sprite2D* spStageSpr_;
	
	// curten
	static YGame::Sprite2D* spCurtenSpr_;

public:
	
	/// <summary> 
	/// 静的初期化
	/// </summary>
	static void StaticInitialize();

public:
	
	virtual ~PauseDrawerCommon() = default;

};

class PauseDrawer : private PauseDrawerCommon
{

private:
	
	// ----- Object ----- //

	// pause
	std::unique_ptr<YGame::Sprite2D::Object> pauseObj_;
	// resume
	std::unique_ptr<YGame::Sprite2D::Object> resumeObj_;
	// change
	std::unique_ptr<YGame::Sprite2D::Object> changeObj_;

	// curten
	std::unique_ptr<YGame::Sprite2D::Object> curtenObj_;
	
	// ----- Color ----- //

	// resumeColor
	std::unique_ptr<YGame::CBColor> resumeColor_;
	// changeColor
	std::unique_ptr<YGame::CBColor> changeColor_;

	// curtenColor
	std::unique_ptr<YGame::CBColor> curtenColor_;


	// ポーズ中か
	bool isPause_ = false;

	// ポーズ中だったか
	bool isElderPause_ = false;

	// 現在の選択
	Selection current_ = Selection::Resume;

	// 選択Resumeパワー
	YMath::Power selectResumePow_;
	
	// 選択Changeパワー
	YMath::Power selectChangePow_;

	// 選択スケールイージング
	YMath::Ease<float> selectScaleEas_;

public:
	// 初期化
	void Initialize();
	// リセット
	void Reset();
	// 更新
	void Update();
	// 描画
	void Draw();
private:
	void ResumeReset();
public:
	// ポーズ中か
	bool IsPause() const { return isPause_; }
	// ポーズ中だったか
	bool IsElderPause() const { return isElderPause_; }
};


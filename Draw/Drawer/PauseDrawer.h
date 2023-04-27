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
	enum class Select
	{
		Resume, // 戻る
		Title, // タイトル
		Stage, // ステージセレクト
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
	// 静的初期化
	static void StaticInitialize();
public:
	virtual ~PauseDrawerCommon() = default;
};

class PauseDrawer : private PauseDrawerCommon
{
public:
	// 初期化用シーン
	enum class SceneType
	{
		Select, // ステージセレクト
		Play, // ゲーム
	};

private:
	// ----- Object ----- //

	// pause
	std::unique_ptr<YGame::Sprite2DObject> pauseObj_;
	// resume
	std::unique_ptr<YGame::Sprite2DObject> resumeObj_;
	// change
	std::unique_ptr<YGame::Sprite2DObject> changeObj_;

	// curten
	std::unique_ptr<YGame::Sprite2DObject> curtenObj_;
	
	// ----- Color ----- //

	// resumeColor
	std::unique_ptr<YGame::Color> resumeColor_;
	// changeColor
	std::unique_ptr<YGame::Color> changeColor_;

	// curtenColor
	std::unique_ptr<YGame::Color> curtenColor_;


	// ポーズ中か
	bool isPause_ = false;

	// ポーズ中だったか
	bool isElderPause_ = false;

	// 現在の選択
	Select current_ = Select::Resume;

	// 現在のシーン
	SceneType sceneType_ = SceneType::Select;

	// 選択Resumeパワー
	YMath::Power selectResumePow_;
	// 選択Changeパワー
	YMath::Power selectChangePow_;

	// 選択スケールイージング
	YMath::Ease<float> selectScaleEas_;

public:
	// 初期化
	void Initialize(const SceneType& sceneType);
	// リセット
	void Reset(const SceneType& sceneType);
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


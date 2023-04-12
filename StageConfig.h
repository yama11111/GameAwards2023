#pragma once

// ステージ設定
class StageConfig
{
public:
	// ステージ数
	const int StageNum_ = 10;
private:
	// 現在のステージ番号
	int currentIdx_ = 1;
public:
	// 初期化
	void Initialize();
public:
	// ステージ番号設定
	void SetCurrentStageIndex(const int index);
	// ステージ番号取得
	int GetCurrentStageIndex() const { return currentIdx_; }
public:
	static StageConfig* GetInstance();
private:
	StageConfig() = default;
	~StageConfig() = default;
	StageConfig(const StageConfig&) = delete;
	const StageConfig& operator=(const StageConfig&) = delete;
};

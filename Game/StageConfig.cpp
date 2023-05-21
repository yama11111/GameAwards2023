#include "StageConfig.h"
#include "MathUtillity.h"

using YMath::Clamp;

StageConfig* StageConfig::GetInstance()
{
	static StageConfig instance;
	return &instance;
}

void StageConfig::Initialize()
{
	currentIdx_ = 1;

	for (size_t i = 0; i < isClears_.size(); i++)
	{
		isClears_[i] = false;
	}
}

void StageConfig::SetCurrentStageIndex(const int index)
{
	// 代入
	currentIdx_ = index;

	// クランプ
	currentIdx_ = Clamp(currentIdx_, 1, StageNum_);
}

void StageConfig::ClearStage(const int index)
{
	// クリア
	isClears_[index] = true;
}

bool StageConfig::GetIsClearStage(const int index)
{
	// クリアしているか
	return isClears_[index];
}

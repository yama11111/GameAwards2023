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
}

void StageConfig::SetCurrentStageIndex(const int index)
{
	// 代入
	currentIdx_ = index;

	// クランプ
	currentIdx_ = Clamp(currentIdx_, 1, StageNum_);
}

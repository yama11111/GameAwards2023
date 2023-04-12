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
	// ‘ã“ü
	currentIdx_ = index;

	// ƒNƒ‰ƒ“ƒv
	currentIdx_ = Clamp(currentIdx_, 1, StageNum_);
}

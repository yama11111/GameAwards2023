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
	// ���
	currentIdx_ = index;

	// �N�����v
	currentIdx_ = Clamp(currentIdx_, 1, StageNum_);
}

void StageConfig::ClearStage(const int index)
{
	// �N���A
	isClears_[index] = true;
}

bool StageConfig::GetIsClearStage(const int index)
{
	// �N���A���Ă��邩
	return isClears_[index];
}

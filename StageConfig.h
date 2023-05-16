#pragma once
#include <array>

// �X�e�[�W�ݒ�
class StageConfig
{

public:
	
	// �X�e�[�W��
	static const int StageNum_ = 10;

private:
	
	// ���݂̃X�e�[�W�ԍ�
	int currentIdx_ = 1;

	// �N���A������
	std::array<bool, StageNum_> isClears_ = {};

public:
	
	// ������
	void Initialize();

public:
	
	// �X�e�[�W�ԍ��ݒ�
	void SetCurrentStageIndex(const int index);
	
	// �X�e�[�W�ԍ��擾
	int GetCurrentStageIndex() const { return currentIdx_; }

	// �X�e�[�W�N���A
	void ClearStage(const int index);

	// �X�e�[�W�N���A
	bool GetIsClearStage(const int index);
	
public:
	
	static StageConfig* GetInstance();

private:
	
	StageConfig() = default;
	~StageConfig() = default;
	StageConfig(const StageConfig&) = delete;
	const StageConfig& operator=(const StageConfig&) = delete;
};

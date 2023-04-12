#pragma once

// �X�e�[�W�ݒ�
class StageConfig
{
public:
	// �X�e�[�W��
	const int StageNum_ = 10;
private:
	// ���݂̃X�e�[�W�ԍ�
	int currentIdx_ = 1;
public:
	// ������
	void Initialize();
public:
	// �X�e�[�W�ԍ��ݒ�
	void SetCurrentStageIndex(const int index);
	// �X�e�[�W�ԍ��擾
	int GetCurrentStageIndex() const { return currentIdx_; }
public:
	static StageConfig* GetInstance();
private:
	StageConfig() = default;
	~StageConfig() = default;
	StageConfig(const StageConfig&) = delete;
	const StageConfig& operator=(const StageConfig&) = delete;
};

#pragma once
#include "ParticleManager.h"
#include "SlimeActor.h"
#include <memory>

// �`����N���X
class IDrawer : protected YGame::SlimeActor
{
public:
	// ���
	enum class Mode
	{
		Normal	  = 0, // �ʏ�
		Red		  = 1, // ��
		Invisivle = 2, // ����
		None, // ����
	};
	// ���[�h�̐�
	static const size_t ModeNum_ = 3;
protected:
	// �g�����X�t�H�[�� 
	std::unique_ptr<YGame::Transform> core_;
	
	// ���݂̏��
	Mode current_ = Mode::Normal;
	// �ύX��̏��
	Mode next_ = Mode::None;
	
	// �������[�V�����p�^�C�}�[
	YMath::Timer idleTim_;
	
	// �e�|�C���^
	YGame::Transform* pParent_ = nullptr;
protected:
	// ������
	void Initialze(YGame::Transform* pParent, const Mode& mode, const UINT intervalTime);
	// ���Z�b�g
	void Reset(const Mode& mode);
	// �X�V
	void Update(const YGame::Transform::Status& status);
protected:
	// �������[�V����
	virtual void IdleAnimation() = 0;
protected:
	// �ÓI�p�[�e�B�N���}�l�[�W���[�|�C���^
	static YGame::ParticleManager* spParticleMan_;
public:
	// �ÓI������
	static void StaticInitialize(YGame::ParticleManager* pParticleMan);
public:
	virtual ~IDrawer() = default;
};


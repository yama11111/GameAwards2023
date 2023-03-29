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
		Normal,	 // �ʏ�
		Red,	 // ��
		None,	 // ����
	};
protected:
	// �g�����X�t�H�[�� 
	std::unique_ptr<YGame::Transform> core_;
	// �F
	std::unique_ptr<YGame::Color> color_;
	
	// ���݂̏��
	Mode current_ = Mode::Normal;
	// �ύX��̏��
	Mode next_ = Mode::None;
	
	// �������[�V�����p�^�C�}�[
	YMath::Timer idleTim_;
protected:
	// ������
	void Initialze(YMath::Matrix4* pParent, const Mode& mode, const UINT intervalTime);
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


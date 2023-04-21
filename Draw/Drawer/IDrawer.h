#pragma once
#include "ParticleManager.h"
#include "SlimeActor.h"
#include "Camera.h"
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
	
	// �������[�V�����p�^�C�}�[
	YMath::Timer idleTim_;
	
	// �e�|�C���^
	YGame::Transform* pParent_ = nullptr;

protected:

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="pParent"> : �e�g�����X�t�H�[��</param>
	/// <param name="mode"> : ���݂̏��</param>
	/// <param name="intervalTime"> : �������[�V�����̊Ԋu</param>
	void Initialze(YGame::Transform* pParent, const Mode& mode, const UINT intervalTime);

	/// <summary>
	/// ���Z�b�g
	/// </summary>
	/// <param name="mode"> : ���݂̏��</param>
	void Reset(const Mode& mode);

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="status"></param>
	void Update(const YGame::Transform::Status& status);

protected:

	/// <summary>
	/// �������[�V����
	/// </summary>
	virtual void IdleAnimation() = 0;

protected:
	
	// �ÓI�J�����|�C���^
	static YGame::Camera* spCamera_;

	// �ÓI�p�[�e�B�N���}�l�[�W���[�|�C���^
	static YGame::ParticleManager* spParticleMan_;

public:

	/// <summary>
	/// �ÓI������
	/// </summary>
	/// <param name="pCamera"> : �J�����|�C���^</param>
	/// <param name="pParticleMan"> : �p�[�e�B�N���}�l�[�W���[�|�C���^</param>
	static void StaticInitialize(YGame::Camera* pCamera, YGame::ParticleManager* pParticleMan);

public:
	
	virtual ~IDrawer() = default;
};


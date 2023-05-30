#pragma once
#include "PlayerDrawer.h"
#include "IObject.h"
#include "YukiMapchipCollider.h"

// �C���N���[�h���p
namespace YInput { class Keys; }

class Player :
	public IObject,
	public YukiMapchipCollider
{

private:

	// �����Ă��邩
	bool isAlive_ = false;

	// �X�s�[�h
	YMath::Vector3 speed_;

	// ����
	YMath::Vector3 direction_;

	// �W�����v��
	int jumpCount_ = 0;


	// �����t���O������������
	bool isGetOffAct_ = false;
	
	// �����t���O�^�C�}�[
	YMath::Timer isGetOffTimer_;


	// ���������Ă��邩
	bool isKeyHolder_ = false;

	// �N���A��
	bool isGameClear_ = false;


	// �`��N���X
	PlayerDrawer drawer_;

public:

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="signIndex"> : �Ŕԍ�</param>
	/// <param name="pos"> : �����ʒu</param>
	/// <param name="isExistKey"> : ��������</param>
	void Initialize(const size_t signIndex, const YMath::Vector3& pos, const bool isExistKey);

	/// <summary>
	/// ���Z�b�g (���g����������)
	/// </summary>
	/// <param name="signIndex"> : �Ŕԍ�</param>
	/// <param name="pos"> : �����ʒu</param>
	/// <param name="isExistKey"> : ��������</param>
	void Reset(const size_t signIndex, const YMath::Vector3& pos, const bool isExistKey);

	/// <summary>
	/// ����O�X�V
	/// </summary>
	void PreUpdate() override;
	
	/// <summary>
	/// �����X�V
	/// </summary>
	void PostUpdate() override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;

	/// <summary>
	/// ���񂾂��擾
	/// </summary>
	/// <returns>���S�t���O</returns>
	bool IsDead() const { return isAlive_ == false && drawer_.IsEndDeadAnime(); }

    void DrawDebug(void);

public:

	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override;

private:

	/// <summary>
	/// �ړ�
	/// </summary>
	void Move();

	/// <summary>
	/// �W�����v
	/// </summary>
	void Jump();

	/// <summary>
	/// ���n
	/// </summary>
	void Landing();

	/// <summary>
	/// ���������X�V
	/// </summary>
	void UpdatePhysics();

public:

	/// <summary>
	/// ���W (�Q�Ɠn��)
	/// </summary>
	/// <returns>���W (�Q�Ɠn��)</returns>
	YMath::Vector3& PosRef() override;

	/// <summary>
	/// �X�s�[�h (�Q�Ɠn��)
	/// </summary>
	/// <returns>�X�s�[�h (�Q�Ɠn��)</returns>
	YMath::Vector3& SpeedRef() override;

	/// <summary>
	/// ���W (�|�C���^�n��)
	/// </summary>
	/// <returns>���W (�|�C���^�n��)</returns>
	YMath::Vector3* PosPointer() override;

public:

	/// <summary>
	/// �Փˎ��R�[���o�b�N�֐�
	/// </summary>
	/// <param name="pPair"> : ����R���C�_�[�|�C���^</param>
	void OnCollision(ObjectCollider* pPair) override;

private:

	// �L�[
	static YInput::Keys* spKeys_;

public:

	/// <summary>
	/// �ÓI������
	/// </summary>
	static void StaticInitialize();

};


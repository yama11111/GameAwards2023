#pragma once
#include "CollisionPrimitive.h"

class ObjectCollider :
	public YGame::Box2D
{

public:

	// ���
	enum class Type
	{
		ePlayer,	 // �v���C���[
		eBlock,		 // �u���b�N
		eSpring,	 // �΂�
		ePlatform,	 // ����
		eLaser,		 // ���[�U�[
		eSwitch,	 // �X�C�b�`
		eKey,		 // ��
		eGoal,		 // �S�[��
		eEnd,
	};

private:

	// ���
	Type type_;

	// ���L�̓���
	bool isActSkill_ = false;

	// �Ŕԍ�
	size_t signIndex_ = 0;

	// �~��邩
	bool isGetOff_ = false;

	// ���n������
	bool isLanding_ = false;
	
	// ���n�����u�Ԃ�
	bool isElderLanding_ = false;

	// �A�^������K�p�t���O
	bool isExist_ = true;
	
	// �ۑ��p
	ObjectCollider* pObjCollider_ = nullptr;

public:

	/// <summary>
	/// �Փˎ��R�[���o�b�N�֐�
	/// </summary>
	/// <param name="pPair"> : ����R���C�_�[�|�C���^</param>
	virtual void OnCollision(ObjectCollider* pPair) = 0;
	

	// �X�L�������ݒ�
	void SetIsActSkill(const bool isActSkill) { isActSkill_ = isActSkill; }
	
	// �X�L�������擾
	bool GetIsActSkill() const { return isActSkill_; }
	

	// �Ŕԍ��ݒ�
	void SetSignIndex(const size_t signIndex) { signIndex_ = signIndex; }
	
	// �Ŕԍ��擾
	size_t GetSignIndex() { return signIndex_; }


	// ��ސݒ�
	void SetColliderType(const Type& type) { type_ = type; }

	// ��ފl��
	Type GetColliderType() const { return type_; }
	

	// �~��邩�ݒ�
	void SetIsGetOff(const bool isGetOff) { isGetOff_ = isGetOff; }
	
	// �~��邩�擾
	void GetIsGetOff(const bool isGetOff) { isGetOff_ = isGetOff; }


	// �����邩
	bool GetIsExist() const { return isExist_; }
	
	// �����邩�ݒ�
	void SetIsExist(const bool isExist) { isExist_ = isExist; }


	// ���n������
	bool IsLanding() { return isLanding_; }

	// ���n�����u�Ԃ�
	bool IsLandingMoment() { return isLanding_ && isElderLanding_ == false; }

	// ���n�t���O���Z�b�g
	void ResetIsLanding();


	
	ObjectCollider* GetObjeColliderPointer() const { return pObjCollider_; }

	void SetObjeColliderPointer(ObjectCollider* pObjCollider) { pObjCollider_ = pObjCollider; }


	// ���W (�Q�Ɠn��)
	virtual YMath::Vector3& PosRef();

	// �X�s�[�h (�Q�Ɠn��)
	virtual YMath::Vector3& SpeedRef();

	// ���W (�|�C���^�n��)
	virtual YMath::Vector3* PosPointer();

public:

	/// <summary>
	/// �A�^������
	/// </summary>
	/// <param name="pairObjectBox"> : �I�u�W�F�N�g</param>
	/// <returns>����������</returns>
	bool PerfectPixelCollision(const YGame::Box2D& pairObjectBox);

	/// <summary>
	/// �A�^������ (�㑤�̂�)
	/// </summary>
	/// <param name="pairObjectBox"> : �I�u�W�F�N�g</param>
	/// <returns>����������</returns>
	bool PerfectPixelCollisionUpperSide(const YGame::Box2D& pairObjectBox);

private:

	/// <summary>
	/// ���ړ���̃A�^������
	/// </summary>
	/// <param name="speed"> : �X�s�[�h</param>
	/// <param name="pair"> : �y�A�l�p�`2D</param>
	/// <returns>����������</returns>
	bool CollisionTemporaryBox2D(const YMath::Vector2& speed, const YGame::Box2D& pair);

	/// <summary>
	/// ���ړ���̃A�^������ (�㑤�̂�)
	/// </summary>
	/// <param name="speed"> : �X�s�[�h</param>
	/// <param name="pair"> : �y�A�l�p�`2D</param>
	/// <returns>����������</returns>
	bool CollisionTemporaryBox2DUpperSide(const YMath::Vector2& speed, const YGame::Box2D& pair);

public:

	virtual ~ObjectCollider() = default;

};


#pragma once
#include "CollisionPrimitive.h"
#include "ViewProjection.h"

// �C���N���[�h���p
namespace YInput { class Mouse; }

class MouseColliderCommon
{

protected:

	// �ÓI�}�E�X
	static YInput::Mouse* spMouse_;

	// �}�E�X�̃��C
	static YGame::Ray sMouseRay_;
	
	// ��ʂƂ̃A�^������p
	static YGame::Plane sDisplayPlane_;

	// �ÓI�}�E�X�A�^������p�l�p�`[2D]
	static YGame::Box2D sMouseBox_;

	// �ÓI�r���[�v���W�F�N�V�����|�C���^
	static YGame::ViewProjection* spVP_;

public:

	/// <summary>
	/// �ÓI������
	/// </summary>
	static void StaticInitialize();

	/// <summary>
	/// �ÓI�X�V
	/// </summary>
	static void StaticUpdate();

	/// <summary>
	/// �}�E�X�J�[�\�����[���h���W�擾
	/// </summary>
	/// <returns>�}�E�X�J�[�\�����[���h���W</returns>
	static YMath::Vector3 StaticGetMouseWorldPos();

	/// <summary>
	/// �ÓI�}�E�X�A�^������T�C�Y�ݒ�
	/// </summary>
	/// <param name="size"> : �A�^������T�C�Y</param>
	static void StaticSetMouseCollisionRadSize(const YMath::Vector2& size);

	/// <summary>
	/// �ÓI�r���[�v���W�F�N�V�����ݒ�
	/// </summary>
	/// <param name="pVP"> : �r���[�v���W�F�N�V�����|�C���^</param>
	static void StaticSetViewProjectionPointer(YGame::ViewProjection* pVP);

public:

	virtual ~MouseColliderCommon() = default;

};

class MouseCollider :
	public YGame::Box2D,
	private MouseColliderCommon
{

public:
	
	/// <summary>
	/// �}�E�X�|�C���^�Ɠ����������擾
	/// </summary>
	/// <returns>�}�E�X�|�C���^�Ɠ���������</returns>
	bool CollisionMousePointer();

public:

	virtual ~MouseCollider() = default;

};
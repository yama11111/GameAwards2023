#pragma once
#include "PlayerDrawer.h"
#include "CollisionPrimitive.h"

// �C���N���[�h���p
namespace YInput { class Keys; }

class Player :
	public YGame::Box2D
{

private:

	// �g�����X�t�H�[��
	std::unique_ptr<YGame::Transform> transform_;

	// �X�s�[�h
	YMath::Vector3 speed_;

	// ����
	YMath::Vector3 direction_;

	// �W�����v��
	int jumpCount_ = 0;
	
	// �`��N���X
	PlayerDrawer drawer_;

public:

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="pos"> : �����ʒu</param>
	void Initialize(const YMath::Vector3& pos);

	/// <summary>
	/// ���Z�b�g (���g����������)
	/// </summary>
	/// <param name="pos"> : �����ʒu</param>
	void Reset(const YMath::Vector3& pos);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

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
	/// ���������X�V
	/// </summary>
	void UpdatePhysics();

private:

	// �L�[
	static YInput::Keys* spKeys_;

public:

	/// <summary>
	/// �ÓI������
	/// </summary>
	static void StaticInitialize();


};


#pragma once
#include "PlayerDrawer.h"
#include "MapChip.h"
#include "CollisionPrimitive.h"
#include "Keys.h"

class DemoPlayer : 
	public YGame::MapChipCollider,
	public YGame::Sphere
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

	// �S�[���t���O
	bool isGoal_ = false;

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

public:

	/// <summary>
	/// �S�[��
	/// </summary>
	void Goal();

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

public:

	/// <summary>
	// �ʒu�擾 (�Q��)
	/// </summary>
	/// <returns></returns>
	YMath::Vector3& PosRef() override { return transform_->pos_; }

	/// <summary>
	// �X�s�[�h�擾 (�Q��)
	/// </summary>
	/// <returns></returns>
	YMath::Vector3& SpeedRef() override { return speed_; }

private:

	// �L�[
	static YInput::Keys* spKeys_;

	// �}�b�v�`�b�v
	static YGame::MapChip* spMapChip_;

public:

	/// <summary>
	/// �ÓI������
	/// </summary>
	static void StaticInitialize();
	
	/// <summary>
	/// �ÓI�}�b�v�`�b�v�|�C���^�ݒ�
	/// </summary>
	/// <param name="pMapChip"> : �}�b�v�`�b�v�|�C���^</param>
	static void StaticSetMapChip(YGame::MapChip* pMapChip);
	
};


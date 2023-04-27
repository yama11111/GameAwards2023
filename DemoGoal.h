#pragma once
#include "GoalDrawer.h"
#include "CollisionPrimitive.h"

class DemoGoal :
	public YGame::Sphere
{

private:

	// �g�����X�t�H�[��
	std::unique_ptr<YGame::Transform> transform_;

	// �`��N���X
	GoalDrawer drawer_;

	// �S�[��������
	bool isGoal_ = false;

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
	/// <param name="playerPos"> : �v���C���[�̈ʒu</param>
	void Goal(const YMath::Vector3& playerPos);

};


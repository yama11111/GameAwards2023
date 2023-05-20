#pragma once
#include "BlockDrawer.h"
#include "CollisionPrimitive.h"

class Block :
	public YGame::Box2D
{

private:

	// �g�����X�t�H�[��
	std::unique_ptr<YGame::Transform> transform_;
	
	// �`��N���X
	BlockDrawer drawer_;

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

};


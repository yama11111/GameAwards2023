#pragma once
#include "PlayerDrawer.h"
#include "MapChip.h"
#include "CollisionPrimitive.h"
#include "Keys.h"

class Player
{
private:
	// �g�����X�t�H�[��
	std::unique_ptr<YGame::Transform> transform_;

	// ����
	YMath::Vector3 direction_;

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

	// �L�[
	static YInput::Keys* spKeys_;

public:

	/// <summary>
	/// �ÓI������
	/// </summary>
	static void StaticInitialize();
};
#pragma once
#include "IObject.h"
#include "ObjectCollisionManager.h"

class ObjectManager
{

private:

	// �I�u�W�F�N�g���X�g
	std::list<IObject*> objs_;

	// �I�u�W�F�N�g���m�̔���}�l�[�W���[
	ObjectCollisionManager objCollMan_;

public:

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

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
	/// �N���A
	/// </summary>
	void Clear();

	/// <summary>
	/// �}��
	/// </summary>
	/// <param name="pObject"> : �I�u�W�F�N�g�|�C���^</param>
	void PushBack(IObject* pObject);

};


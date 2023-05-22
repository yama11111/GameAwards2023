#pragma once
#include "ObjectCollider.h"
#include "Transform.h"
#include <memory>

namespace maruyama { class Sign; }

class IObject :
	public ObjectCollider
{

protected:

	// �g�����X�t�H�[��
	std::unique_ptr<YGame::Transform> transform_;

public:

	/// <summary>
	/// ����O�X�V
	/// </summary>
	virtual void PreUpdate() = 0;
	
	/// <summary>
	/// �����X�V
	/// </summary>
	virtual void PostUpdate() = 0;

	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw() = 0;

public:

	virtual ~IObject() = default;

protected:

	// �ÓI�Ŕ}�l�[�W���[�|�C���^
	static maruyama::Sign* spSignMan_;

public:
	
	/// <summary>
	/// �ÓI������
	/// </summary>
	/// <param name="pSignMan"> : �ÓI�Ŕ}�l�[�W���[�|�C���^</param>
	static void StaticInitialize(maruyama::Sign* pSignMan);

};


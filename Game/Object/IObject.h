#pragma once
#include "ObjectCollider.h"
#include "Transform.h"
#include <memory>

class IObject :
	public ObjectCollider
{

protected:

	// トランスフォーム
	std::unique_ptr<YGame::Transform> transform_;

public:

	/// <summary>
	/// 判定前更新
	/// </summary>
	virtual void PreUpdate() = 0;
	
	/// <summary>
	/// 判定後更新
	/// </summary>
	virtual void PostUpdate() = 0;

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw() = 0;

public:

	virtual ~IObject() = default;

};


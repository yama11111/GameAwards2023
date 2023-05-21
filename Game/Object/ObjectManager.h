#pragma once
#include "IObject.h"
#include "ObjectCollisionManager.h"

class ObjectManager
{

private:

	// オブジェクトリスト
	std::list<IObject*> objs_;

	// オブジェクト同士の判定マネージャー
	ObjectCollisionManager objCollMan_;

public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

public:
	
	/// <summary>
	/// クリア
	/// </summary>
	void Clear();

	/// <summary>
	/// 挿入
	/// </summary>
	/// <param name="pObject"> : オブジェクトポインタ</param>
	void PushBack(IObject* pObject);

};


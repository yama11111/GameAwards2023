#pragma once
#include "ObjectCollider.h"
#include <list>

class ObjectCollisionManager
{

private:
	
	// コライダー格納リスト
	std::list<ObjectCollider*> pColliders_;

public:
	
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	
	/// <summary>
	/// 更新
	/// </summary>
	void Update();

public: 
	
	/// <summary>
	/// 格納
	/// </summary>
	/// <param name="pCollider"> : コライダーポインタ</param>
	void PushBack(ObjectCollider* pCollider);
	
	/// <summary>
	/// リストクリア
	/// </summary>
	void Clear();

private:
	
	/// <summary>
	/// 全コリジョン確認
	/// </summary>
	void CheckAllCollision();

private:
	
	/// <summary>
	/// アタリ判定
	/// </summary>
	/// <param name="pColliderA"> : コライダーポインタA</param>
	/// <param name="pColliderB"> : コライダーポインタB</param>
	static void CheckCollisionPair(ObjectCollider* pColliderA, ObjectCollider* pColliderB);
	
};


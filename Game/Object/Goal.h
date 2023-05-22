#pragma once
#include "GoalDrawer.h"
#include "IObject.h"

class Goal :
	public IObject
{

private:

	// 描画クラス
	GoalDrawer drawer_;

	// ロックフラグ
	bool isRock_ = false;

public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="signIndex"> : 看板番号</param>
	/// <param name="pos"> : 初期位置</param>
	/// <param name="isRock"> : ロックフラグ</param>
	void Initialize(const size_t signIndex, const YMath::Vector3& pos, const bool isRock);

	/// <summary>
	/// リセット (中身だけ初期化)
	/// </summary>
	/// <param name="signIndex"> : 看板番号</param>
	/// <param name="pos"> : 初期位置</param>
	/// <param name="isRock"> : ロックフラグ</param>
	void Reset(const size_t signIndex, const YMath::Vector3& pos, const bool isRock);

	/// <summary>
	/// 判定前更新
	/// </summary>
	void PreUpdate() override;

	/// <summary>
	/// 判定後更新
	/// </summary>
	void PostUpdate() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

public:

	/// <summary>
	/// 衝突時コールバック関数
	/// </summary>
	/// <param name="pPair"> : 相手コライダーポインタ</param>
	void OnCollision(ObjectCollider* pPair) override;

};

#pragma once
#include "GoalDrawer.h"
#include "CollisionPrimitive.h"

class DemoGoal :
	public YGame::Sphere
{

private:

	// トランスフォーム
	std::unique_ptr<YGame::Transform> transform_;

	// 描画クラス
	GoalDrawer drawer_;

	// ゴールしたか
	bool isGoal_ = false;

public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pos"> : 初期位置</param>
	void Initialize(const YMath::Vector3& pos);

	/// <summary>
	/// リセット (中身だけ初期化)
	/// </summary>
	/// <param name="pos"> : 初期位置</param>
	void Reset(const YMath::Vector3& pos);

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
	/// ゴール
	/// </summary>
	/// <param name="playerPos"> : プレイヤーの位置</param>
	void Goal(const YMath::Vector3& playerPos);

};


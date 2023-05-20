#pragma once
#include "BlockDrawer.h"
#include "CollisionPrimitive.h"

class Block :
	public YGame::Box2D
{

private:

	// トランスフォーム
	std::unique_ptr<YGame::Transform> transform_;
	
	// 描画クラス
	BlockDrawer drawer_;

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

};


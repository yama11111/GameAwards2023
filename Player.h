#pragma once
#include "PlayerDrawer.h"
#include "MapChip.h"
#include "CollisionPrimitive.h"
#include "Keys.h"

class Player
{
private:
	// トランスフォーム
	std::unique_ptr<YGame::Transform> transform_;

	// 向き
	YMath::Vector3 direction_;

	// 描画クラス
	PlayerDrawer drawer_;

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

private:

	// キー
	static YInput::Keys* spKeys_;

public:

	/// <summary>
	/// 静的初期化
	/// </summary>
	static void StaticInitialize();
};
#pragma once
#include "BlockDrawer.h"
#include "IObject.h"

class Block :
	public IObject
{

private:

	// トランスフォーム
	std::unique_ptr<YGame::Transform> transform_;

	// スピード
	YMath::Vector3 speed_;
	
	// 描画クラス
	BlockDrawer drawer_;

public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="signIndex"> : 看板番号</param>
	/// <param name="pos"> : 初期位置</param>
	void Initialize(const size_t signIndex, const YMath::Vector3& pos);

	/// <summary>
	/// リセット (中身だけ初期化)
	/// </summary>
	/// <param name="signIndex"> : 看板番号</param>
	/// <param name="pos"> : 初期位置</param>
	void Reset(const size_t signIndex, const YMath::Vector3& pos);

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
	/// 座標 (参照渡し)
	/// </summary>
	/// <returns>座標 (参照渡し)</returns>
	YMath::Vector3& PosRef() override;

	/// <summary>
	/// スピード (参照渡し)
	/// </summary>
	/// <returns>スピード (参照渡し)</returns>
	YMath::Vector3& SpeedRef() override;

public:

	/// <summary>
	/// 衝突時コールバック関数
	/// </summary>
	/// <param name="pPair"> : 相手コライダーポインタ</param>
	void OnCollision(ObjectCollider* pPair) override;

};


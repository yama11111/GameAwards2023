#pragma once
#include "PlatformDrawer.h"
#include "IObject.h"

class Platform :
	public IObject
{

private:

	// トランスフォーム
	std::unique_ptr<YGame::Transform> transform_;

	// 描画クラス
	PlatformDrawer drawer_;

public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="signIndex"> : 看板番号</param>
	/// <param name="pos"> : 初期位置</param>
	/// <param name="length"> : 長さ</param>
	void Initialize(const size_t signIndex, const YMath::Vector3& pos, const float length);

	/// <summary>
	/// リセット (中身だけ初期化)
	/// </summary>
	/// <param name="signIndex"> : 看板番号</param>
	/// <param name="pos"> : 初期位置</param>
	/// <param name="length"> : 長さ</param>
	void Reset(const size_t signIndex, const YMath::Vector3& pos, const float length);

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
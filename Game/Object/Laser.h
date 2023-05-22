#pragma once
#include "LaserDrawer.h"
#include "IObject.h"

class Laser :
	public IObject
{

private:

	// 向き
	YMath::Vector3 direction_;
	
	// ビームの長さ
	float beamLength_ = 0.0f;

	// 当たりフラグ
	bool isColl_ = false;

	// 描画クラス
	LaserDrawer drawer_;

public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="signIndex"> : 看板番号</param>
	/// <param name="pos"> : 初期位置</param>
	/// <param name="direction"> : 向き</param>
	void Initialize(const size_t signIndex, const YMath::Vector3& pos, const YMath::Vector3& direction);

	/// <summary>
	/// リセット (中身だけ初期化)
	/// </summary>
	/// <param name="signIndex"> : 看板番号</param>
	/// <param name="pos"> : 初期位置</param>
	/// <param name="direction"> : 向き</param>
	void Reset(const size_t signIndex, const YMath::Vector3& pos, const YMath::Vector3& direction);

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

private:

	/// <summary>
	/// ビームの長さ計算
	/// </summary>
	void CalcBeamLength();
};


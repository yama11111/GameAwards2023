#pragma once
#include "PlatformDrawer.h"
#include "IObject.h"

class Platform :
	public IObject
{

private:

	// 描画クラス
	PlatformDrawer drawer_;

	// スイッチオンか
	bool* pIsSwitchOn_ = nullptr;

public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="signIndex"> : 看板番号</param>
	/// <param name="pos"> : 初期位置</param>
	/// <param name="length"> : 長さ</param>
	/// <param name="pIsSwitchOn"> : スイッチポインタ</param>
	void Initialize(const size_t signIndex, const YMath::Vector3& pos, const float length, bool* pIsSwitchOn);

	/// <summary>
	/// リセット (中身だけ初期化)
	/// </summary>
	/// <param name="signIndex"> : 看板番号</param>
	/// <param name="pos"> : 初期位置</param>
	/// <param name="length"> : 長さ</param>
	/// <param name="pIsSwitchOn"> : スイッチポインタ</param>
	void Reset(const size_t signIndex, const YMath::Vector3& pos, const float length, bool* pIsSwitchOn);

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
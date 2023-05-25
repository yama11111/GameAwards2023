#pragma once
#include "CollisionPrimitive.h"
#include "ViewProjection.h"

// インクルード回避用
namespace YInput { class Mouse; }

class MouseColliderCommon
{

protected:

	// 静的マウス
	static YInput::Mouse* spMouse_;

	// マウスのレイ
	static YGame::Ray sMouseRay_;
	
	// 画面とのアタリ判定用
	static YGame::Plane sDisplayPlane_;

	// 静的マウスアタリ判定用四角形[2D]
	static YGame::Box2D sMouseBox_;

	// 静的ビュープロジェクションポインタ
	static YGame::ViewProjection* spVP_;

public:

	/// <summary>
	/// 静的初期化
	/// </summary>
	static void StaticInitialize();

	/// <summary>
	/// 静的更新
	/// </summary>
	static void StaticUpdate();

	/// <summary>
	/// マウスカーソルワールド座標取得
	/// </summary>
	/// <returns>マウスカーソルワールド座標</returns>
	static YMath::Vector3 StaticGetMouseWorldPos();

	/// <summary>
	/// 静的マウスアタリ判定サイズ設定
	/// </summary>
	/// <param name="size"> : アタリ判定サイズ</param>
	static void StaticSetMouseCollisionRadSize(const YMath::Vector2& size);

	/// <summary>
	/// 静的ビュープロジェクション設定
	/// </summary>
	/// <param name="pVP"> : ビュープロジェクションポインタ</param>
	static void StaticSetViewProjectionPointer(YGame::ViewProjection* pVP);

public:

	virtual ~MouseColliderCommon() = default;

};

class MouseCollider :
	public YGame::Box2D,
	private MouseColliderCommon
{

public:
	
	/// <summary>
	/// マウスポインタと当たったか取得
	/// </summary>
	/// <returns>マウスポインタと当たったか</returns>
	bool CollisionMousePointer();

public:

	virtual ~MouseCollider() = default;

};
#pragma once
#include "CollisionPrimitive.h"

class ObjectCollider :
	public YGame::Box2D
{

public:

	// 種類
	enum class Type
	{
		ePlayer,	 // プレイヤー
		eBlock,		 // ブロック
		eSpring,	 // ばね
		ePlatform,	 // 足場
		eLaser,		 // レーザー
		eSwitch,	 // スイッチ
		eKey,		 // 鍵
		eGoal,		 // ゴール
		eEnd,
	};

private:

	// 種類
	Type type_;

	// 特有の動き
	bool isActSkill_ = false;

	// 看板番号
	size_t signIndex_ = 0;

	// 降りるか
	bool isGetOff_ = false;

	// 着地したか
	bool isLanding_ = false;
	
	// 着地した瞬間か
	bool isElderLanding_ = false;

	// アタリ判定適用フラグ
	bool isExist_ = true;
	
	// 保存用
	ObjectCollider* pObjCollider_ = nullptr;

public:

	/// <summary>
	/// 衝突時コールバック関数
	/// </summary>
	/// <param name="pPair"> : 相手コライダーポインタ</param>
	virtual void OnCollision(ObjectCollider* pPair) = 0;
	

	// スキル発動設定
	void SetIsActSkill(const bool isActSkill) { isActSkill_ = isActSkill; }
	
	// スキル発動取得
	bool GetIsActSkill() const { return isActSkill_; }
	

	// 看板番号設定
	void SetSignIndex(const size_t signIndex) { signIndex_ = signIndex; }
	
	// 看板番号取得
	size_t GetSignIndex() { return signIndex_; }


	// 種類設定
	void SetColliderType(const Type& type) { type_ = type; }

	// 種類獲得
	Type GetColliderType() const { return type_; }
	

	// 降りるか設定
	void SetIsGetOff(const bool isGetOff) { isGetOff_ = isGetOff; }
	
	// 降りるか取得
	void GetIsGetOff(const bool isGetOff) { isGetOff_ = isGetOff; }


	// 当たるか
	bool GetIsExist() const { return isExist_; }
	
	// 当たるか設定
	void SetIsExist(const bool isExist) { isExist_ = isExist; }


	// 着地したか
	bool IsLanding() { return isLanding_; }

	// 着地した瞬間か
	bool IsLandingMoment() { return isLanding_ && isElderLanding_ == false; }

	// 着地フラグリセット
	void ResetIsLanding();


	
	ObjectCollider* GetObjeColliderPointer() const { return pObjCollider_; }

	void SetObjeColliderPointer(ObjectCollider* pObjCollider) { pObjCollider_ = pObjCollider; }


	// 座標 (参照渡し)
	virtual YMath::Vector3& PosRef();

	// スピード (参照渡し)
	virtual YMath::Vector3& SpeedRef();

	// 座標 (ポインタ渡し)
	virtual YMath::Vector3* PosPointer();

public:

	/// <summary>
	/// アタリ判定
	/// </summary>
	/// <param name="pairObjectBox"> : オブジェクト</param>
	/// <returns>当たったか</returns>
	bool PerfectPixelCollision(const YGame::Box2D& pairObjectBox);

	/// <summary>
	/// アタリ判定 (上側のみ)
	/// </summary>
	/// <param name="pairObjectBox"> : オブジェクト</param>
	/// <returns>当たったか</returns>
	bool PerfectPixelCollisionUpperSide(const YGame::Box2D& pairObjectBox);

private:

	/// <summary>
	/// 仮移動後のアタリ判定
	/// </summary>
	/// <param name="speed"> : スピード</param>
	/// <param name="pair"> : ペア四角形2D</param>
	/// <returns>当たったか</returns>
	bool CollisionTemporaryBox2D(const YMath::Vector2& speed, const YGame::Box2D& pair);

	/// <summary>
	/// 仮移動後のアタリ判定 (上側のみ)
	/// </summary>
	/// <param name="speed"> : スピード</param>
	/// <param name="pair"> : ペア四角形2D</param>
	/// <returns>当たったか</returns>
	bool CollisionTemporaryBox2DUpperSide(const YMath::Vector2& speed, const YGame::Box2D& pair);

public:

	virtual ~ObjectCollider() = default;

};


#include "ObjectCollider.h"

using YMath::Vector2;
using YMath::Vector3;
using YGame::Box2D;

void ObjectCollider::ResetIsLanding()
{
	isElderLanding_ = isLanding_;
	isLanding_ = false;
}

Vector3& ObjectCollider::PosRef()
{
	static Vector3 sPos;
	return sPos;
}

Vector3& ObjectCollider::SpeedRef()
{
	static Vector3 sSpeed;
	return sSpeed;
}

bool ObjectCollider::PerfectPixelCollision(const YGame::Box2D& pairObjectBox)
{
	// 代入
	Vector3& posRef = PosRef();
	Vector3& speedRef = SpeedRef();

	// ぶつかっているか
	bool isCollX = CollisionTemporaryBox2D({ speedRef.x_,0 }, pairObjectBox); // x
	bool isCollY = CollisionTemporaryBox2D({ 0,speedRef.y_ }, pairObjectBox); // y

	// 着地したか
	isLanding_ = isLanding_ || isCollY;

	// ぶつかっていないならスキップ
	if (isCollX == false && isCollY == false) { return false; }

	// 近づく移動量
	YMath::Vector3 approach = speedRef / 100.0f;

	// 押し戻し処理
	while (true)
	{
		// ぶつかっているか (仮移動)
		bool isCollTempX = CollisionTemporaryBox2D({ approach.x_,0 }, pairObjectBox); // x
		bool isCollTempY = CollisionTemporaryBox2D({ 0,approach.y_ }, pairObjectBox); // y

		// ぶつかっているならループ抜ける
		if (isCollTempX || isCollTempY) { break; }

		// 少しづつ近づける
		if (isCollX) { posRef.x_ += approach.x_; }
		if (isCollY) { posRef.y_ += approach.y_; }

		// コライダー位置更新
		Box2D::SetBox2DCenter({ posRef.x_, posRef.y_ });
	}

	// 速度リセット
	if (isCollX) { speedRef.x_ = 0.0f; }
	if (isCollY) { speedRef.y_ = 0.0f; }


	return true;
}

bool ObjectCollider::CollisionTemporaryBox2D(const YMath::Vector2& speed, const YGame::Box2D& pair)
{
	// 仮移動後
	Box2D tempBox;
	tempBox.SetBox2DCenter(this->GetBox2DCenter() + speed);
	tempBox.SetBox2DRadSize(this->GetBox2DRadSize());

	return YGame::CollisionBoxBox2D(tempBox, pair);
}

bool ObjectCollider::PerfectPixelCollisionUpperSide(const YGame::Box2D& pairObjectBox)
{
	// 降りるなら弾く
	if (isGetOff_) { return false; }

	// 代入
	Vector3& posRef = PosRef();
	Vector3& speedRef = SpeedRef();

	// 上昇時は弾く
	if (speedRef.y_ >= 0.0f) { return false; }

	// ぶつかっているか
	bool isCollY = CollisionTemporaryBox2D({ 0,speedRef.y_ }, pairObjectBox); // y

	// 着地したか
	isLanding_ = isLanding_ || isCollY;

	// ぶつかっていないならスキップ
	if (isCollY == false) { return false; }

	// 近づく移動量
	YMath::Vector3 approach = speedRef / 100.0f;

	// 押し戻し処理
	while (true)
	{
		// ぶつかっているか (仮移動)
		bool isCollTempY = CollisionTemporaryBox2D({ 0,approach.y_ }, pairObjectBox); // y

		// ぶつかっているならループ抜ける
		if (isCollTempY) { break; }

		// 少しづつ近づける
		if (isCollY) { posRef.y_ += approach.y_; }

		// コライダー位置更新
		Box2D::SetBox2DCenter({ posRef.x_, posRef.y_ });
	}

	// 速度リセット
	if (isCollY) { speedRef.y_ = 0.0f; }

	return true;
}

bool ObjectCollider::CollisionTemporaryBox2DUpperSide(const YMath::Vector2& speed, const YGame::Box2D& pair)
{
	// 仮移動後
	float tempY = this->GetBox2DCenter().y_ + speed.y_;

	// 内外判定
	return tempY - this->GetBox2DRadSize().y_ <= pair.GetBox2DCenter().y_ + pair.GetBox2DRadSize().y_;
}

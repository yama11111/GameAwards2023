#pragma once
#include "Vector2.h"
#include "Vector3.h"

namespace YMath
{
	// A^»θ (ό~½Κ)
	bool CollisionRayPlane(
		const Vector3& rayStart, const Vector3& rayDirection,
		const Vector3& planeNormal, const float planeDist);
	// A^»θ (ό~½Κ) <£,^π_ζΎver>
	bool CollisionRayPlane(
		const Vector3& rayStart, const Vector3& rayDirection,
		const Vector3& planeNormal, const float planeDist,
		float& distance, Vector3& inter);

	// A^»θ (ό~Op`)
	bool CollisionRayTriangle(
		const Vector3& rayStart, const Vector3& rayDirection,
		const Vector3& triPos0, const Vector3& triPos1, const Vector3& triPos2, const Vector3& triNormal);
	// A^»θ (ό~Op`) <£,^π_ζΎver>
	bool CollisionRayTriangle(
		const Vector3& rayStart, const Vector3& rayDirection,
		const Vector3& triPos0, const Vector3& triPos1, const Vector3& triPos2, const Vector3& triNormal,
		float& distance, Vector3& inter);

	// A^»θ (ό~)
	bool CollisionRaySphere(
		const Vector3& rayStart, const Vector3& rayDirection,
		const Vector3& sphereCenter, const float sphereRad);
	// A^»θ (ό~) <ΡΚ_ζΎver>
	bool CollisionRaySphere(
		const Vector3& rayStart, const Vector3& rayDirection,
		const Vector3& sphereCenter, const float sphereRad,
		float& distance, Vector3& start, Vector3& end);

	// A^»θ (½Κ~)
	bool CollisionPlaneSphere(
		const Vector3& planeNormal, const float planeDist, 
		const Vector3& sphereCenter, const float sphereRad);
	// A^»θ (½Κ~) <^π_ζΎver>
	bool CollisionPlaneSphere(
		const Vector3& planeNormal, const float planeDist,
		const Vector3& sphereCenter, const float sphereRad,
		Vector3& inter);
	
	// A^»θ (Op`~)
	bool CollisionTriangleSphere(
		const Vector3& triPos0, const Vector3& triPos1, const Vector3& triPos2, const Vector3& triNormal,
		const Vector3& sphereCenter, const float sphereRad);
	// A^»θ (Op`~) <^π_ζΎver>
	bool CollisionTriangleSphere(
		const Vector3& triPos0, const Vector3& triPos1, const Vector3& triPos2, const Vector3& triNormal,
		const Vector3& sphereCenter, const float sphereRad,
		Vector3& inter);

	// A^»θ (~)
	bool CollisionSphereSphere(
		const Vector3& sphereCenter1, const float sphereRad1,
		const Vector3& sphereCenter2, const float sphereRad2
	);

	// A^»θ (lp`~lp`) [2D]
	bool CollisionBoxBox2D(
		const Vector2& boxCenter1, const Vector2& boxRadSize1,
		const Vector2& boxCenter2, const Vector2& boxRadSize2
	);
}


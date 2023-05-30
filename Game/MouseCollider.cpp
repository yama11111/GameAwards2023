#include "MouseCollider.h"
#include "CalcTransform.h"
#include "Mouse.h"
#include <cmath>
#include <cassert>
#include <imgui.h>

using YMath::Vector2;
using YMath::Vector3;
using YGame::Box2D;
using YGame::ViewProjection;
using YInput::Mouse;

Mouse* MouseColliderCommon::spMouse_ = nullptr;
YGame::Ray MouseColliderCommon::sMouseRay_;
YGame::Plane MouseColliderCommon::sDisplayPlane_;
Box2D MouseColliderCommon::sMouseBox_;
ViewProjection* MouseColliderCommon::spVP_ = nullptr;
bool MouseColliderCommon::sIsActMouse_ = false;
bool MouseColliderCommon::sIsHoldMouse_ = false;

static Vector2 DefaultMouseCollRadSize = { 5.0f, 5.0f };

void MouseColliderCommon::StaticInitialize()
{
	// インスタンスポインタ取得
	spMouse_ = Mouse::GetInstance();

	// アタリ判定用初期化
	sMouseRay_.SetRayDirection({});
	sMouseRay_.SetRayStart({});

	sDisplayPlane_.SetPlaneDistance(0.0f);
	sDisplayPlane_.SetPlaneNormal(Vector3(0.0f, 0.0f, -1.0f));

	sMouseBox_.SetBox2DCenter({});
	sMouseBox_.SetBox2DRadSize({});

	// マウスデフォルトの大きさ設定
	StaticSetMouseCollisionRadSize(DefaultMouseCollRadSize);

	sIsActMouse_ = false;
	
	sIsHoldMouse_ = false;
}

void MouseColliderCommon::StaticUpdate()
{
	if (sIsActMouse_ == false) { return; }

	// ワールド座標
	Vector3 worldPos = StaticGetMouseWorldPos();

	// マウス位置設定
	sMouseBox_.SetBox2DCenter(Vector2(worldPos.x_, worldPos.y_));

	//ImGui::Begin("Mouse");
	//ImGui::Text("%f, %f", worldPos.x_, worldPos.y_);
	//ImGui::End();
}

Vector3 MouseColliderCommon::StaticGetMouseWorldPos()
{
	// マウスワールド座標取得
	Vector3 nearPos = YMath::WorldPos(spMouse_->Pos(), 0.0f, spVP_->view_, spVP_->pro_);
	Vector3 farPos = YMath::WorldPos(spMouse_->Pos(), 1.0f, spVP_->view_, spVP_->pro_);

	// ベクトル
	Vector3 verocity = farPos - nearPos;

	// レイに反映
	sMouseRay_.SetRayDirection(verocity);
	sMouseRay_.SetRayStart(nearPos);

	// 受け取る用
	float distance = 0.0f;
	Vector3 inter = {};

	// アタリ判定を取って接点を取得
	YGame::CollisionRayPlane(sMouseRay_, sDisplayPlane_, distance, inter);

	return inter;
}

void MouseColliderCommon::StaticSetMouseCollisionRadSize(const Vector2& size)
{
	// サイズ設定
	sMouseBox_.SetBox2DRadSize(size);
}

void MouseColliderCommon::StaticSetViewProjectionPointer(ViewProjection* pVP)
{
	// nullチェック
	assert(pVP);
	
	// 代入
	spVP_ = pVP;
}

bool MouseCollider::CollisionMousePointer()
{
	if (sIsActMouse_ == false)
	{
		return false;
	}

	// 四角形のアタリ判定を返す
	return YGame::CollisionBoxBox2D(*this, sMouseBox_);
}

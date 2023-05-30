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
	// �C���X�^���X�|�C���^�擾
	spMouse_ = Mouse::GetInstance();

	// �A�^������p������
	sMouseRay_.SetRayDirection({});
	sMouseRay_.SetRayStart({});

	sDisplayPlane_.SetPlaneDistance(0.0f);
	sDisplayPlane_.SetPlaneNormal(Vector3(0.0f, 0.0f, -1.0f));

	sMouseBox_.SetBox2DCenter({});
	sMouseBox_.SetBox2DRadSize({});

	// �}�E�X�f�t�H���g�̑傫���ݒ�
	StaticSetMouseCollisionRadSize(DefaultMouseCollRadSize);

	sIsActMouse_ = false;
	
	sIsHoldMouse_ = false;
}

void MouseColliderCommon::StaticUpdate()
{
	if (sIsActMouse_ == false) { return; }

	// ���[���h���W
	Vector3 worldPos = StaticGetMouseWorldPos();

	// �}�E�X�ʒu�ݒ�
	sMouseBox_.SetBox2DCenter(Vector2(worldPos.x_, worldPos.y_));

	//ImGui::Begin("Mouse");
	//ImGui::Text("%f, %f", worldPos.x_, worldPos.y_);
	//ImGui::End();
}

Vector3 MouseColliderCommon::StaticGetMouseWorldPos()
{
	// �}�E�X���[���h���W�擾
	Vector3 nearPos = YMath::WorldPos(spMouse_->Pos(), 0.0f, spVP_->view_, spVP_->pro_);
	Vector3 farPos = YMath::WorldPos(spMouse_->Pos(), 1.0f, spVP_->view_, spVP_->pro_);

	// �x�N�g��
	Vector3 verocity = farPos - nearPos;

	// ���C�ɔ��f
	sMouseRay_.SetRayDirection(verocity);
	sMouseRay_.SetRayStart(nearPos);

	// �󂯎��p
	float distance = 0.0f;
	Vector3 inter = {};

	// �A�^�����������Đړ_���擾
	YGame::CollisionRayPlane(sMouseRay_, sDisplayPlane_, distance, inter);

	return inter;
}

void MouseColliderCommon::StaticSetMouseCollisionRadSize(const Vector2& size)
{
	// �T�C�Y�ݒ�
	sMouseBox_.SetBox2DRadSize(size);
}

void MouseColliderCommon::StaticSetViewProjectionPointer(ViewProjection* pVP)
{
	// null�`�F�b�N
	assert(pVP);
	
	// ���
	spVP_ = pVP;
}

bool MouseCollider::CollisionMousePointer()
{
	if (sIsActMouse_ == false)
	{
		return false;
	}

	// �l�p�`�̃A�^�������Ԃ�
	return YGame::CollisionBoxBox2D(*this, sMouseBox_);
}

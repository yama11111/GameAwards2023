#include "MouseCollider.h"
#include "CalcTransform.h"
#include "Mouse.h"
#include <cmath>
#include <cassert>

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
}

void MouseColliderCommon::StaticUpdate()
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

	// �}�E�X�ʒu�ݒ�
	sMouseBox_.SetBox2DCenter(Vector2(inter.x_, inter.y_));
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
	// �l�p�`�̃A�^�������Ԃ�
	return YGame::CollisionBoxBox2D(*this, sMouseBox_);
}
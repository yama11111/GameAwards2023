#include "ObjectCollider.h"
#include "PilotManager.h"

using YMath::Vector2;
using YMath::Vector3;
using YGame::Box2D;

void ObjectCollider::ResetIsLanding()
{
	isElderLanding_ = isLanding_;
	isLanding_ = false;
}

void ObjectCollider::DrawActionSprite(YGame::Sprite3D::Object* pActionSprObj_)
{
	if (PilotManager::StaticGetIsActInit()) { return; }
	if (PilotManager::StaticGetCurrentPilot() != PilotManager::PilotType::ePlayer) { return; }
	if (isDraw_)
	{
		spActionSpr_->SetDrawCommand(pActionSprObj_, YGame::DrawLocation::Center);
	}
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

Vector3* ObjectCollider::PosPointer()
{
	static Vector3 sPos;
	return &sPos;
}

bool ObjectCollider::PerfectPixelCollision(const YGame::Box2D& pairObjectBox)
{
	// ���
	Vector3& posRef = PosRef();
	Vector3& speedRef = SpeedRef();

	// �Ԃ����Ă��邩
	bool isCollX = CollisionTemporaryBox2D({ speedRef.x_,0 }, pairObjectBox); // x
	bool isCollY = CollisionTemporaryBox2D({ 0,speedRef.y_ }, pairObjectBox); // y

	// ���n������
	isLanding_ = isLanding_ || isCollY;

	// �Ԃ����Ă��Ȃ��Ȃ�X�L�b�v
	if (isCollX == false && isCollY == false) { return false; }

	// �߂Â��ړ���
	YMath::Vector3 approach = speedRef / 100.0f;

	// �����߂�����
	while (true)
	{
		// �Ԃ����Ă��邩 (���ړ�)
		bool isCollTempX = CollisionTemporaryBox2D({ approach.x_,0 }, pairObjectBox); // x
		bool isCollTempY = CollisionTemporaryBox2D({ 0,approach.y_ }, pairObjectBox); // y

		// �Ԃ����Ă���Ȃ烋�[�v������
		if (isCollTempX || isCollTempY) { break; }

		// �����Â߂Â���
		if (isCollX) { posRef.x_ += approach.x_; }
		if (isCollY) { posRef.y_ += approach.y_; }

		// �R���C�_�[�ʒu�X�V
		Box2D::SetBox2DCenter({ posRef.x_, posRef.y_ });
	}

	// ���x���Z�b�g
	if (isCollX) { speedRef.x_ = 0.0f; }
	if (isCollY) { speedRef.y_ = 0.0f; }


	return true;
}

bool ObjectCollider::CollisionTemporaryBox2D(const YMath::Vector2& speed, const YGame::Box2D& pair)
{
	// ���ړ���
	Box2D tempBox;
	tempBox.SetBox2DCenter(this->GetBox2DCenter() + speed);
	tempBox.SetBox2DRadSize(this->GetBox2DRadSize());

	return YGame::CollisionBoxBox2D(tempBox, pair);
}

bool ObjectCollider::PerfectPixelCollisionUpperSide(const YGame::Box2D& pairObjectBox)
{
	// �~���Ȃ�e��
	if (isGetOff_) { return false; }

	// ���
	Vector3& posRef = PosRef();
	Vector3& speedRef = SpeedRef();

	// �㏸���͒e��
	if (speedRef.y_ >= 0.0f) { return false; }
	
	// ���ɂ���Ȃ�e��
	if (this->GetBox2DCenter().y_ - this->GetBox2DRadSize().y_ <= 
		pairObjectBox.GetBox2DCenter().y_ + pairObjectBox.GetBox2DRadSize().y_)
	{
		return false; 
	}

	// �Ԃ����Ă��邩
	bool isCollY = CollisionTemporaryBox2D({ 0,speedRef.y_ }, pairObjectBox); // y

	// ���n������
	isLanding_ = isLanding_ || isCollY;

	// �Ԃ����Ă��Ȃ��Ȃ�X�L�b�v
	if (isCollY == false) { return false; }

	// �߂Â��ړ���
	YMath::Vector3 approach = speedRef / 100.0f;

	// �����߂�����
	while (true)
	{
		// �Ԃ����Ă��邩 (���ړ�)
		bool isCollTempY = CollisionTemporaryBox2D({ 0,approach.y_ }, pairObjectBox); // y

		// �Ԃ����Ă���Ȃ烋�[�v������
		if (isCollTempY) { break; }

		// �����Â߂Â���
		if (isCollY) { posRef.y_ += approach.y_; }

		// �R���C�_�[�ʒu�X�V
		Box2D::SetBox2DCenter({ posRef.x_, posRef.y_ });
	}

	// ���x���Z�b�g
	if (isCollY) { speedRef.y_ = 0.0f; }

	return true;
}

bool ObjectCollider::CollisionTemporaryBox2DUpperSide(const YMath::Vector2& speed, const YGame::Box2D& pair)
{
	// ���ړ���
	float tempY = this->GetBox2DCenter().y_ + speed.y_;

	// ���O����
	return tempY - this->GetBox2DRadSize().y_ <= pair.GetBox2DCenter().y_ + pair.GetBox2DRadSize().y_;
}

YGame::Sprite3D* ObjectCollider::spActionSpr_ = nullptr;
YGame::ViewProjection* ObjectCollider::spVP_ = nullptr;

void ObjectCollider::StaticIntialize(YGame::ViewProjection* pVP)
{
	spActionSpr_ = YGame::Sprite3D::Create(YGame::Texture::Load("UI/key_E_PUSH.png"));

	spVP_ = pVP;
}

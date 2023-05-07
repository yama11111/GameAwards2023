#include "IParticle.h"
#include <cassert>

using YGame::IParticle;
using YGame::IParticleModel;
using YGame::IParticleSprite3D;
using YGame::ModelObject;
using YGame::ViewProjection;
using YGame::Model;
using YGame::Color;
using YMath::Ease;
using YMath::Timer;
using YMath::Power;
using YMath::Vector3;
using YMath::Vector4;
using YMath::Matrix4;

ViewProjection* IParticleModel::spVP_ = nullptr;
ViewProjection* IParticleSprite3D::spVP_ = nullptr;

#pragma region IParticle

void IParticle::Initialize(const uint32_t aliveTime, const DrawLocation& location)
{
	// �����t���O
	isAlive_ = true;

	// �����^�C�}�[������ + �J�n
	aliveTim_.Initialize(aliveTime);
	aliveTim_.SetActive(true);

	// �`��ꏊ
	location_ = location;
}

bool IParticle::UpdateLife()
{
	// ����ł���Ȃ�e��
	if (isAlive_ == false) { return false; }

	// �����^�C�}�[�X�V
	aliveTim_.Update();
	// �����^�C�}�[�I�� �� ���S
	if (aliveTim_.IsEnd()) { isAlive_ = false; }

	// �����Ă��邩�Ԃ�
	return isAlive_;
}

#pragma endregion


#pragma region IParticleModel

void IParticleModel::StaticInitialize(YGame::ViewProjection* pVP)
{
	// null�`�F�b�N
	assert(pVP);
	// ���
	spVP_ = pVP;
}

void IParticleModel::CreateObject()
{
	// ����
	color_.reset(Color::Create());
	obj_.reset(ModelObject::Create({}, spVP_, color_.get(), nullptr, nullptr));
}

#pragma endregion


#pragma region IParticleSprite3D

void IParticleSprite3D::StaticInitialize(YGame::ViewProjection* pVP)
{
	// null�`�F�b�N
	assert(pVP);
	// ���
	spVP_ = pVP;
}

void IParticleSprite3D::CreateObject(const bool isXAxisBillboard, const bool isYAxisBillboard)
{
	// ����
	color_.reset(Color::Create());
	obj_.reset(Sprite3DObject::Create({}, isXAxisBillboard, isYAxisBillboard, spVP_, color_.get()));
}

#pragma endregion



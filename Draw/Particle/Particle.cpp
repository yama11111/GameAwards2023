#include "Particle.h"
#include <cassert>

using YGame::IParticle;
using YGame::BubbleGrid;
using YGame::ModelObject;
using YGame::ViewProjection;
using YGame::Model;
using YGame::Color;
using YMath::Vector3;
using YMath::Vector4;
using YMath::Matrix4;

ViewProjection* IParticle::spVP_ = nullptr;
Model* BubbleGrid::spModel_ = nullptr;

#pragma region IParticle


void IParticle::StaticInitialize(YGame::ViewProjection* pVP)
{
	// null�`�F�b�N
	assert(pVP);
	// ���
	spVP_ = pVP;
}

void IParticle::Initialize(const uint32_t aliveTime)
{
	// �����t���O
	isAlive_ = true;

	// �����^�C�}�[������ + �J�n
	aliveTim_.Initialize(aliveTime);
	aliveTim_.SetActive(true);

	// ����
	color_.reset(Color::Create());
	obj_.reset(ModelObject::Create({}, spVP_, color_.get(), nullptr, nullptr));
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

#pragma region BubbleGrid

void BubbleGrid::Emit(
	const uint32_t aliveTime,
	const YGame::Transform::Status status,
	const Vector3& moveSpeed,
	const Vector3& rotaSpeed,
	const Vector3& color)
{
	// ---------- Object ---------- //

	// ���N���X������
	IParticle::Initialize(aliveTime);

	// �I�u�W�F�N�g������
	obj_->Initialize(status);

	// �F������
	color_->SetRGB(color);

	// ---------- Animation ---------- //

	// �ړ��X�s�[�h
	moveSpeed_ = moveSpeed;

	// ��]�X�s�[�h
	rotaSpeed_ = rotaSpeed;


	// �������͓�����
	isScalePowerSwitch_ = true;

	// �X�P�[���p���[
	scalePow_.Initialize(10);

	// �X�P�[���C�[�W���O
	scaleEas_.Initialize(0.0f, status.scale_.x_, 3.0f);
}

void BubbleGrid::Update()
{
	// �����X�V
	if (IParticle::UpdateLife() == false) { return; }

	// �ړ�
	obj_->pos_ += moveSpeed_;
	
	// ��]
	obj_->rota_ += rotaSpeed_;


	// �������Ԃ��p���[�ő�l��菭�ȂȂ�
	if (aliveTim_.End() - aliveTim_.Current() <= scalePow_.Max())
	{
		// �X�C�b�`�I�t
		isScalePowerSwitch_ = false;
	}

	// �p���[�X�V
	scalePow_.Update(isScalePowerSwitch_);

	// �ۑ��p�X�P�[��
	float sca = 0.0f;
	
	// �X�C�b�`�I���Ȃ�
	if (isScalePowerSwitch_)
	{
		// �C�[�Y�C��
		sca = scaleEas_.In(scalePow_.Ratio());

	}
	// ����ȊO�Ȃ�
	else
	{
		// �C�[�Y�A�E�g
		sca = scaleEas_.Out(scalePow_.Ratio());
	}

	// �X�P�[���ɓK�p
	obj_->scale_ = Vector3(sca, sca, sca);

	// Object�X�V
	obj_->UpdateMatrix();
}

void BubbleGrid::Draw()
{
	// �`��
	spModel_->Draw(obj_.get());
}

void BubbleGrid::StaticInitialize(Model* pModel)
{
	// null�`�F�b�N
	assert(pModel);
	// ������
	spModel_ = pModel;
}

#pragma endregion



#include "Bubble.h"

using YGame::IParticleModel;
using YGame::Bubble;
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

void Bubble::Emit(
	const uint32_t aliveTime,
	const YGame::Transform::Status status,
	const Vector3& moveSpeed,
	const Vector3& rotaSpeed,
	const Vector3& color,
	YGame::Sprite3D* pSprite3D, const DrawLocation& location)
{
	// �X�v���C�g3D�|�C���^���
	pSprite3D_ = pSprite3D;

	// ---------- Object ---------- //

	// ���N���X������
	IParticle::Initialize(aliveTime, location);
	IParticleSprite3D::CreateObject(false, false);

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

void Bubble::Update()
{
	// �����X�V
	if (IParticleSprite3D::UpdateLife() == false) { return; }

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

void Bubble::Draw()
{
	// �`��
	pSprite3D_->SetDrawCommand(obj_.get(), location_);
}
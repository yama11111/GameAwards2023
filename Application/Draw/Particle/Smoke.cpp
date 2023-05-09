#include "Smoke.h"

using YGame::IParticleSprite3D;
using YGame::Smoke;
using YGame::ViewProjection;
using YGame::Model;
using YGame::Color;
using YMath::Ease;
using YMath::Timer;
using YMath::Power;
using YMath::Vector3;
using YMath::Vector4;
using YMath::Matrix4;


void Smoke::Emit(
	const uint32_t aliveTime,
	const Transform::Status status,
	const Vector3& moveSpeed,
	const Vector3& rotaSpeed,
	const Vector3& color,
	YGame::Model* pModel, const DrawLocation& location)
{
	// ���f���|�C���^���
	pModel_ = pModel;

	// ---------- Object ---------- //

	// ���N���X������
	IParticle::Initialize(aliveTime, location);
	IParticleModel::CreateObject();

	// �I�u�W�F�N�g������
	obj_->Initialize(status);

	// �F������
	color_->SetRGB(color);

	// ---------- Animation ---------- //

	// �ړ��X�s�[�h
	moveSpeed_ = moveSpeed;

	// ��]�X�s�[�h
	rotaSpeed_ = rotaSpeed;

	// �A���t�@�l�C�[�W���O
	alphaEas_.Initialize(1.0f, 0.0f, 3.0f);
}

void Smoke::Update()
{
	// �����X�V
	if (IParticle::UpdateLife() == false) { return; }

	// �ړ�
	obj_->pos_ += moveSpeed_;

	// ��]
	obj_->rota_ += rotaSpeed_;

	// Object�X�V
	obj_->UpdateMatrix();

	// �A���t�@�l�C�[�W���O
	color_->SetAlpha(alphaEas_.In(aliveTim_.Ratio()));
}

void Smoke::Draw()
{
	// �`��
	pModel_->SetDrawCommand(obj_.get(), location_);
}

#include "Particle.h"
#include <cassert>

using YGame::IParticle;
using YGame::Smoke;
using YGame::RelayBug;
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

ViewProjection* IParticle::spVP_ = nullptr;
Model* Smoke::spModel_ = nullptr;
Model* Bubble::spModel_ = nullptr;
Model* RelayBug::spModel_ = nullptr;

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

#pragma region Smoke

void Smoke::Emit(
	const uint32_t aliveTime, 
	const Transform::Status status, 
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
	spModel_->Draw(obj_.get());
}

void Smoke::StaticInitialize(YGame::Model* pModel)
{
	// null�`�F�b�N
	assert(pModel);
	// ������
	spModel_ = pModel;
}

#pragma endregion

#pragma region RelayBug

void RelayBug::Emit(
	const uint32_t startToRelayFrame,
	const uint32_t relayToEndFrame,
	const Vector3& start, 
	const Vector3& relay, 
	const Vector3& end,
	const Vector3& rota, 
	const Vector3& scale, 
	const Vector3& color)
{
	// ---------- Object ---------- //

	// ���N���X������
	IParticle::Initialize(startToRelayFrame + relayToEndFrame);

	// �I�u�W�F�N�g������
	obj_->Initialize({ {}, rota, scale });

	// �F������
	color_->SetRGB(color);

	// ---------- Animation ---------- //

	// �J�n�n�_ ���� ���p�n�_ �܂ł̃t���O �� true ��
	isStartToRelay_ = true;

	// �J�n�n�_ ���� ���p�n�_ �܂ł̃^�C�}�[
	startToRelayTim_.Initialize(startToRelayFrame);
	
	// �^�C�}�[�J�n
	startToRelayTim_.SetActive(true);


	// ���p�n�_ ���� �I���n�_ �܂ł̃t���O
	isRelayToEnd_ = false;

	// ���p�n�_ ���� �I���n�_ �܂ł̃^�C�}�[
	relayToEndTim_.Initialize(relayToEndFrame);


	// �ʒu�C�[�W���O
	posEas_.Initialize(start, relay, 3.0f);

	// �I���ʒu
	end_ = end;
}

void RelayBug::Update()
{
	// �����X�V
	if (IParticle::UpdateLife() == false) { return; }

	// ����
	float ratio = 0.0f;

	// �J�n�n�_ ���� ���p�n�_ �Ȃ�
	if (isStartToRelay_)
	{
		// �^�C�}�[�X�V
		startToRelayTim_.Update();

		// �����ۑ�
		ratio = startToRelayTim_.Ratio();

		// �C�[�Y�A�E�g
		obj_->pos_ = posEas_.Out(ratio);

		// �^�C�}�[���I��������
		if (startToRelayTim_.IsEnd())
		{
			// �J�n�n�_ ���� ���p�n�_ ���I��
			isStartToRelay_ = false;

			// ���p�n�_ ���� �I���n�_ ���J�n
			isRelayToEnd_ = true;

			// �ʒu�C�[�W���O������
			posEas_.Initialize(obj_->pos_, end_, 3.0f);

			// �^�C�}�[�J�n
			relayToEndTim_.SetActive(true);
		}
	}
	// ���p�n�_ ���� �I���n�_�Ȃ�
	else if (isRelayToEnd_)
	{
		// �^�C�}�[�X�V
		relayToEndTim_.Update();

		// �����ۑ�
		ratio = relayToEndTim_.Ratio();

		// �C�[�Y�C��
		obj_->pos_ = posEas_.In(ratio);
	}

	// Object�X�V
	obj_->UpdateMatrix();
}

void RelayBug::Draw()
{
	// �`��
	spModel_->Draw(obj_.get());
}

void RelayBug::StaticInitialize(YGame::Model* pModel)
{
	// null�`�F�b�N
	assert(pModel);
	// ������
	spModel_ = pModel;
}

#pragma endregion

#pragma region Bubble

void Bubble::Emit(
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

void Bubble::Update()
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

void Bubble::Draw()
{
	// �`��
	spModel_->Draw(obj_.get());
}

void Bubble::StaticInitialize(Model* pModel)
{
	// null�`�F�b�N
	assert(pModel);
	// ������
	spModel_ = pModel;
}

#pragma endregion

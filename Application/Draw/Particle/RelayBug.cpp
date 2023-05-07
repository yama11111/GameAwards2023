#include "RelayBug.h"

using YGame::IParticleModel;
using YGame::RelayBug;
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

void RelayBug::Emit(
	const uint32_t startToRelayFrame,
	const uint32_t relayToEndFrame,
	const Vector3& start,
	const Vector3& relay,
	const Vector3& end,
	const Vector3& rota,
	const Vector3& scale,
	const Vector3& color,
	YGame::Model* pModel, const DrawLocation& location)
{
	// ���f���|�C���^���
	pModel_ = pModel;

	// ---------- Object ---------- //

	// ���N���X������
	IParticle::Initialize(startToRelayFrame + relayToEndFrame, location);
	IParticleModel::CreateObject();

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
	pModel_->SetDrawCommand(obj_.get(), location_);
}
#include "ParticleManager.h"
#include "MathUtillity.h"
#include "YAssert.h"
#include "Def.h"

using std::unique_ptr;
using YGame::ParticleManager;
using YGame::Transform;
using YGame::ModelObject;
using YGame::Model;
using YMath::Ease;
using YMath::Vector3;
using YMath::Vector4;
using YMath::GetRand;

void ParticleManager::StaticInitialize(YGame::ViewProjection* pVP)
{
	// ���N���X
	IParticle::StaticInitialize(pVP);

	// ----- ���f���ݒ� ----- //
	
	// ��
	Smoke::StaticInitialize(Model::Load("grid", false));
	
	// �����[��
	RelayBug::StaticInitialize(Model::Load("grid", false));
	
	// �A�O���b�h
	Bubble::StaticInitialize(Model::Load("grid", false));
	
}

void ParticleManager::Initialize()
{
	// �p�[�e�B�N���S�폜
	if (particles_.empty() == false)
	{
		particles_.clear();
	}
}

void ParticleManager::Update()
{
	// �p�[�e�B�N�����񂾂�폜
	particles_.remove_if([](std::unique_ptr<IParticle>& particle) { return particle->isAlive_ == false; });

	// �p�[�e�B�N�����X�V
	for (std::unique_ptr<IParticle>& particle : particles_)
	{
		particle->Update();
	}
}

void ParticleManager::Draw()
{
	// �p�[�e�B�N���`��
	for (std::unique_ptr<IParticle>& particle : particles_)
	{
		particle->Draw();
	}
}

void ParticleManager::EmitSmoke(
	const size_t& emitNum,
	const uint32_t& aliveFrame,
	const Vector3& center, const Vector3& range,
	const float& minScale, const float& maxScale,
	const Vector3& minMoveSpeed, const Vector3& maxMoveSpeed,
	const Vector3& minRotaSpeed, const Vector3& maxRotaSpeed,
	const Vector3& color,
	const float& place)
{
	// ���̐�����
	for (size_t i = 0; i < emitNum; i++)
	{
		// �p�[�e�B�N������
		unique_ptr<Smoke> newParticle = std::make_unique<Smoke>();


		// �ݒ�p�X�e�[�^�X
		Transform::Status status;

		// �͈͂Ƀ����_���Ȉʒu
		Vector3 randRange(
			GetRand(-range.x_, +range.x_, place),
			GetRand(-range.y_, +range.y_, place),
			GetRand(-range.z_, +range.z_, place));

		// ���S + �����_���͈͂̈ʒu��
		status.pos_ = center + randRange;

		// �����_���ȃT�C�Y�擾
		float scaleSize = GetRand(minScale, maxScale, place);

		// �����_���ȃT�C�Y�K��
		status.scale_ = Vector3(scaleSize, scaleSize, scaleSize);


		// �����_���Ȉړ��X�s�[�h
		Vector3 moveSpeed(
			GetRand(minMoveSpeed.x_, maxMoveSpeed.x_, place),
			GetRand(minMoveSpeed.y_, maxMoveSpeed.y_, place),
			GetRand(minMoveSpeed.z_, maxMoveSpeed.z_, place));


		// �����_���ȉ�]�X�s�[�h
		Vector3 rotaSpeed(
			GetRand(minRotaSpeed.x_, maxRotaSpeed.x_, place),
			GetRand(minRotaSpeed.y_, maxRotaSpeed.y_, place),
			GetRand(minRotaSpeed.z_, maxRotaSpeed.z_, place));


		// ����
		newParticle->Emit(aliveFrame, status, moveSpeed, rotaSpeed, color);

		// �}��
		particles_.push_back(std::move(newParticle));
	}
}

void ParticleManager::EmitRelayBug(
	const size_t& emitNum,
	const uint32_t& startToRelayFrame, const uint32_t& relayToEndFrame,
	const Vector3& start, const Vector3& end,
	const Vector3& relayRange,
	const Vector3& minRota, const Vector3& maxRota,
	const float& minScale, const float& maxScale,
	const Vector3& color,
	const float& place)
{
	// ���̐�����
	for (size_t i = 0; i < emitNum; i++)
	{
		// �p�[�e�B�N������
		unique_ptr<RelayBug> newParticle = std::make_unique<RelayBug>();


		// �͈�
		Vector3 randRange(
			GetRand(-relayRange.x_, +relayRange.x_, place),
			GetRand(-relayRange.y_, +relayRange.y_, place),
			GetRand(-relayRange.z_, +relayRange.z_, place));

		// ���p�n�_
		Vector3 relay = start + randRange;


		// �����_���ȃT�C�Y�擾
		float scaleSize = GetRand(minScale, maxScale, place);

		// �����_���ȃX�P�[��
		Vector3 scale = Vector3(scaleSize, scaleSize, scaleSize);


		// �����_���ȉ�]
		Vector3 rota(
			GetRand(minRota.x_, maxRota.x_, place),
			GetRand(minRota.y_, maxRota.y_, place),
			GetRand(minRota.z_, maxRota.z_, place));


		// ����
		newParticle->Emit(startToRelayFrame, relayToEndFrame, start, relay, end, rota, scale, color);

		// �}��
		particles_.push_back(std::move(newParticle));
	}
}

void ParticleManager::EmitBubbleGrid(
	const size_t& emitNum,
	const uint32_t& aliveFrame,  
	const Vector3& center, const Vector3& range, 
	const float& minScale, const float& maxScale,
	const Vector3& minMoveSpeed, const Vector3& maxMoveSpeed, 
	const Vector3& minRotaSpeed, const Vector3& maxRotaSpeed, 
	const Vector3& color,
	const float& place)
{
	// ����������
	for (size_t i = 0; i < emitNum; i++)
	{
		// �p�[�e�B�N������
		unique_ptr<Bubble> newParticle = std::make_unique<Bubble>();


		// �ݒ�p�X�e�[�^�X
		Transform::Status status;

		// �͈͂Ƀ����_���Ȉʒu
		Vector3 randRange(
			GetRand(-range.x_, +range.x_, place),
			GetRand(-range.y_, +range.y_, place),
			GetRand(-range.z_, +range.z_, place));

		// ���S + �����_���͈͂̈ʒu��
		status.pos_ = center + randRange;

		// �����_���ȃT�C�Y�擾
		float scaleSize = GetRand(minScale, maxScale, place);

		// �����_���ȃT�C�Y�K��
		status.scale_ = Vector3(scaleSize, scaleSize, scaleSize);


		// �����_���Ȉړ��X�s�[�h
		Vector3 moveSpeed(
			GetRand(minMoveSpeed.x_, maxMoveSpeed.x_, place),
			GetRand(minMoveSpeed.y_, maxMoveSpeed.y_, place),
			GetRand(minMoveSpeed.z_, maxMoveSpeed.z_, place));


		// �����_���ȉ�]�X�s�[�h
		Vector3 rotaSpeed(
			GetRand(minRotaSpeed.x_, maxRotaSpeed.x_, place),
			GetRand(minRotaSpeed.y_, maxRotaSpeed.y_, place),
			GetRand(minRotaSpeed.z_, maxRotaSpeed.z_, place));


		// ����
		newParticle->Emit(aliveFrame, status, moveSpeed, rotaSpeed, color);

		// �}��
		particles_.push_back(std::move(newParticle));
	}
}

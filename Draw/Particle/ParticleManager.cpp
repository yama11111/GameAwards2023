#include "ParticleManager.h"
#include "MathUtillity.h"
#include "YAssert.h"
#include "Def.h"

using YGame::ParticleManager;
using YGame::Model;
using YMath::Vector3;

void ParticleManager::StaticInitialize(YGame::ViewProjection* pVP)
{
	// ���N���X
	IParticle::StaticInitialize(pVP);

	// ----- ���f���ݒ� ----- //
	
	// �Ή�
	//FireSpark::StaticInitialize(Model::LoadObj("", true));
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

void ParticleManager::EmitFireSpark(
	const YMath::Vector3& pos,
	const YMath::Vector3& range,
	const float maxScale,
	const YMath::Vector3& speed,
	const YMath::Vector4& color,
	const uint32_t frame, const size_t num)
{
	for (size_t i = 0; i < num; i++)
	{
		std::unique_ptr<FireSpark> newParticle = std::make_unique<FireSpark>();

		uint32_t swayT = frame / YMath::GetRand(1, 2);

		Vector3 p = pos;
		p.x_ += YMath::GetRand(-range.x_, range.x_, 100.0f);
		p.y_ += YMath::GetRand(-range.y_, range.y_, 100.0f);
		p.z_ += YMath::GetRand(-range.z_, range.z_, 100.0f);
		float s = YMath::GetRand(maxScale / 2.0f, maxScale, 100.0f);

		newParticle->Emit(frame, swayT, speed, p, s, color);
		particles_.push_back(std::move(newParticle));
	}
}
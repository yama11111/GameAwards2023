#pragma once
#include "Particle.h"
#include <list>

namespace YGame
{
	// �p�[�e�B�N���}�l�[�W���[
	class ParticleManager
	{
	private:
		// �p�[�e�B�N�����X�g
		std::list<std::unique_ptr<IParticle>> particles_;
	public:
		// ������
		void Initialize();
		// �X�V
		void Update();
		// �`��
		void Draw();
	public:

		void EmitFireSpark(
			const YMath::Vector3& pos, 
			const YMath::Vector3& range, 
			const float maxScale, 
			const YMath::Vector3& speed, 
			const YMath::Vector4& color, 
			const uint32_t frame, const size_t num);
	public:
		// �ÓI������
		static void StaticInitialize(YGame::ViewProjection* pVP);
	};
}


#pragma once
#include "Particle.h"
#include <list>

namespace YGame
{
	// パーティクルマネージャー
	class ParticleManager
	{
	private:
		// パーティクルリスト
		std::list<std::unique_ptr<IParticle>> particles_;
	public:
		// 初期化
		void Initialize();
		// 更新
		void Update();
		// 描画
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
		// 静的初期化
		static void StaticInitialize(YGame::ViewProjection* pVP);
	};
}


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

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize();

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();
	
	public:
		
		/// <summary>
		/// 光るグリッドブロック発生
		/// </summary>
		/// <param name="frame"> : 生存時間</param>
		/// <param name="pParent"> : 親行列</param>
		/// <param name="color"> : 色</param>
		void EmitIlluminationGridBlock(
			const uint32_t frame,
			YMath::Matrix4* pParent,
			const YMath::Vector3& color);

		/// <summary>
		/// 設置グリッドブロック発生
		/// </summary>
		/// <param name="frame"> : 生存時間</param>
		/// <param name="pParent"> : 親行列</param>
		/// <param name="color"> : 色</param>
		void EmitPlaceGridBlock(
			const uint32_t frame,
			YMath::Matrix4* pParent,
			const YMath::Vector3& color);

	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		static void StaticInitialize(YGame::ViewProjection* pVP);
	
	public:
		
		~ParticleManager() = default;
	};
}


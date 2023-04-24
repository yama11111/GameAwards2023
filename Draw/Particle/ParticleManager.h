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
		/// 泡グリッド発生
		/// </summary>
		/// <param name="frame"> : </param>
		/// <param name="status"> : トランスフォーム設定ステータス</param>
		/// <param name="moveSpeed"> : 移動スピード</param>
		/// <param name="rotaSpeed"> : 回転スピード</param>
		/// <param name="color"> : 色</param>
		void EmitBubbleGrid(
			const uint32_t frame,
			const YGame::Transform::Status status,
			const YMath::Vector3& moveSpeed,
			const YMath::Vector3& rotaSpeed,
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


#pragma once
#include "IParticle.h"

namespace YGame
{
	// 煙
	class Smoke : public IParticleModel
	{

	private:

		// 移動スピード
		YMath::Vector3 moveSpeed_;

		// 回転スピード
		YMath::Vector3 rotaSpeed_;


		// アルファ値イージング
		YMath::Ease<float> alphaEas_;

	public:

		/// <summary>
		/// 発生
		/// </summary>
		/// <param name="aliveFrame"> : 生存時間</param>
		/// <param name="status"> : トランスフォーム設定ステータス</param>
		/// <param name="moveSpeed"> : 移動スピード</param>
		/// <param name="rotaSpeed"> : 回転スピード</param>
		/// <param name="color"> : 色</param>
		/// <param name="pModel"> : モデルポインタ</param>
		/// <param name="location"> : 描画場所</param>
		void Emit(
			const uint32_t aliveFrame,
			const Transform::Status status,
			const YMath::Vector3& moveSpeed,
			const YMath::Vector3& rotaSpeed,
			const YMath::Vector3& color,
			Model* pModel, const DrawLocation& location);

		/// <summary>
		/// 更新
		/// </summary>
		void Update() override;

		/// <summary>
		/// 描画
		/// </summary>
		void Draw() override;

	public:

		~Smoke() = default;
	};
}

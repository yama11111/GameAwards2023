#pragma once
#include "IParticle.h"

namespace YGame
{
	// 泡
	class Bubble : public IParticleSprite3D
	{

	private:

		// 移動スピード
		YMath::Vector3 moveSpeed_;

		// 回転スピード
		YMath::Vector3 rotaSpeed_;


		// 発生 + 消滅スケール用パワースイッチ
		bool isScalePowerSwitch_ = false;

		// 発生 + 消滅用スケール用パワー
		YMath::Power scalePow_;

		// 発生 + 消滅用スケールイージング
		YMath::Ease<float> scaleEas_;

	public:

		/// <summary>
		/// 発生
		/// </summary>
		/// <param name="aliveTime"> : 生存時間</param>
		/// <param name="status"> : トランスフォーム設定ステータス</param>
		/// <param name="moveSpeed"> : 移動スピード</param>
		/// <param name="rotaSpeed"> : 回転スピード</param>
		/// <param name="color"> : 色</param>
		/// <param name="pSprite"> : スプライト3Dポインタ</param>
		/// <param name="location"> : 描画場所</param>
		void Emit(
			const uint32_t aliveTime,
			const Transform::Status status,
			const YMath::Vector3& moveSpeed,
			const YMath::Vector3& rotaSpeed,
			const YMath::Vector3& color,
			Sprite3D* pSprite, const DrawLocation& location);

		/// <summary>
		/// 更新
		/// </summary>
		void Update() override;

		/// <summary>
		/// 描画
		/// </summary>
		void Draw() override;

	public:

		~Bubble() = default;

	};
}


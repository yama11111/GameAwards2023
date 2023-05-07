#pragma once
#include "IParticle.h"

namespace YGame
{
	// リレー虫
	class RelayBug : public IParticleModel
	{

	private:

		// 開始地点 から 中継地点 までのフラグ
		bool isStartToRelay_ = false;

		// 開始地点 から 中継地点 までのタイマー
		YMath::Timer startToRelayTim_;


		// 中継地点 から 終了地点 までのフラグ
		bool isRelayToEnd_ = false;

		// 中継地点 から 終了地点 までのタイマー
		YMath::Timer relayToEndTim_;


		// 位置イージング
		YMath::Ease<YMath::Vector3> posEas_;

		// 終了地点保存用
		YMath::Vector3 end_;

	public:

		/// <summary>
		/// 発生
		/// </summary>
		/// <param name="startToRelayFrame"> : 開始地点 から 中継地点 までの時間</param>
		/// <param name="relayToEndFrame"> : 中継地点 から 終了地点 までの時間</param>
		/// <param name="start"> : 開始地点</param>
		/// <param name="relay"> : 中継地点</param>
		/// <param name="end"> : 終了地点</param>
		/// <param name="rota"> : 回転</param>
		/// <param name="scale"> : 大きさ</param>
		/// <param name="color"> : 色</param>
		/// <param name="pModel"> : モデルポインタ</param>
		/// <param name="location"> : 描画場所</param>
		void Emit(
			const uint32_t startToRelayFrame,
			const uint32_t relayToEndFrame,
			const YMath::Vector3& start,
			const YMath::Vector3& relay,
			const YMath::Vector3& end,
			const YMath::Vector3& rota,
			const YMath::Vector3& scale,
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

		~RelayBug() = default;
	};
}

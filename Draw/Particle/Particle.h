#pragma once
#include "Model.h"
#include "Lerp.h"
#include "Timer.h"
#include "Power.h"

namespace YGame
{
	// パーティクル基底クラス
	class IParticle
	{
	public:
		// 生存フラグ
		bool isAlive_ = false;
	protected:
		// オブジェクト
		std::unique_ptr<YGame::ModelObject> obj_;
	public:
		// 更新
		virtual void Update() = 0;
		// 描画
		virtual void Draw() = 0;
	public:
		// デストラクタ
		virtual ~IParticle() = default;
	};


	class FireSpark : public IParticle
	{
	private:
		YMath::Timer aliveTim_;

		bool isSwitching_ = false;
		YMath::Power swayingPow_;
		YMath::Vector3 spd_;

		YMath::Ease<float> scaleEas_;
		std::unique_ptr<YGame::Color> color_;
		YMath::Ease<float> alphaEas_;
	public:
		void Emit(
			const uint32_t aliveTime,
			const uint32_t swayingTime,
			const YMath::Vector3& speed,
			const YMath::Vector3& pos, const float scale,
			const YMath::Vector4& color);
		void Update() override;
		void Draw() override;
	public:
		~FireSpark() override = default;
	private:
		static YGame::Model* pModel_;
	public:
		static void StaticInitialize(YGame::Model* pModel);
	};
}

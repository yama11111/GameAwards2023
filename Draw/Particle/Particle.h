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

		// 色
		std::unique_ptr<YGame::Color> color_;
		
		// 生存タイマー
		YMath::Timer aliveTim_;
	
	public:
		
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="aliveTime"> : 生存時間</param>
		void Initialize(const uint32_t aliveTime);
		
		/// <summary>
		/// 生命更新
		/// </summary>
		/// <returns> : 生きているか</returns>
		bool UpdateLife();

		/// <summary>
		/// 更新
		/// </summary>
		virtual void Update() = 0;

		/// <summary>
		/// 描画
		/// </summary>
		virtual void Draw() = 0;
	
	protected:
		
		// ビュープロジェクションポインタ
		static YGame::ViewProjection* spVP_;
	
	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		static void StaticInitialize(YGame::ViewProjection* pVP);
	
	public:

		virtual ~IParticle() = default;
	
	};

	class BubbleGrid : public IParticle
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
		void Emit(
			const uint32_t aliveTime,
			const YGame::Transform::Status status,
			const YMath::Vector3& moveSpeed,
			const YMath::Vector3& rotaSpeed,
			const YMath::Vector3& color);

		/// <summary>
		/// 更新
		/// </summary>
		void Update() override;

		/// <summary>
		/// 描画
		/// </summary>
		void Draw() override;

	private:

		// 静的モデルポインタ
		static YGame::Model* spModel_;

	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		/// <param name="pModel"> : モデルポインタ</param>
		static void StaticInitialize(YGame::Model* pModel);

	public:

		~BubbleGrid() = default;

	};

}

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

	// リレー虫
	class RelayBug : public IParticle
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
		void Emit(
			const uint32_t startToRelayFrame,
			const uint32_t relayToEndFrame,
			const YMath::Vector3& start,
			const YMath::Vector3& relay,
			const YMath::Vector3& end,
			const YMath::Vector3& rota,
			const YMath::Vector3& scale,
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

		~RelayBug() = default;
	};

	// 泡
	class Bubble : public IParticle
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

		~Bubble() = default;

	};

}

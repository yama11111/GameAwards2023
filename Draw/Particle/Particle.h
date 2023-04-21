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

	// 光るグリッドブロック
	class IlluminationGridBlock : public IParticle
	{
	private:

		// アルファ値用パワー
		YMath::Power alphaPow_;

		// アルファ値パワーを動かすか
		bool isActAlphaPower_ = false;

		// アルファ値イージング
		YMath::Ease<float> alphaEas_;

	public:

		/// <summary>
		/// 発生
		/// </summary>
		/// <param name="aliveTime"> : 生存時間</param>
		/// <param name="pParent"> : 親行列</param>
		/// <param name="color"> : 色</param>
		/// <param name="alphaEas"> : アルファ値イージング</param>
		void Emit(
			const uint32_t aliveTime,
			YMath::Matrix4* pParent,
			const YMath::Vector3& color,
			const YMath::Ease<float> alphaEas);

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

		~IlluminationGridBlock() = default;

	};

	// 設置グリッドブロック
	class PlaceGridBlock : public IParticle
	{
	private:

		// 大きさイージング
		YMath::Ease<float> scaleEas_;

	public:

		/// <summary>
		/// 発生
		/// </summary>
		/// <param name="aliveTime"> : 生存時間</param>
		/// <param name="pParent"> : 親行列</param>
		/// <param name="scaleEas"> : 大きさイージング</param>
		/// <param name="color"> : 色</param>
		void Emit(
			const uint32_t aliveTime,
			YMath::Matrix4* pParent,
			const YMath::Ease<float> scaleEas,
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

		~PlaceGridBlock() = default;

	};
}

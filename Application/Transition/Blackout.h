#pragma once
#include "BaseTransition.h"
#include "Sprite2D.h"

namespace YScene
{
	// 暗転
	class Blackout : public BaseTransition
	{
	
	private:
		
		// 暗転段階
		enum class Step
		{
			Dark,	 // 暗
			Load,	 // ロード時間
			Bright,	 // 明
		};
	
	private:
		
		// オブジェクト
		std::unique_ptr<YGame::Sprite2D::Object> obj_;
		
		// 色
		std::unique_ptr<YGame::CBColor> color_;

		// 段階
		Step step_ = Step::Dark;
		

		// 透過度パワー
		YMath::Power blendPow_;
	
	public:

		/// <summary>
		/// 初期化
		/// </summary>
		virtual void Initialize() override;

		/// <summary>
		/// 終了処理
		/// </summary>
		virtual void Finalize() override;

		/// <summary>
		/// リセット (中身だけ初期化)
		/// </summary>
		virtual void Reset() override;

		/// <summary>
		/// 更新
		/// </summary>
		virtual void Update() override;

		/// <summary>
		/// 描画
		/// </summary>
		virtual void Draw() override;

	public:

		/// <summary> 
		/// 動作開始
		/// </summary>
		/// <param name="loadFrame"> : 読み込む時間</param>
		/// <param name="leftTop"> : 1番左上のブロックの位置</param>
		virtual void Activate(const uint32_t changeFrame, const uint32_t loadFrame) override;

	private:
		
		// 切り替え処理更新
		void UpdateChange();
		
		// 透過処理更新
		void UpdateBlend();
	
	private:
		
		// スプライト(2D)
		static YGame::Sprite2D* spCurtenSpr_;

		// 透過度イージング
		static YMath::Ease<float> sBlendEas_;
	
	public:
		
		// 静的初期化
		static void StaticInitialize();
	
	public:
		
		Blackout() = default;
		
		~Blackout() = default;
	};
}

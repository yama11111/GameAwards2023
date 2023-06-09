#pragma once
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Model.h"
#include "Audio.h"
#include "Lerp.h"
#include "Power.h"
#include "Timer.h"
#include <memory>

namespace YScene
{
	// トランジション基底クラス
	class BaseTransition
	{
	
	protected:
		
		// 動作しているか
		bool isAct_ = false;

		// 幕切れ中か
		bool isFalling_ = false;
		
		// 切り替わりの瞬間
		bool isChangeMoment_ = false;
		
		// 幕開け中か
		bool isRising_ = false;

		// 終了しているか
		bool isEnd_ = false;
		
		// ローディング用タイマー
		YMath::Timer loadTim_;
	
	public:
		
		/// <summary>
		/// 初期化
		/// </summary>
		virtual void Initialize() = 0;

		/// <summary>
		/// リセット (中身だけ初期化)
		/// </summary>
		virtual void Reset() = 0;

		/// <summary>
		/// 終了処理
		/// </summary>
		virtual void Finalize() = 0;

		/// <summary>
		/// 更新
		/// </summary>
		virtual void Update() = 0;

		/// <summary>
		/// 描画
		/// </summary>
		virtual void Draw() = 0;
	
	public:
		
		/// <summary> 
		/// 動作開始
		/// </summary>
		/// <param name="loadFrame"> : 読み込む時間</param>
		/// <param name="leftTop"> : 1番左上のブロックの位置</param>
		virtual void Activate(const uint32_t changeFrame, const uint32_t loadFrame) = 0;

	public:

		/// <summary>
		/// 動作中か取得
		/// </summary>
		/// <returns>動作中か</returns>
		bool IsAct() const { return isAct_; }

		/// <summary>
		/// 幕切れ中か
		/// </summary>
		/// <returns></returns>
		bool IsFalling() const { return isFalling_; }
		
		/// <summary> 
		/// 切り替わりの瞬間か取得
		/// </summary>
		/// <returns>切り替わりの瞬間か</returns>
		bool IsChangeMoment() const { return isChangeMoment_; }

		/// <summary>
		/// 幕開け中か
		/// </summary>
		/// <returns>切り替わっている途中か</returns>
		bool IsRising() const { return isRising_; }

		/// <summary>
		/// 終了しているか取得
		/// </summary>
		/// <returns>終了しているか</returns>
		bool IsEnd() const { return isEnd_; }
	
	public:

		// コンストラクタ
		BaseTransition() = default;
		
		// デストラクタ
		virtual ~BaseTransition() = default;
	};
}

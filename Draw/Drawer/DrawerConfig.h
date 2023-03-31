#pragma once
#include "Vector3.h"

// 描画用クラス
namespace DrawerConfig
{
	// 透明モデルの大きさ
	const float InvisibleScale = 0.95f;

	// プレイヤー
	namespace Player 
	{
		// 大きさ
		const YMath::Vector3 DefScale = { 1.0f,1.0f,1.0f };

		// 置けないときの色
		const YMath::Vector3 BadColor = { 1.0f,0.0f,1.0f };

		// 立ちモーション
		namespace Idle
		{
			// 間隔
			const unsigned int IntervalTime = 10;

			// ぷよぷよアニメーション
			namespace SlimeAction
			{
				// 伸縮量
				const float Value = 0.5f;

				// 時間 (F)
				const unsigned int Frame = 20;

				// 指数
				const float Power = 3.0f;
			}
		}

		// ジャンプモーション
		namespace Jump
		{
			// ぷよぷよアニメーション
			namespace SlimeAction
			{
				// 伸縮量
				const float Value = 0.5f;

				// 時間 (F)
				const unsigned int Frame = 20;

				// 指数
				const float Power = 3.0f;
			}
		}

		// 着地モーション
		namespace Landing
		{
			// ぷよぷよアニメーション
			namespace SlimeAction
			{
				// 伸縮量
				const float Value = 0.5f;
				
				// 時間 (F)
				const unsigned int Frame = 20;

				// 指数
				const float Power = 3.0f;
			}
		}
	}

	// フィルター
	namespace Filter 
	{
		// 大きさ
		const YMath::Vector3 DefScale = { 1.0f,1.0f,1.0f };

		// 置けないときの色
		const YMath::Vector3 BadColor = { 0.1f,0.1f,0.1f };

		// 立ちモーション
		namespace Idle
		{
			// 間隔
			const unsigned int IntervalTime = 10;
		}
	}

	// ブロック
	namespace Block
	{
		// 大きさ
		const YMath::Vector3 DefScale = { 1.0f,1.0f,1.0f };

		// 立ちモーション
		namespace Idle
		{
			// 間隔
			const unsigned int IntervalTime = 10;
		}
	}

	// ゲート
	namespace Gate
	{
		// 大きさ
		const YMath::Vector3 DefScale = { 1.0f,1.0f,1.0f };

		// 立ちモーション
		namespace Idle
		{
			// 間隔
			const unsigned int IntervalTime = 10;
		}
	}

	// ゴール
	namespace Goal
	{
		// 大きさ
		const YMath::Vector3 DefScale = { 1.0f,1.0f,1.0f };

		// 立ちモーション
		namespace Idle
		{
			// 間隔
			const unsigned int IntervalTime = 10;
		}
	}
}
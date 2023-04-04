#pragma once
#include "Def.h"

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
			const unsigned int IntervalTime = 20;
		}
		
		// 回転モーション
		namespace Rota 
		{
			// フレーム
			const unsigned int Frame = 100;

			// 量 (内)
			namespace Inside
			{
				// 初期値
				const YMath::Vector3 Start = { +PI / 3.0f,0.0f,+PI / 2.0f };
				// 最終値
				const YMath::Vector3 End   = { +PI / 3.0f,0.0f,+PI / 2.0f + +PI * 2.0f };
			}

			// 量 (外)
			namespace Outside
			{
				// 初期値
				const YMath::Vector3 Start = { -PI / 3.0f,0.0f,-PI / 3.0f };
				// 最終値
				const YMath::Vector3 End   = { -PI / 3.0f,0.0f,-PI / 3.0f - PI * 2.0f };
			}
			
			// 指数
			const float Exponent = 2.0f;
		}
	}

	// セレクトシーン
	namespace Select 
	{
		// 地球
		namespace Earth
		{
			// 大きさ
			const float Scale = 32.0f;
		}

		// ステージ
		namespace Stage
		{
			// フレーム
			const int Frame = 30;
			
			// 指数
			const float Exponent = 1.4f;
		}
	}
}
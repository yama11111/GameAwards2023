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

		// 色
		const YMath::Vector3 DefColor = { 0.1f,0.9f,0.8f };

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
				const float Exponent = 3.0f;
			}
		}

		// ジャンプモーション
		namespace Jump
		{
			// ぷよぷよアニメーション
			namespace SlimeAction
			{
				// 伸縮量
				const float Value = 0.25f;

				// 時間 (F)
				const unsigned int Frame = 4;

				// 指数
				const float Exponent = 3.0f;
			}
		}

		// 着地モーション
		namespace Landing
		{
			// ぷよぷよアニメーション
			namespace SlimeAction
			{
				// 伸縮量
				const float Value = 0.4f;
				
				// 時間 (F)
				const unsigned int Frame = 4;

				// 指数
				const float Exponent = 3.0f;
			}
		}

		// リスポーンモーション
		namespace Respawn
		{
			// 時間 (F)
			const unsigned int Frame = 20;
			
			// 指数
			const float Exponent = 3.0f;

			// ぷよぷよアニメーション
			namespace SlimeAction
			{
				// 伸縮量
				const float Value = 0.4f;

				// 時間 (F)
				const unsigned int Frame = 25;

				// 指数
				const float Exponent = 3.0f;
			}
		}
	}

	// フィルター
	namespace Filter 
	{
		// 大きさ
		const YMath::Vector3 DefScale = { 1.0f,1.0f,1.0f };

		// 色
		const YMath::Vector4 DefColor = { 1.0f,0.0f,0.0f,0.25f };

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

		// 色
		namespace CoreColor
		{
			// フレーム
			const unsigned int Frame = 120;

			// 通常
			namespace Normal
			{
				// 初期値
				const YMath::Vector4 Start = { 0.1f, 0.1f, 0.1f, 1.0f };

				// 最終値
				const YMath::Vector4 End   = { 0.15f, 0.15f, 0.15f, 1.0f };
			}

			// 赤
			namespace Red
			{
				// 初期値
				const YMath::Vector4 Start = { 0.6f, 0.0f, 0.0f, 1.0f };

				// 最終値
				const YMath::Vector4 End   = { 1.0f, 0.0f, 0.0f, 1.0f };
			}

			// 指数
			const float Exponent = 3.0f;
		}
		
		// 立ちモーション
		namespace Idle
		{
			// 間隔
			const unsigned int IntervalTime = 10;
		}

		// 取得アニメーション
		namespace Catch
		{
			// 成功
			namespace Success
			{
				// フレーム
				const unsigned int Frame = 10;


				// 初期値
				const float Start = 0.0f;
				
				// 最終値
				const float End = 0.0f;
				
				// 指数
				const float Exponent = 0.0f;
			}

			// 失敗
			namespace Failure
			{
				// フレーム
				const unsigned int Frame = 10;


				// 初期値
				const float Start = 0.0f;

				// 最終値
				const float End = 0.0f;

				// 指数
				const float Exponent = 0.0f;

				// 揺れ
				namespace Shake
				{
					// 揺れ量
					const float Swing = 0.4f;

					// 収まる量
					const float Dekey = 0.1f;

					// 扱う位
					const float Place = 10.0f;
				}
			}
		}

		// 設置アニメーション
		namespace Place
		{
			// 成功
			namespace Success
			{
				// フレーム
				const unsigned int Frame = 10;


				// 初期値
				const float Start = 0.0f;

				// 最終値
				const float End = 0.0f;

				// 指数
				const float Exponent = 0.0f;
			}

			// 失敗
			namespace Failure
			{
				// フレーム
				const unsigned int Frame = 10;


				// 初期値
				const float Start = 0.0f;

				// 最終値
				const float End = 0.0f;

				// 指数
				const float Exponent = 0.0f;

				// 揺れ
				namespace Shake
				{
					// 揺れ量
					const float Swing = 0.4f;

					// 収まる量
					const float Dekey = 0.1f;

					// 扱う位
					const float Place = 10.0f;
				}
			}
		}
	}

	// ゲート
	namespace Gate
	{
		// 大きさ
		const YMath::Vector3 DefScale = { 1.0f,1.0f,1.0f };
		
		// 色
		const YMath::Vector3 DefColor = { 1.0f,1.0f,1.0f };

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

	// タイトル
	namespace Title
	{
		// ロゴ
		namespace Logo
		{
			// 位置
			const YMath::Vector3 Pos = { WinSize.x_ / 2.0f - 160.0f, WinSize.y_ / 2.0f - 200.0f, 0.0f };

			// 大きさ
			const YMath::Vector3 Scale = { 0.6f,0.6f,0.0f };
		}

		// 影
		namespace Shadow
		{
			// 位置
			const YMath::Vector3 Pos = { WinSize.x_ - 360.0f,WinSize.y_ / 2.0f,0.0f };

			// 大きさ
			const YMath::Vector3 Scale = { 1.0f,WinSize.y_,0.0f };
		}
		
		// 選択
		namespace UI
		{
			// スタート位置
			const YMath::Vector3 Start = { WinSize.x_ - 240.0f,WinSize.y_ - 240.0f,0.0f };
			
			// 終了位置
			const YMath::Vector3 Exit  = { WinSize.x_ - 240.0f,WinSize.y_ - 120.0f,0.0f };

			// 選択中色
			const YMath::Vector4 OnColor  = { 1.0f,1.0f,1.0f,1.0f };
			
			// 無選択色
			const YMath::Vector4 OffColor = { 0.4f,0.4f,0.4f,0.75f };
		}

	}
	
	// セレクト
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

		// カード
		namespace Card 
		{
			// Xの位置
			const float DefPosX = WinSize.x_ - 96.0f;
			
			// 中心の高さ
			const float CenterHeight = WinSize.y_ / 2.0f;
			
			// 全体の高さ
			const float TotalHeight = 512.0f;
		}

		// レターボックス
		namespace LetterBox
		{
			// 高さ (上)
			const float TopHeight = 96.0f;
			// 高さ (下)
			const float BottomHeight = 96.0f;
		}

		// ロゴ
		namespace Logo 
		{
			// 位置
			const YMath::Vector3 Pos = { 224.0f,48.0f,0.0f };
		}
	}

	// カード
	namespace Card
	{
		// ブヨブヨアニメーション
		namespace SlimeAction
		{
			// 時間
			const unsigned int Frame = 10;
			
			// 伸縮量
			const float Value = 0.25f;

			// 指数
			const float Exponent = 1.4f;
		}

		// アニメーション
		namespace Animation
		{
			// フレーム
			const int Frame = 10;

			// 移動
			namespace Move
			{

				// 移動量 (X)
				const float ValueX = -128.0f;

				// 指数
				const float Exponent = 1.2f;
			}

			// 拡大
			namespace Scale
			{
				// 拡大量
				const float Value = 0.25f;

				// 指数
				const float Exponent = 1.2f;
			}
		}
	}

	// グリッド
	namespace Grid
	{
		// 色
		const YMath::Vector3 DefColor = { 0.0f,0.8f,0.8f };

		// アルファ値
		namespace Alpha
		{
			// 時間
			const int Frame = 30;

			// 初期値
			const float Start = 0.5f;

			// 最終値
			const float End = 0.2f;

			// 指数
			const float Exponent = 3.0f;
		}
	}
}
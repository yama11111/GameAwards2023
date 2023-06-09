#pragma once
#include "Def.h"

// 描画用クラス
namespace DrawerConfig
{
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

		// 移動モーション
		namespace Move
		{
			// 回転
			namespace Rota
			{
				// 時間 (F)
				const unsigned int Frame = 10;

				// 回転量
				const float Value = PI * 0.1f;

				// 指数
				const float Exponent = 3.0f;
			}

			// 発生
			namespace Smoke
			{
				// 時間 (F)
				const unsigned int IntervalFrame = 5;


				// 生存時間
				const unsigned int AliveFrame = 20;


				// 最小発生数
				const unsigned int MinNum = 1;

				// 最大発生数
				const unsigned int MaxNum = 2;


				// 範囲
				const YMath::Vector3 Range = { 0.0f, 1.5f, 1.0f };


				// 最小スケールサイズ
				const float MinScaleSize = 0.2f;

				// 最大スケールサイズ
				const float MaxScaleSize = 0.3f;


				// 最小移動スピード
				const YMath::Vector3 MinMoveSpeed = { +0.1f, +0.025f, +0.0f };

				// 最大移動スピード
				const YMath::Vector3 MaxMoveSpeed = { +0.3f, +0.05f, +0.0f };


				// 最小回転スピード
				const YMath::Vector3 MinRotaSpeed = { -0.1f, -0.1f, -0.1f };

				// 最大回転スピード
				const YMath::Vector3 MaxRotaSpeed = { +0.1f, +0.1f, +0.1f };


				// 色
				const YMath::Vector3 Color = { 0.1f,0.9f,0.8f };

				// 位
				const float Place = 100.0f;
				
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

	// ブロック
	namespace Block
	{
		// 大きさ
		const YMath::Vector3 DefScale = { 1.0f,1.0f,1.0f };

		// 殻色
		namespace ShellColor
		{
			// 失敗色
			const YMath::Vector4 Failure = { 0.4f,0.0f,0.0f,1.0f };

			// 原色の比率
			const YMath::Vector4 OriginalRate = { 0.1f,0.1f,0.1f,1.0f };
		}

		// 立ちモーション
		namespace Idle
		{
			// 間隔
			const unsigned int IntervalTime = 10;
		}
	}

	// ばね
	namespace Spring
	{
		// 下リング初期回転量
		static const float BottomRingDefaultRotaValue = +PI / 4.0f;

		// 立ちモーション
		namespace Idle
		{
			// 高さ
			namespace Height
			{
				// フレーム
				static unsigned int Frame = 60;

				// 上
				namespace Top
				{
					// 開始値
					static const float Start = 0.0f;

					// 終了値
					static const float End = 0.25f;

					// 指数
					static const float Exponent = 2.0f;
				}

				// 下
				namespace Bottom
				{
					// 開始値
					static const float Start = 0.0f;

					// 終了値
					static const float End = 0.2f;

					// 指数
					static const float Exponent = 2.0f;
				}
			}

			// 回転スピード
			namespace RotaSpeed
			{
				// フレーム
				static unsigned int Frame = 120;

				// 開始値
				static const float Start = 0.0f;

				// 終了値
				static const float End = +PI * 4.0f;

				// 指数
				static const float Exponent = 1.0f;
			}
		}

		// ジャンプアニメーション
		namespace Jump
		{
			// フレーム
			namespace Frame
			{
				// 予備動作
				static unsigned int Anticipation = 5;

				// 本番
				static unsigned int Performance = 10;
			}

			// 高さ
			namespace Height
			{
				// 予備動作
				namespace Anticipation
				{
					// 開始値
					static const float Start = 0.0f;

					// 終了値
					static const float End = -0.5f;

					// 指数
					static const float Exponent = 3.0f;
				}
				
				// 本番
				namespace Performance
				{
					// 上
					namespace Top
					{
						// 開始値
						static const float Start = 0.0f;

						// 終了値
						static const float End = 1.5f;

						// 指数
						static const float Exponent = 3.0f;
					}

					// 下
					namespace Bottom
					{
						// 開始値
						static const float Start = 0.0f;

						// 終了値
						static const float End = 2.0f;

						// 指数
						static const float Exponent = 3.0f;
					}
				}
			}

			// 大きさ
			namespace Scale
			{
				// 予備動作
				namespace Anticipation
				{
					// 開始値
					static const YMath::Vector3 Start = {};

					// 終了値
					static const YMath::Vector3 End = { -0.5f,0.0f,-0.5f };

					// 指数
					static const float Exponent = 3.0f;
				}

				// 本番
				namespace Performance
				{
					// 上
					namespace Top
					{
						// 開始値
						static const YMath::Vector3 Start = {};

						// 終了値
						static const YMath::Vector3 End = { +0.5f,0.0f,+0.5f };

						// 指数
						static const float Exponent = 3.0f;
					}

					// 下
					namespace Bottom
					{
						// 開始値
						static const YMath::Vector3 Start = {};

						// 終了値
						static const YMath::Vector3 End = { +0.5f,0.0f,+0.5f };

						// 指数
						static const float Exponent = 3.0f;
					}
				}
			}
		}
	}

	// 足場
	namespace Platform
	{
		// 端位置係数
		static const float EdgePosFactor = 0.8f;
	}

	// 接続部
	namespace Junction
	{
		// 大きさの差
		static const YMath::Vector3 ScaleDifference = { 0.4f, 0.4f, 0.2f };

		// 立ちモーション
		namespace Idle
		{
			// フレーム
			static unsigned int Frame = 120;

			// 回転スピード
			namespace RotaSpeed
			{
				// 開始値
				static const float Start = 0.0f;

				// 終了値
				static const float End = +PI * 4.0f;

				// 指数
				static const float Exponent = 2.0f;
			}
		}

		// 接続
		namespace Connect
		{

			// フレーム
			static unsigned int Frame = 120;

			// 位置系数
			namespace PosFactor
			{
				// 開始値
				static const float Start = 0.0f;

				// 終了値
				static const float End = 2.0f;

				// 指数
				static const float Exponent = 3.0f;
			}

			// 回転系数
			namespace RotaFactor
			{
				// 開始値
				static const float Start = 0.0f;

				// 終了値
				static const float End = +PI / 4.0f;

				// 指数
				static const float Exponent = 3.0f;
			}

			// 回転スピード
			namespace RotaSpeed
			{
				// 開始値
				static const float Start = 0.0f;

				// 終了値
				static const float End = +PI * 8.0f;

				// 指数
				static const float Exponent = 3.0f;
			}

			// 大きさ
			namespace Scale
			{
				// 開始値
				static const YMath::Vector3 Start = {};

				// 終了値
				static const YMath::Vector3 End = { 0.4f,0.4f,0.4f };

				// 指数
				static const float Exponent = 3.0f;
			}

			// 向き合わせ
			namespace AlignDirection
			{
				// フレーム
				static unsigned int Frame = 20;

				// 指数
				static const float Exponent = 3.0f;
			}
		}
	}

	// レーザー
	namespace Laser
	{
		// ビームの高さ係数
		static const float BeamHeight = 0.25f;

		// 立ちモーション
		namespace Idle
		{
			// フレーム
			static const unsigned int Frame = 80;

			// ビーム回転
			namespace BeamRota
			{
				// 開始値
				static const float Start = 0.0f;

				// 終了値
				static const float End = +PI * 4.0f;

				// 指数
				static const float Exponent = 1.0f;
			}

			// ファンネル回転
			namespace FannelRota
			{
				// 開始値
				static const float Start = 0.0f;

				// 終了値
				static const float End = +PI * 2.0f;

				// 指数
				static const float Exponent = 1.0f;
			}
		}

		// 発射
		namespace Shoot
		{
			// フレーム
			static const unsigned int Frame = 60;

			// 高度
			namespace Height
			{
				// 開始値
				static const float Start = 0.0f;

				// 終了値
				static const float End = -0.4f;

				// 指数
				static const float Exponent = 3.0f;
			}

			// 位置係数
			namespace PosFactor
			{
				// 開始値
				static const float Start = 0.0f;
				
				// 終了値
				static const float End = 0.4f;

				// 指数
				static const float Exponent = 3.0f;
			}

			// 回転
			namespace Rota
			{
				// 開始値
				static const float Start = 0.0f;

				// 終了値
				static const float End = +PI * 4.0f;

				// 指数
				static const float Exponent = 3.0f;
			}

			// 大きさ
			namespace Scale
			{
				// 開始
				const float Start = -1.0f;

				// 修了
				const float End = -0.90f;

				// 指数
				static const float Exponent = 3.0f;
			}
		}
	}

	// 鍵
	namespace Key
	{
		// リングの高さ
		static const float RingHeight = +0.5f;

		// 立ちモーション
		namespace Idle
		{
			// フレーム
			static const unsigned int Frame = 60;

			// 高さ
			namespace Height
			{
				// 開始値
				static const float Start = 0.0f;

				// 終了値
				static const float End = +0.25f;

				// 指数
				static const float Exponent = 3.0f;
			}
		}
	}

	// スイッチ
	namespace Switch
	{
		// 台座位置
		static const float BaseHeight = -1.0f;
		
		// レバー位置
		static const float LeverHeight = -0.8f;

		// 回転スピード
		namespace RotaSpeed
		{
			// フレーム
			static const unsigned int Frame = 30;
			
			// 開始値
			static const float Start = 0.0f;

			// 終了値
			static const float End = -PI / 2.5f;

			// 指数
			static const float Exponent = 3.0f;
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
		
		// 縛る回転モーション
		namespace BindRota 
		{
			// フレーム
			const unsigned int Frame = 120;

			// 量 (内)
			namespace Inside
			{
				// 初期値
				const YMath::Vector3 Start = { -PI / 3.0f, 0.0f, -PI / 3.0f };
				
				// 最終値
				const YMath::Vector3 End   = { -PI / 3.0f, 0.0f, -PI / 3.0f - PI * 2.0f };
			}

			// 量 (外)
			namespace Outside
			{
				// 初期値
				const YMath::Vector3 Start = { +PI / 3.0f, 0.0f, +PI / 2.0f };
				
				// 最終値
				const YMath::Vector3 End   = { +PI / 3.0f, 0.0f, +PI / 2.0f + PI * 2.0f };
			}
			
			// 指数
			const float Exponent = 3.0f;
		}

		// ログインモーション
		namespace Login
		{
			// フレーム
			const unsigned int Frame = 10;
			
			// リレー虫
			namespace RelayBug
			{
				// 数
				const unsigned int Num = 24;

				// フレーム (初期位置 → 中継地点)
				const unsigned int StartToRelayFrame = 10;

				// フレーム (中継地点 → 終了地点)
				const unsigned int RelayToEndFrame = 20;

				// リレー範囲
				const YMath::Vector3 RelayRange = { 6.0f,6.0f,6.0f };


				// 最小回転
				const YMath::Vector3 MinRota = { -PI / 2.0f,-PI / 2.0f ,-PI / 2.0f };

				// 最大回転
				const YMath::Vector3 MaxRota = { +PI / 2.0f, +PI / 2.0f, +PI / 2.0f };


				// 最小スケール
				const float MinScale = 0.3f;

				// 最大スケール
				const float MaxScale = 0.5f;

				// 色
				const YMath::Vector3 Color = { 0.1f,0.9f,0.8f };

				// 位
				const float Place = 100.0f;
			}
		}

		// ハッキング回転モーション
		namespace HackRota
		{
			// フレーム
			const unsigned int Frame = 60;

			// 加速度 (内)
			const YMath::Vector3 InAcceleration  = { -PI / 1200.0f, 0.0f, -PI / 360.0f };

			// 加速度 (外)
			const YMath::Vector3 OutAcceleration = { +PI / 1200.0f, 0.0f, +PI / 360.0f };
		}

		// クリア回転モーション
		namespace ClearRota
		{
			// フレーム
			const unsigned int Frame = 30;

			// 指数
			const float Exponent = 3.0f;
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

	// タワー
	namespace Tower
	{
	}

	// 核
	namespace CoreColorConfig
	{
		// 色
		namespace Color
		{
			// グレー
			const YMath::Vector3 Gray	 = { 0.30f, 0.30f, 0.30f };

			// 赤
			const YMath::Vector3 Red	 = { 0.60f, 0.00f, 0.00f };

			// 緑
			const YMath::Vector3 Green	 = { 0.00f, 0.60f, 0.00f };

			// 青
			const YMath::Vector3 Blue	 = { 0.05f, 0.20f, 0.90f };
		}

		// アンビエント
		namespace Ambient
		{
			// 通常
			const YMath::Vector3 Normal = { 0.5f, 0.5f, 0.5f };

			// 青
			const YMath::Vector3 Blue = { 0.7f, 0.7f, 0.8f };
		}


		// 明滅
		namespace Flickering
		{
			// フレーム
			const unsigned int Frame = 120;

			// 初期値
			const float Start = 1.0f;

			// 最終値
			const float End = 0.75f;

			// 指数
			const float Exponent = 3.0f;
		}

		// 統一
		namespace Unify
		{
			// フレーム
			const unsigned int Frame = 30;

			// 指数
			const float Exponent = 3.0f;
		}
	}

	// 背景
	namespace Background
	{
		// アンビエント
		const YMath::Vector3 Ambient = { 0.3f,0.2f,0.2f };
		
		// クリア時用アンビエント
		const YMath::Vector3 ClearAmbient = { 0.5f,0.5f,0.7f };

		// 光
		namespace Light
		{
			// 環境光
			const YMath::Vector3 Ambient = { 1.0f,1.0f,1.0f };

			// 平行光源
			namespace Direction
			{ 
				// 色
				const YMath::Vector3 Color = { 1.0f,0.0f,0.0f };
				
				// クリア時の色
				const YMath::Vector3 ClearColor = { 0.0f,0.0f,1.0f };
				
				// 向き
				const YMath::Vector3 Dire = { -0.3f,-1.0f,-0.3f };
			}
		}

		// 統一
		namespace Unify
		{
			// フレーム
			const unsigned int Frame = 30;

			// 指数
			const float Exponent = 3.0f;
		}

		// タワー
		namespace Towers
		{
			// 数
			const unsigned int Num = 5;

			// 位置
			const YMath::Vector3 Poss[Num] =
			{
				YMath::Vector3(- 200.0f, - 200.0f, + 225.0f),
				YMath::Vector3(-  35.0f, - 200.0f, + 225.0f),

				YMath::Vector3(+ 400.0f, - 300.0f, + 450.0f),

				YMath::Vector3(- 230.0f, - 350.0f, + 600.0f),
				YMath::Vector3(+ 250.0f, - 350.0f, + 600.0f),
			};

			// 回転
			const YMath::Vector3 Rotas[Num] =
			{
				YMath::Vector3(0.0f, - PI * 1.4f, 0.0f),
				YMath::Vector3(0.0f, + PI * 0.4f, 0.0f),

				YMath::Vector3(0.0f, - PI * 1.2f, 0.0f),

				YMath::Vector3(0.0f, - PI * 0.6f, 0.0f),
				YMath::Vector3(0.0f, - PI * 1.6f, 0.0f),
			};

			// 大きさ
			const YMath::Vector3 Scales[Num] =
			{
				YMath::Vector3(  32.0f,  64.0f,  32.0f),
				YMath::Vector3(  32.0f,  48.0f,  32.0f),

				YMath::Vector3(  64.0f, 128.0f,  64.0f),

				YMath::Vector3(  48.0f,  64.0f,  48.0f),
				YMath::Vector3(  48.0f,  80.0f,  48.0f),
			};

			// 状態番号 (0 : 通常, 1 : 赤)
			const unsigned int ModeIdx[Num] =
			{
				0,
				0,

				0,

				0,
				1,
			};
		}

		// 天球サイズ
		const float SkydomeSize = 800.0f;

		// 泡グリッド
		namespace BubbleGrid
		{
			// 間隔
			const unsigned int IntervalFrame = 240;
			

			// 生存時間
			const unsigned int AliveFrame = 720;
			

			// 最小発生数
			const unsigned int MinNum = 4;
			
			// 最大発生数
			const unsigned int MaxNum = 6;


			// 中心
			const YMath::Vector3 Center = { 0.0f, -50.0f, +150.0f };

			// 範囲
			const YMath::Vector3 Range = { 150.0f, 50.0f, 10.0f };

			
			// 最小スケールサイズ
			const float MinScaleSize = 1.5f;
			
			// 最大スケールサイズ
			const float MaxScaleSize = 3.0f;


			// 最小移動スピード
			const YMath::Vector3 MinMoveSpeed = { +0.0f, +0.1f, +0.0f };

			// 最大移動スピード
			const YMath::Vector3 MaxMoveSpeed = { +0.0f, +0.3f, +0.0f };


			// 最小回転スピード
			const YMath::Vector3 MinRotaSpeed = { -0.01f, -0.01f, -0.01f };

			// 最大回転スピード
			const YMath::Vector3 MaxRotaSpeed = { +0.01f, +0.01f, +0.01f };


			// 色
			const YMath::Vector3 Color = { 0.02f,0.0f,0.0f };

			// 位
			const float Place = 100.0f;
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
			const YMath::Vector3 Exit  = { WinSize.x_ - 200.0f,WinSize.y_ - 120.0f,0.0f };

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
			const float CenterHeight = WinSize.y_ / 2.0f + 8.0f;
			
			// 全体の高さ
			const float TotalHeight = 448.0f;
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


		// タワー
		namespace Tower
		{
			// マテリアル
			namespace Material
			{
				// アンビエント
				const YMath::Vector3 Ambient = { 0.9f,0.6f,0.6f };
			}

			// 光
			namespace Light
			{
				// 環境光
				const YMath::Vector3 Ambient = { 1.0f,1.0f,1.0f };

				// 平行光源
				namespace Direction
				{
					// 色
					const YMath::Vector3 Color = { 0.3f,0.0f,0.1f };

					// 向き
					const YMath::Vector3 Dire = { +0.1f,-0.4f,-0.3f };
				}
			}
		}

		// 地球
		namespace Earth
		{
			// 色
			const YMath::Vector4 Color = { 0.02f,0.0f,0.02f,1.0f };

			// マテリアル
			namespace Material
			{
				// アンビエント
				const YMath::Vector3 Ambient = { 1.0f,0.3f,0.5f };
			}

			// 光
			namespace Light
			{
				// 環境光
				const YMath::Vector3 Ambient = { 1.0f,1.0f,1.0f };

				// 平行光源
				namespace Direction
				{
					// 色
					const YMath::Vector3 Color = { 0.8f,0.0f,0.4f };

					// 向き
					const YMath::Vector3 Dire = { 0.0f,+1.0f,0.0f };
				}
			}
		}

		// 泡グリッド
		namespace BubbleGrid
		{
			// 間隔
			const unsigned int IntervalFrame = 240;
			

			// 位
			const float Place = 100.0f;
			

			// 生存時間
			const unsigned int AliveFrame = 720;
			

			// 最小発生数
			const unsigned int MinNum = 4;
			
			// 最大発生数
			const unsigned int MaxNum = 6;


			// 中心
			const YMath::Vector3 Center = { -10.0f, 0.0f, +150.0f };

			// 範囲
			const YMath::Vector3 Range = { 100.0f, 20.0f, 50.0f };

			
			// 最小スケールサイズ
			const float MinScaleSize = 1.5f;
			
			// 最大スケールサイズ
			const float MaxScaleSize = 3.0f;


			// 最小移動スピード
			const YMath::Vector3 MinMoveSpeed = { +0.0f, +0.1f, +0.0f };

			// 最大移動スピード
			const YMath::Vector3 MaxMoveSpeed = { +0.0f, +0.3f, +0.0f };


			// 最小回転スピード
			const YMath::Vector3 MinRotaSpeed = { -0.01f, -0.01f, -0.01f };

			// 最大回転スピード
			const YMath::Vector3 MaxRotaSpeed = { +0.01f, +0.01f, +0.01f };


			// 色
			const YMath::Vector3 Color = { 0.02f,0.0f,0.0f };
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
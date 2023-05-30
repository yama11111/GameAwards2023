#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "StageConfig.h"
#include <vector>

// オブジェクト設定
namespace LevelData
{
	// プレイヤー
	namespace Player
	{
		// 加速力 (1F毎に加算)
		static const float Acceleration = 0.5f;
		
		// 摩擦力 (1F毎に減算)
		static const float Friction = 0.1f;
		
		// ジャンプ力
		static const float JumpPower = 1.0f;

		// 重力
		static const float Gravity = 0.1f;
		//static const float Gravity = 0.0f;

		// 最大重力
		static const float MaxGravity = 1.5f;
		
		// 最大速度
		static const YMath::Vector2 MaxSpeed = { 0.5f, 3.0f };

		// アタリ判定用半径
		static const YMath::Vector2 CollRadSize = { 1.0f, 1.0f };

		// 初期化ステータス
		struct InitStatus
		{
			// 看板インデックス
			size_t signIndex_;

			// 座標
			YMath::Vector2 pos_;
		};
		
		// 初期化ステータス
		static std::array<InitStatus, StageConfig::StageNum_> InitStatuses =
		{
			// 看板、座標
			{
				{0, { 4.0f,-4.0f }},  //  1
				{0, { 6.0f,-4.0f }},  //  2
				{1, { 4.0f,-4.0f }},  //  3
				{0, { 10.0f,-13.0f }},  //  4
				{0, { +5.0f,-4.0f }},  //  5
				{2, { +16.0f,-10.0f }},  //  6
				{1, { +4.0f,-17.0f }},  //  7
				{1, { 5.0f,-5.0f }},  //  8
				//{0, { 0.0f,0.0f }},  //  9
				//{0, { 0.0f,0.0f }},  // 10
			}
		};
	}

	// ブロック
	namespace Block
	{
		// アタリ判定用半径
		static const YMath::Vector2 CollRadSize = { 0.9f, 0.9f };

		// 初期化ステータス
		struct InitStatus
		{
			// 看板インデックス
			size_t signIndex_;

			// 座標
			YMath::Vector2 pos_;
		};

		// 初期化ステータス
		static std::array<std::vector<InitStatus>, StageConfig::StageNum_> InitStatuses =
		{
			// 看板、座標
			{
				//  1
				{
				}, 
				//  2
				{
				}, 
				//  3
				{
					{0, { +9.0f,-7.0f }},
					{1, { +9.0f,-13.0f }},
				},
				//  4
				{
					{2, { +15.0f,-6.0f }},
				},
				//  5
				{
					{0, {+15.0f,-7.0f}},
					{1, {+35.0f,-7.0f}},
				},
				//  6
				{
					{1,{+9.0f,-15.0f}},
					{1,{+15.0f,-15.0f}},
					{1,{+15.0f,-5.0f}},
				},
				//  7
				{
					{0,{+17.0f,-4.0f}},
					{1,{+23.0f,-18.0f}},
				},
				//  8
				{
					{2,{+15.0f,-6.0f}},
				},
				////  9
				//{
				//},
				////  10
				//{
				//},
			}, 
		};
	}

	// ばね
	namespace Spring
	{
		// アタリ判定用半径
		static const YMath::Vector2 CollRadSize = { 1.0f, 0.5f };

		// 初期化ステータス
		struct InitStatus
		{
			// 看板インデックス
			size_t signIndex_;

			// 座標
			YMath::Vector2 pos_;

			// ジャンプ力
			float jumpPowar_;
		};

		// 初期化ステータス
		static std::array<std::vector<InitStatus>, StageConfig::StageNum_> InitStatuses =
		{
			// 看板、座標
			{
				//  1
				{
				},
				//  2
				{
				},
				//  3
				{
					{2, { +9.0f,-23.0f }, 1.5f},
					{2, { +11.0f,-23.0f }, 1.5f},
				},
				//  4
				{
				},
				//  5
				{
				},
				//  6
				{
					{0,{ +11.0f,-27.0f },2.0f},
					{0,{ +13.0f,-27.0f },2.0f},
					{1,{ +3.0f,-21.0f },2.0f},
					{1,{ +5.0f,-21.0f },2.0f},
					{2,{ +9.0f,-17.0f },2.0f},
					{2,{ +11.0f,-17.0f },2.0f},
					{2,{ +13.0f,-17.0f },2.0f},
				},
				//  7
				{
					{1,{+ 9.0f,-23.0f},1.5f},
					{1,{+11.0f,-23.0f},1.5f},
					{1,{+17.0f,-23.0f},1.5f},
					{1,{+19.0f,-23.0f},1.5f},
				},
				//  8
				{
					{3,{ 13.0f,-16.0f },1.5f},
					{3,{ 15.0f,-16.0f },1.5f},
				},
				////  9
				//{
				//},
				////  10
				//{
				//},
			},
		};
	}

	// 足場
	namespace Platform
	{
		// 分厚さ
		static const float Thickness_ = 0.5f;

		// 初期化ステータス
		struct InitStatus
		{
			// 看板インデックス
			size_t signIndex_;

			// 座標
			YMath::Vector2 pos_;

			// 長さ
			float length_;

			// スイッチ番号
			int switchIdx_ = -1;
		};

		// 初期化ステータス
		static std::array<std::vector<InitStatus>, StageConfig::StageNum_> InitStatuses =
		{
			// 看板、座標
			{
				//  1
				{
					{1, { +13.0f,-8.5f }, 5.0f},
					{1, { +14.0f,-12.5f }, 4.0f},
					{2, { +8.0f,-8.5f }, 7.0f},
					{2, { +11.0f,-12.0f }, 10.0f},
				},
				//  2
				{
					//{2, { +13.0f,-8.5f }, 4.0f},
					{2, { +13.0f,-8.25f }, 12.0f},
				},
				//  3
				{
					{2, { +11.0f,-12.25f }, 4.0f},
				},
				//  4
				{
					{0, { +4.0f,-8.5f }, 2.0f},
					{0, { +4.0f,-12.5f }, 2.0f},
					{1, { +10.0f,-8.5f }, 3.0f},
					{1, { +27.0f,-12.5f }, 8.0f},
					{1, { +27.0f,-16.5f }, 8.0f},
					{1, { +18.0f,-22.5f }, 17.0f},
				},
				//  5
				{
					{0, { +7.0f,-16.5f }, 5.0f},
					{0, { +7.0f,-20.5f }, 5.0f},
					{1, { +11.0f,-10.0f }, 2.0f},
					{1, { +22.0f,-10.0f }, 4.0f},
				},
				//  6
				{
					{0, { +7.5f,-8.5f }, 5.0f},
					{0, { +27.5f,-8.5f }, 5.0f},
					{0, { +7.5f,-12.5f }, 5.0f},
					{0, { +7.5f,-16.5f }, 5.0f},
					{0, { +22.5f,-24.25f }, 3.0f},
					{1, { +7.0f,-8.5f  }, 6.0f},
					{2, { +11.0f,-8.0f  }, 2.0f},
				},
				//  7
				{
					{1,{+10.0f,-8.5f},3.0f},
					{1,{+18.0f,-12.5f},3.0f},
				},
				//  8
				{
					{2,{+21.0f,-8.25f},3.0f},
					{2,{+19.0f,-12.25f},5.5f},
				},
				////  9
				//{
				//},
				////  10
				//{
				//},
			},
		};
	}

	// レーザー
	namespace Laser
	{
		// 伸びるスピード
		static const float GrowSpeed = 0.4f;

		// 初期化ステータス
		struct InitStatus
		{
			// 看板インデックス
			size_t signIndex_;

			// 座標
			YMath::Vector2 pos_;

			// 向き (+ : 右と上, - :左と下)
			YMath::Vector2 direction_;

			// 長さ
			float length_;

			// スイッチ番号
			int switchIdx_ = -1;
		};

		// 初期化ステータス
		static std::array<std::vector<InitStatus>, StageConfig::StageNum_> InitStatuses =
		{
			// 看板、座標、向き
			{
				//  1
				{
				},
				//  2
				{
				},
				//  3
				{
				},
				//  4
				{
					{0, { +19.0f,-3.0f }, { 0.0f,-1.0f }, 12.0f,0},
					{1, { +3.0f,-21.0f }, { +1.0f,0.0f }, 30.0f},
				},
				//  5
				{
					{1, { +35.0f,-15.0f }, { -1.0f,0.0f }, 32.0f},
					{1, { +37.0f,-23.0f }, { -1.0f,0.0f }, 34.0f},
				},
				//  6
				{
					{0, { +5.0f,-11.0f }, { +1.0f,0.0f }, 28.0f},
					{0, { +5.0f,-15.0f }, { +1.0f,0.0f }, 28.0f},
				},
				//  7
				{
					{1,{+25.0f,-11.0f},{-1.0f,0.0f},22.0f},
				},
				////  8
				//{
				//},
				////  9
				//{
				//},
				////  10
				//{
				//},
			},
		};
	}

	// スイッチ
	namespace Switch
	{
		// 初期化ステータス
		struct InitStatus
		{
			// 看板インデックス
			size_t signIndex_;

			// 座標
			YMath::Vector2 pos_;

			// 動作しているか
			bool isAct_;
		};

		// 初期化ステータス
		static std::array<std::vector<InitStatus>, StageConfig::StageNum_> InitStatuses =
		{
			// 看板、座標、動作しているか
			{
				//  1
				{
				},
				//  2
				{
				},
				//  3
				{
				},
				//  4
				{
					{0, { +11.0f,-7.0f }, true},
				},
				//  5
				{
				},
				//  6
				{
				},
				//  7
				{
				},
				//  8
				{
				},
				////  9
				//{
				//},
				////  10
				//{
				//},
			},
		};
	}

	// 鍵
	namespace Key
	{
		// 初期化ステータス
		struct InitStatus
		{
			// 看板インデックス
			size_t signIndex_;

			// 座標
			YMath::Vector2 pos_;
		};

		// 初期化ステータス
		static std::array<std::vector<InitStatus>, StageConfig::StageNum_> InitStatuses =
		{
			// 看板、座標
			{
				//  1
				{
					//{2, { +19.0f,-15.0f }}
				},
				//  2
				{
					{1, { +15.0f,-6.0f }},
				},
				//  3
				{
				},
				//  4
				{
				},
				//  5
				{
					{1, { +22.0f,-7.0f }},
				},
				//  6
				{
				},
				//  7
				{
					{1,{+24.0f,-6.0f}},
				},
				//  8
				{
					{0,{5.0f,-5.0f}},
				},
				////  9
				//{
				//},
				//// 10
				//{
				//},
			}
		};
	}

	// ゴール
	namespace Goal
	{
		// 初期化ステータス
		struct InitStatus
		{
			// 看板インデックス
			size_t signIndex_;

			// 座標
			YMath::Vector2 pos_;
		};

		// 初期化ステータス
		static std::array<InitStatus, StageConfig::StageNum_> InitStatuses =
		{
			// 看板、座標、鍵フラグ
			{
				{2, { +17.0f,-14.0f }},	 //  1
				{1, { +10.0f, -6.0f }},  //  2
				{2, { +22.0f, -5.0f }},  //  3
				{1, { +30.0f,-26.0f }},  //  4
				{0, { +22.0f,-14.0f }},  //  5
				{0, { +32.0f,-26.0f }},  //  6
				{0, {  +4.0f,-15.0f }},  //  7
				{3,  { 27.0f,-13.0f }},  //  8
				//{0, { 0.0f,0.0f }, false},  //  9
				//{0, { 0.0f,0.0f }, false},  // 10
			}
		};
	}
}

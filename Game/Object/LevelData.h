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
				{0, { 0.0f,0.0f }},  //  2
				{0, { 0.0f,0.0f }},  //  3
				{0, { 0.0f,0.0f }},  //  4
				{0, { 0.0f,0.0f }},  //  5
				{0, { 0.0f,0.0f }},  //  6
				{0, { 0.0f,0.0f }},  //  7
				{0, { 0.0f,0.0f }},  //  8
				{0, { 0.0f,0.0f }},  //  9
				{0, { 0.0f,0.0f }},  // 10
			}
		};
	}

	// ブロック
	namespace Block
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
					{0, { 4.0f,0.0f }},
				}, 
				//  2
				{ 
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
				}, 
				//  3
				{
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
				},
				//  4
				{
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
				},
				//  5
				{
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
				},
				//  6
				{
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
				},
				//  7
				{
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
				},
				//  8
				{
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
				},
				//  9
				{
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
				},
				//  10
				{
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
				},
			}, 
		};
	}

	// ばね
	namespace Spring
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
					{0, { -10.0f,0.0f }},
				},
				//  2
				{
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
				},
				//  3
				{
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
				},
				//  4
				{
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
				},
				//  5
				{
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
				},
				//  6
				{
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
				},
				//  7
				{
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
				},
				//  8
				{
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
				},
				//  9
				{
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
				},
				//  10
				{
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
					{0, { 0.0f,0.0f }},
				},
			},
		};
	}

	// 足場
	namespace Platform
	{
		// 初期化ステータス
		struct InitStatus
		{
			// 看板インデックス
			size_t signIndex_;

			// 座標
			YMath::Vector2 pos_;

			// 長さ
			float length_;
		};

		// 初期化ステータス
		static std::array<std::vector<InitStatus>, StageConfig::StageNum_> InitStatuses =
		{
			// 看板、座標
			{
				//  1
				{
					{0, { -5.0f,5.0f }, 4.0f},
				},
				//  2
				{
					{0, { 0.0f,0.0f }, 0.0f},
					{0, { 0.0f,0.0f }, 0.0f},
					{0, { 0.0f,0.0f }, 0.0f},
				},
				//  3
				{
					{0, { 0.0f,0.0f }, 0.0f},
					{0, { 0.0f,0.0f }, 0.0f},
					{0, { 0.0f,0.0f }, 0.0f},
				},
				//  4
				{
					{0, { 0.0f,0.0f }, 0.0f},
					{0, { 0.0f,0.0f }, 0.0f},
					{0, { 0.0f,0.0f }, 0.0f},
				},
				//  5
				{
					{0, { 0.0f,0.0f }, 0.0f},
					{0, { 0.0f,0.0f }, 0.0f},
					{0, { 0.0f,0.0f }, 0.0f},
				},
				//  6
				{
					{0, { 0.0f,0.0f }, 0.0f},
					{0, { 0.0f,0.0f }, 0.0f},
					{0, { 0.0f,0.0f }, 0.0f},
				},
				//  7
				{
					{0, { 0.0f,0.0f }, 0.0f},
					{0, { 0.0f,0.0f }, 0.0f},
					{0, { 0.0f,0.0f }, 0.0f},
				},
				//  8
				{
					{0, { 0.0f,0.0f }, 0.0f},
					{0, { 0.0f,0.0f }, 0.0f},
					{0, { 0.0f,0.0f }, 0.0f},
				},
				//  9
				{
					{0, { 0.0f,0.0f }, 0.0f},
					{0, { 0.0f,0.0f }, 0.0f},
					{0, { 0.0f,0.0f }, 0.0f},
				},
				//  10
				{
					{0, { 0.0f,0.0f }, 0.0f},
					{0, { 0.0f,0.0f }, 0.0f},
					{0, { 0.0f,0.0f }, 0.0f},
				},
			},
		};
	}

	// レーザー
	namespace Laser
	{
		// 初期化ステータス
		struct InitStatus
		{
			// 看板インデックス
			size_t signIndex_;

			// 座標
			YMath::Vector2 pos_;

			// 向き (+ : 右と上, - :左と下)
			YMath::Vector2 direction_;
		};

		// 初期化ステータス
		static std::array<std::vector<InitStatus>, StageConfig::StageNum_> InitStatuses =
		{
			// 看板、座標、向き
			{
				//  1
				{
					{0, { +10.0f,0.0f }, { -1.0f,0.0f }},
				},
				//  2
				{
					{0, { 0.0f,0.0f }, { +1.0f,+0.0f }},
					{0, { 0.0f,0.0f }, { +1.0f,+0.0f }},
					{0, { 0.0f,0.0f }, { +1.0f,+0.0f }},
				},
				//  3
				{
					{0, { 0.0f,0.0f }, { +1.0f,+0.0f }},
					{0, { 0.0f,0.0f }, { +1.0f,+0.0f }},
					{0, { 0.0f,0.0f }, { +1.0f,+0.0f }},
				},
				//  4
				{
					{0, { 0.0f,0.0f }, { +1.0f,+0.0f }},
					{0, { 0.0f,0.0f }, { +1.0f,+0.0f }},
					{0, { 0.0f,0.0f }, { +1.0f,+0.0f }},
				},
				//  5
				{
					{0, { 0.0f,0.0f }, { +1.0f,+0.0f }},
					{0, { 0.0f,0.0f }, { +1.0f,+0.0f }},
					{0, { 0.0f,0.0f }, { +1.0f,+0.0f }},
				},
				//  6
				{
					{0, { 0.0f,0.0f }, { +1.0f,+0.0f }},
					{0, { 0.0f,0.0f }, { +1.0f,+0.0f }},
					{0, { 0.0f,0.0f }, { +1.0f,+0.0f }},
				},
				//  7
				{
					{0, { 0.0f,0.0f }, { +1.0f,+0.0f }},
					{0, { 0.0f,0.0f }, { +1.0f,+0.0f }},
					{0, { 0.0f,0.0f }, { +1.0f,+0.0f }},
				},
				//  8
				{
					{0, { 0.0f,0.0f }, { +1.0f,+0.0f }},
					{0, { 0.0f,0.0f }, { +1.0f,+0.0f }},
					{0, { 0.0f,0.0f }, { +1.0f,+0.0f }},
				},
				//  9
				{
					{0, { 0.0f,0.0f }, { +1.0f,+0.0f }},
					{0, { 0.0f,0.0f }, { +1.0f,+0.0f }},
					{0, { 0.0f,0.0f }, { +1.0f,+0.0f }},
				},
				//  10
				{
					{0, { 0.0f,0.0f }, { +1.0f,+0.0f }},
					{0, { 0.0f,0.0f }, { +1.0f,+0.0f }},
					{0, { 0.0f,0.0f }, { +1.0f,+0.0f }},
				},
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
					{0, { -4.0f,0.0f }, true},
				},
				//  2
				{
					{0, { 0.0f,0.0f }, false},
					{0, { 0.0f,0.0f }, false},
					{0, { 0.0f,0.0f }, false},
				},
				//  3
				{
					{0, { 0.0f,0.0f }, false},
					{0, { 0.0f,0.0f }, false},
					{0, { 0.0f,0.0f }, false},
				},
				//  4
				{
					{0, { 0.0f,0.0f }, false},
					{0, { 0.0f,0.0f }, false},
					{0, { 0.0f,0.0f }, false},
				},
				//  5
				{
					{0, { 0.0f,0.0f }, false},
					{0, { 0.0f,0.0f }, false},
					{0, { 0.0f,0.0f }, false},
				},
				//  6
				{
					{0, { 0.0f,0.0f }, false},
					{0, { 0.0f,0.0f }, false},
					{0, { 0.0f,0.0f }, false},
				},
				//  7
				{
					{0, { 0.0f,0.0f }, false},
					{0, { 0.0f,0.0f }, false},
					{0, { 0.0f,0.0f }, false},
				},
				//  8
				{
					{0, { 0.0f,0.0f }, false},
					{0, { 0.0f,0.0f }, false},
					{0, { 0.0f,0.0f }, false},
				},
				//  9
				{
					{0, { 0.0f,0.0f }, false},
					{0, { 0.0f,0.0f }, false},
					{0, { 0.0f,0.0f }, false},
				},
				//  10
				{
					{0, { 0.0f,0.0f }, false},
					{0, { 0.0f,0.0f }, false},
					{0, { 0.0f,0.0f }, false},
				},
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
					{0, { -3.0f,0.0f }} ,
				},
				//  2
				{
					{0, { 0.0f,0.0f }},
				},
				//  3
				{
					{0, { 0.0f,0.0f }},
				},
				//  4
				{
					{0, { 0.0f,0.0f }}, 
				},
				//  5
				{
					{0, { 0.0f,0.0f }},
				},
				//  6
				{
					{0, { 0.0f,0.0f }},
				},
				//  7
				{
					{0, { 0.0f,0.0f }},
				},
				//  8
				{
					{0, { 0.0f,0.0f }},
				},
				//  9
				{
					{0, { 0.0f,0.0f }},
				},
				// 10
				{
					{0, { 0.0f,0.0f }},
				},
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

			// 鍵がかかっているか
			bool isRock_;
		};

		// 初期化ステータス
		static std::array<InitStatus, StageConfig::StageNum_> InitStatuses =
		{
			// 看板、座標、鍵フラグ
			{
				{0, { 5.0f,5.0f }, false},  //  1
				{0, { 0.0f,0.0f }, false},  //  2
				{0, { 0.0f,0.0f }, false},  //  3
				{0, { 0.0f,0.0f }, false},  //  4
				{0, { 0.0f,0.0f }, false},  //  5
				{0, { 0.0f,0.0f }, false},  //  6
				{0, { 0.0f,0.0f }, false},  //  7
				{0, { 0.0f,0.0f }, false},  //  8
				{0, { 0.0f,0.0f }, false},  //  9
				{0, { 0.0f,0.0f }, false},  // 10
			}
		};
	}
}

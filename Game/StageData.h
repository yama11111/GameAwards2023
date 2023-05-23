#pragma once
#include "Vector2.h"
#include "StageConfig.h"
#include <vector>

// -------------------------------------- //
// 0 = 何もなし
// 1 = ブロック
// 2 = ワープ 1
// 3 = ワープ 2
// -------------------------------------- //

namespace StageData
{
	// 看板
	struct SignDataSet
	{
		// 基準点 (左上)
		YMath::Vector3 leftTop_;

		// 番号
		std::vector<std::vector<int>> numbers;
	};

	static const std::array<std::vector<SignDataSet>, StageConfig::StageNum_> Datas =
	{
		{
			// ----- ステージ 1 ----- //
			{
				// 看板 1
				{
					// 左上
					{ -20.0f,0.0f,0.0f },
					// 番号
					{
						{ 1,1,1,1,1,1,1,1,1,1,1 },
						{ 1,0,0,0,0,0,0,0,0,0,1 },
						{ 1,0,0,0,0,0,0,0,0,0,1 },
						{ 1,0,0,0,0,0,0,0,0,0,1 },
						{ 1,0,0,0,0,0,0,0,0,0,1 },
						{ 1,0,0,0,0,0,0,0,0,2,1 },
						{ 1,0,0,0,0,0,1,1,1,1,1 },
						{ 1,0,0,0,1,1,1,1,1,1,1 },
						{ 1,1,1,1,1,1,1,1,1,1,1 },
					}
				},
				
				// 看板 2
				{
					// 左上
					{ +20.0f,0.0f,0.0f },
					// 番号
					{
						{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
						{ 1,0,0,0,0,0,0,0,0,0,0,0,0,1 },
						{ 1,0,0,0,0,0,0,0,0,0,0,0,0,1 },
						{ 1,0,0,0,0,0,0,0,0,0,0,0,0,1 },
						{ 1,1,1,1,1,0,0,0,0,0,0,0,0,1 },
						{ 1,0,0,0,0,0,0,0,0,0,0,0,0,1 },
						{ 1,0,0,0,0,0,0,0,0,0,0,0,0,1 },
						{ 1,2,0,0,0,0,0,0,0,0,0,0,3,1 },
						{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
					}
				},

				// 看板 3
				{
					// 左上
					{ +20.0f,-30.0f,0.0f },
					// 番号
					{
						{ 1,1,1,1,1,1,1,1,1,1,1 },
						{ 1,0,0,0,0,0,0,0,0,3,1 },
						{ 1,0,0,0,0,0,0,0,0,0,1 },
						{ 1,0,0,0,0,0,0,0,0,0,1 },
						{ 1,0,0,0,0,0,0,1,1,1,1 },
						{ 1,0,0,0,0,0,0,0,0,0,1 },
						{ 1,0,0,0,0,0,0,0,0,0,1 },
						{ 1,0,0,0,0,0,0,0,0,0,1 },
						{ 1,0,0,0,0,0,0,0,0,0,1 },
						{ 1,1,1,1,1,1,1,1,1,1,1 },
					}
				},
			},

			// ----- ステージ 2 ----- //
			{
				// 看板 1
				{
					// 左上
					{ -20.0f,0.0f,0.0f },
					// 番号
					{
						{ 1,1,1,1,1,1,1,1,1,1,1 },
						{ 1,0,0,0,0,0,0,0,0,0,1 },
						{ 1,0,0,0,0,0,0,0,0,0,1 },
						{ 1,2,0,0,0,0,0,0,0,2,1 },
						{ 1,1,1,1,1,1,1,1,1,1,1 },
						{ 1,0,0,0,0,0,0,0,0,0,1 },
						{ 1,0,0,0,0,0,0,0,0,0,1 },
						{ 1,2,0,0,0,0,0,0,0,0,1 },
						{ 1,1,1,1,1,1,1,1,1,1,1 },
					}
				},
				
				// 看板 2
				{
					// 左上
					{ -20.0f,-30.0f,0.0f },
					// 番号
					{
						{ 1,1,1,1,1,1,1,1,1,1,1,1,1 },
						{ 1,0,0,0,0,0,1,0,0,0,0,0,1 },
						{ 1,0,0,0,0,0,1,0,0,0,0,0,1 },
						{ 1,0,0,0,0,0,1,0,0,0,0,2,1 },
						{ 1,1,1,1,1,1,1,1,1,1,1,1,1 },
					}
				},

				// 看板 3
				{
					// 左上
					{ +20.0f,0.0f,0.0f },
					// 番号
					{
						{ 1,1,1,1,1,1,1,1,1,1,1,1,1 },
						{ 1,0,0,0,0,0,0,0,0,0,0,0,1 },
						{ 1,0,0,0,0,0,0,0,0,0,0,0,1 },
						{ 1,2,0,0,0,0,0,0,0,0,0,2,1 },
						{ 1,1,1,1,1,0,0,0,1,1,1,1,1 },
						{ 1,0,0,0,0,0,0,0,0,0,0,0,1 },
						{ 1,0,0,0,0,0,0,0,0,0,0,0,1 },
						{ 1,0,0,0,0,0,0,0,0,0,0,2,1 },
						{ 1,1,1,1,1,1,1,1,1,1,1,1,1 },
					}
				},
			},

			// ----- ステージ 3 ----- //
			{
			},

			// ----- ステージ 4 ----- //
			{
			},

			// ----- ステージ 5 ----- //
			{
			},
			
			// ----- ステージ 6 ----- //
			{
			},
			
			// ----- ステージ 7 ----- //
			{
			},

			// ----- ステージ 8 ----- //
			{
			},

			// ----- ステージ 9 ----- //
			{
			},

			// ----- ステージ 10 ----- //
			{
			},
		}
	};
}
#pragma once
#include "Def.h"

namespace HUDConfig
{
	// 操作
	namespace Operation
	{
		// ステージセレクト
		namespace Title
		{
			// キー
			namespace Key
			{
				// 大きさ
				const YMath::Vector3 Scale = { 1.0f,1.0f,0.0f };

				// ----- 位置 ----- //

				// WASD
				const YMath::Vector3 WASD = { +96.0f, WinSize.y_ - 48.0f, 0.0f };
				// SPACE
				const YMath::Vector3 Space = { +192.0f, WinSize.y_ - 32.0f, 0.0f };
				// TAB
				const YMath::Vector3 Esc = { -100.0f, -100.0f, 0.0f };
			}

			// パッド
			namespace Pad
			{
				// 大きさ
				const YMath::Vector3 Scale = { 2.0f,2.0f,0.0f };

				// ----- 位置 ----- //
			}
		}

		// ステージセレクト
		namespace Select
		{
			// キー
			namespace Key
			{
				// 大きさ
				const YMath::Vector3 Scale = { 1.0f,1.0f,0.0f };

				// ----- 位置 ----- //

				// WASD
				const YMath::Vector3 WASD = { +96.0f, WinSize.y_ - 48.0f, 0.0f };
				// SPACE
				const YMath::Vector3 Space = { +192.0f, WinSize.y_ - 32.0f, 0.0f };
				// TAB
				const YMath::Vector3 Esc = { -100.0f, -100.0f, 0.0f };
			}

			// パッド
			namespace Pad
			{
				// 大きさ
				const YMath::Vector3 Scale = { 2.0f,2.0f,0.0f };

				// ----- 位置 ----- //
			}
		}

		// ゲーム
		namespace Play
		{
			// キー
			namespace Key
			{
				// 大きさ
				const YMath::Vector3 Scale = { 1.5f,1.5f,0.0f };

				// ----- 位置 ----- //

				// WASD
				const YMath::Vector3 WASD = { +96.0f, WinSize.y_ - 160.0f, 0.0f };
				// SPACE
				const YMath::Vector3 Space = { +192.0f, WinSize.y_ - 64.0f, 0.0f };
				// TAB
				const YMath::Vector3 Esc = { WinSize.x_ - 96.0f, +64.0f, 0.0f };
			}

			// パッド
			namespace Pad
			{
				// 大きさ
				const YMath::Vector3 Scale = { 2.0f,2.0f,0.0f };

				// ----- 位置 ----- //
			}
		}
	}

	// 操縦
	namespace Pilot
	{
		// 大きさ
		const YMath::Vector3 Scale = { 1.0f,1.0f,0.0f };

		// ----- 位置 ----- //

		// player
		const YMath::Vector3 Player = { +384.0f, WinSize.y_ - 80.0f, 0.0f };
		// filter
		const YMath::Vector3 Filter = { +384.0f, WinSize.y_ - 48.0f, 0.0f };
		
		// ----- 色 ----- //

		// 操縦中
		const YMath::Vector4 OnColor  = { 0.8f,0.8f,0.8f,1.0f };
		// 操縦していない
		const YMath::Vector4 OffColor = { 0.3f,0.3f,0.3f,0.5f };
	}

	// ポーズ
	namespace Pause
	{
		// 文字
		namespace Font
		{
			// 大きさ
			const YMath::Vector3 Scale = { 1.0f,1.0f,0.0f };

			// ----- 位置 ----- //

			// pause
			const YMath::Vector3 Pause	 = { WinSize.x_ / 2.0f, +128.0f, 0.0f };
			// resume
			const YMath::Vector3 Resume	 = { WinSize.x_ / 2.0f, +416.0f, 0.0f };
			// title
			const YMath::Vector3 Title	 = { WinSize.x_ / 2.0f, +576.0f, 0.0f };

			// ----- 色 ----- //
			
			// 選択中
			const YMath::Vector3 OnColor  = { 1.0f,1.0f,1.0f };
			// 選択していない
			const YMath::Vector3 OffColor = { 0.3f,0.3f,0.3f };
		}

		// 画面全体
		namespace Curten
		{
			// 位置
			const YMath::Vector3 Pos	 = { WinSize.x_ / 2.0f, WinSize.y_ / 2.0f, 0.0f };

			// 大きさ
			const YMath::Vector3 Scale	 = { WinSize.x_, WinSize.y_, 0.0f };

			// 色
			const YMath::Vector4 Color	 = { 0.0f,0.0f,0.0f,0.75f };
		}
	}
}
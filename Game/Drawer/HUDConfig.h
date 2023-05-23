#pragma once
#include "Def.h"

namespace HUDConfig
{
	// ����
	namespace Operation
	{
		// �L�[
		namespace Key
		{
			// �^�C�g��
			namespace Title
			{
				// �傫��
				const YMath::Vector3 Scale = { 1.0f,1.0f,0.0f };

				// ----- �ʒu ----- //

				// WASD
				const YMath::Vector3 W = { +96.0f, WinSize.y_ - 48.0f, 0.0f };
				const YMath::Vector3 A = { +96.0f, WinSize.y_ - 48.0f, 0.0f };
				const YMath::Vector3 S = { +96.0f, WinSize.y_ - 48.0f, 0.0f };
				const YMath::Vector3 D = { +96.0f, WinSize.y_ - 48.0f, 0.0f };

				// EF
				const YMath::Vector3 E = { -1000.0f, -1000.0f, 0.0f };
				const YMath::Vector3 F = { -1000.0f, -1000.0f, 0.0f };
				
				// SPACE
				const YMath::Vector3 Space = { +192.0f, WinSize.y_ - 32.0f, 0.0f };
				
				// TAB
				const YMath::Vector3 Esc = { -100.0f, -100.0f, 0.0f };

			}
			// �X�e�[�W�Z���N�g
			namespace Select
			{
				// �傫��
				const YMath::Vector3 Scale = { 1.0f,1.0f,0.0f };

				// ----- �ʒu ----- //

				// WASD
				const YMath::Vector3 W = { +96.0f, WinSize.y_ - 48.0f, 0.0f };
				const YMath::Vector3 A = { +96.0f, WinSize.y_ - 48.0f, 0.0f };
				const YMath::Vector3 S = { +96.0f, WinSize.y_ - 48.0f, 0.0f };
				const YMath::Vector3 D = { +96.0f, WinSize.y_ - 48.0f, 0.0f };

				// EF
				const YMath::Vector3 E = { -1000.0f, -1000.0f, 0.0f };
				const YMath::Vector3 F = { -1000.0f, -1000.0f, 0.0f };
				
				// SPACE
				const YMath::Vector3 Space = { +192.0f, WinSize.y_ - 32.0f, 0.0f };
				
				// TAB
				const YMath::Vector3 Esc = { WinSize.x_ - 64.0f, +32.0f, 0.0f };
			}
			// �Q�[��
			namespace Play
			{
				// �傫��
				const YMath::Vector3 Scale = { 1.0f,1.0f,0.0f };

				// ----- �ʒu ----- //

				// WASD
				const YMath::Vector3 W = { +96.0f, WinSize.y_ - 48.0f, 0.0f };
				const YMath::Vector3 A = { +96.0f, WinSize.y_ - 48.0f, 0.0f };
				const YMath::Vector3 S = { +96.0f, WinSize.y_ - 48.0f, 0.0f };
				const YMath::Vector3 D = { +96.0f, WinSize.y_ - 48.0f, 0.0f };

				// EF
				const YMath::Vector3 E = { +96.0f + 64.0f, WinSize.y_ - 48.0f - 32.0f, 0.0f };
				const YMath::Vector3 F = { +96.0f + 96.0f, WinSize.y_ - 48.0f, 0.0f };
				
				// SPACE
				const YMath::Vector3 Space = { +256.0f, WinSize.y_ - 32.0f, 0.0f };
				
				// TAB
				const YMath::Vector3 Esc = { WinSize.x_ - 64.0f, +32.0f, 0.0f };
			}
		}

		// �p�b�h
		namespace Pad
		{
			// �^�C�g��
			namespace Title
			{
				// �傫��
				const YMath::Vector3 Scale = { 2.0f,2.0f,0.0f };

				// ----- �ʒu ----- //
			}
			// �X�e�[�W�Z���N�g
			namespace Select
			{
				// �傫��
				const YMath::Vector3 Scale = { 2.0f,2.0f,0.0f };

				// ----- �ʒu ----- //
			}
			// �Q�[��
			namespace Play
			{
				// �傫��
				const YMath::Vector3 Scale = { 2.0f,2.0f,0.0f };

				// ----- �ʒu ----- //
			}
		}
	}

	// �|�[�Y
	namespace Pause
	{
		// ����
		namespace Font
		{
			// �傫��
			const YMath::Vector3 Scale = { 1.0f,1.0f,0.0f };

			// ----- �ʒu ----- //

			// pause
			const YMath::Vector3 Pause	 = { WinSize.x_ / 2.0f, +128.0f, 0.0f };
			// resume
			const YMath::Vector3 Resume	 = { WinSize.x_ / 2.0f, +416.0f, 0.0f };
			// title
			const YMath::Vector3 Title	 = { WinSize.x_ / 2.0f, +576.0f, 0.0f };

			// ----- �F ----- //
			
			// �I��
			const YMath::Vector3 OnColor  = { 1.0f,1.0f,1.0f };
			// �I�����Ă��Ȃ�
			const YMath::Vector3 OffColor = { 0.3f,0.3f,0.3f };
		}

		// ��ʑS��
		namespace Curten
		{
			// �ʒu
			const YMath::Vector3 Pos	 = { WinSize.x_ / 2.0f, WinSize.y_ / 2.0f, 0.0f };

			// �傫��
			const YMath::Vector3 Scale	 = { WinSize.x_, WinSize.y_, 0.0f };

			// �F
			const YMath::Vector4 Color	 = { 0.0f,0.0f,0.0f,0.75f };
		}
	}
}
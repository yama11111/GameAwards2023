#pragma once
#include "Def.h"

namespace HUDConfig
{
	// ����
	namespace Operation
	{
		// �X�e�[�W�Z���N�g
		namespace Title
		{
			// �L�[
			namespace Key
			{
				// �傫��
				const YMath::Vector3 Scale = { 1.0f,1.0f,0.0f };

				// ----- �ʒu ----- //

				// WASD
				const YMath::Vector3 WASD = { +96.0f, WinSize.y_ - 48.0f, 0.0f };
				// SPACE
				const YMath::Vector3 Space = { +192.0f, WinSize.y_ - 32.0f, 0.0f };
				// TAB
				const YMath::Vector3 Esc = { -100.0f, -100.0f, 0.0f };
			}

			// �p�b�h
			namespace Pad
			{
				// �傫��
				const YMath::Vector3 Scale = { 2.0f,2.0f,0.0f };

				// ----- �ʒu ----- //
			}
		}

		// �X�e�[�W�Z���N�g
		namespace Select
		{
			// �L�[
			namespace Key
			{
				// �傫��
				const YMath::Vector3 Scale = { 1.0f,1.0f,0.0f };

				// ----- �ʒu ----- //

				// WASD
				const YMath::Vector3 WASD = { +96.0f, WinSize.y_ - 48.0f, 0.0f };
				// SPACE
				const YMath::Vector3 Space = { +192.0f, WinSize.y_ - 32.0f, 0.0f };
				// TAB
				const YMath::Vector3 Esc = { -100.0f, -100.0f, 0.0f };
			}

			// �p�b�h
			namespace Pad
			{
				// �傫��
				const YMath::Vector3 Scale = { 2.0f,2.0f,0.0f };

				// ----- �ʒu ----- //
			}
		}

		// �Q�[��
		namespace Play
		{
			// �L�[
			namespace Key
			{
				// �傫��
				const YMath::Vector3 Scale = { 1.5f,1.5f,0.0f };

				// ----- �ʒu ----- //

				// WASD
				const YMath::Vector3 WASD = { +96.0f, WinSize.y_ - 160.0f, 0.0f };
				// SPACE
				const YMath::Vector3 Space = { +192.0f, WinSize.y_ - 64.0f, 0.0f };
				// TAB
				const YMath::Vector3 Esc = { WinSize.x_ - 96.0f, +64.0f, 0.0f };
			}

			// �p�b�h
			namespace Pad
			{
				// �傫��
				const YMath::Vector3 Scale = { 2.0f,2.0f,0.0f };

				// ----- �ʒu ----- //
			}
		}
	}

	// ���c
	namespace Pilot
	{
		// �傫��
		const YMath::Vector3 Scale = { 1.0f,1.0f,0.0f };

		// ----- �ʒu ----- //

		// player
		const YMath::Vector3 Player = { +384.0f, WinSize.y_ - 80.0f, 0.0f };
		// filter
		const YMath::Vector3 Filter = { +384.0f, WinSize.y_ - 48.0f, 0.0f };
		
		// ----- �F ----- //

		// ���c��
		const YMath::Vector4 OnColor  = { 0.8f,0.8f,0.8f,1.0f };
		// ���c���Ă��Ȃ�
		const YMath::Vector4 OffColor = { 0.3f,0.3f,0.3f,0.5f };
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
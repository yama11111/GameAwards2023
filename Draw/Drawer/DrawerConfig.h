#pragma once
#include "Def.h"

// �`��p�N���X
namespace DrawerConfig
{
	// �������f���̑傫��
	const float InvisibleScale = 0.95f;

	// �v���C���[
	namespace Player 
	{
		// �傫��
		const YMath::Vector3 DefScale = { 1.0f,1.0f,1.0f };

		// �u���Ȃ��Ƃ��̐F
		const YMath::Vector3 BadColor = { 1.0f,0.0f,1.0f };

		// �������[�V����
		namespace Idle
		{
			// �Ԋu
			const unsigned int IntervalTime = 10;

			// �Ղ�Ղ�A�j���[�V����
			namespace SlimeAction
			{
				// �L�k��
				const float Value = 0.5f;

				// ���� (F)
				const unsigned int Frame = 20;

				// �w��
				const float Power = 3.0f;
			}
		}

		// �W�����v���[�V����
		namespace Jump
		{
			// �Ղ�Ղ�A�j���[�V����
			namespace SlimeAction
			{
				// �L�k��
				const float Value = 0.5f;

				// ���� (F)
				const unsigned int Frame = 20;

				// �w��
				const float Power = 3.0f;
			}
		}

		// ���n���[�V����
		namespace Landing
		{
			// �Ղ�Ղ�A�j���[�V����
			namespace SlimeAction
			{
				// �L�k��
				const float Value = 0.5f;
				
				// ���� (F)
				const unsigned int Frame = 20;

				// �w��
				const float Power = 3.0f;
			}
		}
	}

	// �t�B���^�[
	namespace Filter 
	{
		// �傫��
		const YMath::Vector3 DefScale = { 1.0f,1.0f,1.0f };

		// �u���Ȃ��Ƃ��̐F
		const YMath::Vector3 BadColor = { 0.1f,0.1f,0.1f };

		// �������[�V����
		namespace Idle
		{
			// �Ԋu
			const unsigned int IntervalTime = 10;
		}
	}

	// �u���b�N
	namespace Block
	{
		// �傫��
		const YMath::Vector3 DefScale = { 1.0f,1.0f,1.0f };

		// �������[�V����
		namespace Idle
		{
			// �Ԋu
			const unsigned int IntervalTime = 10;
		}
	}

	// �Q�[�g
	namespace Gate
	{
		// �傫��
		const YMath::Vector3 DefScale = { 1.0f,1.0f,1.0f };

		// �������[�V����
		namespace Idle
		{
			// �Ԋu
			const unsigned int IntervalTime = 10;
		}
	}

	// �S�[��
	namespace Goal
	{
		// �傫��
		const YMath::Vector3 DefScale = { 1.0f,1.0f,1.0f };

		// �������[�V����
		namespace Idle
		{
			// �Ԋu
			const unsigned int IntervalTime = 20;
		}
		
		// ��]���[�V����
		namespace Rota 
		{
			// �t���[��
			const unsigned int Frame = 100;

			// �� (��)
			namespace Inside
			{
				// �����l
				const YMath::Vector3 Start = { +PI / 3.0f,0.0f,+PI / 2.0f };
				// �ŏI�l
				const YMath::Vector3 End   = { +PI / 3.0f,0.0f,+PI / 2.0f + +PI * 2.0f };
			}

			// �� (�O)
			namespace Outside
			{
				// �����l
				const YMath::Vector3 Start = { -PI / 3.0f,0.0f,-PI / 3.0f };
				// �ŏI�l
				const YMath::Vector3 End   = { -PI / 3.0f,0.0f,-PI / 3.0f - PI * 2.0f };
			}
			
			// �w��
			const float Exponent = 2.0f;
		}
	}

	// �Z���N�g�V�[��
	namespace Select 
	{
		// �n��
		namespace Earth
		{
			// �傫��
			const float Scale = 32.0f;
		}

		// �X�e�[�W
		namespace Stage
		{
			// �t���[��
			const int Frame = 30;
			
			// �w��
			const float Exponent = 1.4f;
		}
	}
}
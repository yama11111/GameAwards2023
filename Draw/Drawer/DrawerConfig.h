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

		// �F
		namespace DefColor
		{
			// �ʏ�
			const YMath::Vector4 Normal	   = { 0.1f,0.9f,0.8f,1.0f };
			// ��
			const YMath::Vector4 Red	   = { 1.0f,0.2f,0.1f,1.0f };
			// ����
			const YMath::Vector4 Invisible = { 1.0f,1.0f,1.0f,0.4f };
		}

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
				const float Exponent = 3.0f;
			}
		}

		// �W�����v���[�V����
		namespace Jump
		{
			// �Ղ�Ղ�A�j���[�V����
			namespace SlimeAction
			{
				// �L�k��
				const float Value = 0.25f;

				// ���� (F)
				const unsigned int Frame = 4;

				// �w��
				const float Exponent = 3.0f;
			}
		}

		// ���n���[�V����
		namespace Landing
		{
			// �Ղ�Ղ�A�j���[�V����
			namespace SlimeAction
			{
				// �L�k��
				const float Value = 0.4f;
				
				// ���� (F)
				const unsigned int Frame = 4;

				// �w��
				const float Exponent = 3.0f;
			}
		}

		// ���X�|�[�����[�V����
		namespace Respawn
		{
			// ���� (F)
			const unsigned int Frame = 20;
			
			// �w��
			const float Exponent = 3.0f;

			// �Ղ�Ղ�A�j���[�V����
			namespace SlimeAction
			{
				// �L�k��
				const float Value = 0.4f;

				// ���� (F)
				const unsigned int Frame = 25;

				// �w��
				const float Exponent = 3.0f;
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

		// �F
		namespace DefColor
		{
			// �ʏ�
			const YMath::Vector4 Normal	   = { 0.0f,0.0f,0.3f,1.0f };
			// ��
			const YMath::Vector4 Red	   = { 1.0f,0.0f,0.0f,1.0f };
			// ����
			const YMath::Vector4 Invisible = { 1.0f,1.0f,1.0f,0.25f };
		}


		// �������[�V����
		namespace Idle
		{
			// �Ԋu
			const unsigned int IntervalTime = 10;
		}

		// �t�F�[�h�C�����[�V����
		namespace FadeIn
		{	
			// �w��
			const float Exponent = 3.0f;
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

		// �J�[�h
		namespace Card 
		{
			// X�̈ʒu
			const float DefPosX = WinSize.x_ - 96.0f;
			
			// ���S�̍���
			const float CenterHeight = WinSize.y_ / 2.0f;
			
			// �S�̂̍���
			const float TotalHeight = 512.0f;
		}

		// ���^�[�{�b�N�X
		namespace LetterBox
		{
			// ���� (��)
			const float TopHeight = 96.0f;
			// ���� (��)
			const float BottomHeight = 96.0f;
		}

		// ���S
		namespace Logo 
		{
			// �ʒu
			const YMath::Vector3 Pos = { 224.0f,48.0f,0.0f };
		}
	}

	// �J�[�h
	namespace Card
	{
		// �u���u���A�j���[�V����
		namespace SlimeAction
		{
			// ����
			const unsigned int Frame = 10;
			
			// �L�k��
			const float Value = 0.25f;

			// �w��
			const float Exponent = 1.4f;
		}

		// �A�j���[�V����
		namespace Animation
		{
			// �t���[��
			const int Frame = 10;

			// �ړ�
			namespace Move
			{

				// �ړ��� (X)
				const float ValueX = -128.0f;

				// �w��
				const float Exponent = 1.2f;
			}

			// �g��
			namespace Scale
			{
				// �g���
				const float Value = 0.25f;

				// �w��
				const float Exponent = 1.2f;
			}
		}
	}
}
#pragma once
#include "Def.h"

// �`��p�N���X
namespace DrawerConfig
{
	// �v���C���[
	namespace Player 
	{
		// �傫��
		const YMath::Vector3 DefScale = { 1.0f,1.0f,1.0f };

		// �F
		const YMath::Vector3 DefColor = { 0.1f,0.9f,0.8f };

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

		// �ړ����[�V����
		namespace Move
		{
			// ��]
			namespace Rota
			{
				// ���� (F)
				const unsigned int Frame = 10;

				// ��]��
				const float Value = PI * 0.1f;

				// �w��
				const float Exponent = 3.0f;
			}

			// ����
			namespace Smoke
			{
				// ���� (F)
				const unsigned int IntervalFrame = 5;


				// ��������
				const unsigned int AliveFrame = 20;


				// �ŏ�������
				const unsigned int MinNum = 1;

				// �ő唭����
				const unsigned int MaxNum = 2;


				// �͈�
				const YMath::Vector3 Range = { 0.0f, 1.5f, 1.0f };


				// �ŏ��X�P�[���T�C�Y
				const float MinScaleSize = 0.2f;

				// �ő�X�P�[���T�C�Y
				const float MaxScaleSize = 0.3f;


				// �ŏ��ړ��X�s�[�h
				const YMath::Vector3 MinMoveSpeed = { +0.1f, +0.025f, +0.0f };

				// �ő�ړ��X�s�[�h
				const YMath::Vector3 MaxMoveSpeed = { +0.3f, +0.05f, +0.0f };


				// �ŏ���]�X�s�[�h
				const YMath::Vector3 MinRotaSpeed = { -0.1f, -0.1f, -0.1f };

				// �ő��]�X�s�[�h
				const YMath::Vector3 MaxRotaSpeed = { +0.1f, +0.1f, +0.1f };


				// �F
				const YMath::Vector3 Color = { 0.1f,0.9f,0.8f };

				// ��
				const float Place = 100.0f;
				
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

	// �u���b�N
	namespace Block
	{
		// �傫��
		const YMath::Vector3 DefScale = { 1.0f,1.0f,1.0f };

		// �k�F
		namespace ShellColor
		{
			// ���s�F
			const YMath::Vector4 Failure = { 0.4f,0.0f,0.0f,1.0f };

			// ���F�̔䗦
			const YMath::Vector4 OriginalRate = { 0.1f,0.1f,0.1f,1.0f };
		}

		// �������[�V����
		namespace Idle
		{
			// �Ԋu
			const unsigned int IntervalTime = 10;
		}

		// �O���b�h
		namespace GridColor
		{
			// �F
			const YMath::Vector4 Success = { 1.0f,1.0f,0.0f,0.75f };

			// ���s�F
			const YMath::Vector4 Failure = { 1.0f,0.0f,0.0f,1.0f };
		}

		// �擾�A�j���[�V����
		namespace Catch
		{
			// ����
			namespace Success
			{
				// �t���[��
				const unsigned int Frame = 30;


				// �����l
				const float Start = 1.0f;
				
				// �ŏI�l
				const float End = 0.0f;
				
				// �w��
				const float Exponent = 3.0f;
			}

			// ���s
			namespace Failure
			{
				// �t���[��
				const unsigned int Frame = 20;


				// �����l
				const float Start = 1.0f;

				// �ŏI�l
				const float End = 0.5f;

				// �w��
				const float Exponent = 3.0f;

				// �h��
				namespace Shake
				{
					// �h���
					const float Swing = 0.4f;

					// ���܂��
					const float Dekey = 0.1f;

					// ������
					const float Place = 10.0f;
				}
			}
		}

		// �ݒu�A�j���[�V����
		namespace Place
		{
			// ����
			namespace Success
			{
				// �t���[��
				const unsigned int Frame = 20;


				// �����l
				const float Start = 0.0f;

				// �ŏI�l
				const float End = 0.5f;

				// �w��
				const float Exponent = 3.0f;
			}

			// ���s
			namespace Failure
			{
				// �t���[��
				const unsigned int Frame = 20;


				// �����l
				const float Start = 0.0f;

				// �ŏI�l
				const float End = 0.25f;

				// �w��
				const float Exponent = 3.0f;

				// �h��
				namespace Shake
				{
					// �h���
					const float Swing = 0.4f;

					// ���܂��
					const float Dekey = 0.1f;

					// ������
					const float Place = 10.0f;
				}
			}
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
		
		// �����]���[�V����
		namespace BindRota 
		{
			// �t���[��
			const unsigned int Frame = 120;

			// �� (��)
			namespace Inside
			{
				// �����l
				const YMath::Vector3 Start = { -PI / 3.0f, 0.0f, -PI / 3.0f };
				
				// �ŏI�l
				const YMath::Vector3 End   = { -PI / 3.0f, 0.0f, -PI / 3.0f - PI * 2.0f };
			}

			// �� (�O)
			namespace Outside
			{
				// �����l
				const YMath::Vector3 Start = { +PI / 3.0f, 0.0f, +PI / 2.0f };
				
				// �ŏI�l
				const YMath::Vector3 End   = { +PI / 3.0f, 0.0f, +PI / 2.0f + PI * 2.0f };
			}
			
			// �w��
			const float Exponent = 3.0f;
		}

		// ���O�C�����[�V����
		namespace Login
		{
			// �t���[��
			const unsigned int Frame = 10;
			
			// �����[��
			namespace RelayBug
			{
				// ��
				const unsigned int Num = 24;

				// �t���[�� (�����ʒu �� ���p�n�_)
				const unsigned int StartToRelayFrame = 10;

				// �t���[�� (���p�n�_ �� �I���n�_)
				const unsigned int RelayToEndFrame = 20;

				// �����[�͈�
				const YMath::Vector3 RelayRange = { 6.0f,6.0f,6.0f };


				// �ŏ���]
				const YMath::Vector3 MinRota = { -PI / 2.0f,-PI / 2.0f ,-PI / 2.0f };

				// �ő��]
				const YMath::Vector3 MaxRota = { +PI / 2.0f, +PI / 2.0f, +PI / 2.0f };


				// �ŏ��X�P�[��
				const float MinScale = 0.3f;

				// �ő�X�P�[��
				const float MaxScale = 0.5f;

				// �F
				const YMath::Vector3 Color = { 0.1f,0.9f,0.8f };

				// ��
				const float Place = 100.0f;
			}
		}

		// �n�b�L���O��]���[�V����
		namespace HackRota
		{
			// �t���[��
			const unsigned int Frame = 60;

			// �����x (��)
			const YMath::Vector3 InAcceleration  = { -PI / 1200.0f, 0.0f, -PI / 360.0f };

			// �����x (�O)
			const YMath::Vector3 OutAcceleration = { +PI / 1200.0f, 0.0f, +PI / 360.0f };
		}

		// �N���A��]���[�V����
		namespace ClearRota
		{
			// �t���[��
			const unsigned int Frame = 30;

			// �w��
			const float Exponent = 3.0f;
		}
	}

	// �Q�[�g
	namespace Gate
	{
		// �傫��
		const YMath::Vector3 DefScale = { 1.0f,1.0f,1.0f };
		
		// �F
		const YMath::Vector3 DefColor = { 1.0f,1.0f,1.0f };

		// �������[�V����
		namespace Idle
		{
			// �Ԋu
			const unsigned int IntervalTime = 10;
		}
	}

	// �^���[
	namespace Tower
	{
	}

	// �j
	namespace CoreColorConfig
	{
		// �F
		namespace Color
		{
			// �ʏ�
			const YMath::Vector3 Normal = { 0.30f, 0.30f, 0.30f };

			// ��
			const YMath::Vector3 Movable = { 0.60f, 0.00f, 0.00f };

			// �N���A
			const YMath::Vector3 Clear = { 0.05f, 0.20f, 0.90f };
		}

		// �A���r�G���g
		namespace Ambient
		{
			// �ʏ�
			const YMath::Vector3 Normal = { 0.5f, 0.5f, 0.5f };

			// �N���A
			const YMath::Vector3 Clear = { 0.7f, 0.7f, 0.8f };
		}

		// ����
		namespace Flickering
		{
			// �t���[��
			const unsigned int Frame = 120;

			// �����l
			const float Start = 1.0f;

			// �ŏI�l
			const float End = 0.75f;

			// �w��
			const float Exponent = 3.0f;
		}

		// ����
		namespace Unify
		{
			// �t���[��
			const unsigned int Frame = 30;

			// �w��
			const float Exponent = 3.0f;
		}
	}

	// �w�i
	namespace Background
	{
		// �A���r�G���g
		const YMath::Vector3 Ambient = { 0.3f,0.2f,0.2f };
		
		// �N���A���p�A���r�G���g
		const YMath::Vector3 ClearAmbient = { 0.5f,0.5f,0.7f };

		// ��
		namespace Light
		{
			const YMath::Vector3 Ambient = { 1.0f,1.0f,1.0f };

			// ���s����
			namespace Direction
			{ 
				// �F
				const YMath::Vector3 Color = { 1.0f,0.0f,0.0f };
				
				// ����
				const YMath::Vector3 Dire = { 0.0f,-1.0f,0.0f };
			}
		}

		// ����
		namespace Unify
		{
			// �t���[��
			const unsigned int Frame = 30;

			// �w��
			const float Exponent = 3.0f;
		}

		// �^���[
		namespace Towers
		{
			// ��
			const unsigned int Num = 5;

			// �ʒu
			const YMath::Vector3 Poss[Num] =
			{
				YMath::Vector3(- 200.0f, - 200.0f, + 225.0f),
				YMath::Vector3(-  35.0f, - 200.0f, + 225.0f),

				YMath::Vector3(+ 400.0f, - 300.0f, + 450.0f),

				YMath::Vector3(- 230.0f, - 350.0f, + 600.0f),
				YMath::Vector3(+ 250.0f, - 350.0f, + 600.0f),
			};

			// ��]
			const YMath::Vector3 Rotas[Num] =
			{
				YMath::Vector3(0.0f, - PI * 1.4f, 0.0f),
				YMath::Vector3(0.0f, + PI * 0.4f, 0.0f),

				YMath::Vector3(0.0f, - PI * 1.2f, 0.0f),

				YMath::Vector3(0.0f, - PI * 0.6f, 0.0f),
				YMath::Vector3(0.0f, - PI * 1.6f, 0.0f),
			};

			// �傫��
			const YMath::Vector3 Scales[Num] =
			{
				YMath::Vector3(  32.0f,  64.0f,  32.0f),
				YMath::Vector3(  32.0f,  48.0f,  32.0f),

				YMath::Vector3(  64.0f, 128.0f,  64.0f),

				YMath::Vector3(  48.0f,  64.0f,  48.0f),
				YMath::Vector3(  48.0f,  80.0f,  48.0f),
			};

			// ��Ԕԍ� (0 : �ʏ�, 1 : ��)
			const unsigned int ModeIdx[Num] =
			{
				0,
				0,

				0,

				0,
				1,
			};
		}

		// �V���T�C�Y
		const float SkydomeSize = 800.0f;

		// �A�O���b�h
		namespace BubbleGrid
		{
			// �Ԋu
			const unsigned int IntervalFrame = 240;
			

			// ��������
			const unsigned int AliveFrame = 720;
			

			// �ŏ�������
			const unsigned int MinNum = 4;
			
			// �ő唭����
			const unsigned int MaxNum = 6;


			// ���S
			const YMath::Vector3 Center = { 0.0f, -50.0f, +150.0f };

			// �͈�
			const YMath::Vector3 Range = { 150.0f, 50.0f, 10.0f };

			
			// �ŏ��X�P�[���T�C�Y
			const float MinScaleSize = 1.5f;
			
			// �ő�X�P�[���T�C�Y
			const float MaxScaleSize = 3.0f;


			// �ŏ��ړ��X�s�[�h
			const YMath::Vector3 MinMoveSpeed = { +0.0f, +0.1f, +0.0f };

			// �ő�ړ��X�s�[�h
			const YMath::Vector3 MaxMoveSpeed = { +0.0f, +0.3f, +0.0f };


			// �ŏ���]�X�s�[�h
			const YMath::Vector3 MinRotaSpeed = { -0.01f, -0.01f, -0.01f };

			// �ő��]�X�s�[�h
			const YMath::Vector3 MaxRotaSpeed = { +0.01f, +0.01f, +0.01f };


			// �F
			const YMath::Vector3 Color = { 1.0f,1.0f,1.0f };

			// ��
			const float Place = 100.0f;
		}
	}

	// �^�C�g��
	namespace Title
	{
		// ���S
		namespace Logo
		{
			// �ʒu
			const YMath::Vector3 Pos = { WinSize.x_ / 2.0f - 160.0f, WinSize.y_ / 2.0f - 200.0f, 0.0f };

			// �傫��
			const YMath::Vector3 Scale = { 0.6f,0.6f,0.0f };
		}

		// �e
		namespace Shadow
		{
			// �ʒu
			const YMath::Vector3 Pos = { WinSize.x_ - 360.0f,WinSize.y_ / 2.0f,0.0f };

			// �傫��
			const YMath::Vector3 Scale = { 1.0f,WinSize.y_,0.0f };
		}
		
		// �I��
		namespace UI
		{
			// �X�^�[�g�ʒu
			const YMath::Vector3 Start = { WinSize.x_ - 240.0f,WinSize.y_ - 240.0f,0.0f };
			
			// �I���ʒu
			const YMath::Vector3 Exit  = { WinSize.x_ - 200.0f,WinSize.y_ - 120.0f,0.0f };

			// �I�𒆐F
			const YMath::Vector4 OnColor  = { 1.0f,1.0f,1.0f,1.0f };
			
			// ���I��F
			const YMath::Vector4 OffColor = { 0.4f,0.4f,0.4f,0.75f };
		}

	}
	
	// �Z���N�g
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
			const float CenterHeight = WinSize.y_ / 2.0f + 8.0f;
			
			// �S�̂̍���
			const float TotalHeight = 448.0f;
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

		// �A���r�G���g
		const YMath::Vector3 Ambient = { 0.8f,0.6f,0.6f };

		// �A�O���b�h
		namespace BubbleGrid
		{
			// �Ԋu
			const unsigned int IntervalFrame = 240;
			

			// ��
			const float Place = 100.0f;
			

			// ��������
			const unsigned int AliveFrame = 720;
			

			// �ŏ�������
			const unsigned int MinNum = 4;
			
			// �ő唭����
			const unsigned int MaxNum = 6;


			// ���S
			const YMath::Vector3 Center = { -10.0f, 0.0f, +150.0f };

			// �͈�
			const YMath::Vector3 Range = { 100.0f, 20.0f, 50.0f };

			
			// �ŏ��X�P�[���T�C�Y
			const float MinScaleSize = 1.5f;
			
			// �ő�X�P�[���T�C�Y
			const float MaxScaleSize = 3.0f;


			// �ŏ��ړ��X�s�[�h
			const YMath::Vector3 MinMoveSpeed = { +0.0f, +0.1f, +0.0f };

			// �ő�ړ��X�s�[�h
			const YMath::Vector3 MaxMoveSpeed = { +0.0f, +0.3f, +0.0f };


			// �ŏ���]�X�s�[�h
			const YMath::Vector3 MinRotaSpeed = { -0.01f, -0.01f, -0.01f };

			// �ő��]�X�s�[�h
			const YMath::Vector3 MaxRotaSpeed = { +0.01f, +0.01f, +0.01f };


			// �F
			const YMath::Vector3 Color = { 1.0f,1.0f,1.0f };
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

	// �O���b�h
	namespace Grid
	{
		// �F
		const YMath::Vector3 DefColor = { 0.0f,0.8f,0.8f };

		// �A���t�@�l
		namespace Alpha
		{
			// ����
			const int Frame = 30;

			// �����l
			const float Start = 0.5f;

			// �ŏI�l
			const float End = 0.2f;

			// �w��
			const float Exponent = 3.0f;
		}
	}
}
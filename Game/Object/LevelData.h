#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "StageConfig.h"
#include <vector>

// �I�u�W�F�N�g�ݒ�
namespace LevelData
{
	// �v���C���[
	namespace Player
	{
		// ������ (1F���ɉ��Z)
		static const float Acceleration = 0.5f;
		
		// ���C�� (1F���Ɍ��Z)
		static const float Friction = 0.1f;
		
		// �W�����v��
		static const float JumpPower = 1.0f;

		// �d��
		static const float Gravity = 0.1f;
		//static const float Gravity = 0.0f;

		// �ő�d��
		static const float MaxGravity = 1.5f;
		
		// �ő呬�x
		static const YMath::Vector2 MaxSpeed = { 0.5f, 3.0f };

		// �A�^������p���a
		static const YMath::Vector2 CollRadSize = { 1.0f, 1.0f };

		// �������X�e�[�^�X
		struct InitStatus
		{
			// �ŔC���f�b�N�X
			size_t signIndex_;

			// ���W
			YMath::Vector2 pos_;
		};
		
		// �������X�e�[�^�X
		static std::array<InitStatus, StageConfig::StageNum_> InitStatuses =
		{
			// �ŔA���W
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

	// �u���b�N
	namespace Block
	{
		// �A�^������p���a
		static const YMath::Vector2 CollRadSize = { 0.9f, 0.9f };

		// �������X�e�[�^�X
		struct InitStatus
		{
			// �ŔC���f�b�N�X
			size_t signIndex_;

			// ���W
			YMath::Vector2 pos_;
		};

		// �������X�e�[�^�X
		static std::array<std::vector<InitStatus>, StageConfig::StageNum_> InitStatuses =
		{
			// �ŔA���W
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

	// �΂�
	namespace Spring
	{
		// �A�^������p���a
		static const YMath::Vector2 CollRadSize = { 1.0f, 0.5f };

		// �������X�e�[�^�X
		struct InitStatus
		{
			// �ŔC���f�b�N�X
			size_t signIndex_;

			// ���W
			YMath::Vector2 pos_;

			// �W�����v��
			float jumpPowar_;
		};

		// �������X�e�[�^�X
		static std::array<std::vector<InitStatus>, StageConfig::StageNum_> InitStatuses =
		{
			// �ŔA���W
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

	// ����
	namespace Platform
	{
		// ������
		static const float Thickness_ = 0.5f;

		// �������X�e�[�^�X
		struct InitStatus
		{
			// �ŔC���f�b�N�X
			size_t signIndex_;

			// ���W
			YMath::Vector2 pos_;

			// ����
			float length_;

			// �X�C�b�`�ԍ�
			int switchIdx_ = -1;
		};

		// �������X�e�[�^�X
		static std::array<std::vector<InitStatus>, StageConfig::StageNum_> InitStatuses =
		{
			// �ŔA���W
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

	// ���[�U�[
	namespace Laser
	{
		// �L�т�X�s�[�h
		static const float GrowSpeed = 0.4f;

		// �������X�e�[�^�X
		struct InitStatus
		{
			// �ŔC���f�b�N�X
			size_t signIndex_;

			// ���W
			YMath::Vector2 pos_;

			// ���� (+ : �E�Ə�, - :���Ɖ�)
			YMath::Vector2 direction_;

			// ����
			float length_;

			// �X�C�b�`�ԍ�
			int switchIdx_ = -1;
		};

		// �������X�e�[�^�X
		static std::array<std::vector<InitStatus>, StageConfig::StageNum_> InitStatuses =
		{
			// �ŔA���W�A����
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

	// �X�C�b�`
	namespace Switch
	{
		// �������X�e�[�^�X
		struct InitStatus
		{
			// �ŔC���f�b�N�X
			size_t signIndex_;

			// ���W
			YMath::Vector2 pos_;

			// ���삵�Ă��邩
			bool isAct_;
		};

		// �������X�e�[�^�X
		static std::array<std::vector<InitStatus>, StageConfig::StageNum_> InitStatuses =
		{
			// �ŔA���W�A���삵�Ă��邩
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

	// ��
	namespace Key
	{
		// �������X�e�[�^�X
		struct InitStatus
		{
			// �ŔC���f�b�N�X
			size_t signIndex_;

			// ���W
			YMath::Vector2 pos_;
		};

		// �������X�e�[�^�X
		static std::array<std::vector<InitStatus>, StageConfig::StageNum_> InitStatuses =
		{
			// �ŔA���W
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

	// �S�[��
	namespace Goal
	{
		// �������X�e�[�^�X
		struct InitStatus
		{
			// �ŔC���f�b�N�X
			size_t signIndex_;

			// ���W
			YMath::Vector2 pos_;
		};

		// �������X�e�[�^�X
		static std::array<InitStatus, StageConfig::StageNum_> InitStatuses =
		{
			// �ŔA���W�A���t���O
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

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
				{0, { 0.0f,0.0f }},  //  1
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

	// �u���b�N
	namespace Block
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

	// �΂�
	namespace Spring
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

	// ����
	namespace Platform
	{
		// �������X�e�[�^�X
		struct InitStatus
		{
			// �ŔC���f�b�N�X
			size_t signIndex_;

			// ���W
			YMath::Vector2 pos_;

			// ����
			float length_;
		};

		// �������X�e�[�^�X
		static std::array<std::vector<InitStatus>, StageConfig::StageNum_> InitStatuses =
		{
			// �ŔA���W
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

	// ���[�U�[
	namespace Laser
	{
		// �������X�e�[�^�X
		struct InitStatus
		{
			// �ŔC���f�b�N�X
			size_t signIndex_;

			// ���W
			YMath::Vector2 pos_;

			// ���� (+ : �E�Ə�, - :���Ɖ�)
			YMath::Vector2 direction_;
		};

		// �������X�e�[�^�X
		static std::array<std::vector<InitStatus>, StageConfig::StageNum_> InitStatuses =
		{
			// �ŔA���W�A����
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

			// �����������Ă��邩
			bool isRock_;
		};

		// �������X�e�[�^�X
		static std::array<InitStatus, StageConfig::StageNum_> InitStatuses =
		{
			// �ŔA���W�A���t���O
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

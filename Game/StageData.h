#pragma once
#include "Vector2.h"
#include "StageConfig.h"
#include <vector>

// -------------------------------------- //
// 0 = �����Ȃ�
// 1 = �u���b�N
// 2 = ���[�v 1 �o�������F��
// 3 = ���[�v 1 �o�������F�E
// 4 = ���[�v 2 �o�������F��
// 5 = ���[�v 2 �o�������F��
// -------------------------------------- //

namespace StageData
{
	// �Ŕ�
	struct SignDataSet
	{
		// ��_ (����)
		YMath::Vector3 leftTop_;

		// �ԍ�
		std::vector<std::vector<int>> numbers;
	};

	static const std::array<std::vector<SignDataSet>, StageConfig::StageNum_> Datas =
	{
		{
			// ----- �X�e�[�W 1 ----- //
			{
				// �Ŕ� 1
				{
					// ����
					{ -20.0f,0.0f,0.0f },
					// �ԍ�
					{
						{ 1,1,1,1,1,1,1,1,1,1,1 },
						{ 1,0,0,0,0,0,0,0,0,0,1 },
						{ 1,0,0,0,0,0,0,0,0,0,1 },
						{ 1,0,0,0,0,0,0,0,0,0,1 },
						{ 1,0,0,0,0,0,0,0,0,0,1 },
						{ 1,0,0,0,0,0,0,0,0,0,2 },
						{ 1,0,0,0,0,0,1,1,1,1,1 },
						{ 1,0,0,0,1,1,1,1,1,1,1 },
						{ 1,1,1,1,1,1,1,1,1,1,1 },
					}
				},

		// �Ŕ� 2
		{
			// ����
			{ +20.0f,0.0f,0.0f },
			// �ԍ�
			{
				{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
				{ 1,0,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 1,0,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 1,0,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 1,1,1,1,1,0,0,0,0,0,0,0,0,1 },
				{ 1,0,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 1,0,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 3,0,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 1,1,1,1,1,1,1,1,1,1,1,1,4,1 },
			}
		},

		// �Ŕ� 3
		{
			// ����
			{ +20.0f,-30.0f,0.0f },
			// �ԍ�
			{
				{ 1,1,1,1,1,1,1,1,1,5,1 },
				{ 1,0,0,0,0,0,0,0,0,0,1 },
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

		// ----- �X�e�[�W 2 ----- //
		{
			// �Ŕ� 1
			{
				// ����
				{ -20.0f,0.0f,0.0f },
				// �ԍ�
				{
					{ 1,1,1,1,1,1,1,1,1,1,1 },
					{ 1,0,0,0,0,0,0,0,0,0,1 },
					{ 1,0,0,0,0,0,0,0,0,0,1 },
					{ 3,0,0,0,0,0,0,0,0,0,2 },
					{ 1,1,1,1,1,1,1,1,1,1,1 },
					{ 1,0,0,0,0,0,0,0,0,0,1 },
					{ 1,0,0,0,0,0,0,0,0,0,1 },
					{ 3,0,0,0,0,0,0,0,0,0,1 },
					{ 1,1,1,1,1,1,1,1,1,1,1 },
				}
			},

		// �Ŕ� 2
		{
			// ����
			{ -20.0f,-30.0f,0.0f },
			// �ԍ�
			{
				{ 1,1,1,1,1,1,1,1,1,1,1,1,1 },
				{ 1,0,0,0,0,0,1,0,0,0,0,0,1 },
				{ 1,0,0,0,0,0,1,0,0,0,0,0,1 },
				{ 3,0,0,0,0,0,1,0,0,0,0,0,2 },
				{ 1,1,1,1,1,1,1,1,1,1,1,1,1 },
			}
		},

		// �Ŕ� 3
		{
			// ����
			{ +20.0f,0.0f,0.0f },
			// �ԍ�
			{
				{ 1,1,1,1,1,1,1,1,1,1,1,1,1 },
				{ 1,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 1,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 3,0,0,0,0,0,0,0,0,0,0,0,2 },
				{ 1,1,1,1,1,0,0,0,1,1,1,1,1 },
				{ 1,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 1,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 1,0,0,0,0,0,0,0,0,0,0,0,2 },
				{ 1,1,1,1,1,1,1,1,1,1,1,1,1 },
			}
		},
	},

		// ----- �X�e�[�W 3 ----- //
		{
			// �Ŕ� 1
			{
				// ����
				{ -20.0f,0.0f,0.0f },
				// �ԍ�
				{

					{ 1,1,1,1,1,1,1,1,1,1,1 },
					{ 1,0,0,0,0,0,0,0,0,0,1 },
					{ 1,0,0,0,0,0,0,0,0,0,1 },
					{ 1,0,0,0,0,0,0,0,0,0,2 },
					{ 1,1,1,1,1,1,1,1,1,1,1 },
				}
			},

		// �Ŕ� 2
		{
			// ����
			{ -20.0f,-30.0f,0.0f },
			// �ԍ�
			{
				{ 1,1,1,1,1,1,1,1,1,1,1,1,1 },
				{ 1,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 1,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 1,0,0,0,0,0,0,0,0,0,0,0,2 },
				{ 1,0,0,0,0,0,0,1,1,1,1,1,1 },
				{ 1,0,0,0,0,0,0,1,1,1,1,1,1 },
				{ 1,0,0,0,0,0,0,1,1,1,1,1,1 },
				{ 1,1,1,1,1,1,1,1,1,1,1,1,1 },
			}
		},

		// �Ŕ� 3
		{
			// ����
			{ +20.0f,0.0f,0.0f },
			// �ԍ�
			{
				{ 1,1,1,1,1,1,1,1,1,1,1,1,1 },
				{ 1,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 1,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 1,0,0,0,0,0,0,0,0,1,1,1,1 },
				{ 1,0,0,0,0,0,0,0,0,1,1,1,1 },
				{ 3,0,0,0,0,0,0,0,0,1,1,1,1 },
				{ 1,1,1,0,0,0,1,1,1,1,1,1,1 },
				{ 1,1,1,0,0,0,1,1,1,1,1,1,1 },
				{ 1,1,1,0,0,0,1,1,1,1,1,1,1 },
				{ 1,0,0,0,0,0,1,1,1,1,1,1,1 },
				{ 3,0,0,0,0,0,1,1,1,1,1,1,1 },
				{ 1,1,1,1,0,0,1,1,1,1,1,1,1 },
				{ 1,1,1,1,1,1,1,1,1,1,1,1,1 },
			}
		},
},

// ----- �X�e�[�W 4 ----- //
{
	// �Ŕ� 1
	{
		// ����
		{ -20.0f,0.0f,0.0f },
		// �ԍ�
		{
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,0,0,0,0,0,1,0,0,0,0,0,1 },
			{ 1,0,0,0,0,0,1,0,0,0,0,0,1 },
			{ 1,0,0,0,0,0,1,0,0,0,0,0,1 },
			{ 1,0,0,1,1,1,1,0,0,0,0,0,1 },
			{ 1,0,0,0,0,0,0,0,0,0,0,0,1 },
			{ 1,0,0,0,0,0,0,0,0,0,0,0,1 },
			{ 1,0,0,0,0,0,0,0,0,0,0,0,2 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1 },
		}
	},

		// �Ŕ� 2
		{
			// ����
			{ -20.0f,-25.0f,0.0f },
			// �ԍ�
			{
				{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
				{ 1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1 },
				{ 1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1 },
				{ 3,0,0,0,0,0,1,0,0,0,0,0,0,0,0,2 },
				{ 1,1,1,1,0,0,1,0,0,0,0,0,1,1,1,1 },
				{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1 },
				{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			}
		},

		// �Ŕ� 3
		{
			// ����
			{ +20.0f,0.0f,0.0f },
			// �ԍ�
			{
				{ 1,1,1,1,1,1,1,1,1,1,1,1,1 },
				{ 1,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 1,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 3,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 1,1,1,1,1,1,1,1,1,1,1,1,1 },
			}
		},
},

// ----- �X�e�[�W 5 ----- //
{
	// �Ŕ� 1
	{
		// ����
		{ -20.0f,-5.0f,0.0f },
		// �ԍ�
		{
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,0,0,0,0,0,0,0,0,0,0,0,1 },
			{ 1,0,0,0,0,0,0,0,0,0,0,0,1 },
			{ 1,0,0,0,0,0,0,0,0,0,0,0,2 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,0,0,0,0,0,0,0,0,0,0,0,1 },
			{ 1,0,0,0,0,0,0,0,0,0,0,0,1 },
			{ 1,0,0,0,0,0,0,0,0,0,0,0,1 },
			{ 1,0,0,0,0,0,1,1,1,1,1,1,1 },
			{ 1,0,0,0,0,0,0,0,0,0,0,0,1 },
			{ 1,0,0,0,0,0,0,0,0,0,0,0,1 },
			{ 1,0,0,0,0,0,0,0,0,0,0,0,2 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1 },
		}
	},

		// �Ŕ� 2
		{
			// ����
			{ +20.0f,-5.0f,0.0f },
			// �ԍ�
				{
					{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
					{ 1,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1 },
					{ 1,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1 },
					{ 3,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1 },
					{ 1,1,1,1,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1 },
					{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1 },
					{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1 },
					{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
					{ 1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
					{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					{ 3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
				}
			},
		},

		// ----- �X�e�[�W 6 ----- //
		{

			// �Ŕ� 1
			{
				// ����
				{ -20.0f,-5.0f,0.0f },
				// �ԍ�
				{
					{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
					{ 1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1 },
					{ 1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1 },
					{ 3,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,2 },
					{ 1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,1,1,1 },
					{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					{ 1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,0,0,1 },
					{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					{ 1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,0,0,1 },
					{ 1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1 },
					{ 1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1 },
					{ 1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1 },
					{ 3,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1 },
					{ 1,1,1,1,1,0,0,1,1,1,1,1,0,1,0,0,0,0,1 },
					{ 1,1,1,1,1,1,1,1,1,1,1,1,4,1,1,1,1,1,1 },
				}
			},

		// �Ŕ� 2
		{
			// ����
			{ +20.0f,+5.0f,0.0f },
			// �ԍ�
			{
				{ 1,1,1,1,1,1,1,1,1,1,1,1,1 },
				{ 1,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 1,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 1,0,0,0,0,0,0,0,0,0,0,0,2 },
				{ 1,0,0,0,0,0,1,1,1,1,1,1,1 },
				{ 1,0,0,0,0,0,1,1,1,1,1,1,1 },
				{ 1,0,0,0,0,0,1,1,1,1,1,1,1 },
				{ 1,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 1,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 1,0,0,0,0,0,0,0,0,0,0,0,2 },
				{ 1,0,0,1,1,1,1,1,1,1,1,1,1 },
				{ 1,1,1,1,1,1,1,1,1,1,1,1,1 },
			}
		},

		// �Ŕ� 3
		{
			// ����
			{ +20.0f,-25.0f,0.0f },
			// �ԍ�
			{
				{ 1,1,1,1,1,5,1,1,1,1,1 },
				{ 1,0,0,0,0,0,0,0,0,0,1 },
				{ 1,0,0,0,0,0,0,0,0,0,1 },
				{ 1,0,0,0,0,0,0,0,0,0,1 },
				{ 1,0,0,0,0,0,0,0,0,0,1 },
				{ 1,0,0,0,0,0,0,0,0,0,1 },
				{ 1,0,0,0,0,0,0,0,0,0,1 },
				{ 3,0,0,0,0,0,0,0,0,0,1 },
				{ 1,1,1,1,0,0,0,1,1,1,1 },
				{ 1,1,1,1,1,1,1,1,1,1,1 },
			}
		},

	},

		// ----- �X�e�[�W 7 ----- //
		{
			// �Ŕ� 1
			{
				// ����
				{ -20.0f,0.0f,0.0f },
				// �ԍ�
				{
					{ 1,1,1,1,1,1,1,1,1,1,1,1,1 },
					{ 1,0,0,0,0,0,0,0,0,0,0,0,1 },
					{ 1,0,0,0,0,0,0,0,0,0,0,0,1 },
					{ 1,0,0,0,0,0,0,0,0,0,0,0,2 },
					{ 1,1,1,1,1,1,1,1,1,1,1,1,1 },
					{ 1,0,0,0,0,0,0,0,0,0,0,0,1 },
					{ 1,0,0,0,0,0,0,0,0,0,0,0,1 },
					{ 1,0,0,0,0,0,0,0,0,0,0,0,2 },
					{ 1,1,1,1,1,1,1,1,1,1,1,1,1 },
				}
			},

		// �Ŕ� 2
		{
			// ����
			{ +20.0f,0.0f,0.0f },
			// �ԍ�
			{
				{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
				{ 1,0,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 1,0,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 3,0,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 1,1,1,1,0,0,1,1,1,1,1,1,1,1 },
				{ 1,0,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 1,1,1,1,0,0,1,1,0,0,1,1,1,1 },
				{ 1,0,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 1,0,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 3,0,0,0,0,0,0,0,0,0,0,0,0,1 },
				{ 1,1,1,1,0,0,1,1,0,0,1,1,1,1 },
				{ 1,1,1,1,0,0,1,1,0,0,1,1,1,1 },
				{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			}
		},

	},

		//// ----- �X�e�[�W 8 ----- //
		{
			// �Ŕ� 1
{
				// ����
				{ -40.0f,-15.0f,0.0f },
				// �ԍ�
				{
					{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
					{ 1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1 },
					{ 1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1 },
					{ 1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,2,1 },
					{ 1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,1,1,1 },
					{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					{ 1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,0,0,1 },
					{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					{ 1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,0,0,1 },
					{ 1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1 },
					{ 1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1 },
					{ 1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1 },
					{ 1,2,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1 },
					{ 1,1,1,1,1,0,1,1,1,1,1,2,1,0,0,0,0,1 },
					{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
				}
			},
		},

		//// ----- �X�e�[�W 9 ----- //
		//{
		//},

		//// ----- �X�e�[�W 10 ----- //
		//{
		//},
	}
	};
}
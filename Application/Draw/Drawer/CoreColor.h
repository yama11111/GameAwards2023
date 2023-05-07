#pragma once
#include "Color.h"
#include "Lerp.h"
#include "Power.h"
#include "Timer.h"
#include <array>
#include <memory>

class CoreColor
{

public:

	// ���
	enum class ColorType
	{
		Gray = 0, // �D�F
		Red  = 1, // �ԐF
		Blue = 2, // �F
	};

	// ��ނ̐�
	static const size_t sTypeNum_ = 3;

private:
	
	// �j�F
	static std::array<std::unique_ptr<YGame::Color>, sTypeNum_> sColors_;

	// �j�F�l
	static std::array<YMath::Vector3, sTypeNum_> sColorValues_;


	// �j�F���Ńp���[
	static YMath::Power sFlickeringPow_;

	// �j�F���Ńp���[�X�C�b�`
	static bool sIsSwitchFlickeringPow_;

	// �j�F���Ŋ����C�[�W���O
	static YMath::Ease<float> sFlickeringColorRateEas_;


	// �F����p�t���O
	static bool sIsUnify_;

	// �F����p�^�C�}�[
	static YMath::Timer sUnifyTim_;

	// �F����p�C�[�W���O
	static std::array<YMath::Ease<YMath::Vector3>, sTypeNum_> sUnifyColorEass_;

public:

	/// <summary>
	/// �ÓI������
	/// </summary>
	static void StaticInitialize();

	/// <summary>
	/// �ÓI���Z�b�g
	/// </summary>
	static void StaticReset();

	/// <summary>
	/// �ÓI�X�V
	/// </summary>
	static void StaticUpdate();

public:

	/// <summary>
	/// �N���A���o (�S�Ă̐F�𓝈ꂷ��)
	/// </summary>
	/// <param name="colorType"> : �F�̃^�C�v</param>
	static void StaticClearAnimation(const ColorType& colorType);

public:

	/// <summary>
	/// �F�|�C���^�擾
	/// </summary>
	/// <param name="colorType"> : �F�̃^�C�v</param>
	/// <returns>�Ή�����F�̃|�C���^</returns>
	static YGame::Color* ColorPtr(const ColorType& colorType);

	/// <summary>
	/// �F�|�C���^�擾
	/// </summary>
	/// <param name="idx"> : �C���f�b�N�X</param>
	/// <returns>�Ή�����F�̃|�C���^</returns>
	static YGame::Color* ColorPtr(const size_t& idx);
};


#pragma once
#include "CBColor.h"
#include "CBMaterial.h"
#include "Lerp.h"
#include "Power.h"
#include "Timer.h"
#include <array>
#include <memory>

class CoreColor
{

public:

	// �F���
	enum class ColorType
	{
		eGray	 = 0, // �D�F
		eRed	 = 1, // �ԐF
		eGreen	 = 2, // �ΐF
		eBlue	 = 3, // �F
		eOrange	 = 4, // ��F
		eEnd, // ���T�C�Y�p
	};

	// �p�[�c���
	enum class PartsType
	{
		eCore = 0, // �j
		eShell = 1, // �k
		eEnd, // ���T�C�Y�p
	};

	// �F��ނ̐�
	static const size_t sColorTypeNum_ = static_cast<size_t>(ColorType::eEnd);
	
	// �p�[�c��ނ̐�
	static const size_t sPartsTypeNum_ = static_cast<size_t>(PartsType::eEnd);

private:
	
	// �F
	static std::array<std::array<std::unique_ptr<YGame::CBColor>, sColorTypeNum_>, sPartsTypeNum_> sColors_;

	// �}�e���A��
	static std::array<std::array<std::unique_ptr<YGame::CBMaterial>, sColorTypeNum_>, sPartsTypeNum_> sMates_;


	// �F�l
	static std::array<std::array<YMath::Vector3, sColorTypeNum_>, sPartsTypeNum_> sColorValues_;

	// �}�e���A���l
	static std::array<std::array<YMath::Vector3, sColorTypeNum_>, sPartsTypeNum_> sMateValues_;


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
	static std::array<std::array<YMath::Ease<YMath::Vector3>, sColorTypeNum_>, sPartsTypeNum_ > sUnifyColorEass_;
	
	// �}�e���A������p�C�[�W���O
	static std::array<std::array<YMath::Ease<YMath::Vector3>, sColorTypeNum_>, sPartsTypeNum_ > sUnifyMateEass_;

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
	/// <param name="colorType"> : �F�^�C�v</param>
	static void StaticClearAnimation(const ColorType colorType);

public:

	/// <summary>
	/// �F�|�C���^�擾
	/// </summary>
	/// <param name="colorType"> : �F�̃^�C�v</param>
	/// <param name="partsType"> : �p�[�c�^�C�v</param>
	/// <returns>�Ή�����F�̃|�C���^</returns>
	static YGame::CBColor* ColorPtr(const ColorType colorType, const PartsType partsType);

	/// <summary>
	/// �}�e���A���|�C���^�擾
	/// </summary>
	/// <param name="colorType"> : �F�̃^�C�v</param>
	/// <param name="partsType"> : �p�[�c�^�C�v</param>
	/// <returns>�}�e���A���̃|�C���^</returns>
	static YGame::CBMaterial* MaterialPtr(const ColorType colorType, const PartsType partsType);

};


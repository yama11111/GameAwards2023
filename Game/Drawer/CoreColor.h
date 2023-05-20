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

	// ���
	enum class ColorType
	{
		eGray	 = 0, // �D�F
		eRed	 = 1, // �ԐF
		eGreen	 = 2, // �ΐF
		eBlue	 = 3, // �F
		eEnd, // ���T�C�Y�p
	};

	// ��ނ̐�
	static const size_t sTypeNum_ = static_cast<size_t>(ColorType::eEnd);

private:
	
	// �j�F
	static std::array<std::unique_ptr<YGame::CBColor>, sTypeNum_> sColors_;

	// �j�F�l
	static std::array<YMath::Vector3, sTypeNum_> sColorValues_;

	// �}�e���A��
	static std::unique_ptr<YGame::CBMaterial> sMate_;


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
	
	// �}�e���A������p�C�[�W���O
	static YMath::Ease<YMath::Vector3> sUnifyMaterialEas_;

public:

	/// <summary>
	/// �ÓI������
	/// </summary>
	static void StaticInitialize(const bool isPlay);

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
	static YGame::CBColor* ColorPtr(const ColorType& colorType);

	/// <summary>
	/// �F�|�C���^�擾
	/// </summary>
	/// <param name="index"> : �C���f�b�N�X</param>
	/// <returns>�Ή�����F�̃|�C���^</returns>
	static YGame::CBColor* ColorPtr(const size_t& index);

	/// <summary>
	/// �}�e���A���|�C���^�擾
	/// </summary>
	/// <returns>�}�e���A���̃|�C���^</returns>
	static YGame::CBMaterial* MaterialPtr();

};


#include "CoreColor.h"
#include "DrawerConfig.h"
#include <cassert>

#include "SceneExecutive.h"

#pragma region ���O���

using std::array;
using std::unique_ptr;

using YGame::CBColor;
using YGame::CBMaterial;

using YMath::Ease;
using YMath::Timer;
using YMath::Power;
using YMath::Vector3;
using YMath::Vector4;

using namespace DrawerConfig::CoreColorConfig;

#pragma endregion

#pragma region Static

array<array<unique_ptr<CBColor>, CoreColor::sColorTypeNum_>, CoreColor::sPartsTypeNum_> CoreColor::sColors_;
array<array<unique_ptr<CBMaterial>, CoreColor::sColorTypeNum_>, CoreColor::sPartsTypeNum_> CoreColor::sMates_;

array<array<Vector3, CoreColor::sColorTypeNum_>, CoreColor::sPartsTypeNum_> CoreColor::sColorValues_;
array<array<Vector3, CoreColor::sColorTypeNum_>, CoreColor::sPartsTypeNum_> CoreColor::sMateValues_;

Power CoreColor::sFlickeringPow_;
bool CoreColor::sIsSwitchFlickeringPow_ = false;
Ease<float> CoreColor::sFlickeringColorRateEas_;

bool CoreColor::sIsUnify_ = false;
Timer CoreColor::sUnifyTim_;
array<array<Ease<Vector3>, CoreColor::sColorTypeNum_>, CoreColor::sPartsTypeNum_> CoreColor::sUnifyColorEass_;
array<array<Ease<Vector3>, CoreColor::sColorTypeNum_>, CoreColor::sPartsTypeNum_> CoreColor::sUnifyMateEass_;

#pragma endregion

#pragma region Index

static const size_t CoreIdx = static_cast<size_t>(CoreColor::PartsType::eCore);
static const size_t ShellIdx = static_cast<size_t>(CoreColor::PartsType::eShell);

#pragma endregion


void CoreColor::StaticInitialize()
{
	// ����
	for (size_t i = 0; i < sPartsTypeNum_; i++)
	{
		for (size_t j = 0; j < sColorTypeNum_; j++)
		{
			// �F
			sColors_[i][j].reset(CBColor::Create());

			// �}�e���A��
			sMates_[i][j].reset(CBMaterial::Create());
		}
	}

	// �F�l
	sColorValues_ = 
	{
		{
			{
				Core::Color::Gray, Core::Color::Red, Core::Color::Green, Core::Color::Blue, Core::Color::Orange
			},
			{
				Shell::Color::Gray, Shell::Color::Red, Shell::Color::Green, Shell::Color::Blue, Shell::Color::Orange
			}
		}
	};

	// �}�e���A���l
	sMateValues_ =
	{
		{
			{
				Core::Material::Gray, Core::Material::Red, Core::Material::Green, Core::Material::Blue, Core::Material::Orange
			},
			{
				Shell::Material::Gray, Shell::Material::Red, Shell::Material::Green, Shell::Material::Blue, Shell::Material::Orange
			}
		}
	};


	// ���Ńp���[
	sFlickeringPow_.Initialize(Flickering::Frame);

	// ���ŐF�C�[�W���O
	sFlickeringColorRateEas_.Initialize(Flickering::Start, Flickering::End, Flickering::Exponent);


	// �F����p�^�C�}�[
	sUnifyTim_.Initialize(Unify::Frame);

	// ���Z�b�g
	StaticReset();
}

void CoreColor::StaticReset()
{
	// ������
	for (size_t i = 0; i < sPartsTypeNum_; i++)
	{
		
		for (size_t j = 0; j < sColorTypeNum_; j++)
		{
			// �A���t�@�l
			//sColors_[CoreIdx][j]->SetAlpha(0.75f);
			
			// �F
			sColors_[i][j]->SetRGB(sColorValues_[i][j]);

			// �}�e���A��
			sMates_[i][j]->SetAmbient(sMateValues_[i][j]);


			// �F�C�[�W���O
			sUnifyColorEass_[i][j].Initialize({}, {}, 0.0f);

			// �}�e���A���C�[�W���O
			sUnifyMateEass_[i][j].Initialize({}, {}, 0.0f);
		}
	}


	// ���Ńp���[���Z�b�g
	sFlickeringPow_.Reset();

	// ���Ńp���[�X�C�b�`�I��
	sIsSwitchFlickeringPow_ = true;


	// �F����p�t���O
	sIsUnify_ = false;

	// �F����p�^�C�}�[
	sUnifyTim_.Reset(false);
}

void CoreColor::StaticUpdate()
{
	// �A���t�@�l�p���[�X�V
	sFlickeringPow_.Update(sIsSwitchFlickeringPow_);

	// �ۑ��p����
	float rate = 0.0f;

	// �X�C�b�`�I���Ȃ�
	if (sIsSwitchFlickeringPow_)
	{
		// �C�[�Y�A�E�g
		rate = sFlickeringColorRateEas_.Out(sFlickeringPow_.Ratio());
	}
	// ����ȊO�Ȃ�
	else
	{
		// �C�[�Y�C��
		rate = sFlickeringColorRateEas_.In(sFlickeringPow_.Ratio());
	}

	// �p���[���}�b�N�X�Ȃ�
	if (sFlickeringPow_.IsMax())
	{
		// �X�C�b�`�I��
		sIsSwitchFlickeringPow_ = false;
	}
	// �p���[���[���Ȃ�
	else if (sFlickeringPow_.IsZero())
	{
		// �X�C�b�`�I�t
		sIsSwitchFlickeringPow_ = true;
	}

	// �^�C�}�[�X�V
	sUnifyTim_.Update();

	// �F����
	for (size_t i = 0; i < sPartsTypeNum_; i++)
	{
		for (size_t j = 0; j < sColorTypeNum_; j++)
		{
			// �ݒ�F, �}�e���A��
			Vector3 color{}, mate{};

			// ���ꒆ�Ȃ�
			if (sIsUnify_)
			{
				// �C�[�Y�C��
				color = sUnifyColorEass_[i][j].In(sUnifyTim_.Ratio()) * rate;
				mate  = sUnifyMateEass_[i][j].In(sUnifyTim_.Ratio());
			}
			// ����ȊO�Ȃ�
			else
			{
				// �l * ����
				color = sColorValues_[i][j] * rate;
				mate  = sMateValues_[i][j];
			}

			// �X�V
			sColors_[i][j]->SetRGB(color);
			sMates_[i][j]->SetAmbient(mate);
		}
	}

	// �����I��
	if (sUnifyTim_.IsEnd())
	{
		YScene::SceneExecutive::GetInstance()->Change("SELECT", "INFECTION", 10, 10);
	}
}

void CoreColor::StaticClearAnimation(const ColorType colorType)
{
	// ����J�n
	sIsUnify_ = true;

	// �C���f�b�N�X
	size_t idx = static_cast<size_t>(colorType);

	for (size_t i = 0; i < sPartsTypeNum_; i++)
	{
		// �ŏI�l�ݒ�
		Vector3 endColor = Vector3(sColorValues_[i][idx]);
		Vector3 endMate = Vector3(sMateValues_[i][idx]);
		
		// �F�̐�����
		for (size_t j = 0; j < sColorTypeNum_; j++)
		{
			// �����l�ݒ�
			Vector3 startColor = sColorValues_[i][j];
			Vector3 startMate = sMateValues_[i][j];

			// �F����p�C�[�W���O������
			sUnifyColorEass_[i][j].Initialize(startColor, endColor, Unify::Exponent);

			// �}�e���A������p�C�[�W���O������
			sUnifyMateEass_[i][j].Initialize(startMate, endMate, Unify::Exponent);
		}
	}

	// �^�C�}�[���Z�b�g + �J�n
	sUnifyTim_.Reset(true);
}

CBColor* CoreColor::ColorPtr(const ColorType colorType, const PartsType partsType)
{
	// �C���f�b�N�X
	size_t colorIdx = static_cast<size_t>(colorType);
	size_t partsIdx = static_cast<size_t>(partsType);

	// �F�|�C���^��Ԃ�
	return sColors_[partsIdx][colorIdx].get();
}

CBMaterial* CoreColor::MaterialPtr(const ColorType colorType, const PartsType partsType)
{
	// �C���f�b�N�X
	size_t colorIdx = static_cast<size_t>(colorType);
	size_t partsIdx = static_cast<size_t>(partsType);

	// �}�e���A���|�C���^��Ԃ�
	return sMates_[partsIdx][colorIdx].get();
}

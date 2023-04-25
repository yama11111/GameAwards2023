#include "CoreColor.h"
#include "DrawerConfig.h"
#include <cassert>

#pragma region ���O���

using std::array;
using std::unique_ptr;

using YGame::Color;

using YMath::Ease;
using YMath::Power;
using YMath::Vector3;
using YMath::Vector4;

using namespace DrawerConfig::CoreColorConfig;

#pragma endregion

#pragma region Static

array<unique_ptr<Color>, CoreColor::sTypeNum_> CoreColor::sColors_;
array<Vector3, CoreColor::sTypeNum_> CoreColor::sColorValues_;
array<Ease<Vector3>, CoreColor::sTypeNum_> CoreColor::sColorValueEass_;

Power CoreColor::sFlickeringPow_;
bool CoreColor::sIsSwitchFlickeringPow_ = false;
Ease<float> CoreColor::sFlickeringColorRateEas_;

#pragma endregion

void CoreColor::StaticInitialize()
{
	// �F
	for (size_t i = 0; i < sColors_.size(); i++)
	{
		// ����
		sColors_[i]. reset(Color::Create());
	}

	// �F�l
	sColorValues_ = { Normal, Movable, Clear };

	// ���Ńp���[
	sFlickeringPow_.Initialize(Flickering::Frame);

	// ���ŐF�C�[�W���O
	sFlickeringColorRateEas_.Initialize(Flickering::Start, Flickering::End, Flickering::Exponent);

	// ���Z�b�g
	StaticReset();
}

void CoreColor::StaticReset()
{
	// �j�F������
	for (size_t i = 0; i < sColors_.size(); i++)
	{
		sColors_[i] ->SetRGB(sColorValues_[i]);
	}

	// ���Ńp���[���Z�b�g
	sFlickeringPow_.Reset();

	// ���Ńp���[�X�C�b�`�I��
	sIsSwitchFlickeringPow_ = true;
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

	// �j�F����
	for (size_t i = 0; i < sColors_.size(); i++)
	{
		// �ݒ�F
		Vector3 color = sColorValues_[i] * rate;

		// �F�X�V
		sColors_[i]->SetRGB(color);
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
}

Color* CoreColor::ColorPtr(const ColorType& colorType)
{
	// �C���f�b�N�X
	size_t idx = static_cast<size_t>(colorType);

	// �F�|�C���^��Ԃ�
	return sColors_[idx].get();
}

Color* CoreColor::ColorPtr(const size_t& idx)
{
	// 0�ȉ� �� �ő�l�𒴂��� �Ȃ�e��
	assert(0 <= idx);
	assert(idx < sColors_.size());

	// �F�|�C���^��Ԃ�
	return sColors_[idx].get();
}

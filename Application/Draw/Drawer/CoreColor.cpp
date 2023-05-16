#include "CoreColor.h"
#include "DrawerConfig.h"
#include <cassert>

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

array<unique_ptr<CBColor>, CoreColor::sTypeNum_> CoreColor::sColors_;
array<Vector3, CoreColor::sTypeNum_> CoreColor::sColorValues_;
unique_ptr<CBMaterial> CoreColor::sMate_;

Power CoreColor::sFlickeringPow_;
bool CoreColor::sIsSwitchFlickeringPow_ = false;
Ease<float> CoreColor::sFlickeringColorRateEas_;

bool CoreColor::sIsUnify_ = false;
Timer CoreColor::sUnifyTim_;
array<Ease<Vector3>, CoreColor::sTypeNum_> CoreColor::sUnifyColorEass_;
Ease<Vector3> CoreColor::sUnifyMaterialEas_;

#pragma endregion

void CoreColor::StaticInitialize(const bool isPlay)
{
	// �F
	for (size_t i = 0; i < sColors_.size(); i++)
	{
		// ����
		sColors_[i]. reset(CBColor::Create());
	}

	// �F�l
	sColorValues_ = { Color::Normal, Color::Movable, Color::Spring, Color::Clear };

	// �}�e���A��
	sMate_.reset(CBMaterial::Create(Ambient::Normal));


	// �F����p�^�C�}�[
	sUnifyTim_.Initialize(Unify::Frame);


	// ���Ńp���[
	sFlickeringPow_.Initialize(Flickering::Frame);

	// ���ŐF�C�[�W���O
	sFlickeringColorRateEas_.Initialize(Flickering::Start, Flickering::End, Flickering::Exponent);

	// ���Z�b�g
	StaticReset();
}

void CoreColor::StaticReset()
{
	// �F�̐�����
	for (size_t i = 0; i < sColors_.size(); i++)
	{
		// �j�F������
		sColors_[i] ->SetRGB(sColorValues_[i]);
		
		// �j�F�l������
		sUnifyColorEass_[i].Initialize({}, {}, 0.0f);
	}

	// �j�}�e���A���l������
	sMate_->SetAmbient(Ambient::Normal);
	
	// �j�}�e���A���l������
	sUnifyMaterialEas_.Initialize({}, {}, 0.0f);


	// �F����p�t���O
	sIsUnify_ = false;

	// �F����p�^�C�}�[
	sUnifyTim_.Reset(false);


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

	// �j�F����
	for (size_t i = 0; i < sColors_.size(); i++)
	{
		// �ݒ�F
		Vector3 color{};
		
		// ���ꒆ�Ȃ�
		if (sIsUnify_)
		{
			// �C�[�Y�C��
			color = sUnifyColorEass_[i].In(sUnifyTim_.Ratio()) * rate;
		}
		// ����ȊO�Ȃ�
		else
		{
			// �F�l * ����
			color = sColorValues_[i] * rate;
		}

		// �F�X�V
		sColors_[i]->SetRGB(color);
	}

	// ���ꒆ�Ȃ�
	if (sIsUnify_)
	{
		// �C�[�Y�C��
		sMate_->SetAmbient(sUnifyMaterialEas_.In(sUnifyTim_.Ratio()));
	}
}

void CoreColor::StaticClearAnimation(const ColorType& colorType)
{
	// ����J�n
	sIsUnify_ = true;

	// �C���f�b�N�X
	size_t idx = static_cast<size_t>(colorType);

	// �ŏI�l�ݒ�
	Vector3 end = Vector3(sColorValues_[idx]);

	// �F�̐�����
	for (size_t i = 0; i < sColors_.size(); i++)
	{
		// �����l�ݒ�
		Vector3 start = sColorValues_[i];

		// �F����p�C�[�W���O������
		sUnifyColorEass_[i].Initialize(start, end, Unify::Exponent);
	}

	// �}�e���A������p�C�[�W���O������
	sUnifyMaterialEas_.Initialize(Ambient::Normal, Ambient::Clear, Unify::Exponent);

	// �^�C�}�[���Z�b�g + �J�n
	sUnifyTim_.Reset(true);
}

CBColor* CoreColor::ColorPtr(const ColorType& colorType)
{
	// �C���f�b�N�X
	size_t idx = static_cast<size_t>(colorType);

	// �F�|�C���^��Ԃ�
	return sColors_[idx].get();
}

CBColor* CoreColor::ColorPtr(const size_t& index)
{
	// �C���f�b�N�X
	size_t idx = index;

	// �N�����v
	if (idx <= 0) { idx = 0; }
	if (idx >= sColors_.size() - 1) { idx = sColors_.size() - 1; }

	// �F�|�C���^��Ԃ�
	return sColors_[idx].get();
}

CBMaterial* CoreColor::MaterialPtr()
{
	// �}�e���A���|�C���^��Ԃ�
	return sMate_.get();
}

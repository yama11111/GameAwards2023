#include "TowerDrawer.h"
#include "CalcTransform.h"
#include "DrawerConfig.h"
#include <cassert>

#pragma region ���O���

using std::array;
using std::unique_ptr;

using YGame::Transform;
using YGame::ModelObject;
using YGame::Model;
using YGame::Color;
using YGame::Material;

using YMath::Ease;
using YMath::Power;
using YMath::Vector3;
using YMath::Vector4;

using namespace DrawerConfig::Tower;

#pragma endregion

#pragma region Static

array<array<Model*, TowerDrawerCommon::PartsNum_>, TowerDrawerCommon::ModeNum_> TowerDrawerCommon::spModels_ =
{
	nullptr, nullptr, 
	nullptr, nullptr, 
};
YGame::ViewProjection* TowerDrawerCommon::spVP_ = nullptr;
Material* TowerDrawerCommon::spMate_ = nullptr;
array<unique_ptr<Color>, TowerDrawerCommon::ModeNum_> TowerDrawerCommon::sCoreColor_;
unique_ptr<Material> TowerDrawerCommon::sCoreMate_;
Power TowerDrawerCommon::coreColorPow_;
bool TowerDrawerCommon::isSwitchCoreColorPower_ = false;
array<Ease<Vector4>, TowerDrawerCommon::ModeNum_> TowerDrawerCommon::coreColorEas_;
#pragma endregion

#pragma region �C���f�b�N�X

static const size_t NormalIdx = static_cast<size_t>(TowerDrawerCommon::Mode::Normal); // �ʏ�
static const size_t RedIdx = static_cast<size_t>(TowerDrawerCommon::Mode::Red); // ��

static const size_t CoreIdx = static_cast<size_t>(TowerDrawerCommon::Parts::Core); // �j
static const size_t ShellIdx = static_cast<size_t>(TowerDrawerCommon::Parts::Shell); // �k

#pragma endregion

#pragma region Common

void TowerDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP, YGame::Material* pMate)
{
	// null�`�F�b�N
	assert(pVP);
	assert(pMate);
	// ���
	spVP_ = pVP;
	spMate_ = pMate;

	// ----- ���f���ǂݍ��� ----- //

	// �ʏ�
	spModels_[NormalIdx][CoreIdx] = Model::Load("tower/normal/core", true); // �j
	spModels_[NormalIdx][ShellIdx] = Model::Load("tower/normal/shell", true); // �k

	// ��
	spModels_[RedIdx][CoreIdx] = Model::Load("tower/red/core", true); // �j
	spModels_[RedIdx][ShellIdx] = Model::Load("tower/red/shell", true); // �k


	// �F
	sCoreColor_[NormalIdx].reset(Color::Create(CoreColor::Normal::Start));
	sCoreColor_[RedIdx].reset(Color::Create(CoreColor::Red::Start));

	// �}�e���A��
	sCoreMate_.reset(Material::Create());

	// �j�F�p�p���[
	coreColorPow_.Initialize(CoreColor::Frame);

	// �j�F�C�[�W���O
	coreColorEas_[NormalIdx].Initialize(CoreColor::Normal::Start, CoreColor::Normal::End, CoreColor::Exponent);
	coreColorEas_[RedIdx].Initialize(CoreColor::Red::Start, CoreColor::Red::End, CoreColor::Exponent);


	// ���Z�b�g
	StaticReset();
}

void TowerDrawerCommon::StaticReset()
{
	// �j�F�p�p���[
	coreColorPow_.Reset();

	// �j�F�p���[�X�C�b�`
	isSwitchCoreColorPower_ = true;
}

void TowerDrawerCommon::StaticUpdate()
{
	// �A���t�@�l�p���[�X�V
	coreColorPow_.Update(isSwitchCoreColorPower_);

	// �X�C�b�`�I���Ȃ�
	if (isSwitchCoreColorPower_)
	{
		// �j�F����
		for (size_t i = 0; i < sCoreColor_.size(); i++)
		{
			// �A���t�@�l�X�V (�C�[�Y�A�E�g)
			sCoreColor_[i]->SetRGBA(coreColorEas_[i].Out(coreColorPow_.Ratio()));
		}
	}
	// ����ȊO�Ȃ�
	else
	{
		// �j�F����
		for (size_t i = 0; i < sCoreColor_.size(); i++)
		{
			// �A���t�@�l�X�V (�C�[�Y�C��)
			sCoreColor_[i]->SetRGBA(coreColorEas_[i].In(coreColorPow_.Ratio()));
		}
	}

	// �p���[���}�b�N�X�Ȃ�
	if (coreColorPow_.IsMax())
	{
		// �X�C�b�`�I��
		isSwitchCoreColorPower_ = false;
	}
	// �p���[���[���Ȃ�
	else if (coreColorPow_.IsZero())
	{
		// �X�C�b�`�I�t
		isSwitchCoreColorPower_ = true;
	}
}

#pragma endregion

#pragma region Drawer

void TowerDrawer::Initialize(YMath::Matrix4* pParent, const Mode& mode)
{
	// null�`�F�b�N
	assert(pParent);

	// �I�u�W�F�N�g���� + �e�s��}��
	core_.reset(new Transform());
	core_->Initialize({});
	core_->parent_ = pParent;

	// �I�u�W�F�N�g���� + �e�s��}�� (�p�[�c�̐�)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		// �F�|�C���^
		Color* pColor = nullptr;

		// �}�e���A���|�C���^
		Material* pMate = nullptr;

		// �j�Ȃ�
		if (i == CoreIdx)
		{
			// ���ʂ̃u���b�N�Ȃ�
			if (mode == Mode::Normal)
			{
				// ���ʐF
				pColor = sCoreColor_[NormalIdx].get();
			}
			// �ԂȂ�
			else if (mode == Mode::Red)
			{
				// �ԐF
				pColor = sCoreColor_[RedIdx].get();
			}

			// �f�t�H���g�̃}�e���A��
			pMate = sCoreMate_.get();
		}
		// �k�Ȃ�
		else if (i == ShellIdx)
		{
			// �}�e���A���|�C���^
			pMate = spMate_;
		}

		// ����
		modelObjs_[i].reset(ModelObject::Create({}, spVP_, pColor, nullptr, pMate));

		// �e�s��}��
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// ���Z�b�g
	Reset(mode);
}

void TowerDrawer::Reset(const Mode& mode)
{
	// �j
	core_->Initialize({});

	// �I�u�W�F�N�g������(�p�[�c�̐�)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->Initialize({});
	}

	// ��Ԗ��ɐF�ς���
	if (mode == Mode::Normal)
	{
		modelObjs_[CoreIdx]->SetColor(sCoreColor_[NormalIdx].get());
	}
	else if (mode == Mode::Red)
	{
		modelObjs_[CoreIdx]->SetColor(sCoreColor_[RedIdx].get());
	}

	// ���
	mode_ = mode;

	// ��Ԕԍ�
	modeIdx_ = static_cast<size_t>(mode);
}

void TowerDrawer::Update()
{
	// �s��X�V (�e)
	core_->UpdateMatrix();

	// �s��X�V (�q)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix();
	}
}

void TowerDrawer::Draw()
{
	// �`��
	for (size_t i = 0; i < spModels_.size(); i++)
	{
		spModels_[modeIdx_][i]->Draw(modelObjs_[i].get());
	}
}

#pragma endregion
#include "TowerDrawer.h"
#include "CalcTransform.h"
#include "CoreColor.h"
#include "DrawerConfig.h"
#include <cassert>

#pragma region ���O���

using std::array;
using std::unique_ptr;

using YGame::Transform;
using YGame::Model;
using YGame::CBColor;
using YGame::CBMaterial;

using YMath::Ease;
using YMath::Power;
using YMath::Vector3;
using YMath::Vector4;

using namespace DrawerConfig::Tower;

#pragma endregion

#pragma region Static

array<array<Model*, TowerDrawerCommon::PartsNum_>, IMode::sTypeNum_> TowerDrawerCommon::spModels_ =
{
	nullptr, nullptr, 
	nullptr, nullptr, 
};
YGame::ViewProjection* TowerDrawerCommon::spVP_ = nullptr;
CBMaterial* TowerDrawerCommon::spMate_ = nullptr;

#pragma endregion

#pragma region �C���f�b�N�X

static const size_t CoreIdx = static_cast<size_t>(TowerDrawerCommon::Parts::Core); // �j
static const size_t ShellIdx = static_cast<size_t>(TowerDrawerCommon::Parts::Shell); // �k

#pragma endregion

#pragma region Common

void TowerDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP, YGame::CBMaterial* pMate)
{
	// null�`�F�b�N
	assert(pVP);
	assert(pMate);
	// ���
	spVP_ = pVP;
	spMate_ = pMate;

	// ----- ���f���ǂݍ��� ----- //

	// �ʏ�
	spModels_[IMode::sNormalIdx][CoreIdx] = Model::LoadObj("tower/normal/core", true); // �j
	spModels_[IMode::sNormalIdx][ShellIdx] = Model::LoadObj("tower/normal/shell", true); // �k

	// ��
	spModels_[IMode::sMovableIdx][CoreIdx] = Model::LoadObj("tower/red/core", true); // �j
	spModels_[IMode::sMovableIdx][ShellIdx] = Model::LoadObj("tower/red/shell", true); // �k
}

#pragma endregion

#pragma region Drawer

void TowerDrawer::Initialize(YMath::Matrix4* pParent, const IMode::Type& modeType)
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
		// ����
		modelObjs_[i].reset(Model::Object::Create({}, spVP_, nullptr, nullptr, spMate_, nullptr));

		// �e�s��}��
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// ���Z�b�g
	Reset(modeType);
}

void TowerDrawer::Reset(const IMode::Type& modeType)
{
	// �j
	core_->Initialize({});

	// ��ꃂ�[�h������
	IMode::ChangeType(modeType);

	// �I�u�W�F�N�g������(�p�[�c�̐�)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->Initialize({});
	}

	// �j�̐F�ƃ}�e���A���ݒ�
	modelObjs_[CoreIdx]->SetColor(CoreColor::ColorPtr(CurrentTypeIndex()));
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

void TowerDrawer::Draw(const YGame::DrawLocation& location)
{
	// �`��
	for (size_t i = 0; i < spModels_.size(); i++)
	{
		spModels_[CurrentTypeIndex()][i]->SetDrawCommand(modelObjs_[i].get(), location);
	}
}

#pragma endregion
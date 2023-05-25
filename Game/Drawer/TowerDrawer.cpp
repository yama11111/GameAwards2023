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
using YGame::CBLightGroup;

using YMath::Ease;
using YMath::Power;
using YMath::Vector3;
using YMath::Vector4;

using namespace DrawerConfig::Tower;

#pragma endregion

#pragma region Static

array<array<Model*, TowerDrawerCommon::sPartsNum_>, TowerDrawerCommon::sTypeNum_> TowerDrawerCommon::spModels_ =
{
	nullptr, nullptr, 
	nullptr, nullptr,
};
CBMaterial* TowerDrawerCommon::spUniqueMate_ = nullptr;
CBLightGroup* TowerDrawerCommon::spUniqueLight_ = nullptr;

#pragma endregion

#pragma region �C���f�b�N�X

static const size_t CoreIdx = static_cast<size_t>(TowerDrawerCommon::Parts::eCore); // �j
static const size_t ShellIdx = static_cast<size_t>(TowerDrawerCommon::Parts::eShell); // �k

static const size_t BlackIdx = static_cast<size_t>(TowerDrawerCommon::Type::eBlack); // ��
static const size_t WhiteIdx = static_cast<size_t>(TowerDrawerCommon::Type::eWhite); // ��

#pragma endregion

#pragma region Common

void TowerDrawerCommon::StaticInitialize(
	YGame::CBMaterial* pMate,
	YGame::CBLightGroup* pLight)
{
	// null�`�F�b�N
	assert(pMate);
	assert(pLight);
	// ���
	spUniqueMate_ = pMate;
	spUniqueLight_ = pLight;

	// ----- ���f���ǂݍ��� ----- //

	// �ʏ�
	spModels_[BlackIdx][CoreIdx] = Model::LoadObj("tower/black/core", true); // �j
	spModels_[BlackIdx][ShellIdx] = Model::LoadObj("tower/black/shell", true); // �k

	// ��
	spModels_[WhiteIdx][CoreIdx] = Model::LoadObj("tower/white/core", true); // �j
	spModels_[WhiteIdx][ShellIdx] = Model::LoadObj("tower/white/shell", true); // �k
}

#pragma endregion

#pragma region Drawer

void TowerDrawer::Initialize(Transform* pParent, const Type& type)
{
	// ���N���X������
	IDrawer::Initialze(pParent);

	// �I�u�W�F�N�g���� + �e�s��}�� (�p�[�c�̐�)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		CBMaterial* pMate = nullptr;

		if (i == CoreIdx) { pMate = CoreColor::MaterialPtr(); }
		else if (i == ShellIdx) { pMate = spUniqueMate_; }

		// ����
		modelObjs_[i].reset(Model::Object::Create(Transform::Status::Default(), spVP_, nullptr, pMate, spUniqueLight_));

		// �e�s��}��
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// ���Z�b�g
	Reset(type);
}

void TowerDrawer::Reset(const Type& type)
{
	// ���Z�b�g
	IDrawer::Reset();

	// ���
	type_ = type;

	// �C���f�b�N�X���v�Z
	typeIndex_ = static_cast<size_t>(type);

	// �j�̐F�ƃ}�e���A���ݒ�
	CBColor* pColor = nullptr;

	if (type == Type::eBlack)
	{
		pColor = CoreColor::ColorPtr(CoreColor::ColorType::eGray);
	}
	else if (type == Type::eWhite)
	{
		pColor = CoreColor::ColorPtr(CoreColor::ColorType::eBlue);
	}

	modelObjs_[CoreIdx]->SetColor(pColor);

	// �I�u�W�F�N�g������(�p�[�c�̐�)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->Initialize();
	}
}

void TowerDrawer::Update()
{
	// ���N���X�X�V 
	IDrawer::Update({});

	// �s��X�V (�q)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix();
	}
}

void TowerDrawer::Draw(const YGame::DrawLocation& location)
{
	// ���f���̐��`��
	for (size_t i = 0; i < spModels_[typeIndex_].size(); i++)
	{
		spModels_[typeIndex_][i]->SetDrawCommand(modelObjs_[i].get(), location);
	}
}

#pragma endregion
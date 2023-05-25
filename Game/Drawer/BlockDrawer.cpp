#include "BlockDrawer.h"
#include "CalcTransform.h"
#include "DrawerConfig.h"
#include "CoreColor.h"
#include <cassert>

#pragma region ���O���

using std::array;
using std::unique_ptr;

using YGame::Transform;
using YGame::Model;
using YGame::CBColor;
using YGame::CBMaterial;

using YGame::SlimeActor;

using YMath::Ease;
using YMath::Power;
using YMath::Vector3;
using YMath::Vector4;

using namespace DrawerConfig::Block;

#pragma endregion

#pragma region Static

array<array<Model*, BlockDrawerCommon::sPartsNum_>, BlockDrawerCommon::sTypeNum_> BlockDrawerCommon::spModels_ =
{
	nullptr, nullptr,
	nullptr, nullptr,
};

#pragma endregion

#pragma region �C���f�b�N�X

static const size_t CoreIdx = static_cast<size_t>(BlockDrawerCommon::Parts::eCore); // �j
static const size_t ShellIdx = static_cast<size_t>(BlockDrawerCommon::Parts::eShell); // �k

static const size_t BlackIdx = static_cast<size_t>(BlockDrawerCommon::Type::eBlack); // ��
static const size_t WhiteIdx = static_cast<size_t>(BlockDrawerCommon::Type::eWhite); // ��

#pragma endregion

#pragma region Common

void BlockDrawerCommon::StaticInitialize()
{
	// ----- ���f���ǂݍ��� ----- //

	// �u���b�N (��)
	spModels_[BlackIdx][CoreIdx] = Model::LoadObj("block/black/core", true); // �j
	spModels_[BlackIdx][ShellIdx] = Model::LoadObj("block/black/shell", true); // �k

	// �u���b�N (��)
	spModels_[WhiteIdx][CoreIdx] = Model::LoadObj("block/white/core", true); // �j
	spModels_[WhiteIdx][ShellIdx] = Model::LoadObj("block/white/shell", true); // �k
}

#pragma endregion

#pragma region Drawer

void BlockDrawer::Initialize(Transform* pParent, const Type& type)
{
	// ���N���X������
	IDrawer::Initialze(pParent);

	// �I�u�W�F�N�g���� + �e�s��}�� (�p�[�c�̐�)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		// ����
		modelObjs_[i].reset(Model::Object::Create(Transform::Status::Default(), spVP_));

		// �e�s��}��
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// ���Z�b�g
	Reset(type);
}

void BlockDrawer::Reset(const Type& type)
{
	// ���Z�b�g
	IDrawer::Reset();

	// ���
	type_ = type;

	// �C���f�b�N�X���v�Z
	typeIndex_ = static_cast<size_t>(type);

	// �j�̐F�ƃ}�e���A���ݒ�
	CBColor * pColor = nullptr;
	CBMaterial* pMaterial = nullptr;

	if (type == Type::eBlack)
	{
		pColor = CoreColor::ColorPtr(CoreColor::ColorType::eGray);
		pMaterial = CoreColor::MaterialPtr();
	}
	else if (type == Type::eWhite)
	{
		pColor = CoreColor::ColorPtr(CoreColor::ColorType::eBlue);
		pMaterial = CoreColor::MaterialPtr();
	}

	modelObjs_[CoreIdx]->SetColor(pColor);
	modelObjs_[CoreIdx]->SetMaterial(pMaterial);

	// �I�u�W�F�N�g������(�p�[�c�̐�)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->Initialize();
	}
}

void BlockDrawer::Update()
{
	// ���N���X�X�V 
	IDrawer::Update({});

	// �s��X�V (�q)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix();
	}
}

void BlockDrawer::Draw()
{
	// ���f���̐��`��
	for (size_t i = 0; i < spModels_[typeIndex_].size(); i++)
	{
		spModels_[typeIndex_][i]->SetDrawCommand(modelObjs_[i].get(), YGame::DrawLocation::Center);
	}
}

#pragma endregion
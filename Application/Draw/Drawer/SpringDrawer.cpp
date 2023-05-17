#include "SpringDrawer.h"
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

array<array<Model*, SpringDrawerCommon::sPartsNum_>, SpringDrawerCommon::sTypeNum_> SpringDrawerCommon::spModels_ =
{
	nullptr, nullptr,
	//nullptr, nullptr,
};

#pragma endregion

#pragma region �C���f�b�N�X

static const size_t CoreIdx = static_cast<size_t>(SpringDrawerCommon::Parts::eCore); // �j
static const size_t ShellIdx = static_cast<size_t>(SpringDrawerCommon::Parts::eShell); // �k

static const size_t GreenIdx = static_cast<size_t>(SpringDrawerCommon::Type::eGreen); // ��
//static const size_t WhiteIdx = static_cast<size_t>(SpringDrawerCommon::Type::); // ��

#pragma endregion

#pragma region Common

void SpringDrawerCommon::StaticInitialize()
{
	// ----- ���f���ǂݍ��� ----- //

	// �u���b�N (��)
	spModels_[GreenIdx][CoreIdx] = Model::LoadObj("junction/core", true); // �j
	spModels_[GreenIdx][ShellIdx] = Model::LoadObj("junction/shell", true); // �k
}

#pragma endregion

#pragma region Drawer

void SpringDrawer::Initialize(Transform* pParent, const Type& type)
{
	// ���N���X������
	IDrawer::Initialze(pParent, Idle::IntervalTime);

	// �I�u�W�F�N�g���� + �e�s��}�� (�p�[�c�̐�)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		// ����
		modelObjs_[i].reset(Model::Object::Create({}, spVP_, nullptr, nullptr, nullptr, nullptr));

		// �e�s��}��
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// ���Z�b�g
	Reset(type);
}

void SpringDrawer::Reset(const Type& type)
{
	// ���Z�b�g
	IDrawer::Reset();

	// ���
	type_ = type;

	// �C���f�b�N�X���v�Z
	typeIndex_ = static_cast<size_t>(type);

	// �j�̐F�ƃ}�e���A���ݒ�
	CBColor* pColor = nullptr;
	CBMaterial* pMaterial = nullptr;

	if (type == Type::eGreen)
	{
		pColor = CoreColor::ColorPtr(CoreColor::ColorType::eGreen);
		pMaterial = CoreColor::MaterialPtr();
	}
	//else if (type == Type::eRed)
	//{
	//	pColor = CoreColor::ColorPtr(CoreColor::ColorType::eRed);
	//	pMaterial = CoreColor::MaterialPtr();
	//}

	modelObjs_[CoreIdx]->SetColor(pColor);
	modelObjs_[CoreIdx]->SetMaterial(pMaterial);
}

void SpringDrawer::Update()
{
	// ���N���X�X�V 
	IDrawer::Update({});

	// �s��X�V (�q)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix();
	}
}

void SpringDrawer::Draw()
{
	// ���f���̐��`��
	for (size_t i = 0; i < spModels_[typeIndex_].size(); i++)
	{
		spModels_[typeIndex_][i]->SetDrawCommand(modelObjs_[i].get(), YGame::DrawLocation::Center);
	}
}

#pragma endregion
#include "FilterDrawer.h"
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

using YGame::SlimeActor;

using YMath::Vector3;
using YMath::Vector4;

using namespace DrawerConfig::Filter;

#pragma endregion

#pragma region Static

// �ÓI ���f���z�� ������
array<Model*, FilterDrawerCommon::PartsNum_> FilterDrawerCommon::spModels_ =
{
	nullptr, nullptr, 
};

#pragma endregion

// �C���f�b�N�X
static const size_t MonitorIdx = static_cast<size_t>(FilterDrawerCommon::Parts::Monitor); // ���j�^�[

void FilterDrawerCommon::StaticInitialize()
{
	// ----- ���f���ǂݍ��� ----- //

	// ��
	spModels_[MonitorIdx] = Model::CreateCube();
	spModels_[1] = Model::CreateCube();
}


void FilterDrawer::Initialize(YGame::Transform* pParent)
{
	// ���N���X������
	IDrawer::Initialze(pParent, Mode::Red, Idle::IntervalTime);

	// �F����
	color_.reset(Color::Create());

	// �I�u�W�F�N�g���� + �e�s��}�� (�p�[�c�̐�)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		// ����
		modelObjs_[i].reset(ModelObject::Create({}, spVP_, color_.get(), nullptr, nullptr));
		
		// �e�s����
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// ���Z�b�g
	Reset();
}

void FilterDrawer::Reset()
{
	// ���Z�b�g
	IDrawer::Reset(Mode::Red);

	// ----- ���f���p�I�u�W�F�N�g������ ----- //
	
	// ���j�^�[
	modelObjs_[MonitorIdx]->Initialize(
		{
			{0.0f,0.0f,0.0f},
			{},
			{1.0f,1.0f,1.0f},
		}
	);

	// �F������
	color_->SetRGBA(DefColor);
}

void FilterDrawer::Update()
{
	// ���N���X�X�V 
	IDrawer::Update({});

	// �s��X�V (�q)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix();
	}
}

void FilterDrawer::Draw()
{
	// �`��
	spModels_[MonitorIdx]->Draw(modelObjs_[MonitorIdx].get());
}

void FilterDrawer::IdleAnimation()
{
}

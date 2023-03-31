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
using namespace DrawerConfig::Filter;

#pragma endregion

#pragma region Static

// �C���f�b�N�X
static const size_t MonitorIdx = static_cast<size_t>(FilterDrawerCommon::Parts::Monitor); // ���j�^�[


// �ÓI ���f���z�� ������
array<unique_ptr<Model>, FilterDrawerCommon::PartsNum_> FilterDrawerCommon::sModels_ =
{
	nullptr, nullptr, 
};

// �ÓI�r���[�v���W�F�N�V����
YGame::ViewProjection* FilterDrawerCommon::spVP_ = nullptr;

void FilterDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP)
{
	// null�`�F�b�N
	assert(pVP);
	// ���
	spVP_ = pVP;

	// ----- ���f���ǂݍ��� ----- //

	// ��
	sModels_[MonitorIdx].reset(Model::Create());
	sModels_[1].reset(Model::Create());
}

#pragma endregion

void FilterDrawer::Initialize(YGame::Transform* pParent)
{
	// ���N���X������
	IDrawer::Initialze(pParent, Mode::Red, Idle::IntervalTime);

	// �I�u�W�F�N�g���� + �e�s��}�� (�p�[�c�̐�)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i].reset(ModelObject::Create({}, spVP_, color_.get(), nullptr));
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
			{0.0f,0.0f,-4.0f},
			{},
			{1.0f,1.0f,0.0001f},
		}
	);

	color_->SetRGBA({ 1.0f,0.0f,0.0f,0.25f });

	// �t�B���^�[�ƏՓ˂��Ă��邩������
	isCollPlayer_ = false;
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


	// �t�B���^�[���� && �v���C���[�ƏՓ˂��Ă�����
	if (*spIsPlayer_ == false && isCollPlayer_)
	{
		// �F��ς���
		color_->SetRGB(BadColor);
	}
	// �Ⴄ�Ȃ�
	else
	{
		// �f�t�H���g�̐F��
		color_->SetRGB({ 1.0f,0.0f,0.0f });
	}
}

void FilterDrawer::Draw()
{
	// �`��
	sModels_[MonitorIdx]->Draw(modelObjs_[MonitorIdx].get());
}

void FilterDrawer::IdleAnimation()
{
}

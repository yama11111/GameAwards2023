#include "BlockDrawer.h"
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
using namespace DrawerConfig::Block;

#pragma endregion

#pragma region Static

// �C���f�b�N�X
static const size_t NormalIdx = static_cast<size_t>(IDrawer::Mode::Normal); // �ʏ�
static const size_t RedIdx = static_cast<size_t>(IDrawer::Mode::Red); // ��
static const size_t InvisibleIdx = static_cast<size_t>(IDrawer::Mode::Invisivle); // ����

static const size_t CubeIdx = static_cast<size_t>(BlockDrawerCommon::Parts::Cube); // ��


// �ÓI ���f���z�� ������
array<unique_ptr<Model>, BlockDrawerCommon::PartsNum_> BlockDrawerCommon::sModels_ =
{
	nullptr, nullptr,
};

// �ÓI�r���[�v���W�F�N�V����
YGame::ViewProjection* BlockDrawerCommon::spVP_ = nullptr;

void BlockDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP)
{
	// null�`�F�b�N
	assert(pVP);
	// ���
	spVP_ = pVP;

	// ----- ���f���ǂݍ��� ----- //

	sModels_[CubeIdx].reset(Model::Create("blockInvisible.png")); // ������
	sModels_[1].reset(Model::Create());
}

#pragma endregion

void BlockDrawer::Initialize(YGame::Transform* pParent, const Mode& mode)
{
	// ���N���X������
	IDrawer::Initialze(pParent, mode, Idle::IntervalTime);

	// �F����
	color_.reset(Color::Create());

	// �I�u�W�F�N�g���� + �e�s��}�� (�p�[�c�̐�)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		// ����
		modelObjs_[i].reset(ModelObject::Create({}, spVP_, color_.get(), nullptr));
		
		// �e�s��}��
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// ���Z�b�g
	Reset(mode);
}

void BlockDrawer::Reset(const Mode& mode)
{
	// ���Z�b�g
	IDrawer::Reset(mode);

	// ���f���p�I�u�W�F�N�g������
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->Initialize({});
	}

	// �F������
	color_->Initialize(DefColor::Red);

	// ��Ԃ�ۑ�
	save_ = current_;

	// ----- �A�j���[�V���� ----- //

	// �t�F�[�h�C���t���O
	isFadeIn_ = false;
	// �t�F�[�h�C���p�^�C�}�[
	fadeInTim_.Initialize(0);
	// �t�F�[�h�C���p�F�C�[�W���O
	fadeInColorEas_.Initialize(DefColor::Invisible, DefColor::Red, FadeIn::Exponent);
}

void BlockDrawer::ResetAnimation()
{
	// �u���u���A�j���[�V����������
	SlimeActor::Initialize();

	// �������[�V�����^�C�}�[���Z�b�g
	idleTim_.Reset(true);

	// �t�F�[�h�C���p�^�C�}�[���Z�b�g
	fadeInTim_.Initialize(0);
}

void BlockDrawer::Update()
{
	// ���N���X�X�V 
	IDrawer::Update({});

	// �t�F�[�h�C�����Ȃ�
	if (isFadeIn_)
	{
		// �t�F�[�h�C���p�^�C�}�[�X�V
		fadeInTim_.Update();
		// �t�F�[�h�C���p�̐F�v�Z
		Vector4 fadeInColor = fadeInColorEas_.In(fadeInTim_.Ratio());

		// ���
		color_->SetRGBA(fadeInColor);
	}
	else
	{
		// ��Ԃ�߂�
		current_ = save_;
	}


	// �s��X�V (�q)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix();
	}
}

void BlockDrawer::Draw()
{
	// �`��
	sModels_[CubeIdx]->Draw(modelObjs_[CubeIdx].get());
}

void BlockDrawer::FadeInAnimation(const unsigned int frame)
{
	// �A�j���[�V�������Z�b�g
	ResetAnimation();

	// ��Ԃ�ۑ�
	save_ = current_;

	// ��Ԃ𓧖���
	current_ = Mode::Invisivle;

	// �t�F�[�h�C���^�C�}�[������ + �J�n
	fadeInTim_.Initialize(frame);
	fadeInTim_.SetActive(true);

	// �t�F�[�h�C���A�j���[�V�����J�n
	isFadeIn_ = true;
}

void BlockDrawer::IdleAnimation()
{
}

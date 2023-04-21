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
array<Model*, BlockDrawerCommon::PartsNum_> BlockDrawerCommon::spModels_ =
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

	spModels_[CubeIdx] = Model::CreateCube("blockInvisible.png"); // ������
	spModels_[1] = Model::CreateCube();
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

	// ��Ԗ��ɐF������
	if (mode == Mode::Normal)
	{
		color_->Initialize(DefColor::Normal);
	}
	else if(mode == Mode::Red)
	{
		color_->Initialize(DefColor::Red);
	}

	// ----- �A�j���[�V���� ----- //

	// �擾�\��Ԃ�
	isRetrievable_ = false;

	// �O�͎擾�\��Ԃ�������
	isElderRetrievable_ = false;

	// �擾�\�A�j���[�V�����p�^�C�}�[
	RetrievableTim_.Initialize(Retrievable::Frame);


	// �u���Ȃ���Ԃ�
	isCanPlace_ = true;

	// �O�͒u���Ȃ���Ԃ�������
	isElderCanPlace_ = false;

	// �u���Ȃ���ԗp�h��
	notPlaceShake_.Initialize();
}

void BlockDrawer::Update()
{
	// �u���Ȃ��������p�V�F�C�N�X�V
	notPlaceShake_.Update();

	// ���N���X�X�V 
	IDrawer::Update({ notPlaceShake_.Value() });

	// �擾�\�A�j���[�V����
	RetrievableAnimation();
	
	// �u���Ȃ���ԃA�j���[�V����
	NotPlaceAnimation();

	// �s��X�V (�q)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix();
	}
}

void BlockDrawer::Draw()
{
	// �`��
	spModels_[CubeIdx]->Draw(modelObjs_[CubeIdx].get());
}

void BlockDrawer::PlaceAnimation()
{
	// �p�[�e�B�N������
	spParticleMan_->EmitPlaceGridBlock(Place::Frame, core_->parent_, Place::Color);
}

void BlockDrawer::CanNotPlaceAnimation()
{
	// �h��J�n
	notPlaceShake_.Activate(Place::NotShake::Swing, Place::NotShake::Dekey, Place::NotShake::Place);
}

void BlockDrawer::RetrievableAnimation()
{
	// �擾�\���ȑO�ƈႤ�Ȃ�
	if (isRetrievable_ != isElderRetrievable_)
	{
		// �擾�\�A�j���[�V�����p�^�C�}�[���Z�b�g
		RetrievableTim_.Reset(false);

		// �擾�\�Ȃ�
		if (isRetrievable_)
		{
			// �p�[�e�B�N������
			spParticleMan_->EmitIlluminationGridBlock(Retrievable::Frame, core_->parent_, Retrievable::Color);
		}
	}

	// �t���O�ۑ�
	isElderRetrievable_ = isRetrievable_;

	// �擾�\��Ԃ���Ȃ��Ȃ�e��
	if (isRetrievable_ == false) { return; }

	// �擾�\�Ȃ�^�C�}�[�X�^�[�g
	RetrievableTim_.SetActive(isRetrievable_);

	// �擾�\�^�C�}�[�X�V
	RetrievableTim_.Update();

	// �擾�\�^�C�}�[���I��������
	if (RetrievableTim_.IsEnd())
	{
		// �p�[�e�B�N������
		spParticleMan_->EmitIlluminationGridBlock(Retrievable::Frame, core_->parent_, Retrievable::Color);

		// �^�C�}�[������
		RetrievableTim_.Reset(isRetrievable_);
	}
}

void BlockDrawer::NotPlaceAnimation()
{
	// �u���邩�ȑO�ƈႤ�Ȃ�
	if (isCanPlace_ != isElderCanPlace_)
	{
		// ��Ԗ��ɐF������
		if (current_ == Mode::Normal)
		{
			color_->SetRGBA(DefColor::Normal);
		}
		else if (current_ == Mode::Red)
		{
			color_->SetRGBA(DefColor::Red);
		}
	}

	// �t���O�ۑ�
	isElderCanPlace_ = isCanPlace_;

	// �u����Ȃ�e��
	if (isCanPlace_) { return; }

	// �u���Ȃ��F�ɂ���
	color_->SetRGBA(DefColor::Invisible);
}

void BlockDrawer::IdleAnimation()
{
}

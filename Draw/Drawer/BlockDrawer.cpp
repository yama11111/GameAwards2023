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
using YGame::Material;

using YGame::SlimeActor;

using YMath::Ease;
using YMath::Power;
using YMath::Vector3;
using YMath::Vector4;

using namespace DrawerConfig::Block;

#pragma endregion

#pragma region Static

array<array<Model*, BlockDrawerCommon::PartsNum_>, BlockDrawerCommon::ModeNum_> BlockDrawerCommon::spModels_ =
{
	nullptr, nullptr,
	nullptr, nullptr,
};
array<unique_ptr<Color>, BlockDrawerCommon::ModeNum_> BlockDrawerCommon::sCoreColor_;
unique_ptr<Material> BlockDrawerCommon::sCoreMate_;
Power BlockDrawerCommon::coreColorPow_;
bool BlockDrawerCommon::isSwitchCoreColorPower_ = false;
array<Ease<Vector4>, BlockDrawerCommon::ModeNum_> BlockDrawerCommon::coreColorEas_;

Model* BlockDrawerCommon::spGridModel_ = nullptr;
unique_ptr<Color> BlockDrawerCommon::sGridColor_;
unique_ptr<Material> BlockDrawerCommon::sGridMate_;
Ease<float> BlockDrawerCommon::catchGridScaleValueEas_;
Ease<float> BlockDrawerCommon::failToCatchGridScaleValueEas_;
Ease<float> BlockDrawerCommon::placeGridScaleValueEas_;
Ease<float> BlockDrawerCommon::failToPlaceGridScaleValueEas_;

#pragma endregion

#pragma region �C���f�b�N�X

static const size_t NormalIdx = static_cast<size_t>(IDrawer::Mode::Normal); // �ʏ�
static const size_t RedIdx = static_cast<size_t>(IDrawer::Mode::Red); // ��

static const size_t CoreIdx = static_cast<size_t>(BlockDrawerCommon::Parts::Core); // �j
static const size_t ShellIdx = static_cast<size_t>(BlockDrawerCommon::Parts::Shell); // �k

#pragma endregion

#pragma region Common

void BlockDrawerCommon::StaticInitialize()
{
	// ----- ���f���ǂݍ��� ----- //

	// �u���b�N (�ʏ�)
	spModels_[NormalIdx][CoreIdx] = Model::Load("block/normal/core", true); // �j
	spModels_[NormalIdx][ShellIdx] = Model::Load("block/normal/shell", true); // �k

	// �u���b�N (��)
	spModels_[RedIdx][CoreIdx] = Model::Load("block/red/core", true); // �j
	spModels_[RedIdx][ShellIdx] = Model::Load("block/red/shell", true); // �k

	// �O���b�h
	spGridModel_ = Model::Load("grid", true);

	// ---------- ���f�� ---------- //

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

	// --------- �O���b�h --------- //

	// �F
	sGridColor_.reset(Color::Create());

	// �}�e���A��
	sGridMate_.reset(Material::Create());


	// �擾���傫���C�[�W���O
	catchGridScaleValueEas_.Initialize(Catch::Success::Start, Catch::Success::End, Catch::Success::Exponent);

	// �擾���s���傫���C�[�W���O
	failToCatchGridScaleValueEas_.Initialize(Catch::Failure::Start, Catch::Failure::End, Catch::Failure::Exponent);

	// �ݒu���傫���C�[�W���O
	placeGridScaleValueEas_.Initialize(Place::Success::Start, Place::Success::End, Place::Success::Exponent);

	// �ݒu���s���傫���C�[�W���O
	failToPlaceGridScaleValueEas_.Initialize(Place::Failure::Start, Place::Failure::End, Place::Failure::Exponent);


	// ���Z�b�g
	StaticReset();
}

void BlockDrawerCommon::StaticReset()
{
	// �j�F�p�p���[
	coreColorPow_.Reset();

	// �j�F�p���[�X�C�b�`
	isSwitchCoreColorPower_ = true;
}

void BlockDrawerCommon::StaticUpdate()
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

void BlockDrawer::Initialize(Transform* pParent, const Mode& mode)
{
	// ���N���X������
	IDrawer::Initialze(pParent, mode, Idle::IntervalTime);

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

		// ����
		modelObjs_[i].reset(ModelObject::Create({}, spVP_, pColor, nullptr, pMate));

		// �e�s��}��
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// �O���b�h����
	gridObj_.reset(ModelObject::Create({}, spVP_, sGridColor_.get(), nullptr, sGridMate_.get()));

	// �e�s��}��
	gridObj_->parent_ = &core_->m_;

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

	// ��Ԗ��ɐF�ς���
	if (mode == Mode::Normal)
	{
		modelObjs_[CoreIdx]->SetColor(sCoreColor_[NormalIdx].get());
	}
	else if (mode == Mode::Red)
	{
		modelObjs_[CoreIdx]->SetColor(sCoreColor_[RedIdx].get());
	}

	// ----- �A�j���[�V���� ----- //

	// ���s�p�h��
	failureShake_.Initialize();


	// �O���b�h����t���O
	isActGrid_ = false;


	// �擾�\��Ԃ�
	isCanCatch_ = false;

	// �O�͎擾�\��Ԃ�������
	isElderCanCatch_ = false;


	// �擾�A�j���[�V���������邩
	isActCatchAnimition_ = false;

	// �擾���C�[�W���O�p�^�C�}�[
	catchGridTim_.Initialize(Catch::Success::Frame);

	// �擾���s�A�j���[�V���������邩
	isActFailToCatchAnimition_ = false;

	// �擾���C�[�W���O�p�^�C�}�[
	failToCatchGridTim_.Initialize(Catch::Failure::Frame);


	// �u���Ȃ���Ԃ�
	isCanPlace_ = true;

	// �O�͒u���Ȃ���Ԃ�������
	isElderCanPlace_ = false;


	// �ݒu�A�j���[�V���������邩
	isActPlaceAnimition_ = false;

	// �ݒu���C�[�W���O�p�^�C�}�[
	placeGridTim_.Initialize(Place::Success::Frame);
	// �ݒu���s�A�j���[�V���������邩
	isActFailToPlaceAnimition_ = false;

	// �ݒu���C�[�W���O�p�^�C�}�[
	failToPlaceGridTim_.Initialize(Place::Failure::Frame);

}

void BlockDrawer::Update()
{
	// ���s�p�V�F�C�N�X�V
	failureShake_.Update();

	// ���N���X�X�V 
	IDrawer::Update({ failureShake_.Value() });


	// �擾�\�A�j���[�V����
	CanCatchAnimation();

	// �u���Ȃ���ԃA�j���[�V����
	NotPlaceAnimation();

	// �s��X�V (�q)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix();
	}


	// �O���b�h����t���O��false�Ȃ�e��
	if (isActGrid_ == false) { return; }

	// �傫��
	float gridSca = 0.0f;

	// �擾�A�j���[�V����������Ȃ�
	if (isActCatchAnimition_)
	{
		// �^�C�}�[�X�V
		catchGridTim_.Update();

		// �C�[�Y�C��
		gridSca += catchGridScaleValueEas_.In(catchGridTim_.Ratio());

		// �^�C�}�[�I����
		if (catchGridTim_.IsEnd())
		{
			// �^�C�}�[���Z�b�g + �I��
			catchGridTim_.Reset(false);

			// �擾�A�j���[�V�����I��
			isActCatchAnimition_ = false;
		}
	}
	// �擾���s�A�j���[�V����������Ȃ�
	if (isActFailToCatchAnimition_)
	{
		// �^�C�}�[�X�V
		failToCatchGridTim_.Update();

		// �C�[�Y�A�E�g
		gridSca += failToCatchGridScaleValueEas_.Out(failToCatchGridTim_.Ratio());

		// �^�C�}�[�I����
		if (failToCatchGridTim_.IsEnd())
		{
			// �^�C�}�[���Z�b�g + �I��
			failToCatchGridTim_.Reset(false);

			// �擾���s�A�j���[�V�����I��
			isActFailToCatchAnimition_ = false;
		}
	}
	// �ݒu�A�j���[�V����������Ȃ�
	if (isActPlaceAnimition_)
	{
		// �^�C�}�[�X�V
		placeGridTim_.Update();

		// �C�[�Y�C��
		gridSca += placeGridScaleValueEas_.In(placeGridTim_.Ratio());

		// �^�C�}�[�I����
		if (placeGridTim_.IsEnd())
		{
			// �^�C�}�[���Z�b�g + �I��
			placeGridTim_.Reset(false);

			// �ݒu�A�j���[�V�����I��
			isActPlaceAnimition_ = false;
		}
	}
	// �ݒu���s�A�j���[�V����������Ȃ�
	if (isActFailToPlaceAnimition_)
	{
		// �^�C�}�[�X�V
		failToPlaceGridTim_.Update();

		// �C�[�Y�A�E�g
		gridSca += failToPlaceGridScaleValueEas_.Out(failToPlaceGridTim_.Ratio());

		// �^�C�}�[�I����
		if (failToPlaceGridTim_.IsEnd())
		{
			// �^�C�}�[���Z�b�g + �I��
			failToPlaceGridTim_.Reset(false);

			// �ݒu���s�A�j���[�V�����I��
			isActFailToPlaceAnimition_ = false;
		}
	}

	// �O���b�h�X�V
	gridObj_->UpdateMatrix({ {},{},Vector3(gridSca, gridSca, gridSca) });

	// �t���O���X�V (�S��false�Ȃ�~�߂�)
	isActGrid_ =
		isActCatchAnimition_ ||
		isActFailToCatchAnimition_ ||
		isActPlaceAnimition_ ||
		isActFailToPlaceAnimition_;
}

void BlockDrawer::Draw()
{
	// ���f���̐��`��
	for (size_t i = 0; i < spModels_.size(); i++)
	{
		spModels_[CurrentModeIndex()][i]->Draw(modelObjs_[i].get());
	}

	// �O���b�h����t���O��false�Ȃ�e��
	if (isActGrid_ == false) { return; }

	// �O���b�h�`��
	spGridModel_->Draw(gridObj_.get());
}

void BlockDrawer::CatchAnimation()
{
	// �O���b�h����
	isActGrid_ = true;

	// �擾�A�j���[�V�����J�n
	isActCatchAnimition_ = true;

	// �^�C�}�[���Z�b�g + �J�n
	catchGridTim_.Reset(true);
}

void BlockDrawer::FailToCatchAnimation()
{
	// �O���b�h����
	isActGrid_ = true;

	// �擾���s�A�j���[�V�����J�n
	isActFailToCatchAnimition_ = true;

	// �^�C�}�[���Z�b�g + �J�n
	failToCatchGridTim_.Reset(true);

	// �h��J�n
	failureShake_.Activate(Catch::Failure::Shake::Swing, Catch::Failure::Shake::Dekey, Catch::Failure::Shake::Place);
}

void BlockDrawer::PlaceAnimation()
{
	// �O���b�h����
	isActGrid_ = true;

	// �擾�A�j���[�V�����J�n
	isActPlaceAnimition_ = true;

	// �^�C�}�[���Z�b�g + �J�n
	placeGridTim_.Reset(true);
}

void BlockDrawer::FailToPlaceAnimation()
{
	// �O���b�h����
	isActGrid_ = true;

	// �擾���s�A�j���[�V�����J�n
	isActFailToPlaceAnimition_ = true;

	// �^�C�}�[���Z�b�g + �J�n
	failToPlaceGridTim_.Reset(true);

	// �h��J�n
	failureShake_.Activate(Place::Failure::Shake::Swing, Place::Failure::Shake::Dekey, Place::Failure::Shake::Place);
}

void BlockDrawer::CanCatchAnimation()
{
	//// �擾�\���ȑO�ƈႤ�Ȃ�
	//if (isCanCatch_ != isElderCanCatch_)
	//{
	//	// �擾�\�A�j���[�V�����p�^�C�}�[���Z�b�g
	//	RetrievableTim_.Reset(false);

	//	// �擾�\�Ȃ�
	//	if (isCanCatch_)
	//	{
	//		// �p�[�e�B�N������
	//		spParticleMan_->EmitIlluminationGridBlock(Retrievable::Frame, core_->parent_, Retrievable::Color);
	//	}
	//}

	//// �t���O�ۑ�
	//isElderCanCatch_ = isCanCatch_;

	//// �擾�\��Ԃ���Ȃ��Ȃ�e��
	//if (isCanCatch_ == false) { return; }

	//// �擾�\�Ȃ�^�C�}�[�X�^�[�g
	//RetrievableTim_.SetActive(isCanCatch_);

	//// �擾�\�^�C�}�[�X�V
	//RetrievableTim_.Update();

	//// �擾�\�^�C�}�[���I��������
	//if (RetrievableTim_.IsEnd())
	//{
	//	// �p�[�e�B�N������
	//	spParticleMan_->EmitIlluminationGridBlock(Retrievable::Frame, core_->parent_, Retrievable::Color);

	//	// �^�C�}�[������
	//	RetrievableTim_.Reset(isCanCatch_);
	//}
}

void BlockDrawer::NotPlaceAnimation()
{
	//// �u���邩�ȑO�ƈႤ�Ȃ�
	//if (isCanPlace_ != isElderCanPlace_)
	//{
	//	// ��Ԗ��ɐF������
	//	if (current_ == Mode::Normal)
	//	{
	//		color_->SetRGBA(DefColor::Normal);
	//	}
	//	else if (current_ == Mode::Red)
	//	{
	//		color_->SetRGBA(DefColor::Red);
	//	}
	//}

	//// �t���O�ۑ�
	//isElderCanPlace_ = isCanPlace_;

	//// �u����Ȃ�e��
	//if (isCanPlace_) { return; }

	//// �u���Ȃ��F�ɂ���
	//color_->SetRGBA(DefColor::Invisible);
}

void BlockDrawer::IdleAnimation()
{
}

#pragma endregion
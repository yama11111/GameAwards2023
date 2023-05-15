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

array<array<Model*, BlockDrawerCommon::PartsNum_>, IMode::sTypeNum_> BlockDrawerCommon::spModels_ =
{
	nullptr, nullptr,
	nullptr, nullptr,
};
unique_ptr<CBColor> BlockDrawerCommon::sFailShellColor_;

Model* BlockDrawerCommon::spGridModel_ = nullptr;
unique_ptr<CBColor> BlockDrawerCommon::sGridColor_;
unique_ptr<CBColor> BlockDrawerCommon::sFailGridColor_;
unique_ptr<CBMaterial> BlockDrawerCommon::sGridMate_;
Ease<float> BlockDrawerCommon::sCatchGridScaleValueEas_;
Ease<float> BlockDrawerCommon::sFailToCatchGridScaleValueEas_;
Ease<float> BlockDrawerCommon::sPlaceGridScaleValueEas_;
Ease<float> BlockDrawerCommon::sFailToPlaceGridScaleValueEas_;

#pragma endregion

#pragma region �C���f�b�N�X

static const size_t CoreIdx = static_cast<size_t>(BlockDrawerCommon::Parts::Core); // �j
static const size_t ShellIdx = static_cast<size_t>(BlockDrawerCommon::Parts::Shell); // �k

#pragma endregion

#pragma region Common

void BlockDrawerCommon::StaticInitialize()
{
	// ----- ���f���ǂݍ��� ----- //

	// �u���b�N (�ʏ�)
	spModels_[IMode::sNormalIdx][CoreIdx] = Model::LoadObj("block/normal/core", true); // �j
	spModels_[IMode::sNormalIdx][ShellIdx] = Model::LoadObj("block/normal/shell", true); // �k

	// �u���b�N (��)
	spModels_[IMode::sMovableIdx][CoreIdx] = Model::LoadObj("block/red/core", true); // �j
	spModels_[IMode::sMovableIdx][ShellIdx] = Model::LoadObj("block/red/shell", true); // �k

	// �O���b�h
	spGridModel_ = Model::LoadObj("grid", true);

	// ---------- �u���b�N ---------- //

	// �k���s�F
	sFailShellColor_.reset(CBColor::Create());
	sFailShellColor_->SetRGBA(ShellColor::Failure);
	sFailShellColor_->SetTexColorRateRGBA(ShellColor::OriginalRate);

	// --------- �O���b�h --------- //

	// �F
	sGridColor_.reset(CBColor::Create());
	sGridColor_->SetRGBA(GridColor::Success);

	// ���s�F
	sFailGridColor_.reset(CBColor::Create());
	sFailGridColor_->SetRGBA(GridColor::Failure);

	// �}�e���A��
	sGridMate_.reset(CBMaterial::Create());


	// �擾���傫���C�[�W���O
	sCatchGridScaleValueEas_.Initialize(Catch::Success::Start, Catch::Success::End, Catch::Success::Exponent);

	// �擾���s���傫���C�[�W���O
	sFailToCatchGridScaleValueEas_.Initialize(Catch::Failure::Start, Catch::Failure::End, Catch::Failure::Exponent);

	// �ݒu���傫���C�[�W���O
	sPlaceGridScaleValueEas_.Initialize(Place::Success::Start, Place::Success::End, Place::Success::Exponent);

	// �ݒu���s���傫���C�[�W���O
	sFailToPlaceGridScaleValueEas_.Initialize(Place::Failure::Start, Place::Failure::End, Place::Failure::Exponent);
}

#pragma endregion

#pragma region Drawer

void BlockDrawer::Initialize(Transform* pParent, const IMode::Type& modeType)
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

	// �O���b�h����
	gridObj_.reset(Model::Object::Create({}, spVP_, sGridColor_.get(), nullptr, sGridMate_.get(), nullptr));

	// �e�s��}��
	gridObj_->parent_ = &core_->m_;

	// ���Z�b�g
	Reset(modeType);
}

void BlockDrawer::Reset(const IMode::Type& modeType)
{
	// ���Z�b�g
	IDrawer::Reset();

	// ��ꃂ�[�h������
	IMode::ChangeType(modeType);

	// ���f���p�I�u�W�F�N�g������
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->Initialize({});
	}

	// �j�̐F�ƃ}�e���A���ݒ�
	modelObjs_[CoreIdx]->SetColor(CoreColor::ColorPtr(CurrentTypeIndex()));

	// �O���b�h
	gridObj_->Initialize({ {}, {}, {1.1f,1.1f,1.1f} });

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

		// �C�[�Y�A�E�g
		gridSca += sCatchGridScaleValueEas_.Out(catchGridTim_.Ratio());

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
		gridSca += sFailToCatchGridScaleValueEas_.Out(failToCatchGridTim_.Ratio());

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

		// �C�[�Y�A�E�g
		gridSca += sPlaceGridScaleValueEas_.Out(placeGridTim_.Ratio());

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
		gridSca += sFailToPlaceGridScaleValueEas_.Out(failToPlaceGridTim_.Ratio());

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

	// �t���O��false�Ȃ�
	if (isActGrid_ == false)
	{
		// �k�̐F��������
		modelObjs_[ShellIdx]->SetColor(nullptr);
	}
}

void BlockDrawer::Draw()
{
	// ���f���̐��`��
	for (size_t i = 0; i < spModels_.size(); i++)
	{
		spModels_[CurrentTypeIndex()][i]->SetDrawCommand(modelObjs_[i].get(), YGame::DrawLocation::Center);
	}

	// �O���b�h����t���O��false�Ȃ�e��
	if (isActGrid_ == false) { return; }

	// �O���b�h�`��
	spGridModel_->SetDrawCommand(gridObj_.get(), YGame::DrawLocation::Center);
}

void BlockDrawer::CatchAnimation()
{
	// �O���b�h����
	isActGrid_ = true;

	// �擾�A�j���[�V�����J�n
	isActCatchAnimition_ = true;

	// �^�C�}�[���Z�b�g + �J�n
	catchGridTim_.Reset(true);

	// �O���b�h�F�ݒ�
	gridObj_->SetColor(sGridColor_.get());
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

	// �O���b�h�F�ݒ�
	gridObj_->SetColor(sFailGridColor_.get());

	// �k�̐F�ݒ�
	modelObjs_[ShellIdx]->SetColor(sFailShellColor_.get());
}

void BlockDrawer::PlaceAnimation()
{
	// �O���b�h����
	isActGrid_ = true;

	// �擾�A�j���[�V�����J�n
	isActPlaceAnimition_ = true;

	// �^�C�}�[���Z�b�g + �J�n
	placeGridTim_.Reset(true);

	// �O���b�h�F�ݒ�
	gridObj_->SetColor(sGridColor_.get());
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

	// �O���b�h�F�ݒ�
	gridObj_->SetColor(sFailGridColor_.get());

	// �k�̐F�ݒ�
	modelObjs_[ShellIdx]->SetColor(sFailShellColor_.get());
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
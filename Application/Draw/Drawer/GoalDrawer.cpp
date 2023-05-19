#include "GoalDrawer.h"
#include "CalcTransform.h"
#include "DrawerConfig.h"
#include "CoreColor.h"
#include "DrawerHelper.h"
#include <cassert>

#pragma region ���O���

using std::array;
using std::unique_ptr;

using YGame::Transform;
using YGame::Model;
using YGame::CBColor;

using YGame::SlimeActor;

using YMath::Vector3;
using YMath::Vector4;

using namespace DrawerConfig::Goal;

#pragma endregion

#pragma region Static

array<Model*, GoalDrawerCommon::sPartsNum_> GoalDrawerCommon::spModels_ =
{
	nullptr, nullptr, nullptr, nullptr, nullptr,
};

#pragma endregion

#pragma region �C���f�b�N�X

static const size_t CoreIdx = static_cast<size_t>(GoalDrawerCommon::Parts::Core); // �j
static const size_t InsideIdx = static_cast<size_t>(GoalDrawerCommon::Parts::InsideCore); // ���g�j
static const size_t InsideCoreIdx = static_cast<size_t>(GoalDrawerCommon::Parts::Inside); // ���g
static const size_t OutsideIdx = static_cast<size_t>(GoalDrawerCommon::Parts::OutsideCore); // �O�g�j
static const size_t OutsideCoreIdx = static_cast<size_t>(GoalDrawerCommon::Parts::Outside); // �O�g

#pragma endregion

#pragma region Common

void GoalDrawerCommon::StaticInitialize()
{
	// ----- ���f���ǂݍ��� ----- //

	spModels_[CoreIdx] = Model::LoadObj("goal/core", true); // �j
	spModels_[InsideIdx] = Model::LoadObj("goal/inside", true); // ���g�j
	spModels_[InsideCoreIdx] = Model::LoadObj("goal/insideCore", true); // ���g
	spModels_[OutsideIdx] = Model::LoadObj("goal/outside", true); // �O�g�j
	spModels_[OutsideCoreIdx] = Model::LoadObj("goal/outsideCore", true); // �O�g
}

#pragma endregion

#pragma region Drawer

void GoalDrawer::Initialize(YGame::Transform* pParent)
{
	// ���N���X������
	IDrawer::Initialze(pParent);

	// �I�u�W�F�N�g���� + �e�s��}�� (�p�[�c�̐�)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i].reset(Model::Object::Create(Transform::Status::Default(), spVP_, nullptr, spMate_));
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// �����]�^�C�}�[
	bindRotaTim_.Initialize(BindRota::Frame);

	// �����] (��)
	inBindRotaEas_.Initialize(BindRota::Inside::Start, BindRota::Inside::End, BindRota::Exponent);
	
	// �����] (�O)
	outBindRotaEas_.Initialize(BindRota::Outside::Start, BindRota::Outside::End, BindRota::Exponent);


	// ���O�C���^�C�}�[
	loginTim_.Initialize(Login::Frame);


	// �n�b�L���O��]�^�C�}�[
	hackRotaTim_.Initialize(HackRota::Frame);


	// �N���A��]�^�C�}�[
	clearRotaTim_.Initialize(ClearRota::Frame);

	// �N���A��] (��) �C�[�W���O
	inClearRotaEas_.Initialize({}, {}, 0.0f);

	// �N���A��] (�O) �C�[�W���O
	outClearRotaEas_.Initialize({}, {}, 0.0f);


	// ���Z�b�g
	Reset();
}

void GoalDrawer::Reset()
{
	// ���Z�b�g
	IDrawer::Reset();

	// ----- �I�u�W�F�N�g������ ----- //

	// �e�g�����X�t�H�[��������
	core_->Initialize({ {0.0f,0.0f,0.0f}, {0.0f,+PI / 6.0f,0.0f}, {1.0f,1.0f,1.0f} });

	// ���f�����Ƃɏ�����
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->Initialize({});
	}

	// �j�̐F�ݒ�
	modelObjs_[CoreIdx]->SetColor(CoreColor::ColorPtr(CoreColor::ColorType::eBlue));
	modelObjs_[InsideCoreIdx] ->SetColor(CoreColor::ColorPtr(CoreColor::ColorType::eBlue));
	modelObjs_[OutsideCoreIdx]->SetColor(CoreColor::ColorPtr(CoreColor::ColorType::eBlue));

	// ----- �A�j���[�V���������� ----- //
	
	// �N���A�t���O
	isClear_ = false;

	// �����]�^�C�}�[
	bindRotaTim_.Reset(true);
	

	// ���O�C���t���O
	isActLogin_ = false;

	// ���O�C���^�C�}�[
	loginTim_.Reset(false);


	// �n�b�L���O��]�t���O
	isActHackRota_ = false;

	// �n�b�L���O��]�^�C�}�[
	hackRotaTim_.Reset(false);

	// �n�b�L���O��]�X�s�[�h
	inHackRotaSpeed_ = outHackRotaSpeed_ = {};


	// �N���A��]�t���O
	isActClearRota_ = false;

	// �N���A��]�^�C�}�[
	clearRotaTim_.Reset(false);
}

void GoalDrawer::ActivateClearAnimation(const Vector3& playerPos)
{
	// �N���A
	isClear_ = true;

	// ���O�C���J�n
	StartLogin(playerPos);
}

void GoalDrawer::StartLogin(const Vector3& emitStartPos)
{
	// ���O�C���J�n
	isActLogin_ = true;

	// �^�C�}�[���Z�b�g + �J�n
	loginTim_.Reset(true);

	// �����[������
	spParticleMan_->EmitRelayBug(
		Login::RelayBug::Num,
		Login::RelayBug::StartToRelayFrame, Login::RelayBug::RelayToEndFrame,
		emitStartPos, pParent_->pos_,
		Login::RelayBug::RelayRange, 
		Login::RelayBug::MinRota, Login::RelayBug::MaxRota, 
		Login::RelayBug::MinScale, Login::RelayBug::MaxScale, 
		Login::RelayBug::Color, 
		Login::RelayBug::Place,
		YGame::DrawLocation::Center);
}

void GoalDrawer::StartHackRota()
{
	// ��]�J�n
	isActHackRota_ = true;

	// �n�b�L���O��]�X�s�[�h������
	inHackRotaSpeed_ = outHackRotaSpeed_ = {};

	// �^�C�}�[���Z�b�g + �J�n
	hackRotaTim_.Reset(true);
}

void GoalDrawer::StartClearRota()
{
	// ��]�J�n
	isActClearRota_ = true;

	// �N���A��] (��) �C�[�W���O
	inClearRotaEas_.Initialize(modelObjs_[InsideCoreIdx]->rota_, {}, ClearRota::Exponent);

	// �N���A��] (�O) �C�[�W���O
	outClearRotaEas_.Initialize(modelObjs_[OutsideCoreIdx]->rota_, {}, ClearRota::Exponent);

	// �^�C�}�[���Z�b�g + �J�n
	clearRotaTim_.Reset(true);
}

void GoalDrawer::BindRotaAnimation()
{
	// �N���A�����Ȃ�e��
	if (isClear_) { return; }

	// �����]�^�C�}�[�X�V
	bindRotaTim_.Update();
	// �^�C�}�[�I��������
	if (bindRotaTim_.IsEnd())
	{
		// �^�C�}�[���Z�b�g
		bindRotaTim_.Reset(true);
	}

	// �����] (��)
	modelObjs_[InsideCoreIdx]->rota_ = inBindRotaEas_.In(bindRotaTim_.Ratio());
	modelObjs_[InsideIdx]->rota_ = inBindRotaEas_.In(bindRotaTim_.Ratio());
	// �����] (�O)
	modelObjs_[OutsideCoreIdx]->rota_ = outBindRotaEas_.In(bindRotaTim_.Ratio());
	modelObjs_[OutsideIdx]->rota_ = outBindRotaEas_.In(bindRotaTim_.Ratio());
}

void GoalDrawer::ClearAnimation()
{
	// �N���A���Ă��Ȃ��Ȃ�e��
	if (isClear_ == false) { return; }
	
	// ���O�C�����Ȃ�
	if (isActLogin_)
	{
		// �^�C�}�[�X�V
		loginTim_.Update();
		// �^�C�}�[�I��������
		if (loginTim_.IsEnd())
		{
			// �n�b�L���O��]�J�n
			StartHackRota();

			// �t���O��false��
			isActLogin_ = false;
		}
	}

	// �n�b�L���O��]���Ȃ�
	else if (isActHackRota_)
	{
		// �n�b�L���O��]�^�C�}�[�X�V
		hackRotaTim_.Update();
		// �^�C�}�[�I��������
		if (hackRotaTim_.IsEnd())
		{
			// �N���A��]�J�n
			StartClearRota();

			// �t���O��false��
			isActHackRota_ = false;
		}

		// �X�s�[�h����
		inHackRotaSpeed_ += HackRota::InAcceleration;
		outHackRotaSpeed_ += HackRota::OutAcceleration;

		// �n�b�L���O��] (��)
		modelObjs_[InsideCoreIdx]->rota_ += inHackRotaSpeed_;
		modelObjs_[InsideIdx]->rota_ += inHackRotaSpeed_;
		// �n�b�L���O��] (�O)
		modelObjs_[OutsideCoreIdx]->rota_ += outHackRotaSpeed_;
		modelObjs_[OutsideIdx]->rota_ += outHackRotaSpeed_;
	}

	// �N���A��]���Ȃ�
	else if (isActClearRota_)
	{
		// �N���A��]�^�C�}�[�X�V
		clearRotaTim_.Update();
		// �^�C�}�[�I��������
		if (clearRotaTim_.IsEnd())
		{
			// �`��N���X�N���A���o
			DrawerHelper::StaticClear();

			// �t���O��false��
			isActClearRota_ = false;
		}

		// �N���A��] (��)
		modelObjs_[InsideCoreIdx]->rota_ = inClearRotaEas_.Out(clearRotaTim_.Ratio());
		modelObjs_[InsideIdx]->rota_ = inClearRotaEas_.Out(clearRotaTim_.Ratio());
		// �N���A��] (�O)
		modelObjs_[OutsideCoreIdx]->rota_ = outClearRotaEas_.Out(clearRotaTim_.Ratio());
		modelObjs_[OutsideIdx]->rota_ = outClearRotaEas_.Out(clearRotaTim_.Ratio());
	}
}

void GoalDrawer::Update()
{
	// ���N���X�X�V 
	IDrawer::Update({});

	// �����]�A�j���[�V����
	BindRotaAnimation();

	// �N���A�A�j���[�V����
	ClearAnimation();

	// �s��X�V (�q)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix();
	}
}

void GoalDrawer::Draw()
{
	// �`��
	for (size_t i = 0; i < spModels_.size(); i++)
	{
		spModels_[i]->SetDrawCommand(modelObjs_[i].get(), YGame::DrawLocation::Center);
	}
}

#pragma endregion

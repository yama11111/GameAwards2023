#include "TitleDrawer.h"
#include "DrawerConfig.h"
#include <cassert>
#include <cmath>

#pragma region ���O���

using std::array;
using std::vector;
using std::unique_ptr;
using YGame::Transform;
using YGame::Sprite2D;
using YGame::Model;
using YGame::Texture;
using YGame::CBColor;
using YMath::Vector3;
using namespace DrawerConfig::Title;

#pragma endregion

#pragma region Static

YInput::Keys* TitleDrawerCommon::sKeys_ = nullptr;
Sprite2D* TitleDrawerCommon::spLogoSpr_ = nullptr;
Sprite2D* TitleDrawerCommon::spShadowSpr_ = nullptr;
Sprite2D* TitleDrawerCommon::spStartSpr_ = nullptr;
Sprite2D* TitleDrawerCommon::spExitSpr_ = nullptr;

#pragma endregion

#pragma region TitleDrawerCommon

void TitleDrawerCommon::StaticInitialize()
{
	// ���S
	spLogoSpr_	 = Sprite2D::Create({}, { Texture::Load("Title/logo.png") });

	// �e
	spShadowSpr_ = Sprite2D::Create({}, { Texture::Load("Title/shadow.png") });

	// �X�^�[�g
	spStartSpr_	 = Sprite2D::Create({}, { Texture::Load("Title/start.png") });
	
	// �I��
	spExitSpr_	 = Sprite2D::Create({}, { Texture::Load("Title/exit.png") });
}

#pragma endregion

#pragma region TitleDrawer

void TitleDrawer::Initialize()
{
	// �j
	core_.reset(new Transform());


	// ���S
	logoObj_.reset(Sprite2D::Object::Create());
	logoObj_->parent_ = &core_->m_;


	// �e
	shadowObj_.reset(Sprite2D::Object::Create());
	shadowObj_->parent_ = &core_->m_;
	

	// �w�i
	backObj_.reset(Sprite2D::Object::Create());
	backObj_->parent_ = &core_->m_;


	// �X�^�[�g�F
	startColor_.reset(CBColor::Create());
	
	// �X�^�[�g
	startObj_.reset(Sprite2D::Object::Create(Transform::Status::Default(), startColor_.get()));
	startObj_->parent_ = &core_->m_;


	// �I���F
	exitColor_.reset(CBColor::Create());
	
	// �I��
	exitObj_.reset(Sprite2D::Object::Create(Transform::Status::Default(), exitColor_.get()));
	exitObj_->parent_ = &core_->m_;


	// �C�[�W���O
	selectMoveXEas_.Initialize(+64.0f, 0.0f, 3.0f);
	selectScaleEas_.Initialize(-0.25f, 0.0f, 3.0f);

	// ���Z�b�g
	Reset();
}

void TitleDrawer::Reset()
{
	// �j
	core_->Initialize();

	// ���S
	logoObj_->Initialize({ Logo::Pos, {}, Logo::Scale });
	
	// �e
	shadowObj_->Initialize({ Shadow::Pos, {}, Shadow::Scale });
	
	// �w�i
	backObj_->Initialize({ {WinSize.x_ / 2.0f, WinSize.y_ / 2.0f, 0.0f} });

	// �X�^�[�g
	startObj_->Initialize({ UI::Start, {}, {1.0f,1.0f,0.0f} });
	startColor_->Initialize();

	// �I��
	exitObj_->Initialize({ UI::Exit, {}, {1.0f,1.0f,0.0f} });
	exitColor_->Initialize();

	// ���쒆
	isAct_ = true;

	// �I��
	current_ = Selection::Start;

	// �p���[
	selectStartPow_.Initialize(20);
	selectExitPow_.Initialize(20);
}

void TitleDrawer::Select(const bool isUp, const bool isUnder)
{
	// �ԍ��擾
	int idx = static_cast<int>(current_);

	// �ύX
	idx += isUp - isUnder;

	// �ԍ����� (���[�v����悤��)
	if (idx > static_cast<int>(Selection::Exit))
	{
		idx = static_cast<int>(Selection::Start);
	}
	else if (idx < static_cast<int>(Selection::Start))
	{
		idx = static_cast<int>(Selection::Exit);
	}

	// ���
	current_ = static_cast<Selection>(idx);
}

void TitleDrawer::Update()
{
	// ----- �A�j���[�V���� ----- //

	// �X�^�[�g��I��ł��邩
	bool isStart = current_ == Selection::Start;

	// �p���[�X�V
	selectStartPow_.Update(isStart);

	// �ۑ��p
	float startMoveX = 0.0f, startSca = 0.0f;

	// �X�^�[�g�Ȃ�
	if (isStart)
	{
		// �C�[�Y�A�E�g
		startMoveX = selectMoveXEas_.Out(selectStartPow_.Ratio());
		startSca = selectScaleEas_.Out(selectStartPow_.Ratio());
	}
	// ����ȊO�Ȃ�
	else
	{
		// �C�[�Y�C��
		startMoveX = selectMoveXEas_.In(selectStartPow_.Ratio());
		startSca = selectScaleEas_.In(selectStartPow_.Ratio());
	}


	// �I����I��ł��邩
	bool isExit = current_ == Selection::Exit;

	// �p���[�X�V
	selectExitPow_.Update(isExit);

	// �ۑ��p
	float exitMoveX = 0.0f, exitSca = 0.0f;

	// �I���Ȃ�
	if (isExit)
	{
		// �C�[�Y�A�E�g
		exitMoveX = selectMoveXEas_.Out(selectExitPow_.Ratio());
		exitSca = selectScaleEas_.Out(selectExitPow_.Ratio());
	}
	// ����ȊO�Ȃ�
	else
	{
		// �C�[�Y�C��
		exitMoveX = selectMoveXEas_.In(selectExitPow_.Ratio());
		exitSca = selectScaleEas_.In(selectExitPow_.Ratio());
	}


	// �F�ύX
	if (current_ == Selection::Start)
	{
		startColor_->SetRGBA(UI::OnColor);
		exitColor_->SetRGBA(UI::OffColor);
	}
	else if (current_ == Selection::Exit)
	{
		startColor_->SetRGBA(UI::OffColor);
		exitColor_->SetRGBA(UI::OnColor);
	}


	// ���S
	logoObj_->UpdateMatrix();

	// �e
	shadowObj_->UpdateMatrix();
	
	// �w�i
	backObj_->UpdateMatrix();

	// �X�^�[�g
	startObj_->UpdateMatrix({ Vector3(startMoveX, 0.0f,0.0f),{}, Vector3(startSca, startSca, startSca) });

	// �I��
	exitObj_->UpdateMatrix({ Vector3(exitMoveX, 0.0f,0.0f),{}, Vector3(exitSca, exitSca, exitSca) });
}

void TitleDrawer::Draw()
{
	// �w�i
	//spBackSpr_->Draw(backObj_.get());
	
	// �e
	spShadowSpr_->SetDrawCommand(shadowObj_.get(), YGame::DrawLocation::Front);

	// ���S
	spLogoSpr_->SetDrawCommand(logoObj_.get(), YGame::DrawLocation::Front);

	// �X�^�[�g
	spStartSpr_->SetDrawCommand(startObj_.get(), YGame::DrawLocation::Front);

	// �I��
	spExitSpr_->SetDrawCommand(exitObj_.get(), YGame::DrawLocation::Front);
}

#pragma endregion
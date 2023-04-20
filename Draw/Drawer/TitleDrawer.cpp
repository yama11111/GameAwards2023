#include "TitleDrawer.h"
#include "DrawerConfig.h"
#include <cassert>
#include <cmath>

#pragma region ���O���

using std::array;
using std::vector;
using std::unique_ptr;
using YGame::Transform;
using YGame::Sprite2DObject;
using YGame::Sprite2D;
using YGame::ModelObject;
using YGame::Model;
using YGame::Texture;
using YGame::Color;
using YMath::Vector3;
using namespace DrawerConfig::Title;

#pragma endregion

Sprite2D* TitleDrawerCommon::spLogoSpr_ = nullptr;
Sprite2D* TitleDrawerCommon::spShadowSpr_ = nullptr;
Sprite2D* TitleDrawerCommon::spBackSpr_ = nullptr;
Sprite2D* TitleDrawerCommon::spStartSpr_ = nullptr;
Sprite2D* TitleDrawerCommon::spExitSpr_ = nullptr;

Model* TitleDrawerCommon::spBuildingMod_ = nullptr;

void TitleDrawerCommon::StaticInitialize()
{
	// ���S
	spLogoSpr_	 = Sprite2D::Create({}, { Texture::Load("Title/logo.png") });

	// �e
	spShadowSpr_ = Sprite2D::Create({}, { Texture::Load("Title/shadow.png") });
	
	// �w�i
	spBackSpr_	 = Sprite2D::Create({}, { Texture::Load("Title/back.png") });

	// �X�^�[�g
	spStartSpr_	 = Sprite2D::Create({}, { Texture::Load("Title/start.png") });
	
	// �I��
	spExitSpr_	 = Sprite2D::Create({}, { Texture::Load("Title/exit.png") });
}

void TitleDrawer::Initalize()
{
	// �j
	core_.reset(new Transform());


	// ���S
	logoObj_.reset(Sprite2DObject::Create({}));
	logoObj_->parent_ = &core_->m_;


	// �e
	shadowObj_.reset(Sprite2DObject::Create({}));
	shadowObj_->parent_ = &core_->m_;
	

	// �w�i
	backObj_.reset(Sprite2DObject::Create({}));
	backObj_->parent_ = &core_->m_;


	// �X�^�[�g�F
	startColor_.reset(Color::Create());
	
	// �X�^�[�g
	startObj_.reset(Sprite2DObject::Create({}, startColor_.get()));
	startObj_->parent_ = &core_->m_;


	// �I���F
	exitColor_.reset(Color::Create());
	
	// �I��
	exitObj_.reset(Sprite2DObject::Create({}, exitColor_.get()));
	exitObj_->parent_ = &core_->m_;

	// ���Z�b�g
	Reset();
}

void TitleDrawer::Reset()
{
	// �j
	core_->Initialize({});

	// ���S
	logoObj_->Initialize({ Logo::Pos, {}, Logo::Scale });
	
	// �e
	shadowObj_->Initialize({ Shadow::Pos, {}, Shadow::Scale });
	
	// �w�i
	backObj_->Initialize({ {WinSize.x_ / 2.0f, WinSize.y_ / 2.0f, 0.0f} });

	// �X�^�[�g
	startObj_->Initialize({ UI::Start });
	startColor_->Initialize();

	// �I��
	exitObj_->Initialize({ UI::Exit });
	exitColor_->Initialize();

	// ���쒆
	isAct_ = true;

	// �I��
	current_ = Selection::Start;
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
	startObj_->UpdateMatrix();

	// �I��
	exitObj_->UpdateMatrix();
}

void TitleDrawer::DrawSprite2D()
{
	// �w�i
	spBackSpr_->Draw(backObj_.get());
	
	// �e
	spShadowSpr_->Draw(shadowObj_.get());

	// ���S
	spLogoSpr_->Draw(logoObj_.get());

	// �X�^�[�g
	spStartSpr_->Draw(startObj_.get());

	// �I��
	spExitSpr_->Draw(exitObj_.get());
}

void TitleDrawer::DrawModel()
{

}

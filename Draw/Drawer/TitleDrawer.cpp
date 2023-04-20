#include "TitleDrawer.h"
#include "DrawerConfig.h"
#include <cassert>
#include <cmath>

#pragma region 名前空間

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
	// ロゴ
	spLogoSpr_	 = Sprite2D::Create({}, { Texture::Load("Title/logo.png") });

	// 影
	spShadowSpr_ = Sprite2D::Create({}, { Texture::Load("Title/shadow.png") });
	
	// 背景
	spBackSpr_	 = Sprite2D::Create({}, { Texture::Load("Title/back.png") });

	// スタート
	spStartSpr_	 = Sprite2D::Create({}, { Texture::Load("Title/start.png") });
	
	// 終了
	spExitSpr_	 = Sprite2D::Create({}, { Texture::Load("Title/exit.png") });
}

void TitleDrawer::Initalize()
{
	// 核
	core_.reset(new Transform());


	// ロゴ
	logoObj_.reset(Sprite2DObject::Create({}));
	logoObj_->parent_ = &core_->m_;


	// 影
	shadowObj_.reset(Sprite2DObject::Create({}));
	shadowObj_->parent_ = &core_->m_;
	

	// 背景
	backObj_.reset(Sprite2DObject::Create({}));
	backObj_->parent_ = &core_->m_;


	// スタート色
	startColor_.reset(Color::Create());
	
	// スタート
	startObj_.reset(Sprite2DObject::Create({}, startColor_.get()));
	startObj_->parent_ = &core_->m_;


	// 終了色
	exitColor_.reset(Color::Create());
	
	// 終了
	exitObj_.reset(Sprite2DObject::Create({}, exitColor_.get()));
	exitObj_->parent_ = &core_->m_;

	// リセット
	Reset();
}

void TitleDrawer::Reset()
{
	// 核
	core_->Initialize({});

	// ロゴ
	logoObj_->Initialize({ Logo::Pos, {}, Logo::Scale });
	
	// 影
	shadowObj_->Initialize({ Shadow::Pos, {}, Shadow::Scale });
	
	// 背景
	backObj_->Initialize({ {WinSize.x_ / 2.0f, WinSize.y_ / 2.0f, 0.0f} });

	// スタート
	startObj_->Initialize({ UI::Start });
	startColor_->Initialize();

	// 終了
	exitObj_->Initialize({ UI::Exit });
	exitColor_->Initialize();

	// 動作中
	isAct_ = true;

	// 選択
	current_ = Selection::Start;
}

void TitleDrawer::Select(const bool isUp, const bool isUnder)
{
	// 番号取得
	int idx = static_cast<int>(current_);

	// 変更
	idx += isUp - isUnder;

	// 番号調整 (ループするように)
	if (idx > static_cast<int>(Selection::Exit))
	{
		idx = static_cast<int>(Selection::Start);
	}
	else if (idx < static_cast<int>(Selection::Start))
	{
		idx = static_cast<int>(Selection::Exit);
	}

	// 代入
	current_ = static_cast<Selection>(idx);
}

void TitleDrawer::Update()
{
	// 色変更
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


	// ロゴ
	logoObj_->UpdateMatrix();

	// 影
	shadowObj_->UpdateMatrix();
	
	// 背景
	backObj_->UpdateMatrix();

	// スタート
	startObj_->UpdateMatrix();

	// 終了
	exitObj_->UpdateMatrix();
}

void TitleDrawer::DrawSprite2D()
{
	// 背景
	spBackSpr_->Draw(backObj_.get());
	
	// 影
	spShadowSpr_->Draw(shadowObj_.get());

	// ロゴ
	spLogoSpr_->Draw(logoObj_.get());

	// スタート
	spStartSpr_->Draw(startObj_.get());

	// 終了
	spExitSpr_->Draw(exitObj_.get());
}

void TitleDrawer::DrawModel()
{

}

#include "TitleDrawer.h"
#include "DrawerConfig.h"
#include <cassert>
#include <cmath>

#pragma region 名前空間

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
	// ロゴ
	spLogoSpr_	 = Sprite2D::Create({}, { Texture::Load("Title/logo.png") });

	// 影
	spShadowSpr_ = Sprite2D::Create({}, { Texture::Load("Title/shadow.png") });

	// スタート
	spStartSpr_	 = Sprite2D::Create({}, { Texture::Load("Title/start.png") });
	
	// 終了
	spExitSpr_	 = Sprite2D::Create({}, { Texture::Load("Title/exit.png") });
}

#pragma endregion

#pragma region TitleDrawer

void TitleDrawer::Initialize()
{
	// 核
	core_.reset(new Transform());


	// ロゴ
	logoObj_.reset(Sprite2D::Object::Create());
	logoObj_->parent_ = &core_->m_;


	// 影
	shadowObj_.reset(Sprite2D::Object::Create());
	shadowObj_->parent_ = &core_->m_;
	

	// 背景
	backObj_.reset(Sprite2D::Object::Create());
	backObj_->parent_ = &core_->m_;


	// スタート色
	startColor_.reset(CBColor::Create());
	
	// スタート
	startObj_.reset(Sprite2D::Object::Create(Transform::Status::Default(), startColor_.get()));
	startObj_->parent_ = &core_->m_;


	// 終了色
	exitColor_.reset(CBColor::Create());
	
	// 終了
	exitObj_.reset(Sprite2D::Object::Create(Transform::Status::Default(), exitColor_.get()));
	exitObj_->parent_ = &core_->m_;


	// イージング
	selectMoveXEas_.Initialize(+64.0f, 0.0f, 3.0f);
	selectScaleEas_.Initialize(-0.25f, 0.0f, 3.0f);

	// リセット
	Reset();
}

void TitleDrawer::Reset()
{
	// 核
	core_->Initialize();

	// ロゴ
	logoObj_->Initialize({ Logo::Pos, {}, Logo::Scale });
	
	// 影
	shadowObj_->Initialize({ Shadow::Pos, {}, Shadow::Scale });
	
	// 背景
	backObj_->Initialize({ {WinSize.x_ / 2.0f, WinSize.y_ / 2.0f, 0.0f} });

	// スタート
	startObj_->Initialize({ UI::Start, {}, {1.0f,1.0f,0.0f} });
	startColor_->Initialize();

	// 終了
	exitObj_->Initialize({ UI::Exit, {}, {1.0f,1.0f,0.0f} });
	exitColor_->Initialize();

	// 動作中
	isAct_ = true;

	// 選択
	current_ = Selection::Start;

	// パワー
	selectStartPow_.Initialize(20);
	selectExitPow_.Initialize(20);
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
	// ----- アニメーション ----- //

	// スタートを選んでいるか
	bool isStart = current_ == Selection::Start;

	// パワー更新
	selectStartPow_.Update(isStart);

	// 保存用
	float startMoveX = 0.0f, startSca = 0.0f;

	// スタートなら
	if (isStart)
	{
		// イーズアウト
		startMoveX = selectMoveXEas_.Out(selectStartPow_.Ratio());
		startSca = selectScaleEas_.Out(selectStartPow_.Ratio());
	}
	// それ以外なら
	else
	{
		// イーズイン
		startMoveX = selectMoveXEas_.In(selectStartPow_.Ratio());
		startSca = selectScaleEas_.In(selectStartPow_.Ratio());
	}


	// 終了を選んでいるか
	bool isExit = current_ == Selection::Exit;

	// パワー更新
	selectExitPow_.Update(isExit);

	// 保存用
	float exitMoveX = 0.0f, exitSca = 0.0f;

	// 終了なら
	if (isExit)
	{
		// イーズアウト
		exitMoveX = selectMoveXEas_.Out(selectExitPow_.Ratio());
		exitSca = selectScaleEas_.Out(selectExitPow_.Ratio());
	}
	// それ以外なら
	else
	{
		// イーズイン
		exitMoveX = selectMoveXEas_.In(selectExitPow_.Ratio());
		exitSca = selectScaleEas_.In(selectExitPow_.Ratio());
	}


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
	startObj_->UpdateMatrix({ Vector3(startMoveX, 0.0f,0.0f),{}, Vector3(startSca, startSca, startSca) });

	// 終了
	exitObj_->UpdateMatrix({ Vector3(exitMoveX, 0.0f,0.0f),{}, Vector3(exitSca, exitSca, exitSca) });
}

void TitleDrawer::Draw()
{
	// 背景
	//spBackSpr_->Draw(backObj_.get());
	
	// 影
	spShadowSpr_->SetDrawCommand(shadowObj_.get(), YGame::DrawLocation::Front);

	// ロゴ
	spLogoSpr_->SetDrawCommand(logoObj_.get(), YGame::DrawLocation::Front);

	// スタート
	spStartSpr_->SetDrawCommand(startObj_.get(), YGame::DrawLocation::Front);

	// 終了
	spExitSpr_->SetDrawCommand(exitObj_.get(), YGame::DrawLocation::Front);
}

#pragma endregion
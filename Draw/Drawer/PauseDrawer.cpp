#include "PauseDrawer.h"
#include "HUDConfig.h"
#include "SceneManager.h"

using YGame::Sprite2D;
using YGame::Sprite2DObject;
using YGame::Color;
using YGame::Texture;
using YMath::Vector3;
using YScene::SceneManager;
using namespace HUDConfig::Pause;

#pragma region PauseDrawerCommon

YInput::Keys* PauseDrawerCommon::sKeys_ = nullptr;
Sprite2D* PauseDrawerCommon::spPauseSpr_ = nullptr;
Sprite2D* PauseDrawerCommon::spResumeSpr_ = nullptr;
Sprite2D* PauseDrawerCommon::spTitleSpr_ = nullptr;
Sprite2D* PauseDrawerCommon::spCurtenSpr_ = nullptr;

void PauseDrawerCommon::StaticInitialize()
{
	// キー
	sKeys_ = YInput::Keys::GetInstance();
	
	// pause
	spPauseSpr_		= Sprite2D::Create({}, { Texture::Load("UI/pause.png") });
	// resume
	spResumeSpr_	= Sprite2D::Create({}, { Texture::Load("UI/resume.png") });
	// title
	spTitleSpr_		= Sprite2D::Create({}, { Texture::Load("UI/title.png") });

	// curten
	spCurtenSpr_	= Sprite2D::Create({}, { Texture::Load("white1x1.png") });
}

#pragma endregion


#pragma region PauseDrawer

void PauseDrawer::Initalize()
{
	// ----- 生成 ----- //

	// pause
	pauseObj_.	reset(Sprite2DObject::Create({}));
	
	// resumeColor
	resumeColor_.reset(Color::Create());
	// resume
	resumeObj_.	reset(Sprite2DObject::Create({}, resumeColor_.get()));
	
	// titleColor
	titleColor_.reset(Color::Create());
	// title
	titleObj_.	reset(Sprite2DObject::Create({}, titleColor_.get()));
	
	// curtenColor
	curtenColor_.reset(Color::Create());
	// curten
	curtenObj_.reset(Sprite2DObject::Create({}, curtenColor_.get()));

	// リセット
	Reset();
}

void PauseDrawer::Reset()
{
	// ----- Object初期化 ----- //

	// pause
	pauseObj_->Initialize({Font::Pause, {}, Font::Scale });
	// resume
	resumeObj_->Initialize({Font::Resume, {}, Font::Scale });
	// title
	titleObj_->Initialize({ Font::Title, {}, Font::Scale });

	// curten
	curtenObj_->Initialize({ Curten::Pos, {}, Curten::Scale });
	

	// ----- Color初期化 ----- //
	
	// resumeColor
	resumeColor_->SetRGB(Font::OnColor);

	// titleColor
	titleColor_->SetRGB(Font::OffColor);


	// curtenColor
	curtenColor_->SetRGBA(Curten::Color);
	

	// ポーズ中か
	isPause_ = false;
	
	// 選択
	current_ = Select::Resume;
}

void PauseDrawer::Update()
{
	// TAB → ポーズ切り替え
	if (sKeys_->IsTrigger(DIK_ESCAPE))
	{
		// ポーズ中じゃないなら
		if (isPause_ == false) 
		{
			// ポーズに
			isPause_ = true; 
		}
		// 違うなら
		else
		{
			// リセット
			Reset();
		}
	}

	// ポーズ中じゃないなら弾く
	if (isPause_ == false) { return; }

	// 選択切り替え (W or S)
	if (sKeys_->IsTrigger(DIK_W) || sKeys_->IsTrigger(DIK_S))
	{
		// 逆になるように
		if (current_ == Select::Resume)
		{
			current_ = Select::Title;
			
			// 選択しているか分かるように
			resumeColor_->SetRGB(Font::OffColor); // resume
			titleColor_->SetRGB(Font::OnColor); // title
		}
		else if (current_ == Select::Title)
		{
			current_ = Select::Resume;

			// 選択しているか分かるように
			resumeColor_->SetRGB(Font::OnColor); // resume
			titleColor_->SetRGB(Font::OffColor); // title
		}
	}

	// 実行 (SPACE)
	if (sKeys_->IsTrigger(DIK_SPACE))
	{
		// Resumeなら
		if (current_ == Select::Resume)
		{
			// リセット
			Reset();
		}
		// タイトルなら
		else if (current_ == Select::Title)
		{
			// シーン遷移
			SceneManager::GetInstance()->Change("TITLE", "BLACKOUT");
		}
	}

	// pause
	pauseObj_->UpdateMatrix();
	// resume
	resumeObj_->UpdateMatrix();
	// title
	titleObj_->UpdateMatrix();
}

void PauseDrawer::Draw()
{
	// ポーズ中じゃないなら弾く
	if (isPause_ == false) { return; }

	// curten
	spCurtenSpr_->Draw(curtenObj_.get());

	// pause
	spPauseSpr_->Draw(pauseObj_.get());
	// resume
	spResumeSpr_->Draw(resumeObj_.get());
	// title
	spTitleSpr_->Draw(titleObj_.get());
}

#pragma endregion
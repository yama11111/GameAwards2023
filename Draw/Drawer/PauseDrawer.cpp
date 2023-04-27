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
Sprite2D* PauseDrawerCommon::spStageSpr_ = nullptr;
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
	// stage
	spStageSpr_		= Sprite2D::Create({}, { Texture::Load("UI/select.png") });

	// curten
	spCurtenSpr_	= Sprite2D::Create({}, { Texture::Load("white1x1.png") });
}

#pragma endregion


#pragma region PauseDrawer

void PauseDrawer::Initialize(const SceneType& sceneType)
{
	// ----- 生成 ----- //

	// pause
	pauseObj_.	reset(Sprite2DObject::Create({}));
	
	// resumeColor
	resumeColor_.reset(Color::Create());
	// resume
	resumeObj_.	reset(Sprite2DObject::Create({}, resumeColor_.get()));
	
	// titleColor
	changeColor_.reset(Color::Create());
	// title
	changeObj_.	reset(Sprite2DObject::Create({}, changeColor_.get()));
	
	// curtenColor
	curtenColor_.reset(Color::Create());
	// curten
	curtenObj_.reset(Sprite2DObject::Create({}, curtenColor_.get()));

	// 選択スケールイージング
	selectScaleEas_.Initialize(-0.25f, 0.0f, 3.0f);

	// リセット
	Reset(sceneType);
}

void PauseDrawer::Reset(const SceneType& sceneType)
{
	// ----- Object初期化 ----- //

	// pause
	pauseObj_->Initialize({Font::Pause, {}, Font::Scale });
	// resume
	resumeObj_->Initialize({Font::Resume, {}, Font::Scale });
	// title
	changeObj_->Initialize({ Font::Title, {}, Font::Scale });

	// curten
	curtenObj_->Initialize({ Curten::Pos, {}, Curten::Scale });
	

	// ----- Color初期化 ----- //
	
	// resumeColor
	resumeColor_->SetRGB(Font::OnColor);

	// titleColor
	changeColor_->SetRGB(Font::OffColor);


	// curtenColor
	curtenColor_->SetRGBA(Curten::Color);
	

	// ポーズ中か
	isPause_ = false;

	// ポーズ中だったか
	isElderPause_ = false;
	
	// 選択
	current_ = Select::Resume;

	// 現在のシーン
	sceneType_ = sceneType;

	// 選択Resumeパワー
	selectResumePow_.Initialize(20);
	// 選択Changeパワー
	selectChangePow_.Initialize(20);
}

void PauseDrawer::ResumeReset()
{
	// resumeColor
	resumeColor_->SetRGB(Font::OnColor);

	// titleColor
	changeColor_->SetRGB(Font::OffColor);


	// curtenColor
	curtenColor_->SetRGBA(Curten::Color);
	// ポーズ中か
	isPause_ = false;
	// 選択
	current_ = Select::Resume;

	// パワーリセット
	selectResumePow_.Reset();
	selectChangePow_.Reset();
}

void PauseDrawer::Update()
{
	// ポーズ保存
	isElderPause_ = isPause_;

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
			ResumeReset();
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
			if (sceneType_ == SceneType::Select)
			{
				current_ = Select::Title;
			}
			else if (sceneType_ == SceneType::Play)
			{
				current_ = Select::Stage;
			}

			// 選択しているか分かるように
			resumeColor_->SetRGB(Font::OffColor); // resume
			changeColor_->SetRGB(Font::OnColor); // change
		}
		else if (current_ == Select::Title || current_ == Select::Stage)
		{
			current_ = Select::Resume;

			// 選択しているか分かるように
			resumeColor_->SetRGB(Font::OnColor); // resume
			changeColor_->SetRGB(Font::OffColor); // change
		}
	}


	// Resumeなら
	bool isResume = current_ == Select::Resume;

	// パワー更新
	selectResumePow_.Update(isResume);

	// 保存用
	float resumeSca = 0.0f;

	// 選択中なら
	if (isResume)
	{
		// イーズアウト
		resumeSca = selectScaleEas_.Out(selectResumePow_.Ratio());
	}
	// それ以外なら
	else
	{
		// イーズイン
		resumeSca = selectScaleEas_.In(selectResumePow_.Ratio());
	}


	// Changeなら
	bool isChange = !isResume;

	// パワー更新
	selectChangePow_.Update(isChange);

	// 保存用
	float changeSca = 0.0f;

	// 選択中なら
	if (isChange)
	{
		// イーズアウト
		changeSca = selectScaleEas_.Out(selectChangePow_.Ratio());
	}
	// それ以外なら
	else
	{
		// イーズイン
		changeSca = selectScaleEas_.In(selectChangePow_.Ratio());
	}

	// pause
	pauseObj_->UpdateMatrix();
	// resume
	resumeObj_->UpdateMatrix({ {}, {}, Vector3(resumeSca, resumeSca, resumeSca) });
	// change
	changeObj_->UpdateMatrix({ {}, {}, Vector3(changeSca, changeSca, changeSca) });

	// 実行 (SPACE)
	if (sKeys_->IsTrigger(DIK_SPACE))
	{
		// Resumeなら
		if (current_ == Select::Resume)
		{
			// リセット
			ResumeReset();
		}
		// タイトルなら
		else if (current_ == Select::Title)
		{
			// シーン遷移
			SceneManager::GetInstance()->Change("TITLE", "BLACKOUT");
		}
		// ステージセレクトなら
		else if (current_ == Select::Stage)
		{
			// シーン遷移
			SceneManager::GetInstance()->Change("SELECT", "BLACKOUT");
		}
	}
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
	if (sceneType_ == SceneType::Select)
	{
		spTitleSpr_->Draw(changeObj_.get());
	}
	// stage
	else if (sceneType_ == SceneType::Play)
	{
		spStageSpr_->Draw(changeObj_.get());
	}
}

#pragma endregion
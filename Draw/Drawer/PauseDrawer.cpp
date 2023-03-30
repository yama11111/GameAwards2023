#include "PauseDrawer.h"
#include "HUDConfig.h"
#include "SceneManager.h"

using YGame::Sprite2D;
using YGame::Sprite2DObject;
using YGame::Color;
using YGame::TextureManager;
using YMath::Vector3;
using YScene::SceneManager;
using namespace HUDConfig::Pause;

#pragma region PauseDrawerCommon

YInput::Keys* PauseDrawerCommon::sKeys_ = nullptr;
std::unique_ptr<Sprite2D> PauseDrawerCommon::pauseSpr_ = nullptr;
std::unique_ptr<Sprite2D> PauseDrawerCommon::resumeSpr_ = nullptr;
std::unique_ptr<Sprite2D> PauseDrawerCommon::titleSpr_ = nullptr;
std::unique_ptr<Sprite2D> PauseDrawerCommon::curtenSpr_ = nullptr;

void PauseDrawerCommon::StaticInitialize()
{
	// �L�[
	sKeys_ = YInput::Keys::GetInstance();
	
	// pause
	pauseSpr_.	reset(Sprite2D::Create({}, { TextureManager::GetInstance()->Load("UI/pause.png") }));
	// resume
	resumeSpr_.	reset(Sprite2D::Create({}, { TextureManager::GetInstance()->Load("UI/resume.png") }));
	// title
	titleSpr_.	reset(Sprite2D::Create({}, { TextureManager::GetInstance()->Load("UI/title.png") }));

	// curten
	curtenSpr_.	reset(Sprite2D::Create({}, { TextureManager::GetInstance()->Load("white1x1.png") }));
}

#pragma endregion


#pragma region PauseDrawer

void PauseDrawer::Initalize()
{
	// ----- ���� ----- //

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

	// ���Z�b�g
	Reset();
}

void PauseDrawer::Reset()
{
	// ----- Object������ ----- //

	// pause
	pauseObj_->Initialize({Font::Pause, {}, Font::Scale });
	// resume
	resumeObj_->Initialize({Font::Resume, {}, Font::Scale });
	// title
	titleObj_->Initialize({ Font::Title, {}, Font::Scale });

	// curten
	curtenObj_->Initialize({ Curten::Pos, {}, Curten::Scale });
	

	// ----- Color������ ----- //
	
	// resumeColor
	resumeColor_->SetRGB(Font::OnColor);

	// titleColor
	titleColor_->SetRGB(Font::OffColor);


	// curtenColor
	curtenColor_->SetRGBA(Curten::Color);
	

	// �|�[�Y����
	isPause_ = false;
	
	// �I��
	current_ = Select::Resume;
}

void PauseDrawer::Update()
{
	// TAB �� �|�[�Y�؂�ւ�
	if (sKeys_->IsTrigger(DIK_TAB))
	{
		// �|�[�Y������Ȃ��Ȃ�
		if (isPause_ == false) 
		{
			// �|�[�Y��
			isPause_ = true; 
		}
		// �Ⴄ�Ȃ�
		else
		{
			// ���Z�b�g
			Reset();
		}
	}

	// �|�[�Y������Ȃ��Ȃ�e��
	if (isPause_ == false) { return; }

	// �I��؂�ւ� (W or S)
	if (sKeys_->IsTrigger(DIK_W) || sKeys_->IsTrigger(DIK_S))
	{
		// �t�ɂȂ�悤��
		if (current_ == Select::Resume)
		{
			current_ = Select::Title;
			
			// �I�����Ă��邩������悤��
			resumeColor_->SetRGB(Font::OffColor); // resume
			titleColor_->SetRGB(Font::OnColor); // title
		}
		else if (current_ == Select::Title)
		{
			current_ = Select::Resume;

			// �I�����Ă��邩������悤��
			resumeColor_->SetRGB(Font::OnColor); // resume
			titleColor_->SetRGB(Font::OffColor); // title
		}
	}

	// ���s (SPACE)
	if (sKeys_->IsTrigger(DIK_SPACE))
	{
		// Resume�Ȃ�
		if (current_ == Select::Resume)
		{
			// ���Z�b�g
			Reset();
		}
		// �^�C�g���Ȃ�
		else if (current_ == Select::Title)
		{
			// �V�[���J��
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
	// �|�[�Y������Ȃ��Ȃ�e��
	if (isPause_ == false) { return; }

	// curten
	curtenSpr_->Draw(curtenObj_.get());

	// pause
	pauseSpr_->Draw(pauseObj_.get());
	// resume
	resumeSpr_->Draw(resumeObj_.get());
	// title
	titleSpr_->Draw(titleObj_.get());
}

#pragma endregion
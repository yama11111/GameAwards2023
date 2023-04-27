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
	// �L�[
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
	// ----- ���� ----- //

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

	// �I���X�P�[���C�[�W���O
	selectScaleEas_.Initialize(-0.25f, 0.0f, 3.0f);

	// ���Z�b�g
	Reset(sceneType);
}

void PauseDrawer::Reset(const SceneType& sceneType)
{
	// ----- Object������ ----- //

	// pause
	pauseObj_->Initialize({Font::Pause, {}, Font::Scale });
	// resume
	resumeObj_->Initialize({Font::Resume, {}, Font::Scale });
	// title
	changeObj_->Initialize({ Font::Title, {}, Font::Scale });

	// curten
	curtenObj_->Initialize({ Curten::Pos, {}, Curten::Scale });
	

	// ----- Color������ ----- //
	
	// resumeColor
	resumeColor_->SetRGB(Font::OnColor);

	// titleColor
	changeColor_->SetRGB(Font::OffColor);


	// curtenColor
	curtenColor_->SetRGBA(Curten::Color);
	

	// �|�[�Y����
	isPause_ = false;

	// �|�[�Y����������
	isElderPause_ = false;
	
	// �I��
	current_ = Select::Resume;

	// ���݂̃V�[��
	sceneType_ = sceneType;

	// �I��Resume�p���[
	selectResumePow_.Initialize(20);
	// �I��Change�p���[
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
	// �|�[�Y����
	isPause_ = false;
	// �I��
	current_ = Select::Resume;

	// �p���[���Z�b�g
	selectResumePow_.Reset();
	selectChangePow_.Reset();
}

void PauseDrawer::Update()
{
	// �|�[�Y�ۑ�
	isElderPause_ = isPause_;

	// TAB �� �|�[�Y�؂�ւ�
	if (sKeys_->IsTrigger(DIK_ESCAPE))
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
			ResumeReset();
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
			if (sceneType_ == SceneType::Select)
			{
				current_ = Select::Title;
			}
			else if (sceneType_ == SceneType::Play)
			{
				current_ = Select::Stage;
			}

			// �I�����Ă��邩������悤��
			resumeColor_->SetRGB(Font::OffColor); // resume
			changeColor_->SetRGB(Font::OnColor); // change
		}
		else if (current_ == Select::Title || current_ == Select::Stage)
		{
			current_ = Select::Resume;

			// �I�����Ă��邩������悤��
			resumeColor_->SetRGB(Font::OnColor); // resume
			changeColor_->SetRGB(Font::OffColor); // change
		}
	}


	// Resume�Ȃ�
	bool isResume = current_ == Select::Resume;

	// �p���[�X�V
	selectResumePow_.Update(isResume);

	// �ۑ��p
	float resumeSca = 0.0f;

	// �I�𒆂Ȃ�
	if (isResume)
	{
		// �C�[�Y�A�E�g
		resumeSca = selectScaleEas_.Out(selectResumePow_.Ratio());
	}
	// ����ȊO�Ȃ�
	else
	{
		// �C�[�Y�C��
		resumeSca = selectScaleEas_.In(selectResumePow_.Ratio());
	}


	// Change�Ȃ�
	bool isChange = !isResume;

	// �p���[�X�V
	selectChangePow_.Update(isChange);

	// �ۑ��p
	float changeSca = 0.0f;

	// �I�𒆂Ȃ�
	if (isChange)
	{
		// �C�[�Y�A�E�g
		changeSca = selectScaleEas_.Out(selectChangePow_.Ratio());
	}
	// ����ȊO�Ȃ�
	else
	{
		// �C�[�Y�C��
		changeSca = selectScaleEas_.In(selectChangePow_.Ratio());
	}

	// pause
	pauseObj_->UpdateMatrix();
	// resume
	resumeObj_->UpdateMatrix({ {}, {}, Vector3(resumeSca, resumeSca, resumeSca) });
	// change
	changeObj_->UpdateMatrix({ {}, {}, Vector3(changeSca, changeSca, changeSca) });

	// ���s (SPACE)
	if (sKeys_->IsTrigger(DIK_SPACE))
	{
		// Resume�Ȃ�
		if (current_ == Select::Resume)
		{
			// ���Z�b�g
			ResumeReset();
		}
		// �^�C�g���Ȃ�
		else if (current_ == Select::Title)
		{
			// �V�[���J��
			SceneManager::GetInstance()->Change("TITLE", "BLACKOUT");
		}
		// �X�e�[�W�Z���N�g�Ȃ�
		else if (current_ == Select::Stage)
		{
			// �V�[���J��
			SceneManager::GetInstance()->Change("SELECT", "BLACKOUT");
		}
	}
}

void PauseDrawer::Draw()
{
	// �|�[�Y������Ȃ��Ȃ�e��
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
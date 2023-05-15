#include "PauseDrawer.h"
#include "HUDConfig.h"
#include "SceneExecutive.h"

#include "YGameSceneFactory.h"

#pragma region ���O���

using YGame::Sprite2D;
using YGame::CBColor;
using YGame::Texture;
using YMath::Vector3;
using YScene::SceneManager;
using YScene::YGameSceneFactory;
using YScene::SceneExecutive;
using namespace HUDConfig::Pause;

#pragma endregion

#pragma region Static

YInput::Keys* PauseDrawerCommon::sKeys_ = nullptr;
Sprite2D* PauseDrawerCommon::spPauseSpr_ = nullptr;
Sprite2D* PauseDrawerCommon::spResumeSpr_ = nullptr;
Sprite2D* PauseDrawerCommon::spTitleSpr_ = nullptr;
Sprite2D* PauseDrawerCommon::spStageSpr_ = nullptr;
Sprite2D* PauseDrawerCommon::spCurtenSpr_ = nullptr;

#pragma endregion

#pragma region PauseDrawerCommon

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

void PauseDrawer::Initialize()
{
	// ----- ���� ----- //

	// pause
	pauseObj_.reset(Sprite2D::Object::Create({}));
	
	// resumeColor
	resumeColor_.reset(CBColor::Create());
	// resume
	resumeObj_.reset(Sprite2D::Object::Create({}, resumeColor_.get()));
	
	// titleColor
	changeColor_.reset(CBColor::Create());
	// title
	changeObj_.reset(Sprite2D::Object::Create({}, changeColor_.get()));
	
	// curtenColor
	curtenColor_.reset(CBColor::Create());
	// curten
	curtenObj_.reset(Sprite2D::Object::Create({}, curtenColor_.get(), nullptr));

	// �I���X�P�[���C�[�W���O
	selectScaleEas_.Initialize(-0.25f, 0.0f, 3.0f);

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
	current_ = Selection::Resume;

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
	current_ = Selection::Resume;

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
		if (current_ == Selection::Resume)
		{
			current_ = Selection::Change;

			// �I�����Ă��邩������悤��
			resumeColor_->SetRGB(Font::OffColor); // resume
			changeColor_->SetRGB(Font::OnColor); // change
		}
		else if (current_ == Selection::Change)
		{
			current_ = Selection::Resume;

			// �I�����Ă��邩������悤��
			resumeColor_->SetRGB(Font::OnColor); // resume
			changeColor_->SetRGB(Font::OffColor); // change
		}
	}


	// Resume�Ȃ�
	bool isResume = current_ == Selection::Resume;

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
		if (current_ == Selection::Resume)
		{
			// ���Z�b�g
			ResumeReset();
		}
		// �J�ڂȂ�
		else if (current_ == Selection::Change)
		{
			// �X�e�[�W�Z���N�g�Ȃ�
			if (SceneManager::GetInstance()->CurrentSceneName() == YGameSceneFactory::Select_)
			{
				// �V�[���J��
				SceneExecutive::GetInstance()->Change("TITLE", "BLACKOUT", 20, 20);
			}
			// �v���C�Ȃ�
			else if (SceneManager::GetInstance()->CurrentSceneName() == YGameSceneFactory::Play_)
			{
				// �V�[���J��
				SceneExecutive::GetInstance()->Change("SELECT", "BLACKOUT", 20, 20);
			}
		}
	}
}

void PauseDrawer::Draw()
{
	// �|�[�Y������Ȃ��Ȃ�e��
	if (isPause_ == false) { return; }

	// curten
	spCurtenSpr_->SetDrawCommand(curtenObj_.get(), YGame::DrawLocation::Front);

	// pause
	spPauseSpr_->SetDrawCommand(pauseObj_.get(), YGame::DrawLocation::Front);
	// resume
	spResumeSpr_->SetDrawCommand(resumeObj_.get(), YGame::DrawLocation::Front);
	
	// �X�e�[�W�Z���N�g�Ȃ�
	if (SceneManager::GetInstance()->CurrentSceneName() == YGameSceneFactory::Select_)
	{
		// title
		spTitleSpr_->SetDrawCommand(changeObj_.get(), YGame::DrawLocation::Front);
	}
	// �v���C�Ȃ�
	else if (SceneManager::GetInstance()->CurrentSceneName() == YGameSceneFactory::Play_)
	{
		// stage
		spStageSpr_->SetDrawCommand(changeObj_.get(), YGame::DrawLocation::Front);
	}
}

#pragma endregion
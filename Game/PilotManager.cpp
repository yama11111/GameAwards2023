#include "PilotManager.h"
#include "Keys.h"
#include "TransitionManager.h"
#include "MouseCollider.h"
#include <cassert>

using std::unique_ptr;
using YInput::Keys;
using YMath::Vector3;
using YMath::Power;
using YMath::Timer;
using YMath::Ease;
using YGame::Texture;
using YGame::Camera;
using YGame::Sprite2D;
using YGame::CBColor;

PilotManager::PilotType PilotManager::sPilot_;
Stage* PilotManager::spStage_ = nullptr;
int PilotManager::sSignIndex_ = 0;
Camera* PilotManager::spCamera_ = nullptr;
Vector3 PilotManager::sInitCameraPos_;
Timer PilotManager::sInitZoomTimer_;
Ease<float> PilotManager::sInitZoomEase_;
bool PilotManager::sIsActInitAnime_ = false;
Keys* PilotManager::spKeys_ = nullptr;

Sprite2D* PilotManager::spPilotPlayerSpr_ = nullptr;
unique_ptr<Sprite2D::Object> PilotManager::sPilotPlayerObj_;
unique_ptr<CBColor> PilotManager::sPilotPlayerColor_;
Sprite2D* PilotManager::spPilotStageSpr_ = nullptr;
unique_ptr<Sprite2D::Object> PilotManager::sPilotStageObj_;
unique_ptr<CBColor> PilotManager::sPilotStageColor_;
Power PilotManager::sChangePlayerPower_;
Power PilotManager::sChangeStagePower_;
Ease<float> PilotManager::sChangeHeight_;
Ease<float> PilotManager::sChangeAlpha_;

void PilotManager::StaticInitialize(Camera* pCamera, Stage* pStage)
{
	assert(pCamera);
	assert(pStage);

	spCamera_ = pCamera;
	spStage_ = pStage;
	spKeys_ = Keys::GetInstance();

	sInitCameraPos_ = {};
	
	sInitZoomEase_.Initialize(-20.0f, 0.0f, 3.0f);

	sInitZoomTimer_.Initialize(40);
	
	sIsActInitAnime_ = true;
	
	spPilotPlayerSpr_ = Sprite2D::Create({}, { Texture::Load("UI/pilot_Player.png")});
	spPilotStageSpr_ = Sprite2D::Create({}, { Texture::Load("UI/pilot_Stage.png") });
	
	sPilotPlayerObj_.reset(Sprite2D::Object::Create());
	sPilotStageObj_.reset(Sprite2D::Object::Create());
	
	sPilotPlayerColor_.reset(CBColor::Create());
	sPilotPlayerObj_->SetColor(sPilotPlayerColor_.get());
	
	sPilotStageColor_.reset(CBColor::Create());
	sPilotStageObj_->SetColor(sPilotStageColor_.get());
		
	sChangePlayerPower_.Initialize(20);
	sChangeStagePower_.Initialize(20);
	sChangeHeight_.Initialize(-120.0f, 0.0f, 3.0f);
	sChangeAlpha_.Initialize(0.0f, 1.0f, 3.0f);

	StaticReset();
}

void PilotManager::StaticReset()
{
	sInitZoomTimer_.SetActive(true);
	
	sSignIndex_ = 0;

	sPilot_ = PilotType::ePlayer;
	
	sPilotPlayerObj_->Initialize({ {272.0f, 80.0f, 0.0f}, {}, {1.0f,1.0f,0.0f} });
	sPilotStageObj_->Initialize({ {272.0f, 80.0f, 0.0f}, {}, {1.0f,1.0f,0.0f} });

	sChangePlayerPower_.Reset();
	sChangeStagePower_.Reset();
}

void PilotManager::StaticUpdate()
{
	if (sIsActInitAnime_ == false)
	{
		if (spKeys_->IsTrigger(DIK_F))
		{
			if (sPilot_ == PilotType::ePlayer)
			{
				StaticChangePilot(PilotType::eStage);
				MouseColliderCommon::StaticSetIsActMouse(true);
			}
			else if (sPilot_ == PilotType::eStage)
			{
				StaticChangePilot(PilotType::ePlayer);
				MouseColliderCommon::StaticSetIsActMouse(false);
			}
		}
	}

	if (sIsActInitAnime_)
	{
		if (YScene::TransitionManager::GetInstance()->IsAct() == false) 
		{
			sInitZoomTimer_.Update();
		}

		spCamera_->pos_.z_ = sInitCameraPos_.z_ + sInitZoomEase_.In(sInitZoomTimer_.Ratio());

		if(sInitZoomTimer_.IsEnd())
		{
			sIsActInitAnime_ = false;
			sInitCameraPos_ = spCamera_->pos_;

			StaticSetFollowStage(sSignIndex_);
		}
	}

	bool isAct = sPilot_ == PilotType::ePlayer;

	if (sIsActInitAnime_ == false)
	{
		sChangePlayerPower_.Update(isAct);
		sChangeStagePower_.Update(!isAct);
	}

	float playerColor = 0.0f;
	float stageColor = 0.0f;

	if (!isAct) { playerColor = sChangeAlpha_.Out(sChangePlayerPower_.Ratio()); }
	else { playerColor = sChangeAlpha_.In(sChangePlayerPower_.Ratio()); }

	if (isAct) { stageColor = sChangeAlpha_.Out(sChangeStagePower_.Ratio()); }
	else { stageColor = sChangeAlpha_.In(sChangeStagePower_.Ratio()); }

	sPilotPlayerColor_->SetAlpha(playerColor);
	sPilotStageColor_->SetAlpha(stageColor);

	float playerHeight = 0.0f;
	float stageHeight = 0.0f;
	
	if (!isAct) { playerHeight = sChangeHeight_.In(sChangePlayerPower_.Ratio()); }
	else { playerHeight = sChangeHeight_.Out(sChangePlayerPower_.Ratio()); }

	if (isAct) { stageHeight = sChangeHeight_.In(sChangeStagePower_.Ratio()); }
	else { stageHeight = sChangeHeight_.Out(sChangeStagePower_.Ratio()); }

	sPilotPlayerObj_->UpdateMatrix({ {0.0f,playerHeight,0.0f}, {},{} });
	sPilotStageObj_->UpdateMatrix({ {0.0f,stageHeight,0.0f}, {},{} });
}

void PilotManager::StaticDraw()
{
	spPilotPlayerSpr_->SetDrawCommand(sPilotPlayerObj_.get(), YGame::DrawLocation::Front);
	spPilotStageSpr_->SetDrawCommand(sPilotStageObj_.get(), YGame::DrawLocation::Front);
}

void PilotManager::StaticChangePilot(const PilotType& pilot)
{
	sPilot_ = pilot;

	if (sPilot_ == PilotType::ePlayer)
	{
		Vector3 pos = spStage_->signVector_[sSignIndex_]->GetCenterPos() + Vector3(0.0f, 0.0f, -50.0f);

		spCamera_->SmoothMoving(40, pos, 3.0f);
	}
	else if (sPilot_ == PilotType::eStage)
	{
		Vector3 pos = sInitCameraPos_;

		spCamera_->SmoothMoving(40, pos, 3.0f);
	}
}

void PilotManager::StaticSetFollowStage(const int signIndex)
{
	sSignIndex_ = signIndex;

	Vector3 pos = spStage_->signVector_[sSignIndex_]->GetCenterPos() + Vector3(0.0f, 0.0f, -50.0f);

	spCamera_->SmoothMoving(40, pos, 3.0f);
}
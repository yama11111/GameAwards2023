#include "PilotManager.h"
#include "Keys.h"
#include "TransitionManager.h"
#include <cassert>

using YInput::Keys;
using YMath::Vector3;
using YMath::Timer;
using YMath::Ease;
using YGame::Camera;

PilotManager::PilotType PilotManager::sPilot_;
Stage* PilotManager::spStage_ = nullptr;
int PilotManager::sSignIndex_ = 0;
Camera* PilotManager::spCamera_ = nullptr;
Vector3 PilotManager::sInitCameraPos_;
Timer PilotManager::sInitZoomTimer_;
Ease<float> PilotManager::sInitZoomEase_;
bool PilotManager::sIsActInitAnime_ = false;
Keys* PilotManager::spKeys_ = nullptr;


void PilotManager::StaticInitialize(Camera* pCamera, Stage* pStage)
{
	assert(pCamera);
	assert(pStage);

	spCamera_ = pCamera;
	spStage_ = pStage;
	spKeys_ = Keys::GetInstance();

	sInitCameraPos_ = {};
	
	sInitZoomEase_.Initialize(-20.0f, 0.0f, 3.0f);

	sInitZoomTimer_.Initialize(30);
	
	sIsActInitAnime_ = true;
	
	StaticReset();
}

void PilotManager::StaticReset()
{
	sInitZoomTimer_.SetActive(true);
	
	sSignIndex_ = 0;
}

void PilotManager::StaticUpdate()
{
	if (spKeys_->IsTrigger(DIK_F))
	{
		if (sPilot_ == PilotType::ePlayer)
		{
			StaticChangePilot(PilotType::eStage);
		}
		else if (sPilot_ == PilotType::eStage)
		{
			StaticChangePilot(PilotType::ePlayer);
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
}

void PilotManager::StaticChangePilot(const PilotType& pilot)
{
	sPilot_ = pilot;

	if (sPilot_ == PilotType::ePlayer)
	{
		Vector3 pos = spStage_->signVector_[sSignIndex_]->GetCenterPos() + Vector3(0.0f, 0.0f, -50.0f);

		spCamera_->SmoothMoving(20, pos, 3.0f);
	}
	else if (sPilot_ == PilotType::eStage)
	{
		Vector3 pos = sInitCameraPos_;

		spCamera_->SmoothMoving(20, pos, 3.0f);
	}
}

void PilotManager::StaticSetFollowStage(const int signIndex)
{
	sSignIndex_ = signIndex;

	Vector3 pos = spStage_->signVector_[sSignIndex_]->GetCenterPos() + Vector3(0.0f, 0.0f, -50.0f);

	spCamera_->SmoothMoving(20, pos, 3.0f);
}
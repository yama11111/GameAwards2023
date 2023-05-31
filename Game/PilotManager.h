#pragma once
#include "Stage.h"
#include "Camera.h"
#include "Sprite2D.h"
#include "Audio.h"

namespace YInput { class Keys; }

class PilotManager
{

public:

	enum class PilotType
	{
		ePlayer,
		eStage,
		eEnd,
	};

private:

	static PilotType sPilot_;

	static Stage* spStage_;

	static int sSignIndex_;


	static YGame::Camera* spCamera_;
	
	static YMath::Vector3 sInitCameraPos_;
	
	static YMath::Timer sInitZoomTimer_;
	
	static YMath::Ease<float> sInitZoomEase_;

	static bool sIsActInitAnime_;


	static YInput::Keys* spKeys_;

	static YGame::Sprite2D* spPilotPlayerSpr_;
	static std::unique_ptr<YGame::Sprite2D::Object> sPilotPlayerObj_;
	static std::unique_ptr<YGame::CBColor> sPilotPlayerColor_;
	
	static YGame::Sprite2D* spPilotStageSpr_;
	static std::unique_ptr<YGame::Sprite2D::Object> sPilotStageObj_;
	static std::unique_ptr<YGame::CBColor> sPilotStageColor_;
	
	static YMath::Power sChangePlayerPower_;
	static YMath::Power sChangeStagePower_;
	static YMath::Ease<float> sChangeHeight_;
	static YMath::Ease<float> sChangeAlpha_;

	static YGame::Audio* spChangeSE_;

public:

	static void StaticInitialize(YGame::Camera* pCamera, Stage* pStage);
	
	static void StaticSetInitCameraPos(const YMath::Vector3& pos) { sInitCameraPos_ = pos; }
	
	static void StaticReset();

	static void StaticUpdate();
	
	static void StaticDraw();

	
	static void StaticChangePilot(const PilotType& pilot);
	
	static void StaticSetSignIndex(const int signIndex) { sSignIndex_ = signIndex; }
	
	static void StaticSetFollowStage(const int signIndex);
	
	static bool StaticGetIsActInit() { return sIsActInitAnime_; }


	static PilotType StaticGetCurrentPilot() { return sPilot_; }

};


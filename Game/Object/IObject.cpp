#include "IObject.h"
#include <cassert>
#include <imgui.h>

#include "Stage.h"

using YMath::Vector2;
using YMath::Vector3;
using YGame::Box2D;
using YGame::Audio;

Stage* IObject::spStageMan_ = nullptr;
Audio* IObject::spWarpSE_ = nullptr;

void IObject::UpdateLeftTop()
{
	// ����ʒu
	Vector3 ltPos = spStageMan_->GetTopLeftPos(GetSignIndex());
	
	// �����v�Z
	Vector3 difference = ltPos - elderLeftTop_;

	// ���
	transform_->pos_ += difference;

	// �L�^
	elderLeftTop_ = ltPos;
	
	//ImGui::Begin("Object");
	//ImGui::Text("%f, %f, %f", difference.x_, difference.y_, difference.z_);
	//ImGui::End();
}

void IObject::StaticInitialize(Stage* pStageMan)
{
	// null �`�F�b�N
	assert(pStageMan);
	// ���
	spStageMan_ = pStageMan;

	spWarpSE_ = Audio::Load("SE/SE_warp.wav");
}

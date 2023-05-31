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
	// 左上位置
	Vector3 ltPos = spStageMan_->GetTopLeftPos(GetSignIndex());
	
	// 差分計算
	Vector3 difference = ltPos - elderLeftTop_;

	// 代入
	transform_->pos_ += difference;

	// 記録
	elderLeftTop_ = ltPos;
	
	//ImGui::Begin("Object");
	//ImGui::Text("%f, %f, %f", difference.x_, difference.y_, difference.z_);
	//ImGui::End();
}

void IObject::StaticInitialize(Stage* pStageMan)
{
	// null チェック
	assert(pStageMan);
	// 代入
	spStageMan_ = pStageMan;

	spWarpSE_ = Audio::Load("SE/SE_warp.wav");
}

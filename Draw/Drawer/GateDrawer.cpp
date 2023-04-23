#include "GateDrawer.h"
#include "CalcTransform.h"
#include "DrawerConfig.h"
#include <cassert>

#pragma region 名前空間

using std::array;
using std::unique_ptr;

using YGame::Transform;
using YGame::ModelObject;
using YGame::Model;
using YGame::Color;

using YGame::SlimeActor;

using YMath::Vector3;
using YMath::Vector4;

using namespace DrawerConfig::Gate;

#pragma endregion

#pragma region Static

array<Model*, GateDrawerCommon::PartsNum_> GateDrawerCommon::spModels_ =
{
	nullptr, nullptr, nullptr, nullptr,
};

#pragma endregion

// インデックス
static const size_t InsideIdx	 = static_cast<size_t>(GateDrawerCommon::Parts::Inside); // 内枠
static const size_t InLightIdx	 = static_cast<size_t>(GateDrawerCommon::Parts::InsideLight); // 内枠 (光)
static const size_t OutsideIdx	 = static_cast<size_t>(GateDrawerCommon::Parts::Outside); // 外枠
static const size_t OutLightIdx	 = static_cast<size_t>(GateDrawerCommon::Parts::OutsideLight); // 外枠 (光)

void GateDrawerCommon::StaticInitialize()
{
	// ----- モデル読み込み ----- //

	spModels_[InsideIdx]   = Model::Load("gate/inside", true); // 内枠
	spModels_[InLightIdx]  = Model::Load("gate/insideLight", true); // 内枠 (光)
	spModels_[OutsideIdx]  = Model::Load("gate/outside", true); // 外枠
	spModels_[OutLightIdx] = Model::Load("gate/outsideLight", true); // 外枠 (光)
}


void GateDrawer::Initialize(YGame::Transform* pParent)
{
	// 基底クラス初期化
	IDrawer::Initialze(pParent, Mode::Normal, Idle::IntervalTime);

	// 色生成
	color_.reset(Color::Create());

	// オブジェクト生成 + 親行列挿入 (パーツの数)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		// 生成
		modelObjs_[i].reset(ModelObject::Create({}, spVP_, color_.get(), nullptr, spMate_));

		// 親行列挿入
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// リセット
	Reset();
}

void GateDrawer::Reset()
{
	// リセット
	IDrawer::Reset(Mode::Normal);

	// ----- モデル用オブジェクト初期化 ----- //

	core_->Initialize({ {0.0f,0.0f,0.0f}, {0.0f,+PI / 6.0f,0.0f}, {1.0f,1.0f,1.0f} }); // 核

	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->Initialize({ {}, {}, DefScale });
	}

	// 色初期化
	color_->SetRGB(DefColor);
}

void GateDrawer::Update()
{
	// 基底クラス更新 
	IDrawer::Update({});

	// 行列更新 (子)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix();
	}
}

void GateDrawer::Draw()
{
	// モデルの数描画
	for (size_t i = 0; i < spModels_.size(); i++)
	{
		spModels_[i]->Draw(modelObjs_[i].get());
	}
}

void GateDrawer::IdleAnimation()
{
}

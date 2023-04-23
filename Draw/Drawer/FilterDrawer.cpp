#include "FilterDrawer.h"
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

using namespace DrawerConfig::Filter;

#pragma endregion

#pragma region Static

// 静的 モデル配列 初期化
array<Model*, FilterDrawerCommon::PartsNum_> FilterDrawerCommon::spModels_ =
{
	nullptr, nullptr, 
};

#pragma endregion

// インデックス
static const size_t MonitorIdx = static_cast<size_t>(FilterDrawerCommon::Parts::Monitor); // モニター

void FilterDrawerCommon::StaticInitialize()
{
	// ----- モデル読み込み ----- //

	// 体
	spModels_[MonitorIdx] = Model::CreateCube();
	spModels_[1] = Model::CreateCube();
}


void FilterDrawer::Initialize(YGame::Transform* pParent)
{
	// 基底クラス初期化
	IDrawer::Initialze(pParent, Mode::Red, Idle::IntervalTime);

	// 色生成
	color_.reset(Color::Create());

	// オブジェクト生成 + 親行列挿入 (パーツの数)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		// 生成
		modelObjs_[i].reset(ModelObject::Create({}, spVP_, color_.get(), nullptr, nullptr));
		
		// 親行列代入
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// リセット
	Reset();
}

void FilterDrawer::Reset()
{
	// リセット
	IDrawer::Reset(Mode::Red);

	// ----- モデル用オブジェクト初期化 ----- //
	
	// モニター
	modelObjs_[MonitorIdx]->Initialize(
		{
			{0.0f,0.0f,0.0f},
			{},
			{1.0f,1.0f,1.0f},
		}
	);

	// 色初期化
	color_->SetRGBA(DefColor);
}

void FilterDrawer::Update()
{
	// 基底クラス更新 
	IDrawer::Update({});

	// 行列更新 (子)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix();
	}
}

void FilterDrawer::Draw()
{
	// 描画
	spModels_[MonitorIdx]->Draw(modelObjs_[MonitorIdx].get());
}

void FilterDrawer::IdleAnimation()
{
}

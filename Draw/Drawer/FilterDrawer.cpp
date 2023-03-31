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
using namespace DrawerConfig::Filter;

#pragma endregion

#pragma region Static

// インデックス
static const size_t MonitorIdx = static_cast<size_t>(FilterDrawerCommon::Parts::Monitor); // モニター


// 静的 モデル配列 初期化
array<unique_ptr<Model>, FilterDrawerCommon::PartsNum_> FilterDrawerCommon::sModels_ =
{
	nullptr, nullptr, 
};

// 静的ビュープロジェクション
YGame::ViewProjection* FilterDrawerCommon::spVP_ = nullptr;

void FilterDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP)
{
	// nullチェック
	assert(pVP);
	// 代入
	spVP_ = pVP;

	// ----- モデル読み込み ----- //

	// 体
	sModels_[MonitorIdx].reset(Model::Create());
	sModels_[1].reset(Model::Create());
}

#pragma endregion

void FilterDrawer::Initialize(YGame::Transform* pParent)
{
	// 基底クラス初期化
	IDrawer::Initialze(pParent, Mode::Red, Idle::IntervalTime);

	// オブジェクト生成 + 親行列挿入 (パーツの数)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i].reset(ModelObject::Create({}, spVP_, color_.get(), nullptr));
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
			{0.0f,0.0f,-4.0f},
			{},
			{1.0f,1.0f,0.0001f},
		}
	);

	color_->SetRGBA({ 1.0f,0.0f,0.0f,0.25f });

	// フィルターと衝突しているか初期化
	isCollPlayer_ = false;
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


	// フィルター操作 && プレイヤーと衝突していたら
	if (*spIsPlayer_ == false && isCollPlayer_)
	{
		// 色を変える
		color_->SetRGB(BadColor);
	}
	// 違うなら
	else
	{
		// デフォルトの色に
		color_->SetRGB({ 1.0f,0.0f,0.0f });
	}
}

void FilterDrawer::Draw()
{
	// 描画
	sModels_[MonitorIdx]->Draw(modelObjs_[MonitorIdx].get());
}

void FilterDrawer::IdleAnimation()
{
}

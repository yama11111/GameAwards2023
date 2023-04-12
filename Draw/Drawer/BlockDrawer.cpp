#include "BlockDrawer.h"
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
using namespace DrawerConfig::Block;

#pragma endregion

#pragma region Static

// インデックス
static const size_t NormalIdx = static_cast<size_t>(IDrawer::Mode::Normal); // 通常
static const size_t RedIdx = static_cast<size_t>(IDrawer::Mode::Red); // 赤
static const size_t InvisibleIdx = static_cast<size_t>(IDrawer::Mode::Invisivle); // 透明

static const size_t CubeIdx = static_cast<size_t>(BlockDrawerCommon::Parts::Cube); // 体


// 静的 モデル配列 初期化
array<unique_ptr<Model>, BlockDrawerCommon::PartsNum_> BlockDrawerCommon::sModels_ =
{
	nullptr, nullptr,
};

// 静的ビュープロジェクション
YGame::ViewProjection* BlockDrawerCommon::spVP_ = nullptr;

void BlockDrawerCommon::StaticInitialize(YGame::ViewProjection* pVP)
{
	// nullチェック
	assert(pVP);
	// 代入
	spVP_ = pVP;

	// ----- モデル読み込み ----- //

	sModels_[CubeIdx].reset(Model::Create("blockInvisible.png")); // 立方体
	sModels_[1].reset(Model::Create());
}

#pragma endregion

void BlockDrawer::Initialize(YGame::Transform* pParent, const Mode& mode)
{
	// 基底クラス初期化
	IDrawer::Initialze(pParent, mode, Idle::IntervalTime);

	// 色生成
	color_.reset(Color::Create());

	// オブジェクト生成 + 親行列挿入 (パーツの数)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		// 生成
		modelObjs_[i].reset(ModelObject::Create({}, spVP_, color_.get(), nullptr));
		
		// 親行列挿入
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// リセット
	Reset(mode);
}

void BlockDrawer::Reset(const Mode& mode)
{
	// リセット
	IDrawer::Reset(mode);

	// モデル用オブジェクト初期化
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->Initialize({});
	}

	// 色初期化
	color_->Initialize(DefColor::Red);

	// 状態を保存
	save_ = current_;

	// ----- アニメーション ----- //

	// フェードインフラグ
	isFadeIn_ = false;
	// フェードイン用タイマー
	fadeInTim_.Initialize(0);
	// フェードイン用色イージング
	fadeInColorEas_.Initialize(DefColor::Invisible, DefColor::Red, FadeIn::Exponent);
}

void BlockDrawer::ResetAnimation()
{
	// ブヨブヨアニメーション初期化
	SlimeActor::Initialize();

	// 立ちモーションタイマーリセット
	idleTim_.Reset(true);

	// フェードイン用タイマーリセット
	fadeInTim_.Initialize(0);
}

void BlockDrawer::Update()
{
	// 基底クラス更新 
	IDrawer::Update({});

	// フェードイン中なら
	if (isFadeIn_)
	{
		// フェードイン用タイマー更新
		fadeInTim_.Update();
		// フェードイン用の色計算
		Vector4 fadeInColor = fadeInColorEas_.In(fadeInTim_.Ratio());

		// 代入
		color_->SetRGBA(fadeInColor);
	}
	else
	{
		// 状態を戻す
		current_ = save_;
	}


	// 行列更新 (子)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix();
	}
}

void BlockDrawer::Draw()
{
	// 描画
	sModels_[CubeIdx]->Draw(modelObjs_[CubeIdx].get());
}

void BlockDrawer::FadeInAnimation(const unsigned int frame)
{
	// アニメーションリセット
	ResetAnimation();

	// 状態を保存
	save_ = current_;

	// 状態を透明に
	current_ = Mode::Invisivle;

	// フェードインタイマー初期化 + 開始
	fadeInTim_.Initialize(frame);
	fadeInTim_.SetActive(true);

	// フェードインアニメーション開始
	isFadeIn_ = true;
}

void BlockDrawer::IdleAnimation()
{
}

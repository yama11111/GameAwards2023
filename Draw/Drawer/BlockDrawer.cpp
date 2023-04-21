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
array<Model*, BlockDrawerCommon::PartsNum_> BlockDrawerCommon::spModels_ =
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

	spModels_[CubeIdx] = Model::CreateCube("blockInvisible.png"); // 立方体
	spModels_[1] = Model::CreateCube();
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

	// 状態毎に色初期化
	if (mode == Mode::Normal)
	{
		color_->Initialize(DefColor::Normal);
	}
	else if(mode == Mode::Red)
	{
		color_->Initialize(DefColor::Red);
	}

	// ----- アニメーション ----- //

	// 取得可能状態か
	isRetrievable_ = false;

	// 前は取得可能状態だったか
	isElderRetrievable_ = false;

	// 取得可能アニメーション用タイマー
	RetrievableTim_.Initialize(Retrievable::Frame);


	// 置けない状態か
	isCanPlace_ = true;

	// 前は置けない状態だったか
	isElderCanPlace_ = false;

	// 置けない状態用揺れ
	notPlaceShake_.Initialize();
}

void BlockDrawer::Update()
{
	// 置けなかった時用シェイク更新
	notPlaceShake_.Update();

	// 基底クラス更新 
	IDrawer::Update({ notPlaceShake_.Value() });

	// 取得可能アニメーション
	RetrievableAnimation();
	
	// 置けない状態アニメーション
	NotPlaceAnimation();

	// 行列更新 (子)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix();
	}
}

void BlockDrawer::Draw()
{
	// 描画
	spModels_[CubeIdx]->Draw(modelObjs_[CubeIdx].get());
}

void BlockDrawer::PlaceAnimation()
{
	// パーティクル発生
	spParticleMan_->EmitPlaceGridBlock(Place::Frame, core_->parent_, Place::Color);
}

void BlockDrawer::CanNotPlaceAnimation()
{
	// 揺れ開始
	notPlaceShake_.Activate(Place::NotShake::Swing, Place::NotShake::Dekey, Place::NotShake::Place);
}

void BlockDrawer::RetrievableAnimation()
{
	// 取得可能か以前と違うなら
	if (isRetrievable_ != isElderRetrievable_)
	{
		// 取得可能アニメーション用タイマーリセット
		RetrievableTim_.Reset(false);

		// 取得可能なら
		if (isRetrievable_)
		{
			// パーティクル発生
			spParticleMan_->EmitIlluminationGridBlock(Retrievable::Frame, core_->parent_, Retrievable::Color);
		}
	}

	// フラグ保存
	isElderRetrievable_ = isRetrievable_;

	// 取得可能状態じゃないなら弾く
	if (isRetrievable_ == false) { return; }

	// 取得可能ならタイマースタート
	RetrievableTim_.SetActive(isRetrievable_);

	// 取得可能タイマー更新
	RetrievableTim_.Update();

	// 取得可能タイマーが終了したら
	if (RetrievableTim_.IsEnd())
	{
		// パーティクル発生
		spParticleMan_->EmitIlluminationGridBlock(Retrievable::Frame, core_->parent_, Retrievable::Color);

		// タイマー初期化
		RetrievableTim_.Reset(isRetrievable_);
	}
}

void BlockDrawer::NotPlaceAnimation()
{
	// 置けるか以前と違うなら
	if (isCanPlace_ != isElderCanPlace_)
	{
		// 状態毎に色初期化
		if (current_ == Mode::Normal)
		{
			color_->SetRGBA(DefColor::Normal);
		}
		else if (current_ == Mode::Red)
		{
			color_->SetRGBA(DefColor::Red);
		}
	}

	// フラグ保存
	isElderCanPlace_ = isCanPlace_;

	// 置けるなら弾く
	if (isCanPlace_) { return; }

	// 置けない色にする
	color_->SetRGBA(DefColor::Invisible);
}

void BlockDrawer::IdleAnimation()
{
}

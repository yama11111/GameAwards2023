#include "BlockDrawer.h"
#include "CalcTransform.h"
#include "DrawerConfig.h"
#include "CoreColor.h"
#include <cassert>

#pragma region 名前空間

using std::array;
using std::unique_ptr;

using YGame::Transform;
using YGame::Model;
using YGame::CBColor;
using YGame::CBMaterial;

using YGame::SlimeActor;

using YMath::Ease;
using YMath::Power;
using YMath::Vector3;
using YMath::Vector4;

using namespace DrawerConfig::Block;

#pragma endregion

#pragma region Static

array<array<Model*, BlockDrawerCommon::PartsNum_>, IMode::sTypeNum_> BlockDrawerCommon::spModels_ =
{
	nullptr, nullptr,
	nullptr, nullptr,
};
unique_ptr<CBColor> BlockDrawerCommon::sFailShellColor_;

Model* BlockDrawerCommon::spGridModel_ = nullptr;
unique_ptr<CBColor> BlockDrawerCommon::sGridColor_;
unique_ptr<CBColor> BlockDrawerCommon::sFailGridColor_;
unique_ptr<CBMaterial> BlockDrawerCommon::sGridMate_;
Ease<float> BlockDrawerCommon::sCatchGridScaleValueEas_;
Ease<float> BlockDrawerCommon::sFailToCatchGridScaleValueEas_;
Ease<float> BlockDrawerCommon::sPlaceGridScaleValueEas_;
Ease<float> BlockDrawerCommon::sFailToPlaceGridScaleValueEas_;

#pragma endregion

#pragma region インデックス

static const size_t CoreIdx = static_cast<size_t>(BlockDrawerCommon::Parts::Core); // 核
static const size_t ShellIdx = static_cast<size_t>(BlockDrawerCommon::Parts::Shell); // 殻

#pragma endregion

#pragma region Common

void BlockDrawerCommon::StaticInitialize()
{
	// ----- モデル読み込み ----- //

	// ブロック (通常)
	spModels_[IMode::sNormalIdx][CoreIdx] = Model::LoadObj("block/normal/core", true); // 核
	spModels_[IMode::sNormalIdx][ShellIdx] = Model::LoadObj("block/normal/shell", true); // 殻

	// ブロック (可動)
	spModels_[IMode::sMovableIdx][CoreIdx] = Model::LoadObj("block/red/core", true); // 核
	spModels_[IMode::sMovableIdx][ShellIdx] = Model::LoadObj("block/red/shell", true); // 殻

	// グリッド
	spGridModel_ = Model::LoadObj("grid", true);

	// ---------- ブロック ---------- //

	// 殻失敗色
	sFailShellColor_.reset(CBColor::Create());
	sFailShellColor_->SetRGBA(ShellColor::Failure);
	sFailShellColor_->SetTexColorRateRGBA(ShellColor::OriginalRate);

	// --------- グリッド --------- //

	// 色
	sGridColor_.reset(CBColor::Create());
	sGridColor_->SetRGBA(GridColor::Success);

	// 失敗色
	sFailGridColor_.reset(CBColor::Create());
	sFailGridColor_->SetRGBA(GridColor::Failure);

	// マテリアル
	sGridMate_.reset(CBMaterial::Create());


	// 取得時大きさイージング
	sCatchGridScaleValueEas_.Initialize(Catch::Success::Start, Catch::Success::End, Catch::Success::Exponent);

	// 取得失敗時大きさイージング
	sFailToCatchGridScaleValueEas_.Initialize(Catch::Failure::Start, Catch::Failure::End, Catch::Failure::Exponent);

	// 設置時大きさイージング
	sPlaceGridScaleValueEas_.Initialize(Place::Success::Start, Place::Success::End, Place::Success::Exponent);

	// 設置失敗時大きさイージング
	sFailToPlaceGridScaleValueEas_.Initialize(Place::Failure::Start, Place::Failure::End, Place::Failure::Exponent);
}

#pragma endregion

#pragma region Drawer

void BlockDrawer::Initialize(Transform* pParent, const IMode::Type& modeType)
{
	// 基底クラス初期化
	IDrawer::Initialze(pParent, Idle::IntervalTime);

	// オブジェクト生成 + 親行列挿入 (パーツの数)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		// 生成
		modelObjs_[i].reset(Model::Object::Create({}, spVP_, nullptr, nullptr, nullptr, nullptr));

		// 親行列挿入
		modelObjs_[i]->parent_ = &core_->m_;
	}

	// グリッド生成
	gridObj_.reset(Model::Object::Create({}, spVP_, sGridColor_.get(), nullptr, sGridMate_.get(), nullptr));

	// 親行列挿入
	gridObj_->parent_ = &core_->m_;

	// リセット
	Reset(modeType);
}

void BlockDrawer::Reset(const IMode::Type& modeType)
{
	// リセット
	IDrawer::Reset();

	// 基底モード初期化
	IMode::ChangeType(modeType);

	// モデル用オブジェクト初期化
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->Initialize({});
	}

	// 核の色とマテリアル設定
	modelObjs_[CoreIdx]->SetColor(CoreColor::ColorPtr(CurrentTypeIndex()));

	// グリッド
	gridObj_->Initialize({ {}, {}, {1.1f,1.1f,1.1f} });

	// ----- アニメーション ----- //

	// 失敗用揺れ
	failureShake_.Initialize();


	// グリッド動作フラグ
	isActGrid_ = false;


	// 取得可能状態か
	isCanCatch_ = false;

	// 前は取得可能状態だったか
	isElderCanCatch_ = false;


	// 取得アニメーションをするか
	isActCatchAnimition_ = false;

	// 取得時イージング用タイマー
	catchGridTim_.Initialize(Catch::Success::Frame);

	// 取得失敗アニメーションをするか
	isActFailToCatchAnimition_ = false;

	// 取得時イージング用タイマー
	failToCatchGridTim_.Initialize(Catch::Failure::Frame);


	// 置けない状態か
	isCanPlace_ = true;

	// 前は置けない状態だったか
	isElderCanPlace_ = false;


	// 設置アニメーションをするか
	isActPlaceAnimition_ = false;

	// 設置時イージング用タイマー
	placeGridTim_.Initialize(Place::Success::Frame);
	// 設置失敗アニメーションをするか
	isActFailToPlaceAnimition_ = false;

	// 設置時イージング用タイマー
	failToPlaceGridTim_.Initialize(Place::Failure::Frame);

}

void BlockDrawer::Update()
{
	// 失敗用シェイク更新
	failureShake_.Update();

	// 基底クラス更新 
	IDrawer::Update({ failureShake_.Value() });


	// 取得可能アニメーション
	CanCatchAnimation();

	// 置けない状態アニメーション
	NotPlaceAnimation();


	// 行列更新 (子)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix();
	}


	// グリッド動作フラグがfalseなら弾く
	if (isActGrid_ == false) { return; }

	// 大きさ
	float gridSca = 0.0f;

	// 取得アニメーションをするなら
	if (isActCatchAnimition_)
	{
		// タイマー更新
		catchGridTim_.Update();

		// イーズアウト
		gridSca += sCatchGridScaleValueEas_.Out(catchGridTim_.Ratio());

		// タイマー終了時
		if (catchGridTim_.IsEnd())
		{
			// タイマーリセット + 終了
			catchGridTim_.Reset(false);

			// 取得アニメーション終了
			isActCatchAnimition_ = false;
		}
	}
	// 取得失敗アニメーションをするなら
	if (isActFailToCatchAnimition_)
	{
		// タイマー更新
		failToCatchGridTim_.Update();

		// イーズアウト
		gridSca += sFailToCatchGridScaleValueEas_.Out(failToCatchGridTim_.Ratio());

		// タイマー終了時
		if (failToCatchGridTim_.IsEnd())
		{
			// タイマーリセット + 終了
			failToCatchGridTim_.Reset(false);

			// 取得失敗アニメーション終了
			isActFailToCatchAnimition_ = false;
		}
	}
	// 設置アニメーションをするなら
	if (isActPlaceAnimition_)
	{
		// タイマー更新
		placeGridTim_.Update();

		// イーズアウト
		gridSca += sPlaceGridScaleValueEas_.Out(placeGridTim_.Ratio());

		// タイマー終了時
		if (placeGridTim_.IsEnd())
		{
			// タイマーリセット + 終了
			placeGridTim_.Reset(false);

			// 設置アニメーション終了
			isActPlaceAnimition_ = false;
		}
	}
	// 設置失敗アニメーションをするなら
	if (isActFailToPlaceAnimition_)
	{
		// タイマー更新
		failToPlaceGridTim_.Update();

		// イーズアウト
		gridSca += sFailToPlaceGridScaleValueEas_.Out(failToPlaceGridTim_.Ratio());

		// タイマー終了時
		if (failToPlaceGridTim_.IsEnd())
		{
			// タイマーリセット + 終了
			failToPlaceGridTim_.Reset(false);

			// 設置失敗アニメーション終了
			isActFailToPlaceAnimition_ = false;
		}
	}

	// グリッド更新
	gridObj_->UpdateMatrix({ {},{},Vector3(gridSca, gridSca, gridSca) });

	// フラグを更新 (全てfalseなら止める)
	isActGrid_ =
		isActCatchAnimition_ ||
		isActFailToCatchAnimition_ ||
		isActPlaceAnimition_ ||
		isActFailToPlaceAnimition_;

	// フラグがfalseなら
	if (isActGrid_ == false)
	{
		// 殻の色を初期化
		modelObjs_[ShellIdx]->SetColor(nullptr);
	}
}

void BlockDrawer::Draw()
{
	// モデルの数描画
	for (size_t i = 0; i < spModels_.size(); i++)
	{
		spModels_[CurrentTypeIndex()][i]->SetDrawCommand(modelObjs_[i].get(), YGame::DrawLocation::Center);
	}

	// グリッド動作フラグがfalseなら弾く
	if (isActGrid_ == false) { return; }

	// グリッド描画
	spGridModel_->SetDrawCommand(gridObj_.get(), YGame::DrawLocation::Center);
}

void BlockDrawer::CatchAnimation()
{
	// グリッド動作
	isActGrid_ = true;

	// 取得アニメーション開始
	isActCatchAnimition_ = true;

	// タイマーリセット + 開始
	catchGridTim_.Reset(true);

	// グリッド色設定
	gridObj_->SetColor(sGridColor_.get());
}
void BlockDrawer::FailToCatchAnimation()
{
	// グリッド動作
	isActGrid_ = true;

	// 取得失敗アニメーション開始
	isActFailToCatchAnimition_ = true;

	// タイマーリセット + 開始
	failToCatchGridTim_.Reset(true);

	// 揺れ開始
	failureShake_.Activate(Catch::Failure::Shake::Swing, Catch::Failure::Shake::Dekey, Catch::Failure::Shake::Place);

	// グリッド色設定
	gridObj_->SetColor(sFailGridColor_.get());

	// 殻の色設定
	modelObjs_[ShellIdx]->SetColor(sFailShellColor_.get());
}

void BlockDrawer::PlaceAnimation()
{
	// グリッド動作
	isActGrid_ = true;

	// 取得アニメーション開始
	isActPlaceAnimition_ = true;

	// タイマーリセット + 開始
	placeGridTim_.Reset(true);

	// グリッド色設定
	gridObj_->SetColor(sGridColor_.get());
}
void BlockDrawer::FailToPlaceAnimation()
{
	// グリッド動作
	isActGrid_ = true;

	// 取得失敗アニメーション開始
	isActFailToPlaceAnimition_ = true;

	// タイマーリセット + 開始
	failToPlaceGridTim_.Reset(true);

	// 揺れ開始
	failureShake_.Activate(Place::Failure::Shake::Swing, Place::Failure::Shake::Dekey, Place::Failure::Shake::Place);

	// グリッド色設定
	gridObj_->SetColor(sFailGridColor_.get());

	// 殻の色設定
	modelObjs_[ShellIdx]->SetColor(sFailShellColor_.get());
}

void BlockDrawer::CanCatchAnimation()
{
	//// 取得可能か以前と違うなら
	//if (isCanCatch_ != isElderCanCatch_)
	//{
	//	// 取得可能アニメーション用タイマーリセット
	//	RetrievableTim_.Reset(false);

	//	// 取得可能なら
	//	if (isCanCatch_)
	//	{
	//		// パーティクル発生
	//		spParticleMan_->EmitIlluminationGridBlock(Retrievable::Frame, core_->parent_, Retrievable::Color);
	//	}
	//}

	//// フラグ保存
	//isElderCanCatch_ = isCanCatch_;

	//// 取得可能状態じゃないなら弾く
	//if (isCanCatch_ == false) { return; }

	//// 取得可能ならタイマースタート
	//RetrievableTim_.SetActive(isCanCatch_);

	//// 取得可能タイマー更新
	//RetrievableTim_.Update();

	//// 取得可能タイマーが終了したら
	//if (RetrievableTim_.IsEnd())
	//{
	//	// パーティクル発生
	//	spParticleMan_->EmitIlluminationGridBlock(Retrievable::Frame, core_->parent_, Retrievable::Color);

	//	// タイマー初期化
	//	RetrievableTim_.Reset(isCanCatch_);
	//}
}

void BlockDrawer::NotPlaceAnimation()
{
	//// 置けるか以前と違うなら
	//if (isCanPlace_ != isElderCanPlace_)
	//{
	//	// 状態毎に色初期化
	//	if (current_ == Mode::Normal)
	//	{
	//		color_->SetRGBA(DefColor::Normal);
	//	}
	//	else if (current_ == Mode::Red)
	//	{
	//		color_->SetRGBA(DefColor::Red);
	//	}
	//}

	//// フラグ保存
	//isElderCanPlace_ = isCanPlace_;

	//// 置けるなら弾く
	//if (isCanPlace_) { return; }

	//// 置けない色にする
	//color_->SetRGBA(DefColor::Invisible);
}

void BlockDrawer::IdleAnimation()
{
}

#pragma endregion